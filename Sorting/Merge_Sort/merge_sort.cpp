#include<iostream>
#include<fstream>
#include<vector>
#include<ctime>
#include<cstdlib>
using namespace std;

void merge(vector<int> &arr, int low, int mid, int high) {
    int n = (high - low + 1);
    int i = low, j = mid + 1, idx = 0;
    int temp[100000] = {0};  // Fixed-size array for simplicity (to avoid VLA error)

    while (i <= mid && j <= high) {
        if (arr[i] <= arr[j]) temp[idx++] = arr[i++];
        else temp[idx++] = arr[j++];
    }

    while (i <= mid) {
        temp[idx++] = arr[i++];
    }

    while (j <= high) {
        temp[idx++] = arr[j++];
    }

    for (int k = low; k <= high; k++) {
        arr[k] = temp[k - low];
    }
}

void mergeSort(vector<int> &arr, int low, int high) {
    if (low >= high) return;
    int mid = (low + high) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

int main() {
    vector<int> arr;
    int num;
    ifstream f1("frame_sizes.txt");
    if (f1.is_open()) {
        while (f1 >> num) arr.push_back(num);
        f1.close();
    } else {
        cerr << "Unable to open file.\n";
        return 1;
    }

    int n = arr.size();
    clock_t start = clock();
    mergeSort(arr, 0, n - 1);
    clock_t end = clock();
    cout << "Merge Sort Time Taken (10000 values): " << (double)(end - start) / CLOCKS_PER_SEC << endl;

    ofstream f2("out_page_count1.txt");
    for (int i = 0; i < n; i++) {
        f2 << arr[i] << endl;
    }

    return 0;
}
