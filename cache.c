#include "cache.h"


cache* initialize_cache()
{
    cache* cacheMem = (cache*)malloc(sizeof(cache));
    cacheMem->cache = (cacheSet**)malloc(sizeof(cacheSet) * SETS_IN_CACHE);
    for(int i = 0; i < SETS_IN_CACHE; i++)
    {
        cacheSet* cacheSetMem = (cacheSet*)malloc(sizeof(cacheSet));
        cacheSetMem->sets = (cacheBlock**)malloc(sizeof(cacheBlock) * BLOCKS_IN_SET);
        for(int j = 0; j < BLOCKS_IN_SET; j++)
        {
            cacheBlock *cacheBlockMem = (cacheBlock*)malloc(sizeof(cacheBlock));
            
            cacheBlockMem->valid = 0;
            cacheBlockMem->tag = 0;
            cacheBlockMem->data = (void*)malloc(BLOCK_SIZE);
            
            cacheSetMem->sets[j] = cacheBlockMem;
        }
        cacheMem->cache[i] = cacheSetMem;
    }
    return cacheMem;
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