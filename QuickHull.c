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

int getSide(Coordinate a, Coordinate b, Coordinate c)
{

	double p1 = (b.x - a.x) * (c.y - a.y);
	double p2 = (b.y - a.y) * (c.x - a.x);
	double calc = p1 - p2;

	// left
	if (calc > 0)
	{
		return 1;
	} // right
	else if (calc < 0)
	{
		return -1;
	} // Along the same line
	else
	{
		return 0;
	}
}

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

void divideAndConquer(Coordinate coordinates[MAXPAIRS], Coordinate pointA, Coordinate pointB, int coodSize, int side, Coordinate temp[MAXPAIRS], int *tempSize)
{

	int point = -1;
	int check1 = 0;
	int check2 = 0;
	double max = 0.0;
	Coordinate pt;

	for (int i = 0; i < coodSize; i++)
	{

		pt.x = coordinates[i].x;
		pt.y = coordinates[i].y;
		double p1 = (pointB.x - pointA.x) * (pt.y - pointA.y);
		double p2 = (pointB.y - pointA.y) * (pt.x - pointA.x);
		// calculates the line between two points
		double calc = p1 - p2;

		if (calc < 0)
		{
			calc = -calc;
		}

		if (getSide(pointA, pointB, coordinates[i]) == side && calc > max)
		{

			point = i;
			max = calc;
		}
	}

	// If no max point is found
	if (point == -1)
	{
		// Make sure points are not duplicate
		for (int i = 0; i < *tempSize; i++)
		{
			if (pointB.x == temp[i].x && pointB.y == temp[i].y)
			{
				check1 = 1;
			}
			if (pointA.x == temp[i].x && pointA.y == temp[i].y)
			{
				check2 = 1;
			}
		}

		for (int i = 0; i < coodSize; i++)
		{
			// Add to array and check for duplicates
			if (coordinates[i].x == pointB.x && coordinates[i].y == pointB.y && check1 == 0)
			{

				temp[*tempSize].x = coordinates[i].x;
				temp[*tempSize].y = coordinates[i].y;
				(*tempSize)++;

				// Add to array and check for duplicates
			}
			else if (coordinates[i].x == pointA.x && coordinates[i].y == pointA.y && check2 == 0)
			{

				temp[*tempSize].x = coordinates[i].x;
				temp[*tempSize].y = coordinates[i].y;
				(*tempSize)++;
			}
		}

		return;
	}

	// recursively call function
	divideAndConquer(coordinates, coordinates[point], pointA, coodSize, -getSide(coordinates[point], pointA, pointB), temp, tempSize);
	divideAndConquer(coordinates, coordinates[point], pointB, coodSize, -getSide(coordinates[point], pointB, pointA), temp, tempSize);
}

int main(int argc, char const *argv[])
{
	Coordinate cood[MAXPAIRS] = {0};
	Coordinate temp2[MAXPAIRS] = {0};
	Coordinate tempCood[2];
	struct timeb start, end;
	int tempSize2 = 0;
	double dis = 0.0;
	double dis2 = 0.0;
	double totalTime;

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

	ftime(&start);
	divideAndConquer(cood, tempCood[0], tempCood[1], MAXPAIRS, 1, temp2, &tempSize2);
	// Both sides
	divideAndConquer(cood, tempCood[0], tempCood[1], MAXPAIRS, -1, temp2, &tempSize2);
	ftime(&end);

	totalTime = (end.time - start.time) * 1000 + (end.millitm - start.millitm);
	printf("\nDivide and Conquer:\n");
	printf("Convex Hull Points: %d\n", tempSize2);
	printf("Execution time: %.1fms\n", totalTime);

	printf("\n");

	printf("All points on hull\n");
	for (int i = 0; i < tempSize2; i++)
	{
		printf("%d %.1f,%.1f \n", i + 1, temp2[i].x, temp2[i].y);
	}

	printf("\n");

	dis = findPath(temp2, tempSize2, tempCood[0], tempCood[1], path, &pathSize, 1);
	dis2 = findPath(temp2, tempSize2, tempCood[0], tempCood[1], path2, &pathSize2, -1);

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
