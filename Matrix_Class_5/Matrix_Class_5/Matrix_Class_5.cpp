// PHYS 30762 Programming in C++
// Assignment 5: A Matrix Class
// Tobias Fox 10475873

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>

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

	// Parameterised constructor 
	matrix(int m, int n);

	// Destructor
	~matrix()
	{
		delete[] matrix_data;
		matrix_data = nullptr;
		std::cout << "Removing matrix" << std::endl;
	}

	// Copy constructor
	matrix(const matrix& mat);

	// Move constructor
	matrix(matrix&& mat);

	// Copy constructor, overloading =
	matrix& operator=(const matrix& mat);

	// Move constructor, overloading =
	matrix& operator=(matrix&& mat);

	// Return properties of the matrix
	int get_columns() const
	{
		return columns;
	}
	int get_rows() const
	{
		return rows;
	}
	int position_in_array(int i, int j) const;

	// Set values of the matrix
	double& operator()(int m, int n)
	{
		return matrix_data[position_in_array(m, n)];
	}

	// Overload + operator for addition
	matrix operator+(const matrix& mat) const;

	// Overload - operator for subtraction
	matrix operator-(const matrix& mat) const;

	// Overload * operator for multiplication
	matrix operator*(const matrix& mat) const;

	// Return a matrix with the ith row and jth column deleted
	matrix reduce_matrix(int i_row, int j_column) const;

	// Calculate the determinant
	double calculate_determinant() const;
};

// Parameterised constructor
matrix::matrix(int m, int n)
{
	if (m < 0) {
		std::cout << "Error: m must be a positive integer" << std::endl;
	}
	if (n < 0) {
		std::cout << "Error: n must be a positive integer" << std::endl;
	}
	rows = m; columns = n;
	matrix_data = new double[m * n];

	for (int i{ 1 }; i <= m; i++) {
		for (int j{ 1 }; j <= n; j++) {
			matrix_data[position_in_array(i, j)] = 0;
		}
	}
}

// Copy constructor
matrix::matrix(const matrix& mat)
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
matrix::matrix(matrix&& mat)
{
	rows = mat.get_rows(); columns = mat.get_columns();
	matrix_data = mat.matrix_data;
	mat.rows = 0; mat.columns = 0;
	mat.matrix_data = nullptr;
}

