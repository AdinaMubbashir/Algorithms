
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sys/timeb.h>
#include <stdlib.h>

#define MAXPAIRS 30000

typedef struct Coordinate
{

	double x;
	double y;

} Coordinate;

// Finds side the coordinate is in
int getSide(Coordinate a, Coordinate b, Coordinate c)
{

	double p1 = (b.x - a.x) * (c.y - a.y);
	double p2 = (b.y - a.y) * (c.x - a.x);
	double calc = p1 - p2;

	// left
	if (calc > 0)
	{
		return 1;
		// right
	}
	else if (calc < 0)
	{
		return -1;
	}
	// Along the same line
	else
	{
		return 0;
	}

	return 0;
}

// Finds the shortest path
double findPath(Coordinate hull[MAXPAIRS], int size, Coordinate pointA, Coordinate pointB, Coordinate path[100], int *pathSize, int side)
{
	*pathSize = 0;
	path[*pathSize].x = pointA.x;
	path[*pathSize].y = pointA.y;
	(*pathSize)++;
	double tempdis = 0.0;
	double totaldis = 0.0;
	double mindis = 1000000000000000.0;
	int flag = 0;

	while (1)
	{

		for (int i = 0; i < size; i++)
		{
			// side is not ngative
			if (getSide(pointA, pointB, hull[i]) != -side)
			{
				for (int j = 0; j < *pathSize; j++)
				{
					if (path[j].x == hull[i].x && path[j].y == hull[i].y)
					{
						// if same, flag is set to 1
						flag = 1;
					}
				}

				if (flag == 0)
				{

					// formula to get distance between points
					tempdis = sqrt((hull[i].x - path[(*pathSize) - 1].x) * (hull[i].x - path[(*pathSize) - 1].x) + (hull[i].y - path[(*pathSize) - 1].y) * (hull[i].y - path[(*pathSize) - 1].y));

					if (tempdis < mindis)
					{
						// Set new min distance
						mindis = tempdis;
						path[*pathSize].x = hull[i].x;
						path[*pathSize].y = hull[i].y;
					}
				}

				flag = 0;
			}
		}

		(*pathSize)++;
		totaldis += mindis;

		mindis = 1000000000000000.0;

		// if orgignal s2 point is found, return distance
		if (pointB.x == path[(*pathSize) - 1].x && pointB.y == path[(*pathSize) - 1].y)
		{
			return totaldis;
		}
	}
}

