#include "Matrix_class.h"

// -- Matrix --

// Parameterised constructor for the class matrix
matrix::matrix(int m, int n) : rows(m), columns(n)
{
	try {
		if (m <= 0 || n <= 0) {
			throw std::invalid_argument("M and n must be positive integers");
		}
		matrix_data = new complex[m * n];
		for (int i{ 1 }; i <= m; i++) {
			for (int j{ 1 }; j <= n; j++) {
				matrix_data[position_in_array(i, j)] = complex{ 0, 0 };
			}
		}
	}
	catch (std::invalid_argument& error_message) {
		std::cerr << "Error: " << error_message.what() << std::endl;
		exit(1);
	}
}

// Defines a copy constructor for the class matrix
matrix::matrix(const matrix& mat) noexcept
{
	matrix_data = nullptr;
	rows = mat.get_rows(); columns = mat.get_columns();

	matrix_data = new complex[rows * columns];
	for (int i{ 1 }; i <= rows; i++) {
		for (int j{ 1 }; j <= columns; j++) {
			matrix_data[position_in_array(i, j)] = mat.matrix_data[position_in_array(i, j)];
		}
	}
}

matrix& matrix::operator=(const matrix& mat) noexcept
{
	if (&mat == this) return *this;

	delete[] matrix_data;
	matrix_data = nullptr;
	rows = 0; columns = 0;

	rows = mat.get_rows(); columns = mat.get_columns();

	matrix_data = new complex[rows * columns];
	for (int i{ 1 }; i <= rows; i++) {
		for (int j{ 1 }; j <= columns; j++) {
			matrix_data[position_in_array(i, j)] = mat.matrix_data[position_in_array(i, j)];
		}
	}

	return *this;
}

// Implements a move constructor for the class matrix
matrix::matrix(matrix&& mat) noexcept
{
	rows = mat.get_rows(); columns = mat.get_columns();
	matrix_data = mat.matrix_data;
	mat.rows = 0; mat.columns = 0;
	mat.matrix_data = nullptr;
}

matrix& matrix::operator=(matrix&& mat) noexcept
{
	std::swap(rows, mat.rows); std::swap(columns, mat.columns);
	std::swap(matrix_data, mat.matrix_data);

	return *this;
}

// Returns information about the class matrix
int matrix::get_columns() const
{
	return columns;
}

int matrix::get_rows() const
{
	return rows;
}

int matrix::position_in_array(int i, int j) const
{
	try {
		if ((i < 1 || i > rows) || (j < 1 || j > columns)) {
			throw std::out_of_range("Index out of range");
		}
	}
	catch (std::out_of_range& error_message) {
		std::cerr << "Error: " << error_message.what() << std::endl;
		if (i < 1 || j < 1) {
			std::cerr << "i >= 1 and j >= 1" << std::endl;
		}
		exit(1);
	}

	return (j - 1) + (i - 1) * columns;
}

// Overloads the () operator to allow elements in the matrix to be changed
complex& matrix::operator()(int m, int n)
{
	return matrix_data[position_in_array(m, n)];
}

// Overloads the + operator to perform matrix addition
matrix matrix::operator+(const matrix& mat) const
{
	try {
		if (rows != mat.get_rows() || columns != mat.get_columns()) {
			throw std::invalid_argument("Invalid addition");
		}
		matrix temp{ rows, columns };
		temp.matrix_data = new complex[rows * columns];

		for (int i{ 1 }; i <= rows; i++) {
			for (int j{ 1 }; j <= columns; j++) {
				temp(i, j) = matrix_data[position_in_array(i, j)] + mat.matrix_data[position_in_array(i, j)];
			}
		}

		return temp;
	}
	catch (std::invalid_argument& error) {
		std::cerr << "Error: " << error.what() << std::endl;
		std::cerr << "M and N must be the same for both matrices." << std::endl;
		exit(1);
	}
}

