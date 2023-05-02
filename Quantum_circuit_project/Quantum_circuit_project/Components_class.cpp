#include "Components_class.h"

//-- Components --

// Constructor for the identity gate
identity::identity()
{
	gate(1, 1) = 1;	gate(1, 2) = 0;	gate(2, 1) = 0;	gate(2, 2) = 1;
}

// Returns the identity gate matrix
matrix identity::get_matrix() const
{
	return gate;
}

// Returns the symbol of the identity gate
std::vector<std::string> identity::print_component_symbol() const
{
	return { "-----", "" };
}

// Constructor for the hadamard gate
hadamard::hadamard()
{
	gate(1, 1) = 1 / sqrt(2);	gate(1, 2) = 1 / sqrt(2);	gate(2, 1) = 1 / sqrt(2);	gate(2, 2) = -1 / sqrt(2);
}

// Returns the hadamard gate matrix
matrix hadamard::get_matrix() const
{
	return gate;
}

// Returns the symbol of the hadamard gate
std::vector<std::string> hadamard::print_component_symbol() const
{
	return { "-|H|-", "" };
}

// Constructor for the phase gate
phase::phase()
{
	gate(1, 1) = 1;	gate(1, 2) = 0;	gate(2, 1) = 0;	gate(2, 2) = complex{ 0, 1 };
}

// Returns the phase gate matrix
matrix phase::get_matrix() const
{
	return gate;
};

// Returns the symbol of the phase gate
std::vector<std::string> phase::print_component_symbol() const
{
	return { "-|S|-", "" };
};

// Default constructor for the controlled hadamard gate
controlled_hadamard::controlled_hadamard()
{
	std::unique_ptr<component> hadamard_gate = std::make_unique<hadamard>();
	std::unique_ptr<identity> identity_gate = std::make_unique<identity>();
	std::unique_ptr<qbit> qbit_0 = std::make_unique<qbit>(0);
	std::unique_ptr<qbit> qbit_1 = std::make_unique<qbit>(1);

	gate = identity_gate->get_matrix() ^ (qbit_0->get_matrix() * qbit_0->get_matrix().transpose());
	gate += hadamard_gate->get_matrix() ^ (qbit_1->get_matrix() * qbit_1->get_matrix().transpose());
}

// Parameterised constructor for the controlled hadamard gate
controlled_hadamard::controlled_hadamard(int i)
{
	try {
		if (i != 1 && i != 0) {
			throw std::invalid_argument("Must set control gate to act on either inital (0) or parrallel (1) qbit.");
		}
		std::unique_ptr<component> hadamard_gate = std::make_unique<hadamard>();
		std::unique_ptr<identity> identity_gate = std::make_unique<identity>();
		std::unique_ptr<qbit> qbit_0 = std::make_unique<qbit>(0);
		std::unique_ptr<qbit> qbit_1 = std::make_unique<qbit>(1);

		if (i == 0) {
			gate = identity_gate->get_matrix() ^ (qbit_0->get_matrix() * qbit_0->get_matrix().transpose());
			gate += hadamard_gate->get_matrix() ^ (qbit_1->get_matrix() * qbit_1->get_matrix().transpose());
		}
		else {
			gate = (qbit_0->get_matrix() * qbit_0->get_matrix().transpose()) ^ identity_gate->get_matrix();
			gate += (qbit_1->get_matrix() * qbit_1->get_matrix().transpose()) ^ hadamard_gate->get_matrix();
		}
	}
	catch (std::invalid_argument& error) {
		std::cerr << "Error: " << error.what() << std::endl;
	}

}

// Returns the controlled hadamard gate matrix
matrix controlled_hadamard::get_matrix() const
{
	return gate;
}

// Returns the symbol of the controlled hadamard gate
std::vector<std::string> controlled_hadamard::print_component_symbol() const
{
	return { "--x--", "  |  ", "-|H|-", "" };
}