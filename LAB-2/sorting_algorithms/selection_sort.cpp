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

void selectionSort(vector<Employee> &arr) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        size_t minIdx = i;
        for (size_t j = i + 1; j < arr.size(); j++) {
            if (arr[j].id < arr[minIdx].id) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

void runSelectionSort(const string &inputPath, const string &outputPath,
                      const string &scenario, int size,
                      ofstream &perfFile) {
    vector<Employee> employees = loadEmployees(inputPath);
    if (employees.empty()) {
        cerr << "Unable to open input file: " << inputPath << endl;
        return;
    }

    auto start = high_resolution_clock::now();
    selectionSort(employees);
    auto end = high_resolution_clock::now();

    double duration = duration_cast<milliseconds>(end - start).count() / 1000.0;
    cout << "Selection Sort:\n" << inputPath << " Time Taken: " << duration << " seconds\n";

    saveEmployees(outputPath, employees);
    perfFile << scenario << "," << size << "," << duration << "\n";
}

int main() {
    string datasetDir = "dataset/";
    string sortedDir = "sorted_output/";
    string perfFilePath = "performance/selection_sort.csv";

    fs::create_directories(sortedDir);
    fs::create_directories("performance");

    ofstream perfFile(perfFilePath);
    if (!perfFile.is_open()) {
        cerr << "Unable to open performance file: " << perfFilePath << endl;
        return 1;
    }
    perfFile << "Scenario,Input Size,Time Taken\n";

    // Best Case
    runSelectionSort(datasetDir + "ascending_employees_5000.csv", sortedDir + "selection_sorted_5000.csv", "Best Case", 5000, perfFile);
    runSelectionSort(datasetDir + "ascending_employees_10000.csv", sortedDir + "selection_sorted_10000.csv", "Best Case", 10000, perfFile);
    runSelectionSort(datasetDir + "ascending_employees_20000.csv", sortedDir + "selection_sorted_20000.csv", "Best Case", 20000, perfFile);

    // Worst Case
    runSelectionSort(datasetDir + "descending_employees_5000.csv", sortedDir + "selection_sorted_5000_desc.csv", "Worst Case", 5000, perfFile);
    runSelectionSort(datasetDir + "descending_employees_10000.csv", sortedDir + "selection_sorted_10000_desc.csv", "Worst Case", 10000, perfFile);
    runSelectionSort(datasetDir + "descending_employees_20000.csv", sortedDir + "selection_sorted_20000_desc.csv", "Worst Case", 20000, perfFile);

    // Average Case
    runSelectionSort(datasetDir + "random_employees_5000.csv", sortedDir + "selection_sorted_5000_rand.csv", "Average Case", 5000, perfFile);
    runSelectionSort(datasetDir + "random_employees_10000.csv", sortedDir + "selection_sorted_10000_rand.csv", "Average Case", 10000, perfFile);
    runSelectionSort(datasetDir + "random_employees_20000.csv", sortedDir + "selection_sorted_20000_rand.csv", "Average Case", 20000, perfFile);

    perfFile.close();
    return 0;
}
