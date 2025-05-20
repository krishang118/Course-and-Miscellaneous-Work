#include <iostream>
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;}
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; 
    int i = low - 1;     
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);}}
    swap(arr[i + 1], arr[high]);
    return (i + 1);}
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); 
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);}}
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << "\n";}
int main() {
    int n;
    std::cout << "Enter the number of elements in the array: ";
    std::cin >> n;
    int* arr = new int[n];
    std::cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];}
    std::cout << "Entered array: ";
    printArray(arr, n);
    quickSort(arr, 0, n - 1);
    std::cout << "Sorted array: ";
    printArray(arr, n);
    delete[] arr;
    return 0;}