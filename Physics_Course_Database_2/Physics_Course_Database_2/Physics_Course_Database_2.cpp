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
#include <algorithm>

void get_data(std::fstream& file_data, std::vector<double>& column_1, std::vector<std::pair<int, std::string>>& column_2_3, int& number_of_lines, char year)
{
    // Function to turn the file stream into vectors for each column
    std::string temp_line;

    while (getline(file_data, temp_line)) {
        std::string temp; std::string temp_column_3;
        std::stringstream ss_line(temp_line);
        std::vector<std::string> line_vector;

        while (getline(ss_line, temp, ' ')) {
            line_vector.push_back(temp);
        }

        if (year == '0' || line_vector[1][0] == year) {
            column_1.push_back(stod(line_vector[0]));
            for (int i = 4; i < line_vector.size(); i++) {
                temp_column_3 += line_vector[i] += " ";
            }
            column_2_3.push_back(std::make_pair(stoi(line_vector[1]), temp_column_3));

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

void input_valid_0_1(int& input_int)
{
    // Function to check if the user inputs a valid integer
    std::cin >> input_int;

    while (input_int < 0 || input_int > 1 || std::cin.fail()) {
        std::cin.clear(); std::cin.ignore(512, '\n');
        std::cout << "Please enter a 0 or a 1: ";
        std::cin >> input_int;
    }
    std::cin.clear(); std::cin.ignore(512, '\n');
}

void input_valid_year(char& input_year)
{
    // Function to check if the user inputs a valid year
    std::cin >> input_year;

    while (input_year != '1' && input_year != '2' && input_year != '3' && input_year != '4' || std::cin.fail()) {
        std::cin.clear(); std::cin.ignore(512, '\n');
        std::cout << "Please enter a valid year: ";
        std::cin >> input_year;
    }
    std::cin.clear(); std::cin.ignore(512, '\n');
}

void print_course_list(std::vector<std::pair<int, std::string>> course_titles, int number_of_courses, int sort_by)
{
    // Sorts course titles
    if (sort_by == 0) {
        std::sort(course_titles.begin(), course_titles.end(), [](auto& left, auto& right) {return left.second < right.second; });
    }
    else {
        std::sort(course_titles.begin(), course_titles.end());
    }

    // Function to print course list
    for (int j = 0; j < number_of_courses; j++) {
        std::stringstream ss_course_title;
        ss_course_title << course_titles[j].first << " " << course_titles[j].second;
        std::cout << ss_course_title.str() << std::endl;
    }
}

void computations(std::vector<double> grades, int number_of_courses, double& mean, double& standard_deviation, double& standard_error_of_mean)
{
    // Function to calculate the results
    for (int k = 0; k < number_of_courses; k++) {
        mean += grades[k];
    }
    mean /= number_of_courses;
    for (int l = 0; l < number_of_courses; l++) {
        standard_deviation += pow(mean - grades[l], 2);
    }
    standard_deviation = pow(standard_deviation / (number_of_courses - 1), 0.5);
    standard_error_of_mean = standard_deviation / pow(number_of_courses, 0.5);
}

int main()
{
    const std::string default_location = "courselist.dat";
    char y_n_access_data = 'y';

    // Ask the user to enter the filename
    std::string file_name;
    std::cout << "Enter data filename or type default: ";
    std::cin >> file_name;
    if (file_name == "default") {
        std::cout << "The default file location is courselist.dat" << std::endl;
        file_name = default_location;
    }

    while (y_n_access_data == 'y') {
        // Open the file and check if successful
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

        // Determines if to access full data or for a specific year
        char y_n_full_data; char year; char y_n_course_list; int sort_by; char y_n_compute;

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
        std::vector<double> grades; std::vector<std::pair<int, std::string>> course_titles;
        int number_of_courses = 0;

        // Read data from the file
        get_data(course_stream, grades, course_titles, number_of_courses, year);

        // Close the file
        course_stream.close();

        // Print the number of courses reads in
        std::cout << "Number of courses read in: " << number_of_courses << std::endl;

        // Prints course list
        std::cout << "Would you like to print the course list? Please enter y or n: ";
        input_valid_y_n(y_n_course_list);

        if (y_n_course_list == 'y') {
            std::cout << "Would you like to sort the course list by course code or course title? Enter 0 for course name and 1 for course code: ";
            input_valid_0_1(sort_by);

            std::cout << "\n-- Course list --" << std::endl;
            print_course_list(course_titles, number_of_courses, sort_by);
            std::cout << "\n";
        }

        // Compute mean, standard deviation and  standard error of the mean
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