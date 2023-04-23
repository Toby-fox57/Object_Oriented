#include "Quantum_circuit_class.h"

// -- Complex --

double complex::real_part() 
{
	return re;
}

double complex::imaginary_part() 
{
	return im;
}

void complex::set_complex(double real_input, double imaginary_input) 
{
	re = real_input; 
	im = imaginary_input;
}

complex complex::complex_conjugate() const 
{
	complex temp{ re, im * -1 };
	return temp;
}

complex complex::operator+(const complex& z) const 
{
	complex temp{ re + z.re, im + z.im };
	return temp;
}

complex complex::operator-(const complex& z) const 
{
	complex temp{ re - z.re, im - z.im };
	return temp;
}

std::ostream& operator<<(std::ostream& os, const complex& z)
{
	if (z.im >= 0) {
		os << z.re << "+" << z.im << "i";
	}
	else {
		os << z.re << z.im << "i";
	}
	return os;
}

// -- Matrix --

matrix::matrix(int m, int n)
{
	if (m < 0) {
		std::cerr << "Error: m must be a positive integer" << std::endl;
		exit(1);
	} if (n < 0) {
		std::cerr << "Error: n must be a positive integer" << std::endl;
		exit(1);
	} else {
		rows = m; columns = n;
		matrix_data = new double[m * n];

		for (int i{ 1 }; i <= m; i++) {
			for (int j{ 1 }; j <= n; j++) {
				matrix_data[position_in_array(i, j)] = 0;
			}
		}
	}
}

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

matrix::matrix(matrix&& mat)
{
	rows = mat.get_rows(); columns = mat.get_columns();
	matrix_data = mat.matrix_data;
	mat.rows = 0; mat.columns = 0;
	mat.matrix_data = nullptr;
}

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

matrix& matrix::operator=(matrix&& mat)
{
	std::swap(rows, mat.rows); std::swap(columns, mat.columns);
	std::swap(matrix_data, mat.matrix_data);

	return *this;
}

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
	if ((i > 0 && i <= rows) && (j > 0 && j <= columns)) {
		return (j - 1) + (i - 1) * columns;
	}
	else {
		std::cerr << "Error: out of range" << std::endl;
		exit(1);
	}
}

double& matrix::operator()(int m, int n)
{
	return matrix_data[position_in_array(m, n)];
}

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
		std::cerr << "Error: m and n must be the same." << std::endl;
		exit(1);
	}
}

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
		std::cerr << "Error: m and n must be the same." << std::endl;
		exit(1);
	}
}

matrix matrix::operator*(const matrix& mat) const
{
	if (columns == mat.get_rows()) {
		matrix temp{ rows, mat.get_columns() };
		temp.matrix_data = new double[rows * mat.get_columns()];

		for (int i{ 1 }; i <= temp.get_rows(); i++) {
			for (int j{ 1 }; j <= temp.get_columns(); j++) {
				temp(i, j) = 0;

				for (int k{ 1 }; k <= columns; k++) {
					temp(i, j) += matrix_data[position_in_array(i, k)] * mat.matrix_data[mat.position_in_array(k, j)];
				}
			}
		}
		return temp;
	}
	else {
		std::cerr << "Error: n of the first matrix must equal m of the second matrix." << std::endl;
		exit(1);
	}
}

matrix matrix::operator^(const matrix& mat) const
{
	matrix temp{ (rows * mat.get_rows()), (columns * mat.get_columns()) };
	temp.matrix_data = new double[(rows * mat.get_rows()) * (columns * mat.get_columns())];

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
};

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

//-- qbit --

qbit::qbit(int inital_state)
{
	if (inital_state == 0) {
		state(1, 1) = 1; state(2, 1) = 0;
	}
	if (inital_state == 1) {
		state(1, 1) = 0; state(2, 1) = 1;
	}
}

void qbit::set_state(int new_state)
{
	if (new_state == 0) {
		state(1, 1) = 1; state(2, 1) = 0;
	}
	if (new_state == 1) {
		state(1, 1) = 0; state(2, 1) = 1;
	}
}

matrix qbit::get_state() const
{
	return state;
}

//-- Components --

identity::identity()
{
	gate(1, 1) = 1;	gate(1, 2) = 0;	gate(2, 1) = 0;	gate(2, 2) = 1;
}

matrix identity::get_matrix() const
{
	return gate;
}

std::vector<std::string> identity::print_component_symbol() const
{
	return { "     ", "-----", "     " };
}

hadamard::hadamard()
{
	gate(1, 1) = 1 / sqrt(2);	gate(1, 2) = 1 / sqrt(2);	gate(2, 1) = 1 / sqrt(2);	gate(2, 2) = -1 / sqrt(2);
}

matrix hadamard::get_matrix() const
{
	return gate;
}

std::vector<std::string> hadamard::print_component_symbol() const
{
	return { " ┌─┐ ", "-|H|-", " └─┘  " };
}

//-- Circuits --

void circuit::add_qbit(qbit* qbit_a)
{
	qbits.push_back(qbit_a);
};

void circuit::add_components(std::vector<component*> new_components)
{
	int matrix_length{ 0 };
	
	for (int i{ 0 }; i < new_components.size(); i++) {
		matrix_length += new_components[i]->get_matrix().get_rows();
	}

	if (matrix_length / 2 == qbits.size()) {
		for (int j{ 0 }; j < new_components.size(); j++) {
			for (int k{ 0 }; k < new_components[j]->get_matrix().get_rows() / 2; k++)
				components.push_back(new_components[j]);
		}
	} else if (matrix_length / 2 < qbits.size()) {
		std::cerr << "Not enough components inputted" << std::endl;
		exit(1);
	} else {
		std::cerr << "Too many components inputted" << std::endl;
		exit(1);
	}
	
}

void circuit::setup_circuit(std::vector<qbit*> qbit_b, std::vector<component*> inputs)
{
	components = inputs; qbits = qbit_b; // Not updated
}

void circuit::run_circuit()
{
	if (qbits.size() > 0 && components.size() > 0) {
		qbit_state = qbits[0]->get_state();

		for (int i{ 1 }; i < qbits.size(); i++) {
			qbit_state = qbit_state ^ qbits[i]->get_state();
		}

		for (int j{ 0 }; j < components.size() / qbits.size(); j++) {
			matrix in_parallel = components[j * qbits.size()]->get_matrix();

			for (int k{ 1 }; k < qbits.size(); k++) {
				in_parallel = in_parallel ^ components[j + k]->get_matrix();

				if (components[j + k]->get_matrix().get_rows() > 2) {
					k += components[j + k]->get_matrix().get_rows() / 2 - 1;
				}
			}

			qbit_state = in_parallel * qbit_state;
		}

		std::cout << "Final state = " << std::endl;
		std::cout << qbit_state << std::endl;

	} else if (qbits.size() <= 0 && components.size() <= 0) {
		std::cerr << "Need to add qbits and components to run this ciruit" << std::endl;
		exit(1);
	} else if (components.size() <= 0) {
		std::cerr << "Need to add qbits to run this ciruit" << std::endl;
		exit(1);
	} else {
		std::cerr << "Need to add qbits to run this ciruit" << std::endl;
		exit(1);
	}
}

std::ostream& operator<<(std::ostream& os, const circuit& cir)
{
	for (int i{ 0 }; i < cir.qbits.size(); i++) {
		for (int j{ 0 }; j < 3; j++) {
			for (int k{ 0 }; k < cir.components.size() / cir.qbits.size(); k++) {
			




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
