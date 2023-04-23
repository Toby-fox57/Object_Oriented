#ifndef MY_CLASS_H
#define MY_CLASS_H

class complex
{
	friend std::ostream& operator<<(std::ostream& os, const complex& z);

private:
	double re, im;

public:
	// Constructors & destructor
	complex() = default;
	complex(double r, double i) : re{ r }, im{ i }	{}
	~complex()
	{
		std::cout << "Removing complex number" << std::endl;
	}

	// Return real component
	double real_part();

	// Return imaginary component
	double imaginary_part();

	// Input real part
	void set_complex(double real_input, double imaginary_input);

	// Return complex conjugate
	complex complex_conjugate() const;

	// Overload + operator for addition
	complex operator+(const complex& z) const;

	// Overload - operator for subtraction
	complex operator-(const complex& z) const;
};

class matrix
{
	friend std::ostream& operator<<(std::ostream& os, const matrix& mat);

private:
	double* matrix_data{ nullptr };
	int rows{ 0 };
	int columns{ 0 };

public:
	// Constructor and destructor
	matrix() = default;
	matrix(int m, int n);
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
	int get_columns() const;
	int get_rows() const;
	int position_in_array(int i, int j) const;

	// Set values of the matrix
	double& operator()(int m, int n);

	// Overload + operator for addition
	matrix operator+(const matrix& mat) const;

	// Overload - operator for subtraction
	matrix operator-(const matrix& mat) const;

	// Overload * operator for multiplication
	matrix operator*(const matrix& mat) const;

	// Overload * operator for tensor product
	matrix operator^(const matrix& mat) const;
};

class component
{
public:
	virtual ~component() {};

	virtual matrix get_matrix() const = 0;
	virtual std::vector<std::string> print_component_symbol() const = 0;
};

class identity : public component
{
private:
	matrix gate{ 2, 2 };

public:
	identity();
	~identity()
	{
		std::cout << "Removing identity" << std::endl;
	}

	matrix get_matrix() const;
	std::vector<std::string> print_component_symbol() const;
};

class hadamard : public component
{
private:
	matrix gate{ 2, 2 };

public:
	hadamard();
	~hadamard()
	{
		std::cout << "Removing hadamard" << std::endl;
	}

	matrix get_matrix() const;
	std::vector<std::string> print_component_symbol() const;
};

class qbit
{
private:
	matrix state{ 2, 1 };

public:
	qbit() = default;
	qbit(int inital_state);
	~qbit()
	{
		std::cout << "Removing qbit" << std::endl;
	}

	void set_state(int new_state);
	matrix get_state() const;
};

class circuit
{
	friend std::ostream& operator<<(std::ostream& os, const circuit& cir);

private:
	std::vector<component*> components;
	std::vector<qbit*> qbits;
	matrix qbit_state;

public:
	circuit() = default;
	~circuit()
	{
		std::cout << "Removing circuit" << std::endl;
	}

	void add_qbit(qbit* qbit_a);
	void add_components(std::vector<component*> new_component);

	void setup_circuit(std::vector<qbit*> qbit_b, std::vector<component*> inputs);
	void run_circuit();
};

#endif