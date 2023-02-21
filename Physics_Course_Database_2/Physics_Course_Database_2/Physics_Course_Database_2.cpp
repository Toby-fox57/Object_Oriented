// PHYS 30762 Programming in C++
// Assignment 2: Physics Course Database
// Tobias Fox 10475873

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector >
#include <iomanip>

void get_data(std::fstream& file_data, std::vector<double>& column_1, std::vector<int>& column_2, std::vector<std::string>& column_3, int& number_of_lines, char year)
{
    // Function to turn the file stream into vectors for each column
    std::string temp_line;

    while (getline(file_data, temp_line)) {
        std::string temp; std::string temp_column_3;
        std::stringstream line_stream(temp_line);
        std::vector<std::string> line_vector;

        while (getline(line_stream, temp, ' ')) {
            line_vector.push_back(temp);
        }

        if (year == '0' || line_vector[1][0] == year) {
            column_1.push_back(stod(line_vector[0]));
            column_2.push_back(stoi(line_vector[1]));
            for (int i = 4; i < line_vector.size(); i++) {
                temp_column_3 += line_vector[i] += " ";
            }
            column_3.push_back(temp_column_3);

            number_of_lines++;
        }
    }
}

void input_valid_y_n(char& input_char)
{
    // Function to make sure the input is a valid year
    std::cin >> input_char;

    while (input_char != 'y' && input_char != 'n' || std::cin.fail()) {
        std::cin.clear(); std::cin.ignore(512, '\n');
        std::cout << "Please enter a y or n: ";
        std::cin >> input_char;
    }
    std::cin.clear(); std::cin.ignore(512, '\n');
}

void input_valid_year(char& input_year)
{
    // Function to check if the use inputs a valid year
    std::cin >> input_year;

    while (input_year != '1' && input_year != '2' && input_year != '3' && input_year != '4' || std::cin.fail()) {
        std::cin.clear(); std::cin.ignore(512, '\n');
        std::cout << "Please enter a valid year: ";
        std::cin >> input_year;
    }
    std::cin.clear(); std::cin.ignore(512, '\n');
}

void print_course_list(std::vector<int> course_codes, std::vector<std::string> course_names, int number_of_courses)
{
    // Function to print course list
    for (int j = 0; j < number_of_courses; j++) {
        std::stringstream course_code_and_name;
        course_code_and_name << course_codes[j] << " " << course_names[j] << "\n";
        std::cout << course_code_and_name.str() << std::endl;
    }
}

void computations(std::vector<double> grades, int number_of_courses, double& mean, double &standard_deviation, double& standard_error_of_mean) 
{
    // Function to calculate the results
    for (int k = 0; k < number_of_courses; k++) {
        mean += grades[k];
    }
    mean /= number_of_courses;
    for (int l = 0; l < number_of_courses; l++) {
        standard_deviation += pow(grades[l] - mean, 2);
    }
    standard_deviation = pow(standard_deviation / number_of_courses, 0.5);
    standard_error_of_mean = standard_deviation / pow(number_of_courses, 0.5);
}

int main() 
{
    const std::string default_location = "courselist.dat";
    char y_n_access_data = 'y';

    // Ask user to enter filename
    std::string file_name;
    std::cout << "Enter data filename or type default: ";
    std::cin >> file_name;
    if (file_name == "default") {
        std::cout << "The default file location is courselist.dat" << std::endl;
        file_name = default_location;
    }

    while (y_n_access_data == 'y') {
        // Open file and check if successful
        std::fstream course_stream(file_name);

        if (!course_stream.good()) {
            std::cout << "File could not be opened." << std::endl;
            std::cout << "Please enter a valid file name or type default: ";
            std::cin >> file_name;
            if (file_name == "default") {
                std::cout << "The default file location is courselist.dat" << std::endl;
                file_name = default_location;
            }
            course_stream.clear();
            course_stream.open(file_name);
        }
        else if (course_stream.fail()) {
            std::cout << "Error! File data could not be read." << std::endl;
            return 1;
        }

        // Determines if to access full data or for specific year
        char y_n_full_data; char year; char y_n_course_list; char y_n_compute;

        std::cout << "Would you like to access the full course list for every year? Enter y or n: ";
        input_valid_y_n(y_n_full_data);

        if (y_n_full_data == 'n') {
            std::cout << "Please specify a year. Enter 1, 2, 3 or 4: ";
            input_valid_year(year);
        }
        else {
            year = '0';
        }

        // Allocate memory for data
        std::vector<double> grades; std::vector<int> course_codes; std::vector<std::string> course_names;
        int number_of_courses = 0;  int year_number_of_courses = 0;

        // Read data from file
        get_data(course_stream, grades, course_codes, course_names, number_of_courses, year);

        // Close file
        course_stream.close();

        // Print number of courses read in
        std::cout << "Number of courses read in: " << number_of_courses << std::endl;

        // Prints course list
        std::cout << "Would you like to print the course list? Please enter y or n: ";
        input_valid_y_n(y_n_course_list);

        if (y_n_course_list == 'y') {
            std::cout << "\n-- Course list --" << std::endl;
            print_course_list(course_codes, course_names, number_of_courses);
            std::cout << "\n" << std::endl;
        }

        // Compute mean, standard deviation and  standard error of mean
        double mean = 0; double standard_deviation = 0; double standard_error_of_mean;

        std::cout << "Would you like to compute the mean, standard deviation and standard error of mean? Please enter y or n: ";
        input_valid_y_n(y_n_compute);

        if (y_n_compute == 'y') {
            std::cout << "\n-- Computations --" << std::endl;
            computations(grades, number_of_courses, mean, standard_deviation, standard_error_of_mean);

            std::cout << "Mean grade = " << std::setprecision(3) << mean << std::endl;
            std::cout << "Standard Deviation = " << std::setprecision(2) << standard_deviation << std::endl;
            std::cout << "Standard Error = " << std::setprecision(2) << standard_error_of_mean << "\n" << std::endl;
        }

        // Ask user if to access the data again
        std::cout << "Would you like to access the data again? Please enter y or n: ";
        input_valid_y_n(y_n_access_data);
    }
    return 0;
}