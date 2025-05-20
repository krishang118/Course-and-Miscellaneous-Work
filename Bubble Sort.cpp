#include <iostream>
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;}}}}
int main() {
    int n;
    std::cout << "Enter the number of elements in the array: ";
    std::cin >> n;
    int* arr = new int[n];
    std::cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];}
    std::cout << "Entered array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";}
    std::cout << "\n";
    bubbleSort(arr, n);
    std::cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";}
    std::cout << "\n";
    delete[] arr;
    return 0;
}