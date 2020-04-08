#include <stdio.h>
#include <string.h>
#include "wav.h"
#include "file.h"

/*********************************************
 * The all-important .wav reversal process
 ********************************************/

int main (int argc, char** argv) {
	
	//check the number of arguments and provide feedback
	if (argc != 3) {
		printf("Invalid number of arguments. Pass in only the .wav file and desired output file name as parameters.\n");
		return 1; //exit with general error code
	}
	
	//assign clear variable names to arguments. not necessary, but more verbose
	char* inputFileName = argv[1];
	char* outputFileName = argv[2];

	//we need this to read in the file data
	char* buffer;

	//we'll use this string to check the file format before reversal occurs
	char properFormat[4] = "RIFF";
	
	//read in the file to the buffer and determine filesize
	int fileSize = read_file(argv[1], &buffer);

	// read the data to the wav_file format
	wav_file* song = parse(buffer);	
	
	//check the format of the input file to make sure we're not wasting our time
	for (int i = 0; i < 4; i++) {
		if (song->riff[i] != properFormat[i]) {
			printf("Input file was not in .wav format\n");
			return 1; //exit with general use error code
		}
	}
	
	//print file info
	//i believe the strange block-like characters being printed are a result of not
	//having a null string terminator in the char arrays
	printf("File: %s\n", inputFileName);
	printf("==========================\n");
	printf(" - File size is %i. Read %i bytes.\n", fileSize, song->dataSize);
	printf(" - Format is '%s' with format data length %i\n.", song->format, song->formatLength);
	printf(" - Format type is %s format\n", song->wave);
	printf(" - %i channels with a sample rate of %i.\n", song->numChannels, song->sampleRate);
	printf(" - %i byte rate, %i alignment, %i bits per sample.\n", song->byteRate, song->blockAlignment, song->bitsPerSample);
	printf(" - Data is '%s' and data size is %i\n", song->beginData, song->dataSize);
	
	
	//set up data reversal
	int dataBegins = 44; //position at which the data to reverse begins

	//Dalton gave me a hand with this math because my brain doesn't work apparently
	int sampleSwapSize = (song->bitsPerSample) * (song->numChannels);

	int dataEnds = dataBegins + song->dataSize - sampleSwapSize;
	
	//temp storage for a single sample or sample group (based on channls)
	char temp[sampleSwapSize];
	
	//reverse the data to make something either really cool or really concerning
	while (dataBegins != dataEnds){
		memcpy(&temp, &buffer[dataBegins], sampleSwapSize);
		memcpy(&buffer[dataBegins], &buffer[dataEnds], sampleSwapSize);
		memcpy(&buffer[dataEnds], &temp, sampleSwapSize);
		dataBegins = dataBegins + sampleSwapSize;
		dataEnds = dataEnds - sampleSwapSize;

		//account for uneven swapping
		if(dataBegins > dataEnds)
			dataBegins = dataEnds;
	}
	

	//write the newly reversed data in the buffer to a new file, free the buffer memory
	write_file(outputFileName, buffer, fileSize);
	free(buffer);
	return 0;


}

