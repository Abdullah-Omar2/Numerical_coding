#include <stdio.h>
#include <math.h>

// Function to calculate factorial
int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Function to calculate the backward difference table
void backwardDifferenceTable(int n, double x[], double y[][100]) {
    for (int i = 1; i < n; i++) {
        for (int j = n - 1; j >= i; j--) {
            y[j][i] = y[j][i - 1] - y[j - 1][i - 1];
        }
    }
}

// Newton's Backward Difference Formula
double newtonBackwardInterpolation(double x[], double y[][100], int n, double value) {
    double result = y[n - 1][0];
    double h = x[1] - x[0];
    double p = (value - x[n - 1]) / h;

    for (int i = 1; i < n; i++) {
        double term = y[n - 1][i];
        for (int j = 0; j < i; j++) {
            term *= (p + j);
        }
        term /= factorial(i);
        result += term;
    }

    return result;
}

int main() {
    int n;
    double x[100], y[100][100], value, result;

    // Input number of data points
    printf("Enter the number of data points: ");
    scanf("%d", &n);

    // Input x and y values
    printf("Enter the x values:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &x[i]);
    }

    printf("Enter the y values:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &y[i][0]);
    }

    // Generate the backward difference table
    backwardDifferenceTable(n, x, y);

    // Print the backward difference table
    printf("\nBackward Difference Table:\n");
    for (int i = 0; i < n; i++) {
        printf("%lf", x[i]);
        for (int j = 0; j <= i; j++) {
            printf("\t%lf", y[i][j]);
        }
        printf("\n");
    }

    // Input the x value to interpolate
    printf("\nEnter the value of x to calculate its y: ");
    scanf("%lf", &value);

    // Calculate y using Newton's Backward Difference formula
    result = newtonBackwardInterpolation(x, y, n, value);

    printf("\nThe interpolated value of y at x = %lf is %lf\n", value, result);

    return 0;
}
