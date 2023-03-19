// PHYS 30762 Programming in C++
// Assignment 5: A Matrix Class
// Tobias Fox 10475873

#include<iostream>
#include <iomanip>
#include <string>
#include <sstream>

// Defines the class matrix
class matrix
{
// Make function to overload operator<< a friend
friend std::ostream& operator<<(std::ostream& os, const matrix& mat);
friend std::istream& operator>>(std::istream& is, matrix& mat);

private:
	double* matrix_data{ nullptr };
	int rows{ 0 };
	int columns{ 0 };

public:
	// Default constructor
	matrix() = default;

	// Parameterised construtor 
	matrix(int m, int n);

	// Destructor
	~matrix()
	{
		delete[] matrix_data;
		matrix_data = nullptr;
		std::cout << "Removing matrix" << std::endl;
	}

	// Copy constructor
	matrix(const matrix& mat) 
	{
		matrix_data = nullptr;
		rows = mat.get_rows(); columns = mat.get_columns();

		if (rows >= 0 && columns >= 0) {
			matrix_data = new double[rows * columns];
			for (int i{ 1 }; i <= rows; i++) {
				for (int j{ 1 }; j <= columns; j++) {
					matrix_data[position_in_array(i, j)] = mat.matrix_data[position_in_array(i, j)];
				}
			}
		}
	}

	// Move constructor
	matrix(matrix&& mat)
	{
		rows = mat.get_rows(); columns = mat.get_columns();
		matrix_data = mat.matrix_data;
		mat.rows = 0; mat.columns = 0;
		mat.matrix_data = nullptr;
	}

	// Copy constructor, overloading =
	matrix& operator=(const matrix& mat) 
	{
		if (&mat == this) return *this;

		delete[] matrix_data;
		matrix_data = nullptr;
		rows = 0; columns = 0; // Why??

		rows = mat.get_rows(); columns = mat.get_columns();
		if (rows >= 0 && columns >= 0) {
			matrix_data = new double[rows * columns];
			for (int i{ 1 }; i <= rows; i++) {
				for (int j{ 1 }; j <= columns; j++) {
					matrix_data[position_in_array(i, j)] = mat.matrix_data[position_in_array(i, j)];
				}
			}
		}

		return *this;
	}

	// Move constructor, overloading =
	matrix& operator=(matrix&& mat)
	{		
		std::swap(rows, mat.rows); std::swap(columns, mat.columns);
		std::swap(matrix_data, mat.matrix_data);

		return *this;
	}

	// Return properties of the matrix
	int get_columns() const
	{
		return columns;
	}
	int get_rows() const
	{
		return rows;
	}
	int position_in_array(int i, int j) const
	{
		if ((i >= 0 && i <= rows) && (j >= 0 && j <= columns)) {
			return (j - 1) + (i - 1) * columns;
		}
		else {
			std::cout << "Error: out of range" << std::endl;
			exit(1);
		}
	}

	// Delete row i
	matrix& delete_row(int i_row)
	{
		int end_i_row = position_in_array(i_row, columns);

		for (int i = end_i_row + 1; i <= position_in_array(rows, columns); i++) {
			matrix_data[i - columns] = matrix_data[i];
		}

		rows--;

		return *this;
	}

	// Set values of the matrix
	double& operator()(int m, int n) 
	{
		return matrix_data[position_in_array(m, n)];
	}

	// Overload + operator for addition
	matrix operator+(const matrix& mat)
	{
		if (rows == mat.get_rows() && columns == mat.get_columns()) {
			matrix temp{ rows, columns};
			temp.matrix_data = new double[rows * columns];

			for (int i{1}; i <= rows; i++) {
				for (int j{1}; j <= columns; j++) {
					temp(i, j) = matrix_data[position_in_array(i, j)] + mat.matrix_data[position_in_array(i, j)];
				}
			}

			return temp;
		}
		else {
			std::cout << "Error: m and n must be the same.";
			exit(1);
		}
	}

