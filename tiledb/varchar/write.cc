#include <stdio.h>
#include <stdlib.h>
#include "tiledb.h"
#include <string.h>

size_t read(const char* filename, char** buffer)
{
  FILE *f = fopen(filename, "rb");
  size_t size = fread(*buffer, 1, 32*1024*1024, f);
  fclose(f);
  *buffer += size;
  return size;
}

int main() {
  // Initialize context with the default configuration parameters
  TileDB_CTX* context;
  tiledb_ctx_init(&context, NULL);

  // Initialize array
  TileDB_Array* array;
  tiledb_array_init(
      context,                                   // Context
      &array,                                    // Array object
      "workspace/brandon/videos9000",                // Array name
      TILEDB_ARRAY_WRITE,                        // Mode
      NULL,                                      // Entire domain
      NULL,                                      // All attributes
      0);                                        // Number of attributes

  // Cell buffers
//  size_t offsets[] =
//  {
//      0,   1,  2,  3,                                     // Upper left tile
//      4,   5,  6,  7,                                    // Upper right tile
//      8,   9, 10, 11,                                    // Lower left tile
//      12, 13, 14, 15,                                     // Lower right tile
//      16, 17 //, 24
//  };

  size_t offsets[18];
  char *data = (char*)malloc(512*1024*1024), *current = data;

for(size_t j = 0; j < 16; j++)
  {
  current = data;
  char filename[256];

  size_t prev = 0;

  for(size_t i = 0; i < 18; i++)
  {
  snprintf(filename, 256, "/home/ubuntu/inputs/tiles/9000/%ld/%ld.hevc", j, i);
  read(filename, &current);
  //printf("%d %d size: %ld\n", j, i, (current - data) - prev);
  offsets[i + 1] = current - data;
  prev = current - data;
  }

  size_t final_offset = current - data;
  printf("%ld: size %ld\n", j, final_offset);
  //offsets[18] = current - data;


  //for(size_t i = 0; i < 19; i++)
  //  printf("offset: %ld\n", offsets[i]);

  const void* buffers[] = { offsets, data };
  size_t sizes[] =
  {
      sizeof(offsets),
      final_offset //offsets[18]
      //sizeof(data)-1  // TODO deal with terminating null
  };

  int result = tiledb_array_write(array, buffers, sizes);
  if(result != TILEDB_OK)
      printf("%ld: error %d\n", sizes[1], result);
  }

  tiledb_array_finalize(array);
  tiledb_ctx_finalize(context);

  free(data);

  // Initialize context with the default configuration parameters
  tiledb_ctx_init(&context, NULL);

  // Initialize array
  tiledb_array_init(
      context,                                   // Context
      &array,                                    // Array object
      "workspace/brandon/videos9000",                // Array name
      TILEDB_ARRAY_WRITE,                        // Mode
      NULL,                                      // Entire domain
      NULL,                                      // All attributes
      0);                                        // Number of attributes

  // Cell buffers
//  size_t offsets[] =
//  {
//      0,   1,  2,  3,                                     // Upper left tile
//      4,   5,  6,  7,                                    // Upper right tile
//      8,   9, 10, 11,                                    // Lower left tile
//      12, 13, 14, 15,                                     // Lower right tile
//      16, 17 //, 24
//  };

  //size_t offsets[18];
  data = (char*)malloc(128 * 18); //512*1024*1024);
  current = data;

for(size_t j = 0; j < 16; j++)
  {
  char filename[128];
  memset(data, 0, 128*18);

  for(size_t i = 0; i < 18; i++)
  {
  memset(filename, 0, 128);
  snprintf(filename, 128, "/home/ubuntu/inputs/tiles/9000/%ld/%ld.hevc", j, i);  
  memcpy(current, filename, 128);
  //printf("%d %d size: %ld\n", j, i, (current - data) - prev);
  }

  const void* buffers[] = {data};

  size_t sizes[] =
  {
      128*18
      //sizeof(offsets),
      //final_offset //offsets[18]
      //sizeof(data)-1  // TODO deal with terminating null
  };

  int result = tiledb_array_write(array, buffers, sizes);
  if(result != TILEDB_OK)
      printf("%ld: error %d\n", sizes[1], result);
  }

  tiledb_array_finalize(array);
  tiledb_ctx_finalize(context);

  free(data);

  return 0;
}

