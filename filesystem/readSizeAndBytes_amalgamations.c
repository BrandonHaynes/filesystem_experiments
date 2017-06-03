#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 
#include "clearCache.h"

#define NUM_LOOPS 5

int readSizeAndBytes(const char* fileString50, const char* fileString9000){
    FILE *fptr50 = fopen(fileString50, "rb");
    FILE *fptr9000 = fopen(fileString9000, "rb");
    int read_file_size_50;
    int read_file_size_9000;
    int size_read_50;
    int size_read_9000;
    int bytes_read;
    int num_files = 0;

    if(fptr50==NULL || fptr9000==NULL)
        perror("fopen");

    size_read_50 = fread(&read_file_size_50, 4, 1, fptr50);
    size_read_9000 = fread(&read_file_size_9000, 4, 1, fptr9000);
    while(size_read_50 == 1 && size_read_9000 == 1){
        // printf("Size of file %i: %i\n", (num_files+1), read_file_size);

        // if( (num_files < 8  || num_files > 8) ){ // amalgamation 1 

        // if( (num_files < 8  || num_files > 9) ){ // amalgamation 2

        if( (num_files < 7  || num_files > 10) ){  // amalgamation 3

        // if( (num_files > -1  && num_files < 2) || (num_files > 5 && num_files < 8) 
        //     || (num_files > 11 && num_files < 14) ){ // amalgamation 4


            char* buffer = (char*)malloc(read_file_size_50);
            bytes_read = fread(buffer, 1, read_file_size_50, fptr50);
            free(buffer);

            fseek(fptr9000, read_file_size_9000, SEEK_CUR);

            if(bytes_read == read_file_size_50){
                size_read_50 = fread(&read_file_size_50, 4, 1, fptr50);
                size_read_9000 = fread(&read_file_size_9000, 4, 1, fptr9000);
            }

            else
                break;
        }

        else{
            char* buffer = (char*)malloc(read_file_size_9000);
            bytes_read = fread(buffer, 1, read_file_size_9000, fptr9000);
            free(buffer);

            fseek(fptr50, read_file_size_50, SEEK_CUR);

            if(bytes_read == read_file_size_9000){
                size_read_50 = fread(&read_file_size_50, 4, 1, fptr50);
                size_read_9000 = fread(&read_file_size_9000, 4, 1, fptr9000);
            }

            else
                break;
        }
        
        num_files++;
        
        // printf("Bytes read: %i\n", bytes_read);
        // 
        
        
    }

    // printf("Number of Files Read: %i\n", num_files);

    if(bytes_read < 0)
        perror("fread of bytes");
    if(size_read_50 < 0 || size_read_9000 < 0)
        perror("fread of size");
    else if(fclose(fptr9000) != 0 || fclose(fptr50) != 0)
        perror("fclose");

    return 0;
}

int readFiles(){
    char buffer50[256];
    char buffer9000[256];
    for(int j=0; j<16; j++){
        snprintf(buffer50, 256, "/home/ubuntu/inputs/tiles/50/%i/concatenated", j);
        snprintf(buffer9000, 256, "/home/ubuntu/inputs/tiles/9000/%i/concatenated", j);
        readSizeAndBytes(buffer50, buffer9000);
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