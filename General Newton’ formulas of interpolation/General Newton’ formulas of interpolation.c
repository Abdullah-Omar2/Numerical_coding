#include <stdio.h>
#include <stdlib.h>

// Function to calculate divided difference table
void calculateDividedDifference(double x[], double y[], double div_diff[], int n) {
    for (int i = 0; i < n; i++) {
        div_diff[i] = y[i];
    }

    for (int i = 1; i < n; i++) {
        for (int j = n - 1; j >= i; j--) {
            div_diff[j] = (div_diff[j] - div_diff[j - 1]) / (x[j] - x[j - i]);
        }
    }
}

// Function to evaluate polynomial at a given point using the divided difference coefficients
double evaluatePolynomial(double x[], double div_diff[], int n, double val) {
    double result = div_diff[0];
    double term;

    for (int i = 1; i < n; i++) {
        term = div_diff[i];
        for (int j = 0; j < i; j++) {
            term *= (val - x[j]);
        }
        result += term;
    }

    return result;
}

int main() {
    int n;
    printf("Enter number of data points: ");
    scanf("%d", &n);

    double x[n], y[n], div_diff[n];
    printf("Enter x values: ");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &x[i]);
    }
    printf("Enter y values: ");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &y[i]);
    }

    // Calculate divided differences
    calculateDividedDifference(x, y, div_diff, n);

    // File to store x, y, and interpolated values for gnuplot
    FILE *fp = fopen("data.txt", "w");
    double x_range_min = x[0], x_range_max = x[n - 1];
    double step = (x_range_max - x_range_min) / 100.0;
    for (double xi = x_range_min; xi <= x_range_max; xi += step) {
        double yi = evaluatePolynomial(x, div_diff, n, xi);
        fprintf(fp, "%lf %lf\n", xi, yi);
    }
    fclose(fp);

    // Print polynomial
    printf("Interpolated polynomial coefficients (Newton's Form):\n");
    for (int i = 0; i < n; i++) {
        printf("Coefficient of term %d: %lf\n", i, div_diff[i]);
    }

    // Call gnuplot to plot the data
    FILE *gp = fopen("plot.gnuplot", "w");
    fprintf(gp, "set title 'Newton Interpolation'\n");
    fprintf(gp, "set xlabel 'x'\n");
    fprintf(gp, "set ylabel 'y'\n");
    fprintf(gp, "plot 'data.txt' with lines title 'Interpolated Polynomial', '-' with points title 'Data Points'\n");
    for (int i = 0; i < n; i++) {
        fprintf(gp, "%lf %lf\n", x[i], y[i]);
    }
    fprintf(gp, "e\n");
    fclose(gp);
    system("gnuplot -persist plot.gnuplot");

    return 0;
}