	// Overload - operator for subtraction
	matrix operator-(const matrix& mat)
	{
		if (rows == mat.get_rows() && columns == mat.get_columns()) {
			matrix temp{ rows, columns };
			temp.matrix_data = new double[rows * columns];

			for (int i{1}; i <= rows; i++) {
				for (int j{1}; j <= columns; j++) {
					temp(i, j) = matrix_data[position_in_array(i, j)] - mat.matrix_data[position_in_array(i, j)];
				}
			}

			return temp;
		}
		else {
			std::cout << "Error: m and n must be the same.";
			exit(1);
		}
	}

	// Overload * operator for multiplication
	matrix operator*(const matrix& mat)
	{
		if (columns == mat.get_rows()) {
			matrix temp{ rows, mat.get_columns()};
			temp.matrix_data = new double[rows * mat.get_columns()];

			for (int i{1}; i <= rows; i++) {
				for (int j{1}; j <= mat.get_columns(); j++) {
					temp(i, j) = 0;

					for (int k{1}; k <= columns; k++) {
						temp(i, j) += matrix_data[position_in_array(i, k)] * mat.matrix_data[position_in_array(k, j)];
					}
				}
			}

			return temp;
		}
		else {
			std::cout << "Error: m and n must be the same.";
			exit(1);
		}
	}
};

// Parameterised constructor
matrix::matrix(int m, int n) 
{
	if (m < 1) {
		std::cout << "Error: m < 1" << std::endl;
	}
	if (n < 1) {
		std::cout << "Error: n < 1" << std::endl;
	}
	rows = m; columns = n;
	matrix_data = new double[m * n];
	for (int i{1}; i <= m; i++) {
		for (int j{1}; j <= n; j++) {
			matrix_data[position_in_array(i, j)] = 0;
		}
	}
}

// Function to overload << operator for a matrix
std::ostream& operator<<(std::ostream& os, const matrix& mat)
{
	os << "[";
    if (mat.rows > 0 && mat.columns > 0) {
        os << "[";
		for (int i{1}; i <= mat.rows; i++) {
			for (int j{1}; j < mat.columns; j++) {
                os << std::setw(3) << mat.matrix_data[mat.position_in_array(i, j)] << ",";
            }
			os << std::setw(3) << mat.matrix_data[mat.position_in_array(i, mat.get_columns())] << "]";
            if (i != mat.rows) {
                os << "\n [";
            }
        }
    }
	os << "]\n";

    return os;
}

// Function to overload >> operator for a matrix
std::istream& operator>>(std::istream& is, matrix& mat)
{
	bool next_line = true;
	int rows = 0; int columns = 0;

	while (next_line == true) {
		rows++;
		double temp_num;
		std::cout << "Please enter the first row of matrix with spaces inbetween each element and / at the end of the input :";

		while (is >> temp_num) {
			columns++;
		}

		double* temp_column = nullptr;
		temp_column = new double[columns];

		int counter = 0;
		while (is >> temp_num) {
			temp_column[counter] = temp_num;
			counter++;
		}

		next_line = false;
	}

	rows = 1; columns = 2;
	mat.matrix_data = new double[1 * 2];
	for (int i{1}; i < 1; i++) {
		for (int j{1}; j < 2; j++) {
			mat(i, j) = 0;
		}
	}

	return is;
}

