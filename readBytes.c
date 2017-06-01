#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 
#include "clearCache.h"

#define NUM_LOOPS 100
#define CHUNKSIZE 24010000

int readBytes(const char* fileString){
    FILE *fptr = fopen(fileString, "rb");
    char* buffer = (char*)malloc(CHUNKSIZE);
    int bytes_read = 0;
    // int total_bytes = 0;
    // int num_chunks = 0;

    // printf("Size: %i\n", CHUNKSIZE);

    if(fptr==NULL)
        perror("fopen");

    while((bytes_read = fread(buffer, 1, CHUNKSIZE, fptr)) == CHUNKSIZE); //{
        // total_bytes += bytes_read;
    //     num_chunks++;
    // }
    // total_bytes += bytes_read;
    free(buffer);

    // printf("Total Bytes: %i\n\n", total_bytes);
    // printf("Number of Chunks: %i\n\n", num_chunks);

    if(bytes_read < 0)
        perror("fread");
    else if(fclose(fptr) != 0)
        perror("fclose");

    return 0;
}

int readFiles(){
    char filenameBuffer[256];
    for(int j=0; j<1; j++){ // max = 16
        snprintf(filenameBuffer, 256, "/home/ubuntu/inputs/tiles/9000/%i/concatenated_padded_24M", j);
        readBytes(filenameBuffer);
    }
    return 0;
}

int main(int argc, char *argv[]){
    double elapsed_time = 0;
    clock_t start, end, total = {0};

    for(int i=0; i<NUM_LOOPS; i++){
        start = clock();
        readFiles();
        // readBytes(argv[1], atoi(argv[2]));
        end = clock();
        total += (end-start);
        clearCache();
    } 

    // clock_t start = clock();
    // for(int i=0; i<NUM_LOOPS; i++){
    //     readBytes(argv[1], atoi(argv[2]));
    // }
    // clock_t end = clock();
    // elapsed_time += (end - start)/(double)CLOCKS_PER_SEC;
    elapsed_time = (total)/(double)CLOCKS_PER_SEC;
    printf("TIME FOR ALL LOOPS (seconds): %f\n\n", elapsed_time);
    printf("AVERAGE TIME (seconds): %f\n\n", elapsed_time/NUM_LOOPS);
    return 0;
}