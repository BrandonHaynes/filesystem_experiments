#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 
#include "clearCache.h"

#define NUM_LOOPS 100

int readSizeAndBytes(const char* fileString){
    FILE *fptr = fopen(fileString, "rb");
    int read_file_size;
    int size_read;
    int bytes_read;
    // int num_files = 0;

    if(fptr==NULL)
        perror("fopen");

    size_read = fread(&read_file_size, 4, 1, fptr);
    while(size_read == 1){
        // printf("Size of file %i: %i\n", (num_files+1), read_file_size);
        char* buffer = (char*)malloc(read_file_size);
        bytes_read = fread(buffer, 1, read_file_size, fptr);
        free(buffer);
        // printf("Bytes read: %i\n", bytes_read);
        // num_files++;
        if(bytes_read == read_file_size){
            size_read = fread(&read_file_size, 4, 1, fptr);
        }
        else
            break;
    }

    // printf("Number of Files Read: %i\n", num_files);

    if(bytes_read < 0)
        perror("fread of bytes");
    if(size_read < 0)
        perror("fread of size");
    else if(fclose(fptr) != 0)
        perror("fclose");

    return 0;
}

int readFiles(){
    char buffer[256];
    for(int j=0; j<16; j++){
        snprintf(buffer, 256, "/home/ubuntu/inputs/tiles/50/%i/concatenated", j);
        readSizeAndBytes(buffer);
    }
    return 0;
}

int main(int argc, char *argv[]){
    double elapsed_time = 0;
    clock_t start, end, total ={0};
    // if(argc != 2)
    //     perror("Program requires the filename as input");

    for(int i=0; i<NUM_LOOPS; i++){
        start = clock();
        readFiles();
        end = clock();
        total += (end-start);
        clearCache();
    }

    elapsed_time = (total)/(double)CLOCKS_PER_SEC;
    printf("TIME FOR ALL LOOPS (seconds): %f\n\n", elapsed_time);
    printf("AVERAGE TIME (seconds): %f\n\n", elapsed_time/NUM_LOOPS);
    return 0;
}