// 'matrix_operations.c' zawiera matematyczne funkcje operacji na macierzach

// Dyrektywy preprocesora
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "csv_operations.h"

// Funkcja dodawania macierzy
Matrix addition(Matrix matrixA, Matrix matrixB) {
    // Sprawdzenie poprawnosci wymiarow macierzy; jesli blad - zwrocenie macierzy bledow
    if (matrixA.rows != matrixB.rows || matrixA.columns != matrixB.columns) {
        printf("--error--\n--matrices must be the same size--\n");
        Matrix matrix_error = { 0, 0, NULL };
        return matrix_error;
    }
    // Alokacja pamieci dla macierzy wynikowej
    Matrix matrixR = allocate_memory_for_matrix(matrixA.rows, matrixA.columns);
    // Dodawanie macierzy
    for (int i = 0; i < matrixR.rows; i++) {
        for (int j = 0; j < matrixR.columns; j++) {
            matrixR.values[i][j] = matrixA.values[i][j] + matrixB.values[i][j];
        }
    }
    return matrixR;
}

// Funkcja odejmowania macierzy
Matrix subtraction(Matrix matrixA, Matrix matrixB) {
    // Sprawdzenie poprawnosci wymiarow macierzy; jesli blad - zwrocenie macierzy bledow
    if (matrixA.rows != matrixB.rows || matrixA.columns != matrixB.columns) {
        printf("--error--\n--matrices must be the same size--\n");
        Matrix matrix_error = { 0, 0, NULL };
        return matrix_error;
    }
    // Alokacja pamieci dla macierzy wynikowej
    Matrix matrixR = allocate_memory_for_matrix(matrixA.rows, matrixA.columns);
    // Odejmowanie macierzy
    for (int i = 0; i < matrixR.rows; i++) {
        for (int j = 0; j < matrixR.columns; j++) {
            matrixR.values[i][j] = matrixA.values[i][j] - matrixB.values[i][j];
        }
    }
    return matrixR;
}

// Funkcja mnozenia macierzy przez skalar
Matrix multiplication_by_scalar(Matrix matrixA, float scalar) {
    // Alokacja pmieci dla macierzy wynikowej
    Matrix matrixR = allocate_memory_for_matrix(matrixA.rows, matrixA.columns);
    // Mnozenie macierzy przez skalar
    for (int i = 0; i < matrixR.rows; i++) {
        for (int j = 0; j < matrixR.columns; j++) {
            matrixR.values[i][j] = matrixA.values[i][j] * scalar;
        }
    }
    return matrixR;
}

// Funkcja mnozenia macierzy
Matrix multiplication(Matrix matrixA, Matrix matrixB) {
    // Sprawdzenie poprawnosci wymiarow macierzy; jesli blad - zwrocenie macierzy bledow
    if (matrixA.columns != matrixB.rows) {
        printf("--error--\n--the number of columns in first matrix and rows in second must be the same--\n");
        Matrix matrix_error = { 0, 0, NULL };
        return matrix_error;
    }
    // Alokacja pmieci dla macierzy wynikowej
    Matrix matrixR = allocate_memory_for_matrix(matrixA.rows, matrixB.columns);
    // Mnozenie macierzy
    for (int i = 0; i < matrixA.rows; i++) {
        for (int j = 0; j < matrixB.columns; j++) {
            matrixR.values[i][j] = 0;
            for (int k = 0; k < matrixA.columns; k++) {
                matrixR.values[i][j] += matrixA.values[i][k] * matrixB.values[k][j];
            }
        }
    }
    return matrixR;
}

// Funkcja transpozycji macierzy
Matrix transposition(Matrix matrixA) {
    // Alokacja pamieci dla macierzy wynikowej
    Matrix matrixR = allocate_memory_for_matrix(matrixA.columns, matrixA.rows);
    // Transpozycja macierzy
    for (int i = 0; i < matrixA.rows; i++) {
        for (int j = 0; j < matrixA.columns; j++) {
            matrixR.values[j][i] = matrixA.values[i][j];
        }
    }
    return matrixR;
}

