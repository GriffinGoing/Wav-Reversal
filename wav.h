#ifndef WAV_H
#define WAV_H

typedef struct wav_file {
	//B and L refer to endian type (Big or Little)
	char riff[4]; //B
	int chunkSize; //L
	char wave[4]; //B
	char format[4]; //B
	int formatLength; //L
	short formatType; //L
	short numChannels; //L
	int sampleRate; //L
	int byteRate; //L
	short blockAlignment; //L
	short bitsPerSample; //L
	char beginData[4]; //B
	int dataSize; //L, number of bytes in data section
} wav_file;

wav_file* parse(char* contents);

#endif
