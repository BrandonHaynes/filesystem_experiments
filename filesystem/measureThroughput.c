#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 
#include "clearCache.h"

#define NUM_LOOPS 65 // gives a total of 1040 random tiles read 
#define CHUNKSIZE 24010000
#define BUFFER_SIZE 1024*1024

int readRandomFromFile(const char* fileString){
    FILE *fptr = fopen(fileString, "rb");
    char buffer[BUFFER_SIZE];
    int bytes_read = 0;
    while((bytes_read = fread(buffer, 1, BUFFER_SIZE, fptr)) == BUFFER_SIZE);

    if(bytes_read < 0)
        perror("fread");
    else if(fclose(fptr) != 0)
        perror("fclose");
    return 0;
}

int readRandomFromPadded(const char* fileString, int random_tile){
    FILE *fptr = fopen(fileString, "rb");
    int bytes_read;
    fseek(fptr, CHUNKSIZE*random_tile, SEEK_CUR);
    char* buffer = (char*)malloc(CHUNKSIZE);
    bytes_read = fread(buffer, 1, CHUNKSIZE, fptr);
    free(buffer);
    if(bytes_read < 0)
        perror("fread of bytes");
    else if(fclose(fptr) != 0)
        perror("fclose");
    return 0;
}

int readRandomFromAmalgamated(const char* fileString, int random_tile){
    FILE *fptr = fopen(fileString, "rb");
    int read_file_size;
    int size_read;
    int bytes_read;
    int num_files = 0;

    if(fptr==NULL)
        perror("fopen");

    size_read = fread(&read_file_size, 4, 1, fptr);
    while(size_read == 1){
        if(num_files==random_tile){ // read if it's the random tile 
            char* buffer = (char*)malloc(read_file_size);
            bytes_read = fread(buffer, 1, read_file_size, fptr);
            free(buffer);
            break;
        }
        else{ // otherwise just scan to the next size
            fseek(fptr, read_file_size, SEEK_CUR);
            num_files++;
            size_read = fread(&read_file_size, 4, 1, fptr);
        }
    }

    if(bytes_read < 0)
        perror("fread of bytes");
    if(size_read < 0)
        perror("fread of size");
    else if(fclose(fptr) != 0)
        perror("fclose");

    return 0;
}

int measureThroughput(){
    char fileName[256];
    for(int time=0; time<16; time++){
        int random_tile = rand() % 18;
        
        // snprintf(fileName, 256, "/home/ubuntu/inputs/tiles/9000/%i/%i.hevc", time, random_tile);
        // readRandomFromFile(fileName);

        // snprintf(fileName, 256, "/home/ubuntu/inputs/tiles/9000/%i/concatenated", time);
        // readRandomFromAmalgamated(fileName, random_tile);

        snprintf(fileName, 256, "/home/ubuntu/inputs/tiles/9000/%i/concatenated_padded_24M", time);
        readRandomFromPadded(fileName, random_tile);
    }
    return 0;
}

int main(int argc, char *argv[]){
    double elapsed_time = 0;
    clock_t start, end ={0};

    start = clock();
    for(int i=0; i<NUM_LOOPS; i++){
        measureThroughput();
    }
    end = clock();
    elapsed_time = (end-start)/(double)CLOCKS_PER_SEC;
    printf("TIME FOR ALL LOOPS (seconds): %f\n\n", elapsed_time);
    // printf("AVERAGE TIME (seconds): %f\n\n", elapsed_time/NUM_LOOPS);
    return 0;
}




