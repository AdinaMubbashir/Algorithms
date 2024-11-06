#include <stdio.h>
#include <sys/timeb.h>
#include <stdlib.h>
#define MAXPAIRS 100000

void bruteForce(int arr[MAXPAIRS][2], int count);

int main(int argc, char const *argv[])
{
    struct timeb startTime, endTime;
    char filename[100];
    int arr[MAXPAIRS][2];
    int count = 0;

    // Get file
    printf("Enter the file name\n");
    scanf("%s", filename);
    getchar();

    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        fprintf(stderr, "File could not be opened \n");
        return 0;
    }

    // Store file content
    while (fscanf(fp, "%d %d", &arr[count][0], &arr[count][1]) == 2)
    {
        count++;
    }

    fclose(fp);

    printf("Brute Force:\n");

    ftime(&startTime);
    bruteForce(arr, count); // Function call
    ftime(&endTime);

    // Get time in milliseconds
    float totalTime = (endTime.time - startTime.time) * 1000 + (endTime.millitm - startTime.millitm);

    printf("Execution time: %.2fms\n", totalTime);

    return 0;
}

void bruteForce(int arr[MAXPAIRS][2], int count)
{
    int minVar = arr[0][0];
    int maxVar = arr[0][1];
    int countInv = 0;
    int countPoint = 0;

    // Get Max value
    for (int i = 0; i < count; i++)
    {

        if (maxVar < arr[i][1])
        {
            maxVar = arr[i][1];
        }
    }

    // Get min value
    for (int i = 0; i < count; i++)
    {
        if (minVar > arr[i][0])
        {
            minVar = arr[i][0];
        }
    }

    int var = minVar + 1;

    // Don't include end point while looping
    while (var < maxVar)
    {
        int num = 0;
        for (int i = 0; i < count; i++)
        {
            // Look for commont point
            if (var > arr[i][0] && var < arr[i][1])
            {
                num++;
            }
        }
        // Get interval
        if (num > countInv)
        {
            countInv = num;
            countPoint = var;
        }
        var++;
    }

    printf("The maximum number of intervals: %d\n", countInv);
    printf("The intervals include point: %d\n", countPoint);
}
