// you must download gnuplot
#include <stdio.h>
#include <stdlib.h>

void linearRegression(int n, double x[], double y[], double *m, double *c) {
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

    for(int i = 0; i < n; i++) {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
    }

    // Calculate the slope (m) and intercept (c)
    *m = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    *c = (sumY - (*m) * sumX) / n;
}

void plotGraph(int n, double x[], double y[], double m, double c) {
    FILE *dataFile = fopen("data.txt", "w");
    FILE *gnuplotFile = fopen("plot_commands.gp", "w");

    // Write data to a file
    for (int i = 0; i < n; i++) {
        fprintf(dataFile, "%lf %lf\n", x[i], y[i]);
    }
    fclose(dataFile);

    // Write gnuplot commands to a file
    fprintf(gnuplotFile, "set title 'Linear Curve Fitting'\n");
    fprintf(gnuplotFile, "set xlabel 'X'\n");
    fprintf(gnuplotFile, "set ylabel 'Y'\n");
    fprintf(gnuplotFile, "set grid\n");
    fprintf(gnuplotFile, "plot 'data.txt' with points pointtype 7 title 'Data Points', ");
    fprintf(gnuplotFile, "%lf * x + %lf with lines title 'Fitted Line'\n", m, c);
    fprintf(gnuplotFile, "pause -1\n");
    fclose(gnuplotFile);

    // Run gnuplot with the command file
    system("gnuplot plot_commands.gp");
}

int main() {
    int n, i;

    // Input the number of points
    printf("Enter the number of data points: ");
    scanf("%d", &n);

    double x[n], y[n];

    // Input the x and y values
    printf("Enter the x values:\n");
    for(i = 0; i < n; i++) {
        scanf("%lf", &x[i]);
    }

    printf("Enter the y values:\n");
    for(i = 0; i < n; i++) {
        scanf("%lf", &y[i]);
    }

    double m, c;
    // Perform linear regression
    linearRegression(n, x, y, &m, &c);

    // Output the straight-line equation
    printf("The fitted line equation is: y = %.2lfx + %.2lf\n", m, c);

    // Plot the graph using GNUPlot
    plotGraph(n, x, y, m, c);

    return 0;
}
