// PHYS 30762 Programming in C++
// Assignment 4: A Class for Complex Numbers
// Tobias Fox 10475873

#include<iostream>
#include<cmath>
#include<string>
#include <sstream>

class complex
{
	// Make function to overload operator<< a friend
	friend std::ostream& operator<<(std::ostream& os, const complex& z);
	friend std::istream& operator>>(std::istream& is, complex& z);

private:
	double re, im;

public:
	// Constructors & destructor
	complex() = default;
	complex(double r, double i): 
		re{ r }, im{ i }
	{}
	~complex() 
	{
		std::cout << "Removing complex number" << std::endl;
	}

	// Return real component
	double real_part()
	{
		return re;
	}

	// Return imaginary component
	double imaginary_part()
	{
		return im;
	}

	// Return modulus
	double modulus()
	{
		return pow(pow(re, 2) + pow(im, 2), 0.5);
	}

	// Return argument
	double argument()
	{
		return atan(im / re);
	}

	// Return complex conjugate
	complex complex_conjugate() const
	{
		complex temp{ re, im * -1 };
		return temp;
	}

	// Overload + operator for addition
	complex operator+(const complex &z) const
	{
		complex temp{ re + z.re, im + z.im };
		return temp;
	}

	// Overload - operator for subtraction
	complex operator-(const complex& z) const
	{
		complex temp{ re - z.re, im - z.im };
		return temp;
	}

	// Overload * operator for multiplication, z1*z2
	complex operator*(const complex& z) const
	{
		complex temp{ re * z.re, im * z.im };
		return temp;
	}

	// Overload / operator for division, z1/z2
	complex operator/(const complex& z) const
	{
		complex temp{ re / z.re, im / z.im };
		return temp;
	}

	// Input real part
	void set_real_imaginary(double real_input, double imaginary_input)
	{
		re = real_input;
		im = imaginary_input;
	}

	// Print properties of complex number
	void print_properties();
};

// Function to print complex number properties
void complex::print_properties()
{
	std::cout << "--Complex number's properties--" << std::endl;
	std::cout << "Real part = " << complex::real_part() << std::endl;
	std::cout << "Imaginary part = " << complex::imaginary_part() << std::endl;
	std::cout << "Real component = " << complex::modulus() << std::endl;
	std::cout << "Argument = " << complex::argument() << std::endl;
	std::cout << "\n";
}

// Function to overload << operator for complex numbers
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

// Function to overload >> operator for complex numbers
std::istream& operator>>(std::istream& is, complex& z)
{
	double real_input, imaginary_input;
	char sign, i_char;
	std::string input;

	while (true) {
		std::getline(is, input);
		std::stringstream ss(input);

		if (ss >> real_input >> sign >> imaginary_input >> i_char && (sign == '+' || sign == '-') && i_char == 'i') {
			if (sign == '+' || imaginary_input == 0) {
				z.set_real_imaginary(real_input, imaginary_input);
			}
			else if (sign == '-') {
				z.set_real_imaginary(real_input, imaginary_input * -1);
			}
			break;
		}
		else {
			std::cout << "Error. Please input using the format 'a+bi': ";
		}
	}
	return is;
}

int main()
{
	std::cout.precision(3);

	// Create two complex numbers
	complex a{ 3,4 };
	complex b{ 1,-2 };

	// Get real and imaginary components, modulus and argument
	std::cout << "Complex number a = " << a << std::endl;
	a.print_properties();
	std::cout << "Complex number b = " << b << std::endl;
	b.print_properties();

	// Get conjugates
	std::cout << "Complex conjugate of a = " << a.complex_conjugate() << std::endl;
	std::cout << "Complex conjugate of b = " << b.complex_conjugate() << std::endl;
	std::cout << "\n";

	// Get sum, difference, product and quotient of a and b
	complex sum{ a.operator+(b) };
	complex difference{ a.operator-(b) }; 
	complex product{ a.operator*(b) }; 
	complex quotient{ a.operator/(b) };

	// Print out results, also demonstrating use of overloaded operator<<
	std::cout << "Sum = " << sum << std::endl;
	std::cout << "Difference = " << difference << std::endl;
	std::cout << "Product = " << product << std::endl;
	std::cout << "Quotient = " << quotient << std::endl;
	std::cout << "\n";

	// Ask the user to input a complex number
	complex inputted_complex_number;
	std::cout << "Please enter an complex number in the form of 'a+bi': ";
	std::cin >> inputted_complex_number;
	std::cout << "Inputted complex number = " << inputted_complex_number << std::endl;

	return 0;
}
