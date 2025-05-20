#include <stdio.h>
#include <math.h>
#include <float.h>
int main() {
    double values[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
    int count = sizeof(values) / sizeof(values[0]);
    printf("%-10s%-10s%-10s%-15s%-15s%-20s%-20s%-15s%-15s\n", 
           "n", "√n", "log n", "n", "n*log n", "n²", "n²*log n", "2^n", "n^n");
    for (int index = 0; index < count; index++) {
        double current_n = values[index];
        double square_root = sqrt(current_n);  
        double logarithm = log(current_n);      
        double n_logarithm = current_n * logarithm; 
        double square_n = pow(current_n, 2);    
        double square_n_logarithm = square_n * logarithm;  
        double power_of_two;
        if (current_n > 20) {
            power_of_two = INFINITY;  
        } else {
            power_of_two = pow(2, current_n);
        }
        char n_power_n_result[20];
        if (current_n > 10) {
            snprintf(n_power_n_result, sizeof(n_power_n_result), "Overflow");
        } else {
            snprintf(n_power_n_result, sizeof(n_power_n_result), "%.0f", pow(current_n, current_n));
        }
        printf("%-10.0f%-10.2f%-10.2f%-15.0f%-15.2f%-20.0f%-20.2f%-15.0f%-15s\n", 
               current_n, square_root, logarithm, current_n, n_logarithm, square_n, 
               square_n_logarithm, power_of_two, n_power_n_result);
    }
    //inf and Overflow basically indicate towards a similar kind of thing
    return 0;
}