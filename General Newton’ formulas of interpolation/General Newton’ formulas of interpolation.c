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

// Function to plot data and interpolation polynomial using gnuplot
void plot_with_gnuplot(int n, double x[], double y[], double div_diff[], int poly_points) {
    // Create data file for original points
    FILE *dataFile = fopen("data.txt", "w");
    for (int i = 0; i < n; i++) {
        fprintf(dataFile, "%lf %lf\n", x[i], y[i]);
    }
    fclose(dataFile);

    // Create file for interpolated polynomial points
    FILE *polyFile = fopen("poly_data.txt", "w");
    double x_min = x[0], x_max = x[n - 1];
    double step = (x_max - x_min) / poly_points;
    for (double xi = x_min; xi <= x_max; xi += step) {
        double yi = evaluatePolynomial(x, div_diff, n, xi);
        fprintf(polyFile, "%lf %lf\n", xi, yi);
    }
    fclose(polyFile);

    // Write gnuplot commands to a file
    FILE *gnuplotFile = fopen("plot_commands.gp", "w");
    fprintf(gnuplotFile, "set title 'Newton Interpolation Polynomial'\n");
    fprintf(gnuplotFile, "set xlabel 'X'\n");
    fprintf(gnuplotFile, "set ylabel 'Y'\n");
    fprintf(gnuplotFile, "set grid\n");
    fprintf(gnuplotFile, "plot 'data.txt' with points pointtype 7 title 'Data Points', ");
    fprintf(gnuplotFile, "'poly_data.txt' with lines title 'Interpolated Polynomial'\n");
    fprintf(gnuplotFile, "pause -1\n");
    fclose(gnuplotFile);

    // Run gnuplot with the command file
    system("gnuplot plot_commands.gp");
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

    // Print polynomial coefficients
    printf("Interpolated polynomial coefficients (Newton's Form):\n");
    for (int i = 0; i < n; i++) {
        printf("Coefficient of term %d: %lf\n", i, div_diff[i]);
    }

    // Plot with gnuplot
    plot_with_gnuplot(n, x, y, div_diff, 100);

    return 0;
}
