#ifndef COMPONENT_CLASS_QUANTUM_CIRCUIT
#define COMPONENT_CLASS_QUANTUM_CIRCUIT

// Declares an abstract base class for all the quantum circuit components
class component
{
public:
	virtual ~component() {};

	virtual matrix get_matrix() const = 0;
	virtual std::vector<std::string> print_component_symbol() const = 0;
};

// Declares a dervied class for the identity gate
class identity : public component
{
private:
	matrix gate{ 2, 2 };

public:
	identity();
	~identity()
	{
		std::cout << "Removing identity gate" << std::endl;
	}

	matrix get_matrix() const;
	std::vector<std::string> print_component_symbol() const;
};

// Declares a dervied class for a hadamard
class hadamard : public component
{
private:
	matrix gate{ 2, 2 };

public:
	hadamard();
	~hadamard()
	{
		std::cout << "Removing hadamard gate" << std::endl;
	}

	matrix get_matrix() const;
	std::vector<std::string> print_component_symbol() const;
};

class phase : public component
{
private:
	matrix gate{ 2, 2 };

public:
	phase();
	~phase() 
	{
		std::cout << "Removing phase gate" << std::endl;
	}

	matrix get_matrix() const;
	std::vector<std::string> print_component_symbol() const;
};

class controlled_hadamard : public component
{
private:
	matrix gate{ 4, 4 };

public:
	controlled_hadamard();
	controlled_hadamard(int i);
	~controlled_hadamard()
	{
		std::cout << "Removing controlled hadamard gate" << std::endl;
	}

	matrix get_matrix() const;
	std::vector<std::string> print_component_symbol() const;
};

#endif