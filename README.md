-Installation
Clone the repository:
git clone https://github.com/yourusername/matrix-multiplication.git

Navigate to the project directory:
cd matrix-multiplication

Compile the program using make:
make


-Usage
Run the compiled program with the following command:
./pacs24
This will read the matrix data from the file lnsp_131.mtx, perform matrix-vector multiplication, and print the result to the console.

-Customization
You can customize the program by:
Changing the matrix file: Replace lnsp_131.mtx with your own MatrixMarket file containing a matrix.
Modifying the matrix implementation: The matrix implementation is provided in matrix.hpp and matriximpl.hpp. Below are the functions available:
isValidIndex(row, col): Helper function to check if a given index is within the bounds of the matrix.
compress(): Method to compress the matrix representation for efficient storage and computation.
decompress(): Method to decompress the matrix representation back to its original format.
isCompressed(): Method to check if the matrix is currently in compressed format.
resize(newRows, newCols): Method to resize the matrix to the specified dimensions.
operator()(row, col): Method to access elements of the matrix using the const call operator.
operator()(row, col): Non-const version of the call operator to access and change an element of the matrix.
operator*(vector): Method to perform matrix-vector multiplication.
