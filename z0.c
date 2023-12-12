#include <stdio.h>
#include <math.h>

double calculateZScore(double sampleMean, double popMean, double popStdDev, int sampleSize)
{
    printf("Calculating zscore\n"); 
    printf("Divide p\n"); 
    return (sampleMean - popMean) / (popStdDev / sqrt(sampleSize));
}

double calculatePValue(double zScore)
{
    // In a real-world scenario, you would look up the p-value from a Z-table or use a statistical library.
    // For simplicity, this example assumes a two-tailed test.
    // You may need to adapt this part based on your specific statistical library or methodology.
    return 2 * (1 - 0.5 * (1 + erf(zScore / sqrt(2))));
}

int main()
{
    printf("chatgpt makes error of using pop std dev instead of sample dev.\n"); 
    // Given values
    double sampleMean = 66.0;
    double popMean = 65.0;
    double popStdDev = 2.0;
    int sampleSize = 100;

    // Calculate the z-score
    double zScore = calculateZScore(sampleMean, popMean, popStdDev, sampleSize);

    // Calculate the p-value
    double pValue = calculatePValue(zScore);

    // Set the significance level (alpha)
    double alpha = 0.05;

    // Compare the p-value to the significance level
    printf("Pop avg is %2.2f, yo have a sample of size %i, and its mean is %2.2f with stdev of %2.2f\n", popMean, sampleSize, sampleMean, popStdDev); 
    printf("You run z-score test getting %2.2f with pval of %2.2f on which you apply an alpha of %2.2f\n", zScore, pValue, alpha); 
    if (pValue < alpha) {
        printf("Reject the null hypothesis. There is a significant difference in average height.\n");
    } else {
        printf("Fail to reject the null hypothesis. There is no significant difference in average height.\n");
    }

    return 0;
}
