#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include "file.h"

size_t read_file( char* filename, char **buffer ){
	FILE* fptr;
	fptr = fopen(filename, "r"); //open file or reading

	if (fptr == NULL) { //if file is not found
		printf("The file '%s' does not exist", filename);
		exit(1); //stop with exit code 1 (general errors)
	}
	
	//use stat function to evaluate file properties
	struct stat fileStats;
	stat(filename, &fileStats);
	size_t fileSize = fileStats.st_size;

	//Allocate memory in the buffer to the size of the file
	*buffer = malloc(fileSize);

	//read the data to the buffer
	fread(*buffer, sizeof(char), fileSize, fptr);
	fclose(fptr);
	return fileSize;
	
}

size_t write_file( char* filename, char *buffer, size_t size){
	FILE* fptr = fopen(filename, "w");
	fwrite(buffer, sizeof(char), size, fptr);
	fclose(fptr);
	return size;
}
