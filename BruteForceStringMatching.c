#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <string.h>

// Brute-Force String Matching algorithm 
void bruteForce(FILE *fp, char user[150])
{
    struct timeb startTime, endTime;

    ftime(&startTime);

    int patternCount = 0;
    int countShifts = 0;
    char lines[100000];

    // Loop throught file line by line
    while (fgets(lines, 100000, fp) != NULL)
    {
        int length1 = strlen(lines);
        int length2 = strlen(user);

        // Loop through characacter in line
        for (int i = 0; i < length1 - length2; i++)
        {
            int var = 0;
            // Comparing each character on line
            while (var != length2 && user[var] == lines[var + i])
            {
                var++;
            }
            // Match is found
            if (var == length2)
            {
                patternCount++;
            }
            countShifts++;
        }
    }

    ftime(&endTime);
    float totalTime = (endTime.time - startTime.time) * 1000 + (endTime.millitm - startTime.millitm);

    printf("Count: %d\n", patternCount);
    printf("Shifts: %d\n", countShifts);
    printf("Execution time = %.2fms\n", totalTime);
}

int main(int argc, char const *argv[])
{
    char user[150];

    // Open file
    FILE *fp = fopen("data_A3_Q2.txt", "r");

    if (fp == NULL)
    {
        fprintf(stderr, "File could not be opened \n");
        return 0;
    }

    printf("A Brute force program for string search.\n");
    // Prompt for pattern
    printf("Enter a pattern: ");
    scanf("%s", user);
    getchar();

    // Call function
    bruteForce(fp, user);

    return 0;
}
