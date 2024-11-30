#include <stdio.h>

void printForwardDifferenceTable(int n, double x[], double y[]) {
    // Forward Difference Table
    double table[n][n];
    
    // Initialize the first column with y values
    for (int i = 0; i < n; i++) {
        table[i][0] = y[i];
    }
    
    // Compute forward differences
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            table[i][j] = table[i + 1][j - 1] - table[i][j - 1];
        }
    }
    
    // Print the table header with fixed-width columns
    printf("%-8s %-8s %-8s %-8s %-8s %-8s\n", "x", "y", "delta1", "delta2", "delta3", "delta4");

    // Print the table rows
    for (int i = 0; i < n; i++) {
        // Print x and y values
        printf("%-8.1f %-8.1f", x[i], table[i][0]);
        
        // Print forward differences for each order
        for (int j = 1; j < n - i; j++) {
            printf("%-8.1f", table[i][j]);
        }
        
        // Fill empty spaces for alignment
        for (int j = 0; j < i; j++) {
            printf("%-8s", " ");
        }
        printf("\n");
    }
}

int main() {
    int n;
    
    printf("Enter the number of data points: ");
    scanf("%d", &n);
    
    double x[n], y[n];
    
    printf("Enter the values of x:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &x[i]);
    }
    
    printf("Enter the values of y:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &y[i]);
    }
    
    printf("\nForward Difference Table:\n");
    printForwardDifferenceTable(n, x, y);
    
    return 0;
}
