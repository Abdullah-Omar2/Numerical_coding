#include <stdio.h>
#include <math.h>

#define MAX_ITER 20
#define TOLERANCE 1e-6

void print_table_header(int n) {
    printf("\n%-10s", "k");
    for (int i = 0; i < n; i++) {
        printf("x%d%-8s", i + 1, "");
    }
    printf("\n");
}

void print_row(int k, double *x, int n) {
    printf("%-10d", k);
    for (int i = 0; i < n; i++) {
        printf("%-10.4f", x[i]);
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter the number of variables: ");
    scanf("%d", &n);

    double a[n][n], b[n], x[n], new_x[n];
    printf("Enter the coefficients of the system (a[i][j]):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("a[%d][%d] = ", i, j);
            scanf("%lf", &a[i][j]);
        }
    }

    printf("Enter the constants (b[i]):\n");
    for (int i = 0; i < n; i++) {
        printf("b[%d] = ", i);
        scanf("%lf", &b[i]);
    }

    printf("Enter the initial guesses (x[i]):\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = ", i);
        scanf("%lf", &x[i]);
    }

    printf("\nSolving the system using Jacobi's Iterative Method...\n");
    print_table_header(n);

    int k = 0;
    print_row(k, x, n); // Print initial guess

    while (k < MAX_ITER) {
        int converged = 1;

        // Perform Jacobi iteration
        for (int i = 0; i < n; i++) {
            double sum = b[i];
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum -= a[i][j] * x[j];
                }
            }
            new_x[i] = sum / a[i][i];

            // Check for convergence
            if (fabs(new_x[i] - x[i]) > TOLERANCE) {
                converged = 0;
            }
        }

        k++;
        for (int i = 0; i < n; i++) {
            x[i] = new_x[i];
        }
        print_row(k, x, n);

        if (converged) {
            break;
        }
    }

    if (k == MAX_ITER) {
        printf("\nMaximum iterations reached. Solution may not have converged.\n");
    } else {
        printf("\nSolution converged in %d iterations.\n", k);
    }

    return 0;
}
