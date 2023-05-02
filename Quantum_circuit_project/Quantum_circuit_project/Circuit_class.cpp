#include "Circuit_class.h"

//-- Circuits --

// Parameterised constructor for the circuit class
circuit::circuit(int number_of_initalised_qbits)
{
	for (int i{ 0 }; i < number_of_initalised_qbits; i++) {
		qbits.push_back(std::make_shared<qbit>(0));
	}
};

// Defines a function to add a qbit to the circuit
void circuit::add_qbit(const int i)
{
	try {
		if (components.empty() == false) {
			throw std::invalid_argument("Can not add qbits once components have been added.");
		}
		qbits.push_back(std::make_shared<qbit>(i));
		number_of_qbits += 1;

	} catch (std::invalid_argument& error) {
		std::cerr << "Error: " << error.what() << std::endl;
	}
};

// Defines a function to add a components to the circuit
void circuit::add_components(const std::shared_ptr<component> new_component) {
	try {
		if (number_of_qbits != 0) {
			throw std::invalid_argument("Can not add component to this circuit");
		}

		components.push_back(new_component);
		number_of_square_matrices += 1;

	} catch (std::invalid_argument& error) {
		std::cerr << "Error: " << error.what() << std::endl;
		if (number_of_qbits == 0) {
			std::cerr << "Add a qbit to constructor this circuit." << std::endl;
		} else{
			std::cerr << "Too many qbits, add components using a vector." << std::endl;
		}
	}
}

// Defines a function to add a column of components equal to the number of qbits
void circuit::add_components(const std::vector<std::shared_ptr<component>> parrallel_components)
{
	int matrix_length{ 0 };
	
	for (const auto new_component : parrallel_components) {
		matrix_length += new_component->get_matrix().get_rows();
	}

	try {
		if ((matrix_length / 2) != number_of_qbits)	{
			throw std::invalid_argument("Incorrect amount of components");
		}
		for (const auto new_component : parrallel_components) {
			for (int k{ 0 }; k < (new_component->get_matrix().get_rows() / 2); k++) {
				components.push_back(new_component);
				number_of_square_matrices += 1;
			}
		}
	}
	catch (std::invalid_argument& error) {
		std::cerr << "Error: " << error.what() << std::endl;
		if (matrix_length / 2 < number_of_qbits) {
			std::cerr << "Not enough components inputted" << std::endl;
		} else {
			std::cerr << "Too many components inputted" << std::endl;
		}
	}	
}

// Defines a function to set the state of a qbit in the circuit
void circuit::change_state_of_qbit(const int qbit_register_position, const int qbit_state) 
{
	try {
		if (qbit_state != 0 && qbit_state != 1) {
			throw std::invalid_argument("Qbit can only set to state 0 or 1");
		}
		qbits[qbit_register_position]->set_state(qbit_state);
	}
	catch (std::invalid_argument& error) {
		std::cerr << "Error :" << error.what() << std::endl;
	}
}

// Defines a function to remove all the components
void circuit::remove_components() {
	components.clear();
};

// Defines a function to remove all the qbits
void circuit::remove_qbits() {
	try {
		if (number_of_square_matrices > 0) {
			throw std::invalid_argument("Must remove components before removing qbits");
		}
		qbits.clear();
	}
	catch (std::invalid_argument& error) {
		std::cerr << "Error: " << error.what() << std::endl;
	}
};

// Defines a function to run the circuit
void circuit::run_circuit()
{
	try {
		matrix qbit_register;

		for (const auto next_qbit : qbits) {
			qbit_register ^= next_qbit->get_matrix();
		}

		for (int i{ 0 }; i < (number_of_square_matrices / number_of_qbits); i++) {
			matrix in_parallel;

			for (int j{ 0 }; j < number_of_qbits; j++) {
				in_parallel ^= components[(i * number_of_qbits) + j]->get_matrix();
				j += (std::log(components[(i * number_of_qbits) + j]->get_matrix().get_rows()) / std::log(2)) - 1;
			}

			qbit_register = in_parallel * qbit_register;
		}

		std::cout << "Final state = \n" << std::endl;
		std::cout << qbit_register << std::endl;

	} catch (std::out_of_range& error) {
		std::cerr << "Error: " << error.what() << std::endl;

		if (qbits.empty()) {
			std::cerr << "Qbits need to be added to run this ciruit" << std::endl;

		} else if (components.empty()) {
			std::cerr << "Components need to be added to run this ciruit" << std::endl;

		} else {
			std::cerr << "Qbits or components out of range" << std::endl;

		}
		exit(1);
	}
}

// Overloads the << operator to print the circuit diagram
std::ostream& operator<<(std::ostream& os, const circuit& cir)
{
	os << "Circuit diagram: \n" << std::endl;

	std::vector<std::stringstream> output;
	output.resize(cir.number_of_qbits * 2);

	for (int i{ 0 }; i < cir.number_of_square_matrices; i++) {

		for (int j{ 0 }; j < (std::log(cir.components[i]->get_matrix().get_rows()) / std::log(2)) + 1; j++) {
			output[(i % cir.number_of_qbits) * 2 + j] << std::setw(5) << (cir.components[i]->print_component_symbol()[j]);
			if (j > 1 && j % 2 == 0) {
				i++;
			}
		}
	}

	for (int m{ 0 }; m < cir.number_of_qbits * 2; m++) {
		os << output[m].str() << std::endl;
	}

	return os;
}


