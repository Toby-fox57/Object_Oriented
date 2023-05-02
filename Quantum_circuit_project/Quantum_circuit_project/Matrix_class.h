#ifndef MATRIX_CLASS_QUANTUM_CIRCUIT
#define MATRIX_CLASS_QUANTUM_CIRCUIT

// Declares a class for matrices
class matrix
{
	friend std::ostream& operator<<(std::ostream& os, const matrix& mat);

private:
	complex* matrix_data{ nullptr };
	int rows{ 0 };
	int columns{ 0 };

public:
	matrix() = default;
	matrix(int m, int n);
	~matrix()
	{
		delete[] matrix_data;
		matrix_data = nullptr;
	}

	matrix(const matrix& mat) noexcept;
	matrix& operator=(const matrix& mat) noexcept;

	matrix(matrix&& mat) noexcept;
	matrix& operator=(matrix&& mat) noexcept;

	int get_columns() const;
	int get_rows() const;
	int position_in_array(int i, int j) const;

	complex& operator()(int m, int n);

	matrix operator+(const matrix& mat) const;
	matrix& operator+=(const matrix& mat);

	matrix operator-(const matrix& mat) const;
	matrix operator*(const matrix& mat) const;

	matrix operator^(const matrix& mat) const;
	matrix& operator^=(const matrix& mat);

	matrix& transpose();
};

#endif