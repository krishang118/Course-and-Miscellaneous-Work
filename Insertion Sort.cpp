#include <iostream>
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;}
        arr[j + 1] = key;}}
void displayArray(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";}
    std::cout << std::endl;}
int main() {
    int n;
    std::cout << "Enter the number of elements in the array: ";
    std::cin >> n;
    int* arr = new int[n];
    std::cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];}
    std::cout << "Entered array: ";
    displayArray(arr, n);
    insertionSort(arr, n); 
    std::cout << "Sorted array: ";
    displayArray(arr, n);
    delete[] arr; 
    return 0;}