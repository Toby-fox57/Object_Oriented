#ifndef COMPLEX_CLASS_QUANTUM_CIRCUIT
#define COMPLEX_CLASS_QUANTUM_CIRCUIT

// Declares a class for complex numbers
class complex
{
	friend std::ostream& operator<<(std::ostream& os, const complex& z);

private:
	double real_part, imaginary_part;

public:
	complex() = default;
	complex(double r, double i) : real_part{ r }, imaginary_part{ i } {}
	~complex() {}

	double get_real() const;
	double get_imaginary() const;

	void set_complex(const double real_input, const double imaginary_input);

	complex complex_conjugate() const;
	complex operator+(const complex& z) const;
	complex operator+=(const complex& z);

	complex operator-(const complex& z) const;

	complex operator*(const complex& z) const;

	template <typename type_z>
	complex& operator=(const type_z& z) {
		real_part = static_cast<type_z>(z);
		imaginary_part = 0;
		return *this;
	}
};

#endif