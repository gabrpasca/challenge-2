#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <map>
#include <array>
#include <complex>
#include <iostream>
#include <fstream>
#include <sstream>

namespace algebra {

    enum class StorageOrder { 
    RowMajor,
    ColumnMajor
    };

    template<typename T, StorageOrder Order = StorageOrder::RowMajor>
    class Matrix {

         private:
        std::size_t rows;
        std::size_t cols;
        std::map<std::array<std::size_t, 2>, T> data; // Map to store matrix elements
        std::vector<T> Values; // Values of non-zero elements in compressed format
        std::vector<std::size_t> innerIndices; // Inner indices for compressed format
        std::vector<std::size_t> outerIndices; // Outer indices for compressed format
        bool compressed;

    public:
        Matrix(std::size_t rows = 0, std::size_t cols = 0) : rows(rows), cols(cols), compressed(false) {}
        
        bool isCompressed() const;

        bool isValidIndex(std::size_t row, std::size_t col) const;

        void compress();

        void decompress();

        void resize(std::size_t newRows, std::size_t newCols);

         // Method to access elements of the matrix
        T operator()(std::size_t row, std::size_t col) const;

        // Non-const version of the call operator to access and change an element
        T& operator()(std::size_t row, std::size_t col);

        // Function to retrieve a whole row or column
        std::map<std::size_t, T> getRow(std::size_t row) const;

        std::map<std::size_t, T> getColumn(std::size_t col) const;

        std::vector<T> operator*(const std::vector<T>& v) const;
        
        // Function to print the matrix
        void printMatrix() const;
    
   

       
    };
     template <typename T, StorageOrder Order>
    Matrix<T, Order> readMatrixMarket(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line[0] == '%') continue;  // Skip comments
        break;
    }

    std::istringstream iss(line);
    size_t rows, cols, entries;
    iss >> rows >> cols >> entries;

    Matrix<T, Order> matrix(rows, cols);
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        size_t row, col;
        T value;
        iss >> row >> col >> value;
        matrix(row - 1, col - 1) = value;  // Matrix Market format is 1-based
    }

    return matrix;
}
}

#endif // MATRIX_H