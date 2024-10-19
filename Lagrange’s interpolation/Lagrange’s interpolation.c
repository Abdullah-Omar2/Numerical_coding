//you must download gnuplot to see the graph
#include <stdio.h>
#include <stdlib.h>

// Function to calculate the Lagrange basis polynomial for a given point x
double lagrange_basis(int i, double x, double* X, int n) {
    double result = 1.0;
    for (int j = 0; j < n; j++) {
        if (j != i) {
            result *= (x - X[j]) / (X[i] - X[j]);
        }
    }
    return result;
}

// Function to calculate the Lagrange interpolation at a given x
double lagrange_interpolation(double x, double* X, double* Y, int n) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result += Y[i] * lagrange_basis(i, x, X, n);
    }
    return result;
}

// Function to display the Lagrange polynomial in human-readable form
void display_polynomial(double* X, double* Y, int n) {
    printf("The Lagrange interpolation polynomial is:\n");
    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" + ");
        printf("%.3f", Y[i]);
        for (int j = 0; j < n; j++) {
            if (j != i) {
                printf(" * (x - %.3f)", X[j]);
                printf(" / (%.3f - %.3f)", X[i], X[j]);
            }
        }
    }
    printf("\n");
}

// Function to plot data using gnuplot
void plot_with_gnuplot(int n, double X[], double Y[], double interp_X[], double interp_Y[], int interp_n) {
    FILE *dataFile = fopen("data.dat", "w");
    FILE *gnuplotFile = fopen("plot_commands.gp", "w");

    // Write interpolated points (for the curve) to the data file
    for (int i = 0; i < interp_n; i++) {
        fprintf(dataFile, "%lf %lf\n", interp_X[i], interp_Y[i]);
    }
    fclose(dataFile);

    // Write gnuplot commands to a file
    fprintf(gnuplotFile, "set title 'Lagrange Interpolation'\n");
    fprintf(gnuplotFile, "set xlabel 'X'\n");
    fprintf(gnuplotFile, "set ylabel 'P(X)'\n");
    fprintf(gnuplotFile, "set grid\n");
    fprintf(gnuplotFile, "plot 'data.dat' with lines title 'Lagrange Polynomial', '-' with points pointtype 7 title 'Data Points'\n");

    // Add the original data points (given points) to gnuplot
    for (int i = 0; i < n; i++) {
        fprintf(gnuplotFile, "%lf %lf\n", X[i], Y[i]);
    }
    fprintf(gnuplotFile, "e\n");  // End of data input for the points

    fprintf(gnuplotFile, "pause -1\n");  // Keep the plot open
    fclose(gnuplotFile);

    // Run gnuplot with the command file
    system("gnuplot plot_commands.gp");
}

int main() {
    int n;
    
    printf("Enter the number of data points: ");
    scanf("%d", &n);
    
    double X[n], Y[n];
    
    printf("Enter the x values:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &X[i]);
    }
    
    printf("Enter the y values:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &Y[i]);
    }
    
    // Display the Lagrange interpolation polynomial
    display_polynomial(X, Y, n);

    // Generate interpolation data for plotting
    double interpolated_X[1000], interpolated_Y[1000];
    int index = 0;
    for (double x = X[0]; x <= X[n-1]; x += 0.01) {
        interpolated_X[index] = x;
        interpolated_Y[index] = lagrange_interpolation(x, X, Y, n);
        index++;
    }

    // Plot using gnuplot
    plot_with_gnuplot(n, X, Y, interpolated_X, interpolated_Y, index);
    
    return 0;
}
