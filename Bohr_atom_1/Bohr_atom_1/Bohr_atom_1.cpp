// PHYS 30762 Programming in C++
// Assignment 1: The Bohr Atom
// Tobias Fox 10475873

#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

int input_positive_integer()
{
	// Function to make sure the input is a positive integar
	int positive_integer;
	std::cin >> positive_integer;

	while (positive_integer < 1 || cin.fail()) {
		cin.clear(); cin.ignore(512, '\n');
		std::cout << "Please enter a positive integer" << std::endl;
		std::cin >> positive_integer;
	}
	cin.clear(); cin.ignore(512, '\n');
	return positive_integer;
}

int main()
{
	// Declare Varibles
	const double ev_to_joules = 1.602e-19; double delta_e;
	std::string repeat_y_n = "y"; std::string joules_or_ev; std::string repeat_answer;

	while (repeat_y_n == "y") {
		int atomic_number; int n_initial = 0; int n_final = 1;

		//Ask user to input atomic number
		std::cout << "Please enter the atomic number" << std::endl;
		atomic_number = input_positive_integer();

		//Ask user to input initial and final quantum number
		while (n_initial < n_final) {
			std::cout << "Please enter the initial principal quantum number" << std::endl;
			n_initial = input_positive_integer();
			std::cout << "Please enter the final principal quantum number" << std::endl;
			n_final = input_positive_integer();
			if (n_initial >= n_final) {
				break;
			}
			std::cout << "Error n_in < n_fin" << std::endl;
		}

		//Ask user to input the units
		std::cout << "Please enter the units, J or e" << std::endl;
		std::cin >> joules_or_ev;

		//Compute and output delta_E based of selected units
		while ((joules_or_ev == "J" || joules_or_ev == "e" || joules_or_ev == "j" || joules_or_ev == "E") == 0) {
			std::cout << "Please enter a valid input\n" << std::endl;
			std::cin >> joules_or_ev;
		}

		if (joules_or_ev == "J" || joules_or_ev == "j") {
			delta_e = 13.6 * pow(atomic_number, 2) * ((1 / pow(n_final, 2) - (1 / pow(n_initial, 2)))) * ev_to_joules;
			std::cout << "The change in energy is " << std::setprecision(4) << delta_e << " J\n" << std::endl;
		}
		else if (joules_or_ev == "e" || joules_or_ev == "E") {
			delta_e = 13.6 * pow(atomic_number, 2) * ((1 / pow(n_final, 2) - (1 / pow(n_initial, 2))));
			std::cout << "The change in energy is " << std::setprecision(4) << delta_e << " eV\n" << std::endl;
		}

		//Ask user if they would like to repeat
		std::cout << "Would you like to repeat the calculation?" << std::endl;
		std::cin >> repeat_answer;

		while ((repeat_answer == "n" || repeat_answer == "y") == 0) {
			std::cout << "Please input y or n?" << std::endl;
			std::cin >> repeat_answer;
		}
		repeat_y_n = repeat_answer;
	}
	return 0;
}