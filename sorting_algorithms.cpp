#include <iostream>
#include <vector>
using namespace std;

// Helper to print array
void printArray(const vector<int>& arr) {
    for (int x : arr) cout << x << " ";
    cout << '\n';
}

// 1a. Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j)
            if (arr[j] < arr[minIdx]) minIdx = j;
        swap(arr[i], arr[minIdx]);
    }
}

// 1b. Insertion Sort
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// 1c. Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // already sorted
    }
}

// 1d. Merge Sort
void merge(vector<int>& a, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = a[l + i];
    for (int j = 0; j < n2; ++j) R[j] = a[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) a[k++] = L[i++];
        else a[k++] = R[j++];
    }
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
}

void mergeSortRec(vector<int>& a, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSortRec(a, l, m);
    mergeSortRec(a, m + 1, r);
    merge(a, l, m, r);
}

void mergeSort(vector<int>& arr) {
    if (!arr.empty()) mergeSortRec(arr, 0, (int)arr.size() - 1);
}

// 1e. Quick Sort (using Lomuto partition for clarity)
int partitionLomuto(vector<int>& a, int l, int r) {
    int pivot = a[r];
    int i = l - 1;
    for (int j = l; j < r; ++j) {
        if (a[j] <= pivot) {
            ++i; swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[r]);
    return i + 1;
}

void quickSortRec(vector<int>& a, int l, int r) {
    if (l < r) {
        int p = partitionLomuto(a, l, r);
        quickSortRec(a, l, p - 1);
        quickSortRec(a, p + 1, r);
    }
}

void quickSort(vector<int>& arr) {
    if (!arr.empty()) quickSortRec(arr, 0, (int)arr.size() - 1);
}

// 2. Improved Selection Sort (select min and max each pass)
void improvedSelectionSort(vector<int>& arr) {
    int n = arr.size();
    int left = 0, right = n - 1;
    while (left < right) {
        int minIdx = left, maxIdx = left;
        for (int i = left; i <= right; ++i) {
            if (arr[i] < arr[minIdx]) minIdx = i;
            if (arr[i] > arr[maxIdx]) maxIdx = i;
        }
        // place min at left
        swap(arr[left], arr[minIdx]);
        // if max was at left, its index moved to minIdx
        if (maxIdx == left) maxIdx = minIdx;
        // place max at right
        swap(arr[right], arr[maxIdx]);
        ++left; --right;
    }
}

// Menu-driven demo
int main() {
    cout << "Sorting Algorithms Demo (simple, beginner-friendly)\n";
    vector<int> arr;
    int n;
    cout << "Enter number of elements: ";
    if (!(cin >> n) || n <= 0) return 0;
    arr.resize(n);
    cout << "Enter " << n << " integers separated by space:\n";
    for (int i = 0; i < n; ++i) cin >> arr[i];

    cout << "\nChoose sorting algorithm:\n";
    cout << "1. Selection Sort\n2. Insertion Sort\n3. Bubble Sort\n4. Merge Sort\n5. Quick Sort\n6. Improved Selection Sort\n";
    int choice; cin >> choice;

    vector<int> copy = arr; // keep original
    switch (choice) {
        case 1: selectionSort(copy); cout << "Selection Sort result:\n"; break;
        case 2: insertionSort(copy); cout << "Insertion Sort result:\n"; break;
        case 3: bubbleSort(copy); cout << "Bubble Sort result:\n"; break;
        case 4: mergeSort(copy); cout << "Merge Sort result:\n"; break;
        case 5: quickSort(copy); cout << "Quick Sort result:\n"; break;
        case 6: improvedSelectionSort(copy); cout << "Improved Selection Sort result:\n"; break;
        default: cout << "Invalid choice\n"; return 0;
    }

    printArray(copy);
    return 0;
}
