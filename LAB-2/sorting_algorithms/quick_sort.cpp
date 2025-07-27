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

int partition(vector<Employee> &arr, int low, int high) {
    int pivot = arr[high].id; // pivot element
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].id <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<Employee> &arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void runQuickSort(const string &inputPath, const string &outputPath,
                  const string &scenario, int size, ofstream &perfFile) {
    vector<Employee> employees = loadEmployees(inputPath);
    if (employees.empty()) {
        cerr << "Unable to open input file: " << inputPath << endl;
        return;
    }

    auto start = high_resolution_clock::now();
    quickSort(employees, 0, employees.size() - 1);
    auto end = high_resolution_clock::now();

    double duration = duration_cast<milliseconds>(end - start).count() / 1000.0;
    cout << "Quick Sort:\n" << inputPath << " Time Taken: " << duration << " seconds\n";

    saveEmployees(outputPath, employees);
    perfFile << scenario << "," << size << "," << duration << "\n";
}

int main() {
    string datasetDir = "dataset/";
    string sortedDir = "sorted_output/";
    string perfFilePath = "performance/quick_sort.csv";

    fs::create_directories(sortedDir);
    fs::create_directories("performance");

    ofstream perfFile(perfFilePath);
    if (!perfFile.is_open()) {
        cerr << "Unable to open performance file: " << perfFilePath << endl;
        return 1;
    }
    perfFile << "Scenario,Input Size,Time Taken\n";

    // Best Case
    runQuickSort(datasetDir + "ascending_employees_5000.csv", sortedDir + "quick_sorted_5000.csv", "Best Case", 5000, perfFile);
    runQuickSort(datasetDir + "ascending_employees_10000.csv", sortedDir + "quick_sorted_10000.csv", "Best Case", 10000, perfFile);
    runQuickSort(datasetDir + "ascending_employees_20000.csv", sortedDir + "quick_sorted_20000.csv", "Best Case", 20000, perfFile);

    // Worst Case
    runQuickSort(datasetDir + "descending_employees_5000.csv", sortedDir + "quick_sorted_5000_desc.csv", "Worst Case", 5000, perfFile);
    runQuickSort(datasetDir + "descending_employees_10000.csv", sortedDir + "quick_sorted_10000_desc.csv", "Worst Case", 10000, perfFile);
    runQuickSort(datasetDir + "descending_employees_20000.csv", sortedDir + "quick_sorted_20000_desc.csv", "Worst Case", 20000, perfFile);

    // Average Case
    runQuickSort(datasetDir + "random_employees_5000.csv", sortedDir + "quick_sorted_5000_rand.csv", "Average Case", 5000, perfFile);
    runQuickSort(datasetDir + "random_employees_10000.csv", sortedDir + "quick_sorted_10000_rand.csv", "Average Case", 10000, perfFile);
    runQuickSort(datasetDir + "random_employees_20000.csv", sortedDir + "quick_sorted_20000_rand.csv", "Average Case", 20000, perfFile);

    perfFile.close();
    return 0;
}
