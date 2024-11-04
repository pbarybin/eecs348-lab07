// Name: Peter Barybin
// KUID: 3057437
// LAB Session: Thursday 4 p.m.
// LAB Assignment: 07
// Description: Program that uses operator overloading and class methods to carry out operations on matrices.

#include <iostream>
#include <fstream>

using namespace std;

const int SIZE = 4; // Global variable for matrix size

class Matrix {
private:
    int data[SIZE][SIZE]; // 2D array for matrix data (using int for simplicity)
public:
    // 1. Read values from stdin into a matrix
    void readFromStdin() {
        // open .txt file with input (static so that it will pick up from same place for second matrix)
        static ifstream input_file("matrix-data.txt");
        //error if file does not open
        if (!input_file.is_open()) {
            cerr << "Error: Could not open file.";
        }
        //fill matrix with values from .txt file
        else {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    int value;
                    input_file >> value;
                    data[i][j] = value;
                }
            }
        }
    }

    // 2. Display a matrix
    void display() const {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                cout << data[i][j] << " ";
            }
            cout << "\n";
        }
    }

    // 3. Add two matrices (operator overloading for +)
    Matrix operator+(const Matrix& other) const {
        Matrix sum;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                sum.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return sum;
    }

    // 4. Multiply two matrices (operator overloading for *)
    Matrix operator*(const Matrix& other) const {
        Matrix product;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < SIZE; k++) {
                    int value;
                    value = data[i][k] * other.data[k][j];
                    if (k == 0) {
                        product.data[i][j] = value;
                    }
                    else {
                        product.data[i][j] += value;
                    }
                }
            }
        }
        return product;
    }

    // 5. Compute the sum of matrix diagonal elements
    int sumOfDiagonals() const {
        int sum = 0;
        for (int i = 0; i < SIZE; i++) {
            sum += data[i][i] + data[SIZE-1-i][i];
        }
        //delete double counted middle element if SIZE is odd
        if (SIZE % 2 != 0) {
            sum -= data[SIZE/2][SIZE/2];
        }
        return sum;
    }

    // 6. Swap matrix rows
    void swapRows(int row1, int row2) {
        for (int i = 0; i < SIZE; i++) {
            int temp = data[row1][i];
            data[row1][i] = data[row2][i];
            data[row2][i] = temp;
        }
    }
};

int main() {
    // Example usage:
    Matrix mat1;
    cout << "Enter values for Matrix 1:" << endl;
    mat1.readFromStdin();
    cout << "Matrix 1:" << endl;
    mat1.display();

    Matrix mat2;
    cout << "Enter values for Matrix 2:" << endl;
    mat2.readFromStdin();
    cout << "Matrix 2:" << endl;
    mat2.display();

    Matrix sum = mat1 + mat2;
    cout << "Sum of matrices:" << endl;
    sum.display();

    Matrix product = mat1 * mat2;
    cout << "Product of matrices:" << endl;
    product.display();

    cout << "Sum of diagonals of Matrix 1: " << mat1.sumOfDiagonals() << endl;

    mat1.swapRows(0, 2);
    cout << "Matrix 1 after swapping rows:" << endl;
    mat1.display();

    return 0;
}
