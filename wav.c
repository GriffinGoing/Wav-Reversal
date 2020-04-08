#include "wav.h"
#include <stdio.h>
#include <string.h>

/******************************************************
 * This function parses a file (as an array of chars)
 * into the wav type defined in the header 
 * @param contents the char array to be parsed into a wav struct
 *  - should be a .wav file that is passed in
 * ***************************************************/

wav_file* parse( char* contents){
	wav_file* convertedFile;
	convertedFile = (wav_file*) contents;
	return convertedFile;
}
