#ifndef CHC_H__
#define CHC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#define DATA_TYPE unsigned char /* change this to any guaranteed 8 bit type you need */
#define USE_PTHREADS 1 /* set to 0 if you don't want pthreads/threading support */

enum
{
  USING_CUSTOM_ALLOCATORS = 0b00000000000000000000000000000000
};

typedef struct
{
  size_t chunks;
  size_t rank; /* the file's rank in the list */
  DATA_TYPE *ChunkLocations;
  char *path;
} CacheTable_t;

short CHC_Init(size_t maxChunkCount, size_t maxChunk, unsigned int flags);

short CHC_Destroy();

short CHC_SetMemAlloc(void *(*alloc)(size_t bytes));

short CHC_SetMemRealloc(void *(*remalloc)(void *ptr, size_t bytes));

short CHC_SetMemFree(void *(*memfree)(void *ptr));

size_t CHC_BytesUsed();

size_t CHC_BytesFree();

size_t CHC_FilesCached();

short CHC_LoadFileFromCacheOrDisk(const char *path, DATA_TYPE *data, size_t *size);



#ifdef __cplusplus
}
#endif

#endif

/* EOF */
