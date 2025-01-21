#ifndef CACHE_H
#define CACHE_H

#include <stdlib.h>
#include "address_utils.h"

typedef struct 
{
    int valid;     
    unsigned tag;  
    char entering_counter;
    void* data;    
} cacheBlock;


typedef struct 
{
    cacheBlock** sets;  
} cacheSet;


typedef struct 
{
    cacheSet** cache; 
} cache;


cache* initialize_cache();


void free_cache(cache* cache);

#endif 