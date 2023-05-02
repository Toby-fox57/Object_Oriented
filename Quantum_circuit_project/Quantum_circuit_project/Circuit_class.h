#ifndef CIRCUIT_CLASS_QUANTUM_CIRCUIT
#define CIRCUIT_CLASS_QUANTUM_CIRCUIT

// Declares a class for the circuit
class circuit
{
	friend std::ostream& operator<<(std::ostream& os, const circuit& cir);

private:
	std::vector<std::shared_ptr<qbit>> qbits;
	int number_of_qbits{ 0 };

	std::vector<std::shared_ptr<component>> components;
	int number_of_square_matrices{ 0 };

public:
	circuit() = default;
	circuit(int number_of_initalised_qbits);
	~circuit()
	{
		std::cout << "Removing circuit" << std::endl;
	}

	void add_qbit(const int i);
	void add_components(const std::vector<std::shared_ptr<component>> new_component);
	void add_components(const std::shared_ptr<component> new_component);

	void change_state_of_qbit(const int qbit_register_position, const int qbit_state);

	void remove_components();
	void remove_qbits();

	void setup_circuit(const std::vector<qbit*> qbit_b, const std::vector<component*> inputs);
	void run_circuit();
};

#endif