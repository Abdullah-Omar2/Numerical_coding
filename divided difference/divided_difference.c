#include <stdio.h>

#define MAX 100

// Function to print the divided difference table
void printDividedDifferenceTable(double x[], double y[], int n) {
    double table[MAX][MAX]; // To store the divided differences

    // Initialize the first column with y values
    for (int i = 0; i < n; i++) {
        table[i][0] = y[i];
    }

    // Calculate the divided differences
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            table[i][j] = (table[i + 1][j - 1] - table[i][j - 1]) / (x[i + j] - x[i]);
        }
    }

    // Print the table
    printf("\nDivided Difference Table:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d]=%.2f\t", i, x[i]);
        for (int j = 0; j < n - i; j++) {
            printf("%.6f\t", table[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;

    // Input number of points
    printf("Enter the number of data points: ");
    scanf("%d", &n);

    double x[MAX], y[MAX];

    // Input x and y values
    printf("Enter the x values:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d]: ", i);
        scanf("%lf", &x[i]);
    }

    printf("Enter the y values:\n");
    for (int i = 0; i < n; i++) {
        printf("y[%d]: ", i);
        scanf("%lf", &y[i]);
    }

    // Print the divided difference table
    printDividedDifferenceTable(x, y, n);

    return 0;
}
