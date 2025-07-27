#include "include/employee.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <chrono>

// Load employees from CSV
std::vector<Employee> loadEmployees(const std::string &filename) {
    std::vector<Employee> employees;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Unable to open input file: " << filename << std::endl;
        return employees;
    }

    std::string line;
    getline(file, line); // Skip header line

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name, department, salaryStr;
        if (getline(ss, idStr, ',') &&
            getline(ss, name, ',') &&
            getline(ss, department, ',') &&
            getline(ss, salaryStr, ',')) 
        {
            int id = std::stoi(idStr);
            float salary = std::stof(salaryStr);
            employees.emplace_back(id, name, department, salary);
        }
    }

    file.close();
    return employees;
}

// Save employees to CSV
void saveEmployees(const std::string &filename, const std::vector<Employee> &employees) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Unable to open output file: " << filename << std::endl;
        return;
    }

    file << "EmployeeID,Name,Department,Salary\n";
    for (const auto &e : employees) {
        file << e.id << "," << e.name << "," << e.department << "," << e.salary << "\n";
    }
    file.close();
}

// Measure execution time for sorting
template <typename Func>
double measureExecutionTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}
