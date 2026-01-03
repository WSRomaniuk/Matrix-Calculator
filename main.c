// Program do operacji macierzowych i wektorowych
// Odczytujacy i zapisujacy macierze do plikow CSV

// Dyrektywy preprocesora
#include <stdio.h>
#include <math.h>
#include "csv_operations.h"
#include "matrix_operations.h"

// Deklaracje funkcji
void addiction_menu();
void subtraction_menu();
void multiplication_by_scalar_menu();
void multiplication_menu();
void transposition_menu();
void LU_decomposition_menu();
void determinant_with_LU_menu();
void trace_menu();
void cofator_matrix_menu();
void inverse_matrix_menu();

// Funkcja main zawierajaca menu programu
int main() {
    int choice;
    printf("Choose a matrix operation:\n");
    printf("1 - Addition\n");
    printf("2 - Subtraction\n");
    printf("3 - Multiplication by scalar\n");
    printf("4 - Multiplication\n");
    printf("5 - Transposition\n");
    printf("6 - LU decomposition (square matrix)\n");
    printf("7 - Determinant\n");
    printf("8 - Trace\n");
    printf("9 - Cofactor matrix\n");
    printf("10 - Inverse matrix\n");
    printf("11 - Exit program\n");
    while (1) {
        printf("\nEnter your choice: ");
        if (scanf_s("%d", &choice) < 1) {
            printf("Incorrect choice. Please enter a number between 1 and 10 (or 11 to EXIT).\n");
            int c;
            while ((c = getchar()) != '\n');
            continue;
        }
        if (choice == 11) {
            break;
        }
        switch (choice) {
            case 1: addiction_menu(); break;
            case 2: subtraction_menu(); break;
            case 3: multiplication_by_scalar_menu(); break;
            case 4: multiplication_menu(); break;
            case 5: transposition_menu(); break;
            case 6: LU_decomposition_menu(); break; 
            case 7: determinant_with_LU_menu(); break;
            case 8: trace_menu(); break;
            case 9: cofator_matrix_menu(); break;
            case 10: inverse_matrix_menu(); break;
            default:
                printf("Incorrect choice. Please enter a number between 1 and 10 (or 11 to EXIT).\n"); break;
        }
    }
    return 0;
}

// Funkcja odczytuje macierz z pliku CSV na podstawie nazwy pliku podanego w konsoli
Matrix read_matrix_console() {
    char input_fname[100];
    printf("Enter the input file name: ");
    scanf_s("%s", input_fname, (unsigned int)sizeof(input_fname));
    Matrix matrix = read_matrix_from_csv(input_fname);
    return matrix;
}

// Funkcja zapisuje macierz do pliku CSV na podstawie danej macierzy oraz podanej w konsoli nazwy pliku
void write_matrix_console(Matrix matrix) {
    char output_fname[100];
    printf("Enter the output file name: ");
    scanf_s("%s", output_fname, (unsigned int)sizeof(output_fname));
    write_matrix_to_csv(output_fname, matrix);
}

// Funkcje bedace adaptacja odpowiednich funkcji operacji na macierzach dla menu
// Sprawdzaja poprawnosc danych
void addiction_menu() {
    Matrix matrixA = read_matrix_console();
    if (matrixA.values != NULL) {
        Matrix matrixB = read_matrix_console();
        if (matrixB.values != NULL) {
            Matrix matrixR = addition(matrixA, matrixB);
            free_memory_for_matrix(matrixA);
            free_memory_for_matrix(matrixB);
            if (matrixR.values != NULL) {
                write_matrix_console(matrixR);
                free_memory_for_matrix(matrixR);
            }
        }
    } 
}

void subtraction_menu() {
    Matrix matrixA = read_matrix_console();
    if (matrixA.values != NULL) {
        Matrix matrixB = read_matrix_console();
        if (matrixB.values != NULL) {
            Matrix matrixR = subtraction(matrixA, matrixB);
            free_memory_for_matrix(matrixA);
            free_memory_for_matrix(matrixB);
            if (matrixR.values != NULL) {
                write_matrix_console(matrixR);
                free_memory_for_matrix(matrixR);
            }
        }
    }
}

void multiplication_by_scalar_menu() {
    Matrix matrixA = read_matrix_console();
    if (matrixA.values != NULL) {
        float scalar;
        printf("Enter the scalar: ");
        if (scanf_s("%f", &scalar) < 1) {
            printf("--error--\n--scalar must be a number--\n\n");
            int c;
            while ((c = getchar()) != '\n');
            return;
        }
        else {
            Matrix matrixR = multiplication_by_scalar(matrixA, scalar);
            free_memory_for_matrix(matrixA);
            write_matrix_console(matrixR);
            free_memory_for_matrix(matrixR);
        }
    }
}

void multiplication_menu() {
    Matrix matrixA = read_matrix_console();
    if (matrixA.values != NULL) {
        Matrix matrixB = read_matrix_console();
        if (matrixB.values != NULL) {
            Matrix matrixR = multiplication(matrixA, matrixB);
            free_memory_for_matrix(matrixA);
            free_memory_for_matrix(matrixB);
            if (matrixR.values != NULL) {
                write_matrix_console(matrixR);
                free_memory_for_matrix(matrixR);
            }
        }
    }
}

void transposition_menu() {
    Matrix matrixA = read_matrix_console();
    if (matrixA.values != NULL) {
        Matrix matrixR = transposition(matrixA);
        free_memory_for_matrix(matrixA);
        write_matrix_console(matrixR);
        free_memory_for_matrix(matrixR);
    }
}

void LU_decomposition_menu() {
    Matrix matrixA = read_matrix_console();
    if (matrixA.values != NULL) {
        Matrices R = LU_decomposition(matrixA);
        free_memory_for_matrix(matrixA);
        if (R.matrix1.values != NULL && R.matrix2.values != NULL) {
            printf("For lower triangular matrix:\n");
            write_matrix_console(R.matrix1);
            free_memory_for_matrix(R.matrix1);
            printf("For upper triangular matrix:\n");
            write_matrix_console(R.matrix2);
            free_memory_for_matrix(R.matrix2);
        }
    }
}

void determinant_with_LU_menu() {
    Matrix matrixA = read_matrix_console();
    if (matrixA.values != NULL) {
        float det = determinant_with_LU(matrixA);
        free_memory_for_matrix(matrixA);
        if (isnan(det) == 0) {
            printf("Determinant: %.3f\n", det);
        }
    }
}

void trace_menu() {
    Matrix matrixA = read_matrix_console();
    if (matrixA.values != NULL) {
        float det = trace(matrixA);
        free_memory_for_matrix(matrixA);
        if (isnan(det) == 0) {
            printf("Trace: %.3f\n", det);
        }
    }
}

void cofator_matrix_menu() {
    Matrix matrixA = read_matrix_console();
    if (matrixA.values != NULL) {
        Matrix matrixR = cofactor_matrix(matrixA);
        free_memory_for_matrix(matrixA);
        if (matrixR.values != NULL) {
            write_matrix_console(matrixR);
            free_memory_for_matrix(matrixR);
        }
    }
}

void inverse_matrix_menu() {
    Matrix matrixA = read_matrix_console();
    if (matrixA.values != NULL) {
        Matrix matrixR = inverse_matrix(matrixA);
        free_memory_for_matrix(matrixA);
        if (matrixR.values != NULL) {
            write_matrix_console(matrixR);
            free_memory_for_matrix(matrixR);
        }
    }
}