matrix& matrix::operator+=(const matrix& mat) {
	*this = *this + mat;

	return *this;
}

matrix matrix::operator-(const matrix& mat) const
{
	try {
		if (rows != mat.get_rows() || columns != mat.get_columns()) {
			throw std::invalid_argument("Invalid subtraction");
		}
		matrix temp{ rows, columns };
		temp.matrix_data = new complex[rows * columns];

		for (int i{ 1 }; i <= rows; i++) {
			for (int j{ 1 }; j <= columns; j++) {
				temp(i, j) = matrix_data[position_in_array(i, j)] - mat.matrix_data[position_in_array(i, j)];
			}
		}

		return temp;
	}
	catch (std::invalid_argument& error) {
		std::cerr << "Error: " << error.what() << std::endl;
		std::cerr << "M and N must be the same for both matrices." << std::endl;
		exit(1);
	}
}

// Overloads the * operator to perform matrix multiplication
matrix matrix::operator*(const matrix& mat) const
{
	try {
		if (columns != mat.get_rows()) {
			throw std::invalid_argument("Invalid multiplication");
		}
		matrix temp{ rows, mat.get_columns() };
		temp.matrix_data = new complex[rows * mat.get_columns()];

		for (int i{ 1 }; i <= temp.get_rows(); i++) {
			for (int j{ 1 }; j <= temp.get_columns(); j++) {
				temp(i, j) = complex{ 0, 0 };

				for (int k{ 1 }; k <= columns; k++) {
					temp(i, j) += matrix_data[position_in_array(i, k)] * mat.matrix_data[mat.position_in_array(k, j)];
				}
			}
		}
		return temp;
	}
	catch (std::invalid_argument& error) {
		std::cerr << "Error: " << error.what() << std::endl;
		std::cerr << "N of the first matrix must equal M of the second matrix. " << "N_1 = " << columns << ", M_2 = " << mat.get_rows() << std::endl;
		exit(1);
	}
}

// Overloads the ^ operator to perform tensor products
matrix matrix::operator^(const matrix& mat) const
{
	if (rows == 0 && columns == 0) {
		return mat;
	}
	else {
		matrix temp{ (rows * mat.get_rows()), (columns * mat.get_columns()) };
		temp.matrix_data = new complex[(rows * mat.get_rows()) * (columns * mat.get_columns())];

		for (int i{ 1 }; i <= rows; i++) {
			for (int j{ 1 }; j <= columns; j++) {
				for (int k{ 1 }; k <= mat.get_rows(); k++) {
					for (int l{ 1 }; l <= mat.get_columns(); l++) {
						int temp_i = (i - 1) * mat.get_rows() + k; int temp_j = (j - 1) * mat.get_columns() + l;
						temp(temp_i, temp_j) = matrix_data[position_in_array(i, j)] * mat.matrix_data[mat.position_in_array(k, l)];
					}
				}
			}
		}

		return temp;
	}
};

matrix& matrix::operator^=(const matrix& mat) {
	*this = *this ^ mat;

	return *this;
}

matrix& matrix::transpose() {
	std::swap(rows, columns);

	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j < columns; j++) {
			(*this)(j, i) = (*this)(i, j);
		}
	}
	return *this;
}

// Overloads the << to output a matrix
std::ostream& operator<<(std::ostream& os, const matrix& mat)
{
	os << "[";
	if (mat.rows > 0 && mat.columns > 0) {
		os << "[";
		for (int i{ 1 }; i <= mat.rows; i++) {
			for (int j{ 1 }; j < mat.columns; j++) {
				os << std::setw(9) << mat.matrix_data[mat.position_in_array(i, j)] << ",";
			}
			os << std::setw(9) << mat.matrix_data[mat.position_in_array(i, mat.get_columns())] << "]";
			if (i != mat.rows) {
				os << "\n [";
			}
		}
	}
	os << "]\n";

	return os;
}