void bruteConvexHull(Coordinate coordinates[MAXPAIRS], int coodSize, Coordinate temp[MAXPAIRS], int *tempSize)
{

	int i, j, k;
	int isj = 0;
	int isi = 0;
	double part = 0.0;
	double sub = 0.0;
	int left = 0;
	int right = 0;

	for (i = 0; i < coodSize - 1; i++)
	{

		for (j = i + 1; j < coodSize; j++)
		{

			left = 0;
			right = 0;
			double p1 = coordinates[i].x * coordinates[j].y;
			double p2 = coordinates[i].y * coordinates[j].x;
			// calculates the line between two points
			double prod = p1 - p2;
			double px = coordinates[i].x - coordinates[j].x;
			double py = coordinates[j].y - coordinates[i].y;

			for (k = 0; k < coodSize; k++)
			{
				if (k != i)
				{
					// if coordinates are on the same side
					if (k != j)
					{
						part = coordinates[k].x * py + coordinates[k].y * px;
						sub = part - prod;

						if (sub < 0.0)
						{
							// increment right
							right += 1;
						}
						else if (sub > 0.0)
						{
							// increment left
							left += 1;
						}
						else
						{
							break;
						}

						if ((left > 0) && (right > 0))
						{
							break;
						}
					}
				}
			}

			isi = 0;
			isj = 0;
			int num = coodSize - 2;

			if (left == num || right == num)
			{
				// check for duplicates
				for (int l = 0; l < *tempSize; l++)
				{
					if ((temp[l].x == coordinates[i].x) && (temp[l].y == coordinates[i].y))
					{
						isi = 1;
					}
					if ((temp[l].x == coordinates[j].x) && (temp[l].y == coordinates[j].y))
					{
						isj = 1;
					}
				}

				if (isi == 0)
				{
					// add to array
					temp[*tempSize].x = coordinates[i].x;
					temp[*tempSize].y = coordinates[i].y;
					(*tempSize)++;
				}
				if (isj == 0)
				{
					// add to array
					temp[*tempSize].x = coordinates[j].x;
					temp[*tempSize].y = coordinates[j].y;
					(*tempSize)++;
				}
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	Coordinate cood[MAXPAIRS] = {0};
	Coordinate temp[MAXPAIRS] = {0};
	struct timeb start, end;
	int tempSize = 0;
	double dis = 0.0;
	double dis2 = 0.0;
	double totalTime = 0.0;
	Coordinate tempCood[2];
	Coordinate path[100];
	int pathSize = 0;
	Coordinate path2[100];
	int pathSize2 = 0;

	FILE *fp = fopen("data_A2_Q2.txt", "r");

	if (fp == NULL)
	{
		fprintf(stderr, "File could not be opened \n");
		return 0;
	}

	for (int i = 0; i < MAXPAIRS; i++)
	{
		fscanf(fp, "%lf %lf", &cood[i].x, &cood[i].y);
	}

	printf("Enter Two Points:\n");
	printf("Enter first point X:\n");
	scanf("%lf", &tempCood[0].x);
	getchar();
	printf("Enter first point Y:\n");
	scanf("%lf", &tempCood[0].y);
	getchar();
	printf("Enter second point X:\n");
	scanf("%lf", &tempCood[1].x);
	getchar();
	printf("Enter second point Y:\n");
	scanf("%lf", &tempCood[1].y);
	getchar();

	printf("\n");

	ftime(&start);
	bruteConvexHull(cood, MAXPAIRS, temp, &tempSize);
	ftime(&end);

	// calculate time
	totalTime = (end.time - start.time) * 1000 + (end.millitm - start.millitm);

	printf("Brute Force:\n");
	printf("Convex Hull Points: %d\n", tempSize);
	printf("Execution time: %.2fms\n", totalTime);

	printf("\n\n");

	printf("All points on hull\n");
	for (int i = 0; i < tempSize; i++)
	{
		printf("%d. %.1f,%.1f \n", i + 1, temp[i].x, temp[i].y);
	}

	printf("\n");

	// clockwise and counterclockwise
	dis = findPath(temp, tempSize, tempCood[0], tempCood[1], path, &pathSize, 1);
	dis2 = findPath(temp, tempSize, tempCood[0], tempCood[1], path2, &pathSize2, -1);

	if (pathSize == 2)
	{
		printf("Number of points in shortest path including s1 and s2: %d\n", pathSize2);
		for (int i = 0; i < pathSize2; i++)
		{
			printf("X: %.2f Y: %.2f\n", path2[i].x, path2[i].y);
		}
		printf("Total distance : %.4f\n", dis2);
	}
	else if (pathSize2 == 2)
	{
		printf("Number of points in shortest path including s1 and s2: %d\n", pathSize);
		for (int i = 0; i < pathSize; i++)
		{
			printf("X: %.2f Y: %.2f\n", path[i].x, path[i].y);
		}
		printf("Total distance : %.4f\n", dis);
	}
	else if (dis < dis2)
	{
		printf("Number of points in shortest path including s1 and s2: %d\n", pathSize);
		for (int i = 0; i < pathSize; i++)
		{
			printf("X: %.2f Y: %.2f\n", path[i].x, path[i].y);
		}
		printf("Total distance : %.4f\n", dis);
	}
	else
	{
		printf("Number of points in shortest path including s1 and s2: %d\n", pathSize2);
		for (int i = 0; i < pathSize2; i++)
		{
			printf("X: %.2f Y: %.2f\n", path2[i].x, path2[i].y);
		}
		printf("Total distance : %.4f\n", dis2);
	}
}
