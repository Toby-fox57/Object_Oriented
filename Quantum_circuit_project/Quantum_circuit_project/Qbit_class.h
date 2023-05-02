#ifndef QBIT_CLASS_QUANTUM_CIRCUIT
#define QBIT_CLASS_QUANTUM_CIRCUIT

// Declares a class for a qbit
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
	matrix get_matrix() const;
};

#endif