#ifndef CACHE_H
#define CACHE_H

#include <stdlib.h>
#include "address_utils.h"

typedef struct 
{
    int valid;     
    unsigned tag;  
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


void initialize_cache_block(cacheBlock* block);
void initialize_cache_set(cacheSet* set);
void initialize_cache(cache* cache);


void free_cache(cache* cache);

#endif 