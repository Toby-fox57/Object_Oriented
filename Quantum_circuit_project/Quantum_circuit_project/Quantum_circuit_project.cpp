// PHYS 30762 Programming in C++
// Project: Quantum circuit
// Tobias Fox 10475873

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "Complex_class.h"
#include "Complex_class.cpp"
#include "Matrix_class.h"
#include "Matrix_class.cpp"
#include "Qbit_class.h"
#include "Qbit_class.cpp"
#include "Components_class.h"
#include "Components_class.cpp"
#include "Circuit_class.h"
#include "Circuit_class.cpp"

int main()
{
    //-- Define component library --

    std::shared_ptr<component> hadamard_gate = std::make_shared<hadamard>();
    std::shared_ptr<component> identity_gate = std::make_shared<identity>();
    std::shared_ptr<component> phase_gate = std::make_shared<phase>();
    std::shared_ptr<component> controlled_hadamard_gate = std::make_shared<controlled_hadamard>();

    std::map<std::string, std::shared_ptr<component>> component_library;

    component_library["identity"] = (identity_gate);
    component_library["hadamard"] = (hadamard_gate);
    component_library["phase"] = (phase_gate);
    component_library["controlled hadamard"] = (controlled_hadamard_gate);

    //-- Setup_circuit --

    circuit circuit_a;

    std::vector<std::shared_ptr<component>> components_parrellel;
    std::vector<std::shared_ptr<component>> components_parrellel_2;
    std::vector<std::shared_ptr<component>> components_parrellel_3;

    components_parrellel.push_back(component_library["identity"]);
    components_parrellel.push_back(component_library["phase"]);

    components_parrellel_2.push_back(component_library["controlled hadamard"]);

    components_parrellel_3.push_back(component_library["identity"]);
    components_parrellel_3.push_back(component_library["phase"]);

    circuit_a.add_qbit(0);
    circuit_a.add_qbit(1);

    circuit_a.add_components(components_parrellel);
    circuit_a.add_components(components_parrellel_2);
    circuit_a.add_components(components_parrellel_3);

    circuit_a.run_circuit();
    std::cout << circuit_a << std::endl;

    return 0;
};