// Calculate the p-value for the Wilcoxon rank-sum test
// this is for independent samples all from different subjects
// also know as Mann Whitney "U"
// the Wilcoxon signed rank is different and is for depedent aka. matched pair suitbale for before and after.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to compare two values for qsort
int compdoub(const void *a, const void *b)
{
    return (*(double*)a - *(double*)b);
}

// Function to calculate the signed rank test statistic
double signed_rank_test(double *data1, double *data2, size_t n)
{
    // Calculate the differences between pairs
    double *differences = malloc(n * sizeof(double));
    int i, j;

    for(i = 0; i < n; i++)
        differences[i] = data1[i] - data2[i];
    for(i=0;i<n;++i) 
        printf("%2.2f ", differences[i]); 
    printf("\n"); 

    // Sort the absolute differences
    double *abs_diff = malloc(n * sizeof(double));

    for (i = 0; i < n; i++)
        abs_diff[i] = fabs(differences[i]);

    qsort(abs_diff, n, sizeof(double), compdoub);

    // Calculate the signed ranks
    // have to explain waht's going on here.
    double *ranks = malloc(n*sizeof(double));
    for (i = 0; i < n; i++) {
        ranks[i]=1;
        for (j = 0; j < n; j++) {
            if (fabs(differences[i]) > abs_diff[j])
                ranks[i] += (differences[i] > 0) ? 1.0 : -1.0;
            //else if (fabs(differences[i]) == abs_diff[j])
            //    ranks[i] += 0.5 * ((differences[i] > 0) ? 1.0 : -1.0);
        }
    }
    for(i=0;i<n;++i) 
        printf("%2.2f ", ranks[i]); 
    printf("\n"); 

    // Calculate the signed rank test statistic
    double sum_positive_ranks = 0.0;
    double sum_negative_ranks = 0.0;

    for (i = 0; i < n; i++) {
        if (differences[i] > 0) 
            sum_positive_ranks += ranks[i];
        else if (differences[i] < 0)
            sum_negative_ranks += fabs(ranks[i]);
    }

    printf("sum_positive_ranks=%2.2f, sum_negative_ranks=%2.2f\n", sum_positive_ranks, sum_negative_ranks);
    double test_statistic = fmin(sum_positive_ranks, sum_negative_ranks);

    // Clean up allocated memory
    free(differences);
    free(abs_diff);
    free(ranks);

    return test_statistic;
}

int main()
{
    // Define two vectors of floating-point numbers (paired samples)
    // double data1[] = {25.0, 30.0, 35.0, 40.0, 45.0};
    // double data2[] = {22.0, 28.0, 34.0, 41.0, 43.0};
    // this from iMcLoghlin's hand calc video for aluminium levels in paried trees data1 in august data2 in nov.
    // not differences in last 3 values are about double or more and these can be called outliers and will violate normal dist, so no t-test.
    // actually data1 is fine though, normal dist can be assumed, but not data2.
    double data1[] = {18.3, 13.3, 16.5, 12.6, 9.5, 13.6, 8.1, 8.9, 10.0, 8.3, 7.9, 8.1, 13.4};
    double data2[] = {12.7, 11.1, 15.3, 12.7, 10.5, 15.6, 11.2, 14.2, 16.2, 15.5, 19.9, 20.4, 36.8}; 

    // Calculate the size of the vectors
    size_t n = sizeof(data1) / sizeof(data1[0]);

    // Perform the signed rank test
    double test_statistic = signed_rank_test(data1, data2, n);

    // Print the test statistic
    printf("Signed Rank Test Statistic: %f\n", test_statistic);

    return 0;
}
