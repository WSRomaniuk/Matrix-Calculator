#pragma once

// Deklaracje funkcji
Matrix addition(Matrix matrixA, Matrix matrixB);
Matrix subtraction(Matrix matrixA, Matrix matrixB);
Matrix multiplication_by_scalar(Matrix matrixA, float scalar);
Matrix multiplication(Matrix matrixA, Matrix matrixB);
Matrix transposition(Matrix matrixA);
Matrices LU_decomposition(Matrix matrixA);
float determinant_with_LU(Matrix matrixA);
float trace(Matrix matrixA);
Matrix cofactor_matrix(Matrix matrix);
Matrix inverse_matrix(Matrix matrix);