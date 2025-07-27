#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <filesystem> 
#include "../include/employee.hpp"
#include "../utils.cpp"

using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;

void insertionSort(vector<Employee> &arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        Employee key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].id > key.id) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void runInsertionSort(const string &inputPath, const string &outputPath,
                      const string &scenario, int size,
                      ofstream &perfFile) {
    vector<Employee> employees = loadEmployees(inputPath);
    if (employees.empty()) {
        cerr << "Unable to open input file: " << inputPath << endl;
        return;
    }

    auto start = high_resolution_clock::now();
    insertionSort(employees);
    auto end = high_resolution_clock::now();

    double duration = duration_cast<milliseconds>(end - start).count() / 1000.0;
    cout << "Insertion Sort:\n" << inputPath << " Time Taken: " << duration << " seconds\n";

    saveEmployees(outputPath, employees);
    perfFile << scenario << "," << size << "," << duration << "\n";
}

int main() {
    string datasetDir = "dataset/";             // Relative to LAB-2
    string sortedDir = "sorted_output/";
    string perfFilePath = "performance/insertion_sort.csv";

    // Ensure output directories exist
    fs::create_directories(sortedDir);
    fs::create_directories("performance");

    ofstream perfFile(perfFilePath);
    if (!perfFile.is_open()) {
        cerr << "Unable to open performance file: " << perfFilePath << endl;
        return 1;
    }
    perfFile << "Scenario,Input Size,Time Taken\n";

    // Best Case
    runInsertionSort(datasetDir + "ascending_employees_5000.csv", sortedDir + "insertion_sorted_5000.csv", "Best Case", 5000, perfFile);
    runInsertionSort(datasetDir + "ascending_employees_10000.csv", sortedDir + "insertion_sorted_10000.csv", "Best Case", 10000, perfFile);
    runInsertionSort(datasetDir + "ascending_employees_20000.csv", sortedDir + "insertion_sorted_20000.csv", "Best Case", 20000, perfFile);

    // Worst Case
    runInsertionSort(datasetDir + "descending_employees_5000.csv", sortedDir + "insertion_sorted_5000_desc.csv", "Worst Case", 5000, perfFile);
    runInsertionSort(datasetDir + "descending_employees_10000.csv", sortedDir + "insertion_sorted_10000_desc.csv", "Worst Case", 10000, perfFile);
    runInsertionSort(datasetDir + "descending_employees_20000.csv", sortedDir + "insertion_sorted_20000_desc.csv", "Worst Case", 20000, perfFile);

    // Average Case
    runInsertionSort(datasetDir + "random_employees_5000.csv", sortedDir + "insertion_sorted_5000_rand.csv", "Average Case", 5000, perfFile);
    runInsertionSort(datasetDir + "random_employees_10000.csv", sortedDir + "insertion_sorted_10000_rand.csv", "Average Case", 10000, perfFile);
    runInsertionSort(datasetDir + "random_employees_20000.csv", sortedDir + "insertion_sorted_20000_rand.csv", "Average Case", 20000, perfFile);

    perfFile.close();
    return 0;
}
