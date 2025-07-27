#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <string>
#include <iostream>

struct Employee {
    int id;
    std::string name;
    std::string department;
    float salary;

    Employee() : id(0), salary(0.0f) {}

    Employee(int empId, const std::string &empName, const std::string &empDept, float empSalary) {
        id = empId;
        name = empName;
        department = empDept;
        salary = empSalary;
    }

    // For debugging purposes
    void print() const {
        std::cout << id << ", " << name << ", " << department << ", " << salary << std::endl;
    }
};

#endif
