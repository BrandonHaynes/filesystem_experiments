#include <stdio.h>
#include <time.h>
#include <unistd.h> 
#include "clearCache.h"

#define BUFFER_SIZE 1024*1024
#define NUM_LOOPS 100
// #define BILLION  1000000000L

int readFile(const char* fileString){
    FILE *fptr = fopen(fileString, "rb");
    char buffer[BUFFER_SIZE];
    int bytes_read = 0;
    // int total_bytes = 0;

    if(fptr==NULL)
        perror("fopen");

    //read buffer_size records of size 1 byte.
    while((bytes_read = fread(buffer, 1, BUFFER_SIZE, fptr)) == BUFFER_SIZE); //{ 
        // total_bytes += bytes_read;
    // }

    // total_bytes += bytes_read;
    // printf("Total Bytes: %i\n\n", total_bytes);


    if(bytes_read < 0)
        perror("fread");
    else if(fclose(fptr) != 0)
        perror("fclose");

    return 0;
}

int readFiles(){
    char buffer[256];
    for(int j=0; j<16; j++){
        for(int i = 0; i < 2; i++){ // max = 18
            snprintf(buffer, 256, "/home/ubuntu/inputs/tiles/50/%i/%i.hevc", j, i);
            readFile(buffer);
        }
        for(int i = 2; i < 6; i++){ 
            snprintf(buffer, 256, "/home/ubuntu/inputs/tiles/9000/%i/%i.hevc", j, i);
            readFile(buffer);
        }
        for(int i = 6; i < 8; i++){ // max = 18
            snprintf(buffer, 256, "/home/ubuntu/inputs/tiles/50/%i/%i.hevc", j, i);
            readFile(buffer);
        }
        for(int i = 8; i < 12; i++){ 
            snprintf(buffer, 256, "/home/ubuntu/inputs/tiles/9000/%i/%i.hevc", j, i);
            readFile(buffer);
        }
         for(int i = 12; i < 14; i++){ // max = 18
            snprintf(buffer, 256, "/home/ubuntu/inputs/tiles/50/%i/%i.hevc", j, i);
            readFile(buffer);
        }
        for(int i = 14; i < 18; i++){ 
            snprintf(buffer, 256, "/home/ubuntu/inputs/tiles/9000/%i/%i.hevc", j, i);
            readFile(buffer);
        }
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
        // readFile(argv[1]);
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


    // clock_t start = clock();
    // for(int i=0; i<NUM_LOOPS; i++){
    //     // readFile(argv[1]);
    //     clearCache();
    // }
    // clock_t end = clock();
    // elapsed_time += (end - start)/(double)CLOCKS_PER_SEC;


    // struct timespec start, end, total = {0};
    // // if(argc != 2)
    // //     perror("Program requires the filename as input");

    // for(int i=0; i<NUM_LOOPS; i++){
    //     clock_gettime(CLOCK_MONOTONIC, &start);
    //     // readFile(argv[1]);
    //     readFiles();
    //     clock_gettime(CLOCK_MONOTONIC, &end);
    //     total.tv_sec += (end.tv_sec - start.tv_sec);
    //     total.tv_nsec += (end.tv_nsec - start.tv_nsec);
    //     clearCache();
    // }
    // elapsed_time = total.tv_sec + (total.tv_nsec/BILLION);





