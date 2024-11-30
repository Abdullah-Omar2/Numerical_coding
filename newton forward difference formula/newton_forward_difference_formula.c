#include <stdio.h>

#define MAX 20

// Function to calculate factorial
long long factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n - 1);
}

// Function to compute forward difference table
void computeForwardDifference(double table[MAX][MAX], int n) {
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            table[i][j] = table[i + 1][j - 1] - table[i][j - 1];
        }
    }
}

// Function to interpolate using Newton's Forward Difference Formula
double newtonForward(double x[], double table[MAX][MAX], int n, double value) {
    double h = x[1] - x[0]; // Step size
    double u = (value - x[0]) / h; // u parameter
    double y = table[0][0]; // Initial y value (f(x0))
    double uTerm = 1.0; // u term for calculations

    for (int i = 1; i < n; i++) {
        uTerm *= (u - (i - 1)); // Update u term
        y += (uTerm * table[0][i]) / factorial(i); // Add next term
    }

    return y;
}

int main() {
    int n;
    double x[MAX], y[MAX], value;
    double table[MAX][MAX] = {0};

    // Input number of data points
    printf("Enter the number of data points: ");
    scanf("%d", &n);

    // Input x and y values
    printf("Enter the values of x and y:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d]: ", i);
        scanf("%lf", &x[i]);
        printf("y[%d]: ", i);
        scanf("%lf", &y[i]);
        table[i][0] = y[i]; // Initialize the first column of the table with y values
    }

    // Compute forward difference table
    computeForwardDifference(table, n);

    // Print forward difference table
    printf("\nForward Difference Table:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %.4lf | ", i, x[i]);
        for (int j = 0; j < n - i; j++) {
            printf("%.4lf\t", table[i][j]);
        }
        printf("\n");
    }

    // Input x value to interpolate
    printf("\nEnter the value of x to interpolate: ");
    scanf("%lf", &value);

    // Perform interpolation
    double result = newtonForward(x, table, n, value);

    // Print the result
    printf("The interpolated value at x = %.4lf is y = %.4lf\n", value, result);

    return 0;
}
