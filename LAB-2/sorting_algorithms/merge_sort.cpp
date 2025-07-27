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

void merge(vector<Employee> &arr, int low, int mid, int high) {
    vector<Employee> temp;
    int i = low, j = mid + 1;

    while (i <= mid && j <= high) {
        if (arr[i].id <= arr[j].id) temp.push_back(arr[i++]);
        else temp.push_back(arr[j++]);
    }
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= high) temp.push_back(arr[j++]);

    for (int k = low; k <= high; k++) arr[k] = temp[k - low];
}

void mergeSort(vector<Employee> &arr, int low, int high) {
    if (low >= high) return;
    int mid = (low + high) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

void runMergeSort(const string &inputPath, const string &outputPath,
                  const string &scenario, int size,
                  ofstream &perfFile) {
    vector<Employee> employees = loadEmployees(inputPath);
    if (employees.empty()) {
        cerr << "Unable to open input file: " << inputPath << endl;
        return;
    }

    auto start = high_resolution_clock::now();
    mergeSort(employees, 0, employees.size() - 1);
    auto end = high_resolution_clock::now();

    double duration = duration_cast<milliseconds>(end - start).count() / 1000.0;
    cout << "Merge Sort:\n" << inputPath << " Time Taken: " << duration << " seconds\n";

    saveEmployees(outputPath, employees);
    perfFile << scenario << "," << size << "," << duration << "\n";
}

int main() {
    string datasetDir = "dataset/";
    string sortedDir = "sorted_output/";
    string perfFilePath = "performance/merge_sort.csv";

    fs::create_directories(sortedDir);
    fs::create_directories("performance");

    ofstream perfFile(perfFilePath);
    if (!perfFile.is_open()) {
        cerr << "Unable to open performance file: " << perfFilePath << endl;
        return 1;
    }
    perfFile << "Scenario,Input Size,Time Taken\n";

    // Best Case
    runMergeSort(datasetDir + "ascending_employees_5000.csv", sortedDir + "merge_sorted_5000.csv", "Best Case", 5000, perfFile);
    runMergeSort(datasetDir + "ascending_employees_10000.csv", sortedDir + "merge_sorted_10000.csv", "Best Case", 10000, perfFile);
    runMergeSort(datasetDir + "ascending_employees_20000.csv", sortedDir + "merge_sorted_20000.csv", "Best Case", 20000, perfFile);

    // Worst Case
    runMergeSort(datasetDir + "descending_employees_5000.csv", sortedDir + "merge_sorted_5000_desc.csv", "Worst Case", 5000, perfFile);
    runMergeSort(datasetDir + "descending_employees_10000.csv", sortedDir + "merge_sorted_10000_desc.csv", "Worst Case", 10000, perfFile);
    runMergeSort(datasetDir + "descending_employees_20000.csv", sortedDir + "merge_sorted_20000_desc.csv", "Worst Case", 20000, perfFile);

    // Average Case
    runMergeSort(datasetDir + "random_employees_5000.csv", sortedDir + "merge_sorted_5000_rand.csv", "Average Case", 5000, perfFile);
    runMergeSort(datasetDir + "random_employees_10000.csv", sortedDir + "merge_sorted_10000_rand.csv", "Average Case", 10000, perfFile);
    runMergeSort(datasetDir + "random_employees_20000.csv", sortedDir + "merge_sorted_20000_rand.csv", "Average Case", 20000, perfFile);

    perfFile.close();
    return 0;
}
