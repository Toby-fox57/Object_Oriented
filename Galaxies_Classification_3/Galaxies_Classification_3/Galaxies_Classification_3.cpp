// PHYS 30762 Programming in C++
// Assignment 3: Galaxies and their classification
// Tobias Fox 10475873

#include <iostream>
#include <iomanip>
#include <vector>

enum classification { E0_7, S0, Sa, Sb, Sc, SBa, SBb, SBc, Irr };
std::vector<std::string> classification_string = { "E0_7", "S0", "Sa", "Sb", "Sc", "SBa", "SBb", "SBc", "Irr" };

class galaxy
{
private:
    std::string galaxy_name;
    classification hubble_type;
    double redshift;
    double total_mass;
    double stellar_mass_fraction;
    std::vector<galaxy> satellites;
    int number_of_satellites = 0;

public:
    // Default constructor
    galaxy() = default;
    // Parameterised constructor
    galaxy(std::string name, classification galaxy_type, double galaxy_z, double galaxy_m, double f_star) :
        galaxy_name(name), hubble_type(galaxy_type), redshift(galaxy_z), total_mass(galaxy_m),
        stellar_mass_fraction(f_star)
    {}
    // Destructor
    ~galaxy()
    {
        std::cout << "Removing galaxy" << std::endl;
    }

    // Print out galaxy's data
    void print_data(int is_satellite);

    // Change the galaxy type
    void change_galaxy_type(classification new_type)
    {
        hubble_type = new_type;
    }

    // Calculate galaxy mass fraction
    double stellar_mass()
    {
        return stellar_mass_fraction * total_mass;
    }

    // Add a satellite
    void add_satellite(std::string satellite_name, classification satellite_type, double satellite_z, double satellite_m)
    {
        satellites.push_back(galaxy(satellite_name, satellite_type, satellite_z, satellite_m));
        number_of_satellites++;
    }
};

void galaxy::print_data(int is_satellite = 0)
{
    if (is_satellite == 0) {
        std::cout << "--Galaxy--" << std::endl;
    }
    std::cout << "Galaxy name: " << galaxy_name << std::endl;
    std::cout << "Hubble type: " << classification_string[hubble_type] << std::endl;
    std::cout << "Redshift: " << std::setprecision(3) << redshift << std::endl;
    std::cout << "Total mass: " << std::setprecision(3) << total_mass << std::endl;
    std::cout << "Stellar mass fraction: " << std::setprecision(3) << stellar_mass_fraction << std::endl;
    std::cout << "Number of satellites: " << number_of_satellites << std::endl;
    for (auto satellites_it = satellites.begin(); satellites_it < satellites.end(); satellites_it++) {
        std::cout << "--Satellite--" << std::endl;
        satellites_it->print_data(1);
    }
    if (is_satellite == 0) {
        std::cout << "\n";
    }
}

int main()
{
    // Adds  way to the class
    galaxy milky_way("Milky Way", Sa, 0, 1.15e12, 0.03);
    milky_way.print_data();

    // Uses the member functions in the class
    milky_way.change_galaxy_type(Sb);
    std::cout << "The stellar mass: " << milky_way.stellar_mass() << std::endl;
    milky_way.add_satellite("Small Magellanic Cloud", Irr, 0.000527, 7e9);
    milky_way.print_data();

    // Add objects to the class galaxy
    std::vector<galaxy> galaxies;

    galaxies.push_back(milky_way);
    galaxies.push_back(galaxy("Andromeda", Sa, -0.001004, 1.5e12, 0.01));
    galaxies.push_back(galaxy("Messier 87", E0_7, 0.00428, 2.4e12, 0.03));

    // Prints the list of objects and their properties
    for (auto galaxies_it = galaxies.begin(); galaxies_it < galaxies.end(); galaxies_it++) {
        galaxies_it->print_data();
    }
    return 0;
}