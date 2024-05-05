#include "matrix.hpp"
#include "matriximpl.hpp"
#include <iostream>
#include <fstream>
#include <vector>

int main() {
    // Define the type for the matrix elements
    using ElementType = double;
    
    using namespace algebra;
    //using namespace std::chrono;

    //read the matrix
    Matrix<double, StorageOrder::RowMajor> matrix = readMatrixMarket<double, StorageOrder::RowMajor> ("lnsp_131.mtx");
  


    std::vector<ElementType> vector(131, 1.0) ;// Example vector
    
    // Perform matrix-vector multiplication
    std::vector<ElementType> result = matrix * vector;
   
    // Print the result
    std::cout << "Result of matrix-vector multiplication:" << std::endl;
    for (const auto& elem : result) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;


    return 0;
}