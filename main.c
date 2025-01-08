#include <stdio.h>
#include <stdlib.h>
#include "address_utils.h"
#include "cache.h"



int main()
{
    unsigned int address = 0xFBCAF;
    unsigned int offset;
    get_offset(&address, &offset);

    unsigned int block_start;
    get_block_start(&address, &block_start);

    unsigned int index;
    get_set_index(&address, &index);

    unsigned int tag;
    get_tag(&address, &tag);

    printf("address: %x \noffset: %x \nblock start: %x\nindex: %x \ntag: %x \n", 
    address, 
    offset, 
    block_start,
    index,
    tag
    );

    cache* cacheMem = (cache*)malloc(sizeof(cache));
    initialize_cache(cacheMem);


    return 0;
}