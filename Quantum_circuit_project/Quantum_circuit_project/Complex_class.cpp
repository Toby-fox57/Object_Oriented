#include "Complex_class.h"

// -- Complex --

double complex::get_real() const
{
	return real_part;
}

double complex::get_imaginary() const
{
	return imaginary_part;
}

void complex::set_complex(const double real_input, const double imaginary_input)
{
	real_part = real_input;
	imaginary_part = imaginary_input;
}

complex complex::complex_conjugate() const
{
	complex temp{ real_part, imaginary_part * -1 };
	return temp;
}

complex complex::operator+(const complex& z) const
{
	complex temp{ real_part + z.real_part, imaginary_part + z.imaginary_part };
	return temp;
}

complex complex::operator+=(const complex& z) {
	*this = *this + z;

	return *this;
};

complex complex::operator-(const complex& z) const
{
	complex temp{ real_part - z.real_part, imaginary_part - z.imaginary_part };
	return temp;
}

complex complex::operator*(const complex& z) const
{
	complex temp{ real_part * z.real_part + imaginary_part * z.imaginary_part, real_part * z.imaginary_part + imaginary_part * z.real_part };
	return temp;
}

std::ostream& operator<<(std::ostream& os, const complex& z)
{
	std::stringstream complex_number;

	if (z.imaginary_part > 0) {
		complex_number << z.real_part << "+" << z.imaginary_part << "i";
	}
	else if (z.imaginary_part == 0) {
		complex_number << z.real_part;
	}
	else if (z.real_part == 0) {
		complex_number << z.imaginary_part << "i";
	}
	else {
		complex_number << z.real_part << z.imaginary_part << "i";
	}

	os << complex_number.str();

	return os;
}