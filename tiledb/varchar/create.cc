#include <stdio.h>
#include "tiledb.h"

#define TILE_COLUMNS 6
#define TILE_ROWS    3
#define MAX_DURATION 180

int create_workspace(TileDB_CTX* context, const char* workspace_name)
{
return tiledb_workspace_create(context, workspace_name);
}

int create_group(TileDB_CTX* context, const char* group_name)
{
return tiledb_group_create(context, group_name);
}

int create_overflow_array(TileDB_CTX* context, const char* array_name)
{
  const char* attributes[] = { "tile" };
  const char* dimensions[] = { "x", "y", "t" };
  int64_t domain[] =
  {
      0, TILE_COLUMNS-1,    // x
      0, TILE_ROWS-1,       // y
      0, MAX_DURATION       // t
  };
  const int cell_val_num[] =
  {
      128         // tile data
  };
  const int compression[] =
  {
      TILEDB_NO_COMPRESSION, // tile data
      TILEDB_NO_COMPRESSION  // coordinates
  };
  int64_t tile_extents[] =
  {
      TILE_COLUMNS,
      TILE_ROWS,
      1
  };
  const int types[] =
  {
      TILEDB_CHAR,                // tile data
      TILEDB_INT64                // coordinates
  };

  TileDB_ArraySchema array_schema;
  tiledb_array_set_schema(
      &array_schema,              // Array schema struct
      array_name,                 // Array name
      attributes,                 // Attributes
      1,                          // Number of attributes
      0,                          // Capacity
      TILEDB_ROW_MAJOR,           // Cell order
      cell_val_num,               // Number of cell values per attribute
      compression,                // Compression
      1,                          // Dense array
      dimensions,                 // Dimensions
      3,                          // Number of dimensions
      domain,                     // Domain
      6*sizeof(int64_t),          // Domain length in bytes
      tile_extents,               // Tile extents
      3*sizeof(int64_t),          // Tile extents length in bytes
      TILEDB_ROW_MAJOR,           // Tile order
      types                       // Types
  );

  tiledb_array_create(context, &array_schema);
  tiledb_array_free_schema(&array_schema);

  return 0;
}

int create_array(TileDB_CTX* context, const char* array_name)
{
  const char* attributes[] = { "tile" };
  const char* dimensions[] = { "x", "y", "t" };
  int64_t domain[] =
  {
      0, TILE_COLUMNS-1,    // x
      0, TILE_ROWS-1,       // y
      0, MAX_DURATION       // t
  };
  const int cell_val_num[] =
  {
      TILEDB_VAR_NUM         // tile data
  };
  const int compression[] =
  {
      TILEDB_NO_COMPRESSION, // tile data
      TILEDB_NO_COMPRESSION  // coordinates
  };
  int64_t tile_extents[] =
  {
      TILE_COLUMNS,
      TILE_ROWS,
      1
  };
  const int types[] =
  {
      TILEDB_CHAR,                // tile data
      TILEDB_INT64                // coordinates
  };

  TileDB_ArraySchema array_schema;
  tiledb_array_set_schema(
      &array_schema,              // Array schema struct
      array_name,                 // Array name
      attributes,                 // Attributes
      1,                          // Number of attributes
      0,                          // Capacity
      TILEDB_ROW_MAJOR,           // Cell order
      cell_val_num,               // Number of cell values per attribute
      compression,                // Compression
      1,                          // Dense array
      dimensions,                 // Dimensions
      3,                          // Number of dimensions
      domain,                     // Domain
      6*sizeof(int64_t),          // Domain length in bytes
      tile_extents,               // Tile extents
      3*sizeof(int64_t),          // Tile extents length in bytes
      TILEDB_ROW_MAJOR,           // Tile order
      types                       // Types
  );

  tiledb_array_create(context, &array_schema);
  tiledb_array_free_schema(&array_schema);

  return 0;
}

int main()
{
int result;
TileDB_CTX* context;
tiledb_ctx_init(&context, NULL);

if((result = create_workspace(context, "workspace")) != TILEDB_OK)
	printf("workspace error %d\n", result);
else if((result = create_group(context, "workspace/brandon")) != TILEDB_OK)
        printf("group error %d\n", result);
else if((result = create_array(context, "workspace/brandon/videos50")) != TILEDB_OK)
	printf("create array error %d\n", result);
else if((result = create_overflow_array(context, "workspace/brandon/videos9000")) != TILEDB_OK)
        printf("create array error %d\n", result);

tiledb_ctx_finalize(context);
}
