// PHYS 30762 Programming in C++
// Project: Quantum circuit
// Tobias Fox 10475873

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include "Quantum_circuit_class.h"
#include "Quantum_circuit_class.cpp"

int main()
{
    circuit circuit_a;

    component* hadamard_gate = new hadamard;
    component* identity_gate = new identity;

    std::vector<component*> component_library = { identity_gate, hadamard_gate };

    qbit* qbit_1 = new qbit{ 1 };
    qbit* qbits_0 = new qbit{ 0 };

    std::vector<component*> circuit_components = { component_library[1], component_library[0] };
    std::vector<qbit*> qbits = { qbit_1, qbits_0 };
   
    circuit_a.add_qbit(qbits[0]);
    circuit_a.add_qbit(qbits[1]);
    circuit_a.add_components(circuit_components);
    circuit_a.run_circuit();
   
    circuit_components.clear();
    qbits.clear();

    return 0;
};