// Funkcja rozkladu LU (tylko dla macierzy kwadratowych)
Matrices LU_decomposition(Matrix matrixA) {
    // Sprawdzenie czy macierz jest kwadratowa; jesli nie, zwraca blad
    if (matrixA.rows != matrixA.columns) {
        printf("--error--\n--the matrix must be square--\n");
        Matrix matrix_error1 = { 0, 0, NULL };
        Matrix matrix_error2 = { 0, 0, NULL };
        Matrices matrix_error = { matrix_error1, matrix_error2 };
        return matrix_error; // Zwrocenie macierzy z bledem
    }
    // Rozmiar macierzy
    int n = matrixA.rows;
    // Alokacja pamieci dla macierzy L i U
    Matrix L = allocate_memory_for_matrix(n, n);
    Matrix U = allocate_memory_for_matrix(n, n);
    // Wyzerowanie obu macierzy
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            L.values[i][j] = 0;
            U.values[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        // Ustawienie 1 na przekatnej macierzy L
        L.values[i][i] = 1; 
        // Obliczanie wartosci macierzy gornotrojkatnej U
        for (int j = i; j < n; j++) {
            U.values[i][j] = matrixA.values[i][j];
            for (int k = 0; k < i; k++) {
                U.values[i][j] -= L.values[i][k] * U.values[k][j];
            }
        }
        // Obliczanie wartosci dolnotrojkatnej L
        for (int j = i + 1; j < n; j++) {
            L.values[j][i] = matrixA.values[j][i];
            for (int k = 0; k < i; k++) {
                L.values[j][i] -= L.values[j][k] * U.values[k][i];
            }
            L.values[j][i] /= U.values[i][i];
        }
    }
    // Utworzenie struktury wynikowej i jej zwrot
    Matrices R = { L, U };
    return R;
}

// Funkcja obliczania wyznacznika macierzy
float determinant_with_LU(Matrix matrixA) {
    // Wykorzystanie funkcji rozkladu LU
    Matrices R = LU_decomposition(matrixA);
    if (R.matrix1.values != NULL && R.matrix2.values != NULL) {
        // Obliczenie wyznacznika macierzy (iloczyn przekatnej macierzy U)
        float det = 1;
        for (int i = 0; i < R.matrix2.rows; i++) {
            det *= R.matrix2.values[i][i];
        }
        return det;
    }
    else return NAN;
}
// Funkcja obliczania sladu macierzy
float trace(Matrix matrixA) {
    // Sprawdzenie czy macierz jest kwadratowa; jesli nie, zwraca blad
    if (matrixA.rows != matrixA.columns) {
        printf("--error--\n--the matrix must be square--\n");
        return NAN;
    }
    float trace = 0;
    for (int i = 0; i < matrixA.rows; i++) {
        trace += matrixA.values[i][i];
    }
    return trace;
}

// Funkcja do tworzenia minorow (macierz po usuniêciu jednego wiersza i jednej kolumny)
Matrix create_minor(Matrix matrix, int row, int col) {
    // Alokacja pamieci dla minora
    Matrix minor = allocate_memory_for_matrix(matrix.rows - 1, matrix.columns - 1);
    int minor_row = 0, minor_col;
    // Petle do kopiowana odpowiednich elementow macierzy wejsciowej do minora
    for (int i = 0; i < matrix.rows; i++) {
        if (i == row) continue;  // Pominiecie wierszu, ktory chcemy usunac
        minor_col = 0;
        for (int j = 0; j < matrix.columns; j++) {
            if (j == col) continue; //Pominiecie kolumny, ktora chcemy usunac
            minor.values[minor_row][minor_col] = matrix.values[i][j];
            minor_col++;
        }
        minor_row++;
    }
    return minor;
}

// Funkcja do obliczania macierzy dopelnien
Matrix cofactor_matrix(Matrix matrix) {
    // Sprawdzenie czy macierz jest kwadratowa
    if (matrix.rows != matrix.columns) {
        printf("--error--\n--the matrix must be square--\n");
        Matrix matrix_error = { 0, 0, NULL };
        return matrix_error; // Zwrocenie macierzy z bledem
    }
    //Alokacja pamieci dla macierzy dopelnien
    Matrix cofactor = allocate_memory_for_matrix(matrix.rows, matrix.columns);
    // Obliczanie kazdego elementu macierzy dopelnien
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.columns; j++) {
            // Tworzenie minorow
            Matrix minor = create_minor(matrix, i, j);
            //Obliczanie elementu macierzy
            cofactor.values[i][j] = pow(-1, i + j) * determinant_with_LU(minor);
            free_memory_for_matrix(minor);
        }
    }
    return cofactor;
}

// Funkcja do obliczania macierzy odwrotnej
Matrix inverse_matrix(Matrix matrix) {
   //Obliczenie wyznacznika macierzy
    float det = determinant_with_LU(matrix);
    //Sprawdzenie czy macierz jest odwracalna, jesli nie zwrocenie macierzy bledow
    if (isnan(det) == 1) {
        return (Matrix) { 0, 0, NULL };
    }
    // Macierz dopelnien i macierz dopelnien po transpozycji
    Matrix cofactor = cofactor_matrix(matrix);
    Matrix adjugate = transposition(cofactor);
    free_memory_for_matrix(cofactor);
    // Alokacja pamieci dla macierzy odwrotnej
    Matrix inverse = allocate_memory_for_matrix(matrix.rows, matrix.columns);
    // Obliczanie elementow macierzy odwrotnej
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.columns; j++) {
            inverse.values[i][j] = adjugate.values[i][j] / det;
        }
    }
    free_memory_for_matrix(adjugate);
    return inverse;
}