int main() 
{
	// -- Part 1: Construction, deep copy and move --

	// Default constructor
	matrix default_matrix;
	std::cout << "Default construction:" << std::endl;
	std::cout << default_matrix;

	// Parameterised constructor
	const int m{ 2 }, n{ 2 };
	matrix parameterised_matrix{ m, n };

	// Set values for parameterised matrix
	parameterised_matrix(1, 1) = 1; parameterised_matrix(1, 2) = 2;	parameterised_matrix(2, 1) = 3; parameterised_matrix(2, 2) = 4;

	// Print matrix a2
	std::cout << "Parameterised construction:" << std::endl;
	std::cout << parameterised_matrix;

	// Copy by assignment
	matrix copy_by_assignment_matrix{ m, n };
	std::cout << "Default constructed matrix to be used for deep copy:" << std::endl;
	std::cout << copy_by_assignment_matrix;
	copy_by_assignment_matrix = parameterised_matrix;

	std::cout << "Parameterised matrix and copy matrix:" << std::endl;
	std::cout << parameterised_matrix;
	std::cout << copy_by_assignment_matrix;

	// Copy constructor
	matrix test_1_matrix = parameterised_matrix;

	matrix copy_constructor_martix{ test_1_matrix };
	std::cout << "Copy constructor matrix:" << std::endl;
	std::cout << copy_constructor_martix;

	// Shows copy matrix is unchanged when orignal matrix is alterated
	test_1_matrix(1, 1) = 1; test_1_matrix(1, 2) = 1;	test_1_matrix(2, 1) = 1; test_1_matrix(2, 2) = 1;
	
	std::cout << "Showing that the copied matrix is unchanged when the orignal matrix is alterated:" << std::endl;
	std::cout << "Alterated matrix and copy matrix:" << std::endl;
	std::cout << test_1_matrix;
	std::cout << copy_constructor_martix;

	// Move by constructor
	matrix test_2_matrix = parameterised_matrix;

	matrix move_constructor_matrix{ std::move(test_2_matrix) };
	move_constructor_matrix;

	std::cout << "Move by constructor -" << std::endl;
	std::cout << "Dimesions of parameterised matrix that has been moved (expect 0, 0):" << std::endl;
	std::cout << "M, N: " << test_2_matrix.get_rows() << " , " << test_2_matrix.get_columns() << std::endl;
	std::cout << "Dimesions of the move by assignment matrix (expect 2, 2):" << std::endl;
	std::cout << "M, N: " << move_constructor_matrix.get_rows() << " , " << move_constructor_matrix.get_columns() << std::endl;

	// Move by assignment
	matrix test_3_matrix = parameterised_matrix;

	matrix move_by_assignment_matrix;
	move_by_assignment_matrix = std::move(test_3_matrix);

	std::cout << "Move by assigment -" << std::endl;
	std::cout << "Dimesions of parameterised matrix that has been moved (expect 0, 0):" << std::endl;
	std::cout << "M, N: " << test_3_matrix.get_rows() << " , " << test_3_matrix.get_columns() << std::endl;
	std::cout << "Dimesions of the move by assignment matrix (expect 2, 2):" << std::endl;
	std::cout << "M, N: " << move_by_assignment_matrix.get_rows() << " , " << move_by_assignment_matrix.get_columns() << std::endl;

	// -- Part 2: matrix operations --
	
	matrix matrix_1{ m, n };
	matrix_1(1, 1) = 1; matrix_1(1, 2) = 2;	matrix_1(2, 1) = 3; matrix_1(2, 2) = 4;
	std::cout << "Matrix 1:" << std::endl;
	std::cout << matrix_1;

	matrix matrix_2{ m, n };
	matrix_2(1, 1) = 1; matrix_2(1, 2) = 2;	matrix_2(2, 1) = 3; matrix_2(2, 2) = 4;
	std::cout << "Matrix 2:" << std::endl;
	std::cout << matrix_2;

	// Addition
	matrix addition_matrix = matrix_1 + matrix_2;
	std::cout << "Addition:" << std::endl;
	std::cout << addition_matrix;

	// Subtraction
	matrix subtraction_matrix = matrix_1 - matrix_2;
	std::cout << "Subtraction:" << std::endl;
	std::cout << subtraction_matrix;

	// Muliplitcation
	matrix multiplcation_matrix = matrix_1 * matrix_2;
	std::cout << "Multiplication:" << std::endl;
	std::cout << multiplcation_matrix;

	// Delete row i
	matrix matrix_3{ 3, 3 };
	matrix_3(1, 1) = 1; matrix_3(1, 2) = 2;	matrix_3(1, 3) = 3; matrix_3(2, 1) = 4; matrix_3(2, 2) = 5;	matrix_3(2, 3) = 6; matrix_3(3, 1) = 7; matrix_3(3, 2) = 8;	matrix_3(3, 3) = 9;
	std::cout << matrix_3;
	matrix_3.delete_row(3);
	matrix_3.delete_row(1);
	std::cout << matrix_3;

	// Determinant

	return 0;
}