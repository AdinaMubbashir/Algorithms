#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <string.h>

// Returns maximum between two numbers
int maxShift(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

// Builds shift table
void buildBadCharShiftTable(char *pattern, int *table, int patSize)
{

    for (int i = 0; i < 256; i++)
    {
        table[i] = '\0';
    }

    for (int i = 0; i < patSize; i++)
    {
        table[(int)pattern[i]] = i;
    }
}

// Builds good shift table
int *goodTable(char *pattern)
{
    int size = strlen(pattern);
    int i, j;

    // Allocate memory for the table
    int *table = malloc(sizeof(int) * (size + 1));
    int last[size + 1];

    last[size] = size + 1;

    // Calculate each character from right to left beginning from end
    for (i = size, j = size + 1; i >= 0; i--)
    {
        while (j <= size && pattern[i] != pattern[j - 1])
        {
            table[j] = table[j] == 0 ? j - i - 1 : table[j];
            j = last[j];
        }

        last[i] = j;
        j--;
    }

    return table;
}

void boyerMooreSearch(int *badCharShiftTable, char *pattern, int patSize, int *goodShiftTable, FILE *file)
{
    char lines[100000];
    int countShifts = 0;
    int patternCount = 0;
    int l = 0;

    // Read file line by fine
    while (fgets(lines, 100000, file) != NULL)
    {
        int size = strlen(lines);
        int k = 0;
        int num = 1;

        // loop through lines
        while (k <= size - patSize)
        {
            int var = patSize - 1;
            // Compare pattern
            for (; var >= 0 && pattern[var] == lines[k + var]; var--)
            {
            }
            // Match is found
            if (var < 0)
            {
                patternCount++;
                // Compute shift distance
                if ((k + patSize) < size)
                {
                    l += patSize - badCharShiftTable[(int)lines[k + patSize]];
                }
                else
                {
                    l = 1;
                }
                k += maxShift(l, goodShiftTable[0]);
            }
            else
            {
                // If pattern doesn't match
                l = maxShift(num, var - badCharShiftTable[(int)lines[k + var]]);
                k += maxShift(l, goodShiftTable[var + 1]);
                countShifts++;
            }
        }
    }

    printf("Counts: %d\n", patternCount);
    printf("Shifts: %d\n", countShifts);
}

void calCount(FILE *file, char pattern[100])
{

    struct timeb startTime, endTime;

    ftime(&startTime);

    // Size of the pattern
    int patSize = strlen(pattern);

    // Bad shift table
    int badCharShiftTable[256];
    buildBadCharShiftTable(pattern, badCharShiftTable, patSize);

    // Good shift table
    int *goodShiftTable = goodTable(pattern);
    boyerMooreSearch(badCharShiftTable, pattern, patSize, goodShiftTable, file);

    free(goodShiftTable);

    ftime(&endTime);

    float totalTime = (endTime.time - startTime.time) * 1000 + (endTime.millitm - startTime.millitm);

    printf("Execution time: %.2fms\n", totalTime);
}

int main(int argc, char const *argv[])
{
    char user[150];

    FILE *fp = fopen("data_A3_Q2.txt", "r");

    if (fp == NULL)
    {
        fprintf(stderr, "File could not be opened \n");
        return 0;
    }

    printf("Boyer-Moore Algorithm:\n");
    // Prompt for pattern
    printf("Enter a pattern: ");
    scanf("%s", user);
    getchar();

    calCount(fp, user);

    return 0;
}
