// Calculate the p-value for the Wilcoxon rank-sum test
// this is for independent samples all from different subjects
// also know as Mann Whitney "U"
// the Wilcoxon signed rank is different and is for depedent aka. matched pair suitbale for before and after.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to compare two values for qsort
int compdoub(const void *a, const void *b) {
    return (*(double*)a - *(double*)b);
}

// Function to calculate the Wilcoxon rank-sum test p-value
double wilcoxon_p_value(double *data1, size_t n1, double *data2, size_t n2)
{
    // Concatenate the two datasets
    size_t n = n1 + n2;
    double *combined_data = malloc(n * sizeof(double));
    if (!combined_data) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < n1; i++)
        combined_data[i] = data1[i];
    for (size_t i = 0; i < n2; i++)
        combined_data[n1 + i] = data2[i];

    // Sort the combined data
    qsort(combined_data, n, sizeof(double), compdoub);

    // Calculate the ranks
    double *ranks = malloc(n * sizeof(double));
    if (!ranks) {
        fprintf(stderr, "Memory allocation error\n");
        free(combined_data);
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < n; i++)
        ranks[i] = i + 1;

    // Assign ranks to tied values
    for (size_t i = 0; i < n - 1; i++) {
        if (combined_data[i] == combined_data[i + 1]) {
            size_t j = i + 1;
            while (j < n && combined_data[j] == combined_data[i]) {
                j++;
            }

            double tied_rank = 0.5 * (ranks[i] + ranks[j - 1]);
            for (size_t k = i; k < j; k++) {
                ranks[k] = tied_rank;
            }

            i = j - 1;
        }
    }

    // Calculate the sum of ranks for each group
    double sum_ranks_data1 = 0.0;
    double sum_ranks_data2 = 0.0;

    for (size_t i = 0; i < n1; i++)
        sum_ranks_data1 += ranks[i];

    for (size_t i = 0; i < n2; i++)
        sum_ranks_data2 += ranks[n1 + i];

    // Calculate the U statistic
    double U = sum_ranks_data1 - (n1 * (n1 + 1) / 2);

    // Calculate the expected value and standard deviation of U under the null hypothesis
    double expected_U = n1 * n2 / 2.0;
    double sd_U = sqrt((n1 * n2 * (n + 1)) / 12.0);

    // Calculate the z-score
    double z = (U - expected_U) / sd_U;

    // Calculate the two-tailed p-value
    double p_value = 2.0 * (1.0 - fabs(erf(fabs(z) / sqrt(2.0))));

    // Clean up allocated memory
    free(combined_data);
    free(ranks);

    return p_value;
}

int main()
{
    // Define two vectors of floating-point numbers
    double data1[] = {2.5, 3.1, 4.2, 5.0, 6.3};
    double data2[] = {1.8, 2.9, 3.5, 4.8, 5.6};
    
    // ESR1-cg01715172
    double d1 = {0.562563577014331,0.55146342532265,0.455946810417661,0.616839222338544,0.510478606387321,0.531118030813163,0.726735806424479,0.664707332811073};
    double d2 = {0.460506471506335,0.385932921578978,0.602114450889009,0.377267964875068,0.376215045459852,0.542426904936524,0.50088368163438,0.306869441009275};
    double d3 = {0.660603986116313,0.540821576903302,0.63840491824995,0.71881884706584,0.825874722726729,0.620272491434199};

    // Calculate the size of the vectors
    size_t n1 = sizeof(data1) / sizeof(data1[0]);
    size_t n2 = sizeof(data2) / sizeof(data2[0]);

    // Calculate the p-value for the Wilcoxon rank-sum test
    double p_value = wilcoxon_p_value(data1, n1, data2, n2);

    // Print the p-value
    printf("P-value: %f\n", p_value);

    return 0;
}
