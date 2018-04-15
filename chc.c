/* you may be wondering why this is styled so differently from all of my
projects up to this point. A simple explaination is that im tired of looking
at ugly code. This is my first attempt at making my style cleaner. Not every
project will be converted to this style because that's way too large of a task */

/* simple LRU cache. Does what it needs for my purposes */

#include "chc.h"

/* system-specific includes */
#include <sys/types.h>
#include <linux/inotify.h>

/* the rest of the includes */
#ifdef USE_PTHREADS
  #include <pthread.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* global variables */
#ifdef USE_PTHREADS
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#endif
CacheTableGlobals_t state = {
  NULL, /* the cache table pointer */
  0, /* the max chunks var that is set from init */
  1024, /* default chunk size that can be overridden in the init function */
  0 /* the file counter var */
};
/*
CacheTable_t *table = NULL;

size_t maxChunks = 0; * max number of chunks that the chunksize is at *
size_t chunkSize = 1024; * can change this in CHC_Init(); *
size_t files = 0;
*/


void *(*CHCAlloc)(size_t bytes) = NULL;
void *(*CHCRealloc)(void *ptr, size_t bytes) = NULL;
void *(*CHCFree)(void *ptr) = NULL;


/* static function prorotypes here */
static short CHC_AddEntry(CacheTable_t *tempTable);

static short CHC_RemoveEntry(size_t id);

/* functions below */



short CHC_Init(size_t maxChunkCount, size_t maxChunkSize, unsigned int flags)
{
  if(!flags & USING_CUSTOM_ALLOCATORS)
  {
    if(CHC_SetMemAlloc(malloc))
      return 1;
    if(CHC_SetMemRealloc(realloc))
      return 1;
    if(CHC_SetMemFree(free))
      return 1;
  }
  if(maxChunkSize != 0)
    state.chunkSize = maxChunkSize;
  state.maxChunks = maxChunkCount;


  return 0;
}

short CHC_Destroy()
{
  if(table != NULL)
  {
    /* TODO loop through the table entries and specificly free the chunks */
    CHCFree(table);
  }
}

short CHC_SetMemAlloc(void *(*alloc)(size_t bytes)) /* callback for using custom
mem allocators */
{
  if((CHCAlloc = alloc) != NULL)
    return 0;
  else
    return 1;
}

short CHC_SetMemRealloc(void *(*remalloc)(void *ptr, size_t bytes)) /* callback for using custom
mem reallocators */
{
  if((CHCRealloc = remalloc) != NULL)
    return 0;
  else
    return 1;
}

short CHC_SetMemFree(void *(*memfree)(void *ptr)) /* callback for using custom
mem reallocators */
{
  if((CHCFree = memfree) != NULL)
    return 0;
  else
    return 1;
}

/* CHC status related functions */

size_t CHC_BytesUsed()
{

}

size_t CHC_BytesFree()
{

}

size_t CHC_FilesCached()
{
  return files;
}

/* TODO CHC_EnumCachedFileStatus */

/* actual caching functions */

static short CHC_AddEntry(CacheTable_t *tempTable)
{
  if(table == NULL)
  {
    if((table = CHCAlloc(sizeof(CacheTable_t))) == NULL)
      return 1;

    table[0] = *tempTable;
  }
  else
  {
    CacheTable_t *tempTableAlloc = NULL;

    tempTableAlloc = CHCRealloc(table, (sizeof(CacheTable_t) * files) + 1);
    if(tempTable == NULL)
      return 1;

    table = tempTableAlloc;

    table[files + 1] = *tempTable;

    files++;
  }
  return 0;
}

static short CHC_RemoveEntry(size_t id)
{
  if(table != NULL)
  {

  }
  return 0;
}

short CHC_LoadFileFromCacheOrDisk(const char *path, DATA_TYPE *data, size_t *size) /* TODO change to an 8 bit type */
{

}

/* EXTREMELY TEMPORARY TESTING FUNCTIONS. WILL COMPLETELY REMOVE EVENTUALLY */

int main(int argc, char **argv)
{
  printf("Cold hard Cache tester\n");
  CHC_Init(512, (1024 * 1024) * 1, NULL); /* max of 1MiB a chunk X 512 chunks*/

  return 0;
}


/* EOF */
