////////////////////////////////////////////////////////////////////////////////
// Main File:        (name of file with main function)
// This File:        (name of this file)
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Fall 2018
//
// Author:           (your name)
// Email:            (your wisc email address)
// CS Login:         (your CS login name)
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of 
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *COMMA = ","; 

// Structure representing Matrix
// size: Dimension of the square (size*size)
// array: 2D array of integers
typedef struct _Square {  
    int size;
    int **array;
} Square;

/* TODO:
 * Retrieves from the first line of the input file,
 * the size of the square matrix.
 * 
 * fp: file pointer for input file
 * size: pointer to size of the square matrix
 */
void get_dimensions(FILE *fp, int *size) {        
	char *line = NULL; 
	size_t len = 0;
	if (getline(&line, &len, fp) == -1) { 
		printf("Error in reading the file\n");
		exit(1); 
	}

	char *token = NULL; 
	token = strtok(line, COMMA);
	*size = atoi(token); 

}

/* PARTIALLY COMPLETED:
 * Traverses a given layer from the square matrix
 * 
 * array: Heap allocated 2D square matrix
 * rows: pointer to size of square
 * layer: layer number to be traversed
 * op: pointer to the output file
 */
void traverse_layer(int **array, int size, int layer, FILE *op) {       
	int row_num, col_num;
	int i,j;
	
	//corner case: size is odd & the layer is last so only one entry to print
        if(size % 2 == 1 && layer == (size + 1) / 2 - 1){
                fprintf(op, "%d\n", *(*(array + layer) + layer));
                return;
        }

	//Traverse upper row from left to right with appropriate bounds
	row_num = layer;
	for(int x = layer; x < size-layer; x++) {
		fprintf(op,"%i ", *(*(array + row_num) + x));
		printf("%i ", *(*(array + row_num) + x));

	}
	printf("\n");


	//Traverse right column from top to bottom with appropriate bounds
	col_num = size-layer-1;
	for(int x = layer+1; x < size-layer; x++) {
		fprintf(op,"%i ", *(*(array+x)+col_num));
		printf("%i ", *(*(array+x)+col_num));
	
	}
	printf("\n");

	//Traverse lower row from right to left with appropriate bounds
	row_num = size-layer-1;
	for(int x = size-layer-2; x >= layer; x--) {
		fprintf(op,"%i ", *(*(array+row_num)+x));
		printf("%i ", *(*(array+row_num)+x));
		
	}
	printf("\n");
	//Traverse left column from bottom to top with appropriate bounds
	col_num = layer;
	for(int x = size-layer-2; x > layer; x--) {
		fprintf(op,"%i ", *(*(array+x)+col_num));
		printf("%i ", *(*(array+x)+col_num));


	}
	printf("\n");

}


/* COMPLETED:
 * Traverses the square matrix spirally
 * 
 * square: pointer to a structure that contains 2D square matrix
 * op: pointer to the output file
 */
void traverse_spirally(Square *square, FILE *op) {       
	int size = square->size; 
	int num_layers = 0;   
	num_layers = size/2; 
	if(size%2 == 1) {
		num_layers++;
	}
	 
	int i;
	for(i = 0; i < num_layers; i++) {
		traverse_layer(square->array, size, i, op);
	}
}

/* PARTIALLY COMPLETED:
 * This program reads a square matrix from the input file
 * and outputs its spiral order traversal to the output file
 *
 * argc: CLA count
 * argv: CLA value
 */
int main(int argc, char *argv[]) {                  

	int size;
	//Check if number of arguments is correct
	if(argc != 3)
	{
		printf("./traverse_spiral <input_filename> <output_filename>\n");
		exit(1);
	}

	//Open the file and check if it opened successfully
	char *line = NULL;
	size_t len = 0;
	char *token = NULL;
	FILE *fp = fopen(*(argv + 1), "r");
	
	if (fp == NULL) {
		printf("Cannot open file for reading\n");
		exit(1);
	}

	//Call the function get_dimensions to retrieve size of the square matrix
	get_dimensions(fp,&size);
	//Dynamically allocate a 2D array as per the retrieved dimensions
	int **spiral;
		spiral = malloc(sizeof(int *) * size);
		if(spiral == NULL)	//Malloc did not allocate memory correctly
		{
			printf("spiral Memory Allocation Error; Exiting\n");
			exit(1);
		}
		for(int x = 0; x < size; x++)
		{
			spiral[x] = malloc(sizeof(int) * size); //Allocating 2D array of arrays
			if(spiral[x] == NULL)	//Malloc did not allocate memory correctly
			{
				printf("spiral Memory Allocation Error; Exiting\n");
				exit(1);
			}
		}



	//Read the file line by line by using the function getline as used in get_dimensions
	//Tokenize each line wrt comma to store the values in the square matrix

	for(int i = 0; i < size; i++)
	{
		if (getline(&line, &len, fp) == -1) {
			printf("Error while reading the file\n");
			exit(1);	
		}
		token = strtok(line, COMMA);
		for (int j = 0; j < size; j++) {
			
			*(*(spiral+i) + j) = atoi(token);	
			token = strtok(NULL, COMMA);
		}
	}

	//Create a structure and initialize its size and array fields appropriately
	Square *square = malloc(sizeof(Square));
	square->size = size;
	square->array = spiral;


	//Open the output file
	FILE *ofp = fopen(argv[2],"w");
	if(ofp == NULL)
	{
		//fprintf("Can't open output file %s!\n", argv[2]);
		exit(1);
		fclose(fp);
	}	

	//Call the function traverse_spirally
	traverse_spirally(square, ofp);
	//Free the dynamically allocated memory

	//Close the input file

	//Close the output file

	return 0; 
}     
