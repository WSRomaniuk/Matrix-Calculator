# 🧮 Matrix Operations in C

## 🎯 Project Overview
This project is a high-performance console application written in **C**, designed to perform complex mathematical operations on matrices. The primary goal was to implement efficient algorithms for linear algebra while strictly managing memory resources using dynamic allocation.

The application allows users to import matrices from **CSV files**, perform calculations, and export the results back to CSV format.

## 🚀 Key Features

The program features an interactive console menu offering a wide range of operations:

### Basic Operations
* **Arithmetic:** Matrix Addition and Subtraction.
* **Scaling:** Multiplication by a scalar value.
* **Multiplication:** Standard matrix multiplication logic.
* **Transposition:** Rows and columns swapping.

### Advanced Algorithms
* **Trace:** Calculating the sum of elements on the main diagonal.
* **LU Decomposition:** Breaking down a square matrix into Lower (L) and Upper (U) triangular matrices.
* **Determinant:** Calculated using the efficient **LU Decomposition method** (complexity $O(n^3)$), allowing for processing of larger matrices compared to standard recursive methods.
* **Inverse Matrix:** Implemented using the Cofactor Matrix and Determinant approach.

## 🛠️ Technical Implementation
This project was built to demonstrate proficiency in low-level programming concepts:

* **Memory Management:** Full manual control over memory using `malloc` and `free`. The system uses dynamic 2D arrays and ensures no memory leaks occur during operations.
* **Custom Data Structures:** Implementation of `Matrix` (stores dimensions and values) and `Matrices` (stores L and U pairs) structs.
* **File I/O:** Custom parser for `.csv` files that automatically detects matrix dimensions based on delimiters.
* **Error Handling:** Robust validation for file paths, matrix dimensions, and mathematical constraints (e.g., checking if a matrix is singular before inverting).

## 💻 How to Use
1.  **Compile** the source code (e.g., using `gcc`).
2.  **Run** the executable in your terminal.
3.  **Select** an operation from the numbered menu.
4.  **Input** the path to your CSV file (e.g., `data.csv`).
5.  **Save** the result to a new file when prompted.

## 👥 Authors & Contributions

* **Wiktoria Wróbel:** Project supervision, basic algorithms (Addition, Subtraction, Multiplication, Transposition, Trace).
* **Wiktor Suchoński-Romaniuk:** Advanced algorithms (Scalar multiplication, LU Decomposition, Determinant, Inverse Matrix), Data Structures.
* **Sebastian Szklarski:** File I/O (CSV parsing), Memory allocation logic, Console User Interface.

---
*Project created for the Programming in C course.*
