// Name:  Vy Truong
// Email: vt1044384@swccd.edu
// College ID: 1044384

#include <stdio.h>
#include <stdlib.h>


//fuction prototypes
int calcSums(int **topog, int rows, int cols, int sums[]);
int** malloc2d(int, int);


int main(int argc, char* argv[])
{
    // check program arguments
	if (argc != 2) {
		printf("Usage: ./pathFindP2 topo983by450.txt\n");
		return 1;
	}


    // open file
    FILE *inFile = fopen(argv[1], "r");
    if (inFile == NULL) {
    	printf("Could not open file\n");
        return 1;
    }

	// set up to read the number of rows, columns
	char line[100];
    int *r = malloc(sizeof(int));
    int *c = malloc(sizeof(int));
    if (r == NULL || c== NULL)	{
    	printf("Not enough memory");
    	return 2;
    }

	// read colums
    fscanf(inFile, "%s %d", line, c);

    // read rows
    fscanf(inFile, "%s %d", line, r);

	//skip the next 3 lines
	fgets(line, 100, inFile);	// skip the nrows line
	fgets(line, 100, inFile);
	fgets(line, 100, inFile);
	fgets(line, 100, inFile);	// skip the cellsize line


	//setup the array
	int rows = *r;
    int cols = *c;
    int **topodata = malloc2d(rows, cols);

	//read the topo data
	int i,j;
	for (i = 0; i < rows; i++)	{
		for (j = 0; j < cols; j++) {
			fscanf(inFile, "%d", *(topodata+i) + j);
		}
	}

	// calculate and store the elevation change of each path
    int sumList[rows];
	int row_min = calcSums(topodata, rows, cols, sumList);


	// display the starting row with smallest change
	printf("Row: %d \nChange: %d \n", row_min, sumList[row_min]);

    return 0;
}

/*
	allocate memory for a 2d array
	return the pointer to the 2d array
*/
int** malloc2d(r, c)
{
	int **array2d = malloc(r*sizeof(int*));
	if (array2d == NULL)	{
		printf("Not enough memory");
    	exit(1);
	}

    int k;
    for (k = 0; k < r; k++)	{
    	*(array2d+k) = malloc(c*sizeof(int));
    	if (*(array2d+k) == NULL)	{
			printf("Not enough memory");
	    	exit(1);
		}
    }

    return array2d;
}


/*
	calculate the total change in elevation of each path
	return the index of the row with smallest change
*/
int calcSums(int **topog, int rows, int cols, int sums[])
{

	int sum_min = 4000000;
	int min_row = 0;

    int r, c;
    for (r = 0; r < rows; r++)
    {

		int sum = 0;
		int chosen_row = r;

		// calculate correct sums
		for (c = 0; c < cols-1; c++)
		{

			// the top row
			if (chosen_row == 0)
			{
				// calculate changes
				int forward_straight = abs(topog[chosen_row][c+1] - topog[chosen_row][c]);
				int forward_down = abs(topog[chosen_row+1][c+1] - topog[chosen_row][c]);


				if (forward_straight <= forward_down) {
					sum += forward_straight;	// move forward-straight
				}
				else {
					sum += forward_down;	// forward-down
					chosen_row++;
				}
			}

			// the bottom row
			else if (chosen_row == rows-1)
			{
				// calculate changes
				int forward_straight = abs(topog[chosen_row][c+1] - topog[chosen_row][c]);
				int forward_up = abs(topog[chosen_row-1][c+1] - topog[chosen_row][c]);


				if (forward_straight <= forward_up) {
					sum += forward_straight;		// move forward-straight
				}
				else {
					sum += forward_up;		// move forward-up
					chosen_row--;
				}
			}

			// middle rows
			else
			{
				// calculate the changes
				int forward_straight = abs(topog[chosen_row][c+1] - topog[chosen_row][c]);
				int forward_up = abs(topog[chosen_row-1][c+1] - topog[chosen_row][c]);
				int forward_down = abs(topog[chosen_row+1][c+1] - topog[chosen_row][c]);


				if (forward_straight <= forward_up)
				{
					if (forward_straight <= forward_down) {
						sum += forward_straight;
					}
					else {
						sum += forward_down;
						chosen_row++;
					}
				}

				// upward < forward
				else
				{
					if (forward_up < forward_down) {
						// move upward
						sum += forward_up;
						chosen_row--;
					}
					else if (forward_up > forward_down) {
						// move downward
						sum += forward_down;
						chosen_row++;
					}
					else {
						// choose random
						if (rand() % 2 == 1) {
							// move dowward
							sum += forward_down;
							chosen_row++;
						}
						else {
							// move upward
							sum += forward_up;
							chosen_row--;
						}
					}
				} //end upward < forward
			} //end middle rows
		} //end calculating sum

		sums[r] = sum;

		if (sum < sum_min)	{
			sum_min = sum;
			min_row = r;
		}
	}

	return min_row;
}