#include<iostream>
#include<fstream>
#include<vector>
#include<ctime>
#include<cstdlib>
using namespace std;

void insertion_sort(vector<int> &arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    vector<int> arr;
    int num;
    ifstream f("frame_sizes.txt");
    if (f.is_open()) {
        while (f >> num) arr.push_back(num);
        f.close();
    } else {
        cerr << "Unable to Open Frame Sizes Text File.\n";
        return 1;
    }

    int n = arr.size();
    clock_t start = clock();
    insertion_sort(arr, n);
    clock_t end = clock();

    cout << "Insertion Sort Time Taken (10000 values): " 
         << (double)(end - start) / CLOCKS_PER_SEC << endl;

    ofstream f1("frame_sizes.txt");
    for (int i = 0; i < n; i++) {
        f1 << arr[i] << endl;
    }
    return 0;
}
