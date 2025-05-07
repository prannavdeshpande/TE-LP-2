#include <iostream>
#include <vector>

void selectionSort(std::vector<int> &arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {
        // Assume the current position holds the minimum element
        int min_idx = i;

        // Iterate through the unsorted portion to find the actual minimum
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                // Update min_idx if a smaller element is found
                min_idx = j;
            }
        }

        // Move minimum element to its correct position
        std::swap(arr[i], arr[min_idx]);
    }
}

void printArray(std::vector<int> &arr) {
    for (int &val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {
    int n;
    std::cout << "Enter the number of elements in the array: ";
    std::cin >> n;

    // Input validation for array size
    if (n <= 0) {
        std::cout << "Invalid array size!" << std::endl;
        return 1;
    }

    std::vector<int> arr(n);
    std::cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    std::cout << "Original array: ";
    printArray(arr);

    selectionSort(arr);

    std::cout << "Sorted array: ";
    printArray(arr);

    return 0;
}