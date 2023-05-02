#include "Qbit_class.h"

//-- Qbit --

// Parameterised constructor for the class qbit
qbit::qbit(int inital_state)
{
	try {
		if (inital_state != 0 && inital_state != 1) {
			throw std::invalid_argument("A qbit can only be initalised in state 0 or 1.");
		}
		state(1, 1) = (inital_state == 0) ? 1 : 0;
		state(2, 1) = (inital_state == 0) ? 0 : 1;

	}
	catch (std::invalid_argument& error) {
		std::cerr << "Error: " << error.what() << std::endl;
	}
}

// Defines a function to set the state of a qbit
void qbit::set_state(int new_state)
{
	try {
		if (new_state != 0 && new_state != 1) {
			throw std::invalid_argument("A qbit can only be initalised in state 0 or 1.");
		}
		state(1, 1) = (new_state == 0) ? 1 : 0;
		state(2, 1) = (new_state == 0) ? 0 : 1;

	}
	catch (std::invalid_argument& error) {
		std::cerr << "Error: " << error.what() << std::endl;
	}
}

// Returns a matrix containing the state of a qbit
matrix qbit::get_matrix() const
{
	return state;
}