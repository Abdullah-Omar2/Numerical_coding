#include <stdio.h>
#include <stdlib.h>

// Function to calculate factorial
int factorial(int n) {
    if (n == 0 || n == 1) 
        return 1;
    return n * factorial(n - 1);
}

// Function to compute the backward difference table
void backwardDifferenceTable(double x[], double y[], double diff[][100], int n) {
    for (int i = 0; i < n; i++) 
        diff[i][0] = y[i]; // First column is the y values
    
    for (int j = 1; j < n; j++) {
        for (int i = n - 1; i >= j; i--) {
            diff[i][j] = diff[i][j - 1] - diff[i - 1][j - 1];
        }
    }
}

// Function to compute u for Gauss backward interpolation
double calculateU(double xVal, double x[], int n, double h) {
    return (xVal - x[n - 1]) / h;
}

// Function to compute y using Gauss backward difference formula
double gaussBackwardInterpolation(double x[], double diff[][100], int n, double xVal, double h) {
    double result = diff[n - 1][0]; // Starting with y_n
    double u = calculateU(xVal, x, n, h);
    double uProduct = 1;

    for (int i = 1; i < n; i++) {
        uProduct *= (u + i - 1);
        result += (uProduct * diff[n - 1][i]) / factorial(i);
    }

    return result;
}

// Function to print the backward difference table
void printBackwardDifferenceTable(double diff[][100], int n) {
    printf("Backward Difference Table:\n");
    for (int i = 0; i < n; i++) {
        printf("%lf ", diff[i][0]); // x values
        for (int j = 1; j <= i; j++) {
            printf("%lf ", diff[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter the number of data points: ");
    scanf("%d", &n);

    double x[100], y[100], diff[100][100] = {0};

    printf("Enter the x values:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &x[i]);
    }

    printf("Enter the y values:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &y[i]);
    }

    // Calculate the backward difference table
    backwardDifferenceTable(x, y, diff, n);

    // Print the backward difference table
    printBackwardDifferenceTable(diff, n);

    // Ask for the x value to calculate its y
    double xVal;
    printf("Enter the x value to interpolate: ");
    scanf("%lf", &xVal);

    double h = x[1] - x[0]; // Assuming equidistant intervals
    double yVal = gaussBackwardInterpolation(x, diff, n, xVal, h);

    printf("The interpolated value of y at x = %lf is %lf\n", xVal, yVal);

    return 0;
}
