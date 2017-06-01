#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 
#include "clearCache.h"

#define NUM_LOOPS 100
#define CHUNKSIZE 24010000

int readBytes(const char* fileString50, const char* fileString9000){
    FILE *fptr50 = fopen(fileString50, "rb");
    FILE *fptr9000 = fopen(fileString9000, "rb");
    char* buffer = (char*)malloc(CHUNKSIZE*8);
    int bytes_read = 0;
    // int total_bytes = 0;
    // int num_chunks = 0;

    // printf("Size: %i\n", CHUNKSIZE);

    if(fptr50==NULL || fptr9000==NULL)
        perror("fopen");

    // amalgamation 1 
    fseek(fptr9000, CHUNKSIZE*8, SEEK_CUR);
    bytes_read = fread(buffer, 1, CHUNKSIZE*8, fptr50);
    fseek(fptr50, CHUNKSIZE, SEEK_CUR);
    bytes_read = fread(buffer, 1, CHUNKSIZE, fptr9000);
    bytes_read = fread(buffer, 1, CHUNKSIZE*9, fptr50);

    // amalgamation 2
    // fseek(fptr9000, CHUNKSIZE*8, SEEK_CUR);
    // bytes_read = fread(buffer, 1, CHUNKSIZE*8, fptr50);
    // fseek(fptr50, CHUNKSIZE*2, SEEK_CUR);
    // bytes_read = fread(buffer, 1, CHUNKSIZE*2, fptr9000);
    // bytes_read = fread(buffer, 1, CHUNKSIZE*8, fptr50);


    // amalgamation 3
    // fseek(fptr9000, CHUNKSIZE*7, SEEK_CUR);
    // bytes_read = fread(buffer, 1, CHUNKSIZE*7, fptr50);
    // fseek(fptr50, CHUNKSIZE*4, SEEK_CUR);
    // bytes_read = fread(buffer, 1, CHUNKSIZE*4, fptr9000);
    // bytes_read = fread(buffer, 1, CHUNKSIZE*7, fptr50);

    // amalgamation 4
    // for(int j=0; j<3; j++){
    //     fseek(fptr9000, CHUNKSIZE*2, SEEK_CUR);
    //     bytes_read = fread(buffer, 1, CHUNKSIZE*2, fptr50);
    //     fseek(fptr50, CHUNKSIZE*4, SEEK_CUR);
    //     bytes_read = fread(buffer, 1, CHUNKSIZE*4, fptr9000);
    // }
    
    // printf("Total Bytes: %i\n\n", total_bytes);
    // printf("Number of Chunks: %i\n\n", num_chunks);
    free(buffer);
    if(bytes_read < 0)
        perror("fread of bytes");
    else if(fclose(fptr9000) != 0 || fclose(fptr50) != 0)
        perror("fclose");

    return 0;
}

int readFiles(){
    char buffer50[256];
    char buffer9000[256];
    for(int j=0; j<16; j++){ // max=16
        snprintf(buffer50, 256, "/home/ubuntu/inputs/tiles/50/%i/concatenated_padded_24M", j);
        snprintf(buffer9000, 256, "/home/ubuntu/inputs/tiles/9000/%i/concatenated_padded_24M", j);
        readBytes(buffer50, buffer9000);
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