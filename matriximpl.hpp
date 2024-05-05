//

#ifndef MATRIXIMPL_H
#define MATRIXIMPL_H
#include "matrix.hpp"
namespace algebra {


    // Helper function to check if a given index is within bounds
    template<typename T, StorageOrder Order>
    bool Matrix<T, Order>::isValidIndex(std::size_t row, std::size_t col) const {
        return row < rows && col < cols;
    }

    
    
    template<typename T, StorageOrder Order>
    void Matrix<T,Order>::compress(){
        if(compressed)
        return;
    innerIndices.clear();
    outerIndices.clear();
    Values.clear();
    innerIndices.push_back(0);
    for(size_t i=0; i<rows; ++i){
        for(size_t j=0;j<cols; ++j){
            auto it = data.find((Order == StorageOrder::RowMajor) ? std::array<std::size_t, 2>{i, j} : std::array<std::size_t, 2>{j, i});
            if(it!=data.end()){
                outerIndices.push_back(j);
                Values.push_back(it->second);
            }
        }
        innerIndices.push_back(Values.size());
    }
    data.clear();
    compressed=true;
}

// Method to decompress the matrix
    template<typename T, StorageOrder Order>
    void Matrix<T, Order>::decompress() {
        if (!compressed) {
            return; // Already uncompressed
        }
        // Convert compressed format back to the map representation
        for (std::size_t i = 0; i < rows; ++i) {
            for (std::size_t j = innerIndices[i]; j < innerIndices[i + 1]; ++j) {
                if (Order == StorageOrder::RowMajor)
                data[{i, outerIndices[j]}] = Values[j];
                else
                data[{outerIndices[j], i}] = Values[j];
            }
        }
        Values.clear(); // Clear vectors
        innerIndices.clear();
        outerIndices.clear();
        compressed = false;
    }
    
//method to check if the matrix is compressed
template<typename T, StorageOrder Order>
bool Matrix<T, Order>::isCompressed() const {
    return compressed;
}



  // Method to resize the matrix
    template<typename T, StorageOrder Order>
    void Matrix<T, Order>::resize(std::size_t newRows, std::size_t newCols) {
        rows = newRows;
        cols = newCols;
        decompress();
    }

    // Method to access elements of the matrix (const call operator)
    template<typename T, StorageOrder Order>
    T Matrix<T, Order>::operator()(std::size_t row, std::size_t col) const {
        if (!isValidIndex(row, col)) {
            std::cerr << "Error: Index out of range\n";
            return T(); // Return default value if index is out of range
        }
        if (compressed) {
            std::cerr << "Error: Cannot access elements in compressed state\n";
            return T(); // Return default value if matrix is compressed
        } else {
            auto it = data.find((Order == StorageOrder::RowMajor) ? std::array<std::size_t, 2>{row, col} : std::array<std::size_t, 2>{col, row});
            if (it != data.end()) {
                return it->second; // Return value if found
            } else {
                std::cerr << "Error: Element not found\n";
                return T(); // Return default value if element is not found
            }
        }
    }

    // Non-const version of the call operator to access and change an element
    template<typename T, StorageOrder Order>
    T &Matrix<T, Order>::operator()(std::size_t row, std::size_t col) {
        if (!isValidIndex(row, col)) {
            std::cerr << "Error: Index out of range\n";
            // Return a reference to a default value
            static T default_value;
            return default_value;
        } else {
            if (compressed) {
                // In compressed mode, can only change existing non-zero elements
                auto it = data.find((Order == StorageOrder::RowMajor) ? std::array<std::size_t, 2>{row, col} : std::array<std::size_t, 2>{col, row});
                if (it == data.end()) {
                    std::cerr << "Error: Cannot add new elements in compressed state\n";
                    // Return a reference to a default value
                    static T default_value;
                    return default_value;
                } else {
                    return it->second;
                }
            } else {
                // In uncompressed mode, allow modification of existing elements and addition of new elements
                return data[(Order == StorageOrder::RowMajor) ? std::array<std::size_t, 2>{row, col} : std::array<std::size_t, 2>{col, row}];
            }
        }
    }

    // Method to perform matrix-vector multiplication
  template<typename T, StorageOrder Order>
std::vector<T> Matrix<T, Order>::operator*(const std::vector<T> &v) const {
    if (!compressed) {
        if (Order == StorageOrder::RowMajor) {
            if (cols != v.size()) {
                std::cerr << "Error: Vector size does not match matrix dimensions\n";
                return std::vector<T>();
            }
            std::vector<T> result(rows, 0);
            for (const auto &it : data) {
                result[it.first[0]] += it.second * v[it.first[1]];
            }
            return result;
        } else { // ColumnMajor
            if (rows != v.size()) {
                std::cerr << "Error: Vector size does not match matrix dimensions\n";
                return std::vector<T>();
            }
            std::vector<T> result(cols, 0);
            for (const auto &it : data) {
                result[it.first[1]] += it.second * v[it.first[0]];
            }
            return result;
        }
    } else {
        if (Order == StorageOrder::RowMajor) {
            std::vector<T> result(rows, 0);
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = innerIndices[i]; j < innerIndices[i + 1]; ++j) {
                    result[i] += Values[j] * v[outerIndices[j]];
                }
            }
            return result;
        } else {
            std::vector<T> result(rows, 0);
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = innerIndices[i]; j < innerIndices[i + 1]; ++j) {
                    result[j] += Values[i] * v[outerIndices[i]];
                }
            }
            return result;
        }
    }
    // Return a default value in case no other return statement is executed
    return std::vector<T>();
}
           // }
            //else{
             //   std::vector <T> result(rows, 0);
            //for(size_t i=0; i<rows; ++i){
              //  for(size_t j=innerIndices[i]; j<innerIndices[i+1];++j){
                //    result[j]=Values[i]*v[outerIndices[i]];
                //}
            //}
            //}
            //}
  
    // Explicit template instantiation for std::complex<T>
    template class Matrix<std::complex<float>>;
    template class Matrix<std::complex<double>>;

} // namespace algebra

#endif 