// Copy constructor, overloading =
matrix& matrix::operator=(const matrix& mat)
{
	if (&mat == this) return *this;

	delete[] matrix_data;
	matrix_data = nullptr;
	rows = 0; columns = 0;

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
matrix& matrix::operator=(matrix&& mat)
{
	std::swap(rows, mat.rows); std::swap(columns, mat.columns);
	std::swap(matrix_data, mat.matrix_data);

	return *this;
}

// Return position in the array
int matrix::position_in_array(int i, int j) const
{
	if ((i > 0 && i <= rows) && (j > 0 && j <= columns)) {
		return (j - 1) + (i - 1) * columns;
	}
	else {
		std::cout << "Error: out of range" << std::endl; exit(1);
	}
}

// Overload + operator for addition
matrix matrix::operator+(const matrix& mat) const
{
	if (rows == mat.get_rows() && columns == mat.get_columns()) {
		matrix temp{ rows, columns };
		temp.matrix_data = new double[rows * columns];

		for (int i{ 1 }; i <= rows; i++) {
			for (int j{ 1 }; j <= columns; j++) {
				temp(i, j) = matrix_data[position_in_array(i, j)] + mat.matrix_data[position_in_array(i, j)];
			}
		}
		return temp;
	}
	else {
		std::cout << "Error: m and n must be the same." << std::endl;
		matrix temp{ 0, 0 };

		return temp;
	}
}

// Overload - operator for subtraction
matrix matrix::operator-(const matrix& mat) const
{
	if (rows == mat.get_rows() && columns == mat.get_columns()) {
		matrix temp{ rows, columns };
		temp.matrix_data = new double[rows * columns];

		for (int i{ 1 }; i <= rows; i++) {
			for (int j{ 1 }; j <= columns; j++) {
				temp(i, j) = matrix_data[position_in_array(i, j)] - mat.matrix_data[position_in_array(i, j)];
			}
		}
		return temp;
	}
	else {
		std::cout << "Error: m and n must be the same." << std::endl;
		matrix temp{ 0, 0 };

		return temp;
	}
}

// Overload * operator for multiplication
matrix matrix::operator*(const matrix& mat) const
{
	if (columns == mat.get_rows()) {
		matrix temp{ rows, mat.get_columns() };
		temp.matrix_data = new double[rows * mat.get_columns()];

		for (int i{ 1 }; i <= rows; i++) {
			for (int j{ 1 }; j <= mat.get_columns(); j++) {
				temp(i, j) = 0;

				for (int k{ 1 }; k <= columns; k++) {
					temp(i, j) += matrix_data[position_in_array(i, k)] * mat.matrix_data[mat.position_in_array(k, j)];
				}
			}
		}
		return temp;
	}
	else {
		std::cout << "Error: n of the first matrix must equal m of the second matrix." << std::endl;
		matrix temp{ 0, 0 };

		return temp;
	}
}

// Return a matrix with the ith row and jth column deleted
matrix matrix::reduce_matrix(int i_row, int j_column) const
{
	if (i_row <= rows || j_column <= columns) {
		matrix temp{ rows - 1, columns - 1 };
		temp.matrix_data = new double[(rows - 1) * (columns - 1)];

		int j{ 0 };
		for (int i{ 0 }; i <= position_in_array(rows, columns); i++) {
			if ((i >= position_in_array(i_row, 1) && i <= position_in_array(i_row, columns)) || ((i + 1 - j_column) % columns == 0)) {
				j++;
			}
			else {
				temp.matrix_data[i - j] = matrix_data[i];
			}
		}
		return temp;

	}
	else if (i_row > rows || j_column <= columns) {
		std::cout << "ith row inputted is greater than the number of rows of the matrix " << std::endl; exit(1);
	}
	else if (i_row <= rows || j_column < columns) {
		std::cout << "jth column inputted is greater than the number of columns of the matrix " << std::endl; exit(1);
	}
	else {
		std::cout << "ith row and jth column inputted is greater than the number of rows and columns of the matrix " << std::endl; exit(1);
	}
}

double matrix::calculate_determinant() const
{
	if (rows == columns && rows > 1) {
		if (rows == 2) {
			double minor{ 0 };
			minor += matrix_data[position_in_array(1, 1)] * matrix_data[position_in_array(2, 2)];
			minor -= (matrix_data[position_in_array(1, 2)] * matrix_data[position_in_array(2, 1)]);

			return minor;
		}
		else {
			double determinant{ 0 };
			for (int j{ 1 }; j <= columns; j++) {
				determinant += pow(-1, j - 1) * matrix_data[position_in_array(1, j)] * reduce_matrix(1, j).calculate_determinant();
			}
			return determinant;
		}
	}
	else {
		std::cout << "Non-square matrices do not have determinants."; exit(1);
	}
}

// Function to overload << operator for a matrix
std::ostream& operator<<(std::ostream& os, const matrix& mat)
{
	os << "[";
	if (mat.rows > 0 && mat.columns > 0) {
		os << "[";
		for (int i{ 1 }; i <= mat.rows; i++) {
			for (int j{ 1 }; j < mat.columns; j++) {
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
	int inputted_rows; int inputted_columns;
	while (true) {
		std::cout << "Please enter the number of rows the matrix has: ";
		if (is >> inputted_rows && inputted_rows > 0)  {
			mat.rows = inputted_rows;
			break;
		} else {
			std::cout << "Error: Please input a positive integar";
			is.clear(); is.ignore();
		}
	}
	
	while (true) {
		std::cout << "Please enter the number of columns the matrix has: ";
		if (is >> inputted_columns && inputted_columns > 0) {
			mat.columns = inputted_columns;
			break;
		}
		else {
			std::cout << "Error: Please input a positive integar" << std::endl;
			is.clear(); is.ignore();
		}
	}

	mat.matrix_data = new double[mat.rows * mat.columns];

	for (int i{ 1 }; i <= mat.rows; i++) {
		std::cout << "Please enter the next row of matrix with spaces between each element and / at the end of the input: ";

		while (true) {
			double temp_num; int j = 0;
			while (is >> temp_num) {
				j++; 
				if (j <= mat.columns) {
					mat.matrix_data[mat.position_in_array(i, j)] = temp_num;
				} else {
					break; 
				}
			}
			is.clear(); is.ignore();

			if (j < mat.columns) {
				std::cout << "Error: Not enough numbers inputted." << std::endl;
				std::cout << "Please re-enter that line: "; i = i;
			} else if (j > mat.columns) {
				std::cout << "Error: Too many numbers inputted." << std::endl;
				std::cout << "Please re-enter that line: ";  i = i;
			} else {
				break;
			}
		}
	}
	return is;
}

int main()
{
	// -- Part 1: Construction, deep copy and move --

	std::cout << "--Part 1: Construction, deep copy and move--" << std::endl;

	// Parameterised constructor
	const int m{ 3 }, n{ 3 };
	matrix matrix_a{ m, n };
	matrix matrix_b{ m, n };

	const int p{ 2 }, q{ 3 };
	matrix matrix_c{ p, q };

	// Set values for the matrices
	matrix_a(1, 1) = 1; matrix_a(1, 2) = 2; matrix_a(1, 3) = 3; matrix_a(2, 1) = 9;	matrix_a(2, 2) = 8;
	matrix_a(2, 3) = 7, matrix_a(3, 1) = 4; matrix_a(3, 2) = 2; matrix_a(3, 3) = 6;

	matrix_b(1, 1) = 5; matrix_b(1, 2) = 5; matrix_b(1, 3) = 4; matrix_b(2, 1) = 1;	matrix_b(2, 2) = 2;
	matrix_b(2, 3) = 3, matrix_b(3, 1) = 6; matrix_b(3, 2) = 9; matrix_b(3, 3) = 8;

	matrix_c(1, 1) = 3; matrix_c(1, 2) = 4; matrix_c(1, 3) = 1; matrix_c(2, 1) = 2;	matrix_c(2, 2) = 5;
	matrix_c(2, 3) = 6;

	// Print parameterised matrices
	std::cout << "Matrix A:" << std::endl;
	std::cout << matrix_a << std::endl;

	std::cout << "Matrix B:" << std::endl;
	std::cout << matrix_b << std::endl;

	std::cout << "Matrix C:" << std::endl;
	std::cout << matrix_b << std::endl;

	// Copy by assignment
	matrix copy_by_assignment_matrix = matrix_a;
	std::cout << "Deep copy of matrix A by assignement:" << std::endl;
	std::cout << copy_by_assignment_matrix << std::endl;

	// Copy constructor
	matrix copy_constructor_martix{ matrix_a };
	std::cout << "Deep copy of matrix A using the constructor:" << std::endl;
	std::cout << copy_constructor_martix << std::endl;

	// Shows copy matrix is unchanged when the original matrix is altered
	matrix_a(1, 1) = 1; matrix_a(1, 2) = 1; matrix_a(1, 3) = 1; matrix_a(2, 1) = 1;	matrix_a(2, 2) = 1;
	matrix_a(2, 3) = 1, matrix_a(3, 1) = 1; matrix_a(3, 2) = 1; matrix_a(3, 3) = 1;

	std::cout << "Showing that the copied matrix is unchanged when the original matrix is altered:" << std::endl;
	std::cout << "Alterated matrix:" << std::endl;
	std::cout << matrix_a << std::endl;
	std::cout << "Copied matrix" << std::endl;
	std::cout << copy_constructor_martix << std::endl;

	matrix_a = copy_constructor_martix;

	// Move by assignment
	matrix move_by_assignment_matrix = std::move(matrix_a);

	std::cout << "Move by assignment -" << std::endl;
	std::cout << "The moved matrix: " << std::endl;
	std::cout << move_by_assignment_matrix << std::endl;
	std::cout << "Matrix A which has had its content moved: " << std::endl;
	std::cout << matrix_a << std::endl;
	std::cout << "\n";

	matrix_a = std::move(move_by_assignment_matrix);

	// Move by constructor
	matrix move_constructor_matrix{ std::move(matrix_a) };

	std::cout << "Move by constructor -" << std::endl;
	std::cout << "The moved matrix: " << std::endl;
	std::cout << move_constructor_matrix << std::endl;
	std::cout << "Matrix A which has had its content moved: " << std::endl;
	std::cout << matrix_a << std::endl;
	std::cout << "\n";

	matrix_a = copy_constructor_martix;

	// -- Part 2: matrix operations --

	std::cout << "-- Part 2: matrix operations --" << std::endl;

	// Addition
	std::cout << "Addition -" << std::endl;
	std::cout << "Matrix A + Matrix B = " << std::endl;
	std::cout << matrix_a + matrix_b << std::endl;

	// Subtraction
	std::cout << "Subtraction -" << std::endl;
	std::cout << "Matrix A - Matrix B = " << std::endl;
	std::cout << matrix_a - matrix_b << std::endl;

	// Muliplitcation
	std::cout << "Multiplication -" << std::endl;
	std::cout << "Matrix A * Matrix B = " << std::endl;
	std::cout << matrix_a * matrix_b << std::endl;
	std::cout << "Matrix C * Matrix B = " << std::endl;
	std::cout << matrix_c * matrix_b << std::endl;
	std::cout << "Matrix B * Matrix C = " << std::endl;
	std::cout << matrix_b * matrix_c << std::endl;

	// Determinant
	std::cout << "Determinant -" << std::endl;
	std::cout << "det(A) = " << matrix_a.calculate_determinant() << std::endl;
	std::cout << "det(B) = " << matrix_b.calculate_determinant() << std::endl;
	std::cout << "\n" << std::endl;

	// Overloading >> operator
	matrix input_matrix{};
	std::cout << "Input a matrix -" << std::endl;
	std::cin >> input_matrix;
	std::cout << "The inputted matrix: " << std::endl;
	std::cout << input_matrix << std::endl;

	return 0;
}