//In the output, the capital E as the first column and the first row's name indicates an empty string.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
int min(int x, int y, int z) {
    if (x <= y && x <= z) return x;
    if (y <= x && y <= z) return y;
    return z;}
int editDistance(char *str1, char *str2, int m, int n) {
    int dp[MAX][MAX];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else {
                if (str1[i-1] == str2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = 1 + min(
                        dp[i][j-1],   
                        dp[i-1][j],    
                        dp[i-1][j-1]);}}}}
    printf("Dynamic Programming Table for Edit Distance:\n");
    printf("   E  ");
    for (int j = 0; j < n; j++) {
        printf("%c  ", str2[j]);}
    printf("\n");
    for (int i = 0; i <= m; i++) {
        if (i == 0) {
            printf("E  ");
        } else {
            printf("%c  ", str1[i - 1]);}
        for (int j = 0; j <= n; j++) {
            printf("%d  ", dp[i][j]);}
        printf("\n");}
    return dp[m][n];}
int main() {
    char str1[MAX], str2[MAX];
    printf("Enter the first string: ");
    scanf("%s", str1);
    printf("Enter the second string: ");
    scanf("%s", str2);
    int m = strlen(str1);
    int n = strlen(str2);
    int distance = editDistance(str1, str2, m, n);
    printf("The Edit Distance between \"%s\" and \"%s\" is %d.\n", str1, str2, distance);
    return 0;}