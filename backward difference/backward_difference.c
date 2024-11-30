#include <stdio.h>

void printBackwardDifferenceTable(double x[], double y[], int n) {
    double diffTable[n][n];
    
    // Initialize the first column with the y values
    for (int i = 0; i < n; i++) {
        diffTable[i][0] = y[i];
    }

    // Compute backward differences
    for (int j = 1; j < n; j++) {
        for (int i = n - 1; i >= j; i--) {
            diffTable[i][j] = diffTable[i][j - 1] - diffTable[i - 1][j - 1];
        }
    }

    // Print the backward difference table
    printf("\nBackward Difference Table:\n");
    printf("x\t");
    for (int j = 0; j < n; j++) {
        printf("nabla^%d\t", j);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%.2lf\t", x[i]);
        for (int j = 0; j <= i; j++) {
            printf("%.2lf\t", diffTable[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    
    // Input the number of data points
    printf("Enter the number of data points: ");
    scanf("%d", &n);

    double x[n], y[n];

    // Input x and y values
    printf("Enter the values of x:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d]: ", i);
        scanf("%lf", &x[i]);
    }

    printf("Enter the values of y:\n");
    for (int i = 0; i < n; i++) {
        printf("y[%d]: ", i);
        scanf("%lf", &y[i]);
    }

    // Print the backward difference table
    printBackwardDifferenceTable(x, y, n);

    return 0;
}
