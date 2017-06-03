#include <stdio.h>
#include <stdlib.h>
#include "tiledb.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h> // for close


void writeSizes(int segment, char *data, size_t *offsets, size_t *buffer_sizes);
int doread(TileDB_CTX *context, void *subarray50, void *subarray9000);

int clearCache(){
    int fd;
    const char* data = "3";
    sync();
    fd = open("/proc/sys/vm/drop_caches", O_WRONLY);
    write(fd, data, sizeof(char));
    close(fd);
    return 0;
}

int read(void* context, TileDB_Array *array, int64_t *subarray) {
/*
  TileDB_Array* array;
  tiledb_array_init(
      context,                                          // Context
      &array,                                           // Array object
      array_name,                       // Array name
      TILEDB_ARRAY_READ,                                // Mode
      subarray,                                             // Whole domain
      NULL,                                             // All attributes
      0);                                               // Number of attributes
*/
  #define SIZE 32*1024*1024
  size_t offsets[16*18*1024];
  char *data = (char*)malloc(SIZE);
  void* buffers[] = { offsets, data };

  size_t buffer_sizes[] =
  {
      sizeof(offsets),
      SIZE
      //sizeof(data)
  };


  do
    {
        buffer_sizes[0] = sizeof(offsets);
        buffer_sizes[1] = SIZE;
        int result = tiledb_array_read(array, buffers, buffer_sizes);
//printf("%d %d\n", tiledb_array_overflow(array, 0), buffer_sizes[1]);
    }
while(tiledb_array_overflow(array, 0) == 1);
/*
      for(int j = 0; j < 16; j++)
      {
        buffer_sizes[0] = sizeof(offsets);
        buffer_sizes[1] = 512*1024*1024;
        int result = tiledb_array_read(array, buffers, buffer_sizes);
printf("%d\n", tiledb_array_overflow(array, 0));
//       writeSizes(j, data, offsets, buffer_sizes);
      }
*/
//  tiledb_array_finalize(array);

  return 0;
}

void writeSizes(int segment, char *data, size_t *offsets, size_t *buffer_sizes)
{
  // Print only non-empty cell values
  //int64_t result_num = buffer_sizes[0] / sizeof(int);
  //printf("Resultnum %ld\n", result_num);
  int result_num = 18;

  /*printf("Resultnum %d\n", result_num);

  for(size_t i = 0; i < result_num; i++)
    printf("offset: %ld\n", offsets[i]);*/

  //for(int i =0; i < result_num + 1; i++)
  //   printf("offset %ld\n", offsets[i]);
  printf("%d rtotal: %ld\n", segment, buffer_sizes[1]);

  for(int i=0; i < result_num; ++i) {
      size_t var_size = (i != result_num-1) ? offsets[i+1] - offsets[i]
                                            : buffer_sizes[1] - offsets[i];
      //printf("%d %d: size %ld\n", segment, i, var_size);
      //if(var_size > 16)
	//  printf("%ld\n", var_size);
      //else
       //   printf("%.*s\n", int(var_size), &data[offsets[i]]);
  }
}


void read0_18(TileDB_CTX* context)
{
//read(context, "workspace/brandon/videos9000", NULL);
}

clock_t read18_0(TileDB_CTX* context)
{
return doread(context, NULL, NULL);
}

clock_t read17_1(TileDB_CTX* context)
{
int64_t subarray[] = {2, 2, 1, 1, 0, 15};
return doread(context, NULL, subarray);
}

clock_t read14_4(TileDB_CTX* context)
{
int64_t subarray[] = {2, 5, 1, 1, 0, 15};
return doread(context, NULL, subarray);
}

clock_t read16_2(TileDB_CTX* context)
{
int64_t subarray[] = {0, 5, 0, 0, 0, 0};
return doread(context, NULL, subarray);
}

clock_t read6_12(TileDB_CTX* context)
{
int64_t subarray[] = {3, 5, 0, 2, 0, 15};
return doread(context, NULL, subarray);
}

int doread(TileDB_CTX *context, void *subarray50, void *subarray9000)
{
TileDB_Array *array50, *array9000;
tiledb_array_init(context, &array50, "workspace/brandon/videos50", TILEDB_ARRAY_READ, subarray50, NULL, 0);
tiledb_array_init(context, &array9000, "workspace/brandon/videos9000", TILEDB_ARRAY_READ, subarray9000, NULL, 0);

clock_t start = clock();
read(NULL, array50, NULL);
read(NULL, array9000, NULL);
return clock() - start;
}

int main()
{
  TileDB_CTX* context;
  tiledb_ctx_init(&context, NULL);

  size_t runs = 10;
  clock_t elapsed_time = 0;

  for(int i = 0; i < runs; i++)
    elapsed_time += read16_2(context);

  double t =  elapsed_time/(double)CLOCKS_PER_SEC;
  printf("TIME FOR ALL LOOPS (seconds): %f\n\n", t);
  printf("AVERAGE TIME (seconds): %f\n\n", t/runs);

  tiledb_ctx_finalize(context);
}
