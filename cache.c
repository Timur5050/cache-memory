#include "cache.h"


void initialize_cache_block(cacheBlock* cacheBlock)
{   
    cacheBlock->valid = 0;
    cacheBlock->tag = 0;
    cacheBlock->data = (void*)malloc(BLOCK_SIZE);
}

void initialize_cache_set(cacheSet* cacheSet)
{
    cacheSet->sets = (cacheBlock**)malloc(BLOCKS_IN_SET * sizeof(cacheBlock));
    for(int i = 0; i < BLOCKS_IN_SET; i++)
    {
        cacheBlock* block = (cacheBlock*)malloc(sizeof(cacheBlock));    
        initialize_cache_block(block);
        cacheSet->sets[i] = block;
    }
}

void initialize_cache(cache* cache)
{
    cache->cache = (cacheSet**)malloc(SETS_IN_CACHE * sizeof(cacheSet));
    for(int i = 0; i < SETS_IN_CACHE; i++)
    {
        cacheSet* set = (cacheSet*)malloc(sizeof(cacheSet));    
        initialize_cache_set(set);
        cache->cache[i] = set;
    }
}


void free_cache(cache* cache)
{
    for(int i = 0; i < SETS_IN_CACHE; i++)
    {
        cacheSet* set = cache->cache[i];
        for(int j = 0; j < BLOCKS_IN_SET; j++)
        {
            free(set->sets[j]->data);
            free(set->sets[j]);
        }
        free(set->sets);
        free(set);
    }
    free(cache->cache);
}