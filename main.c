#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "address_utils.h"
#include "cache.h"


void* initialize_memory()
{
    return (void*)malloc(MEM_SIZE);
}

void fill_memory_with_data(void *memory)
{
    srand(time(NULL));
    unsigned char* mem = (unsigned char*)memory;
    for(int i = 0; i < MEM_SIZE; i++)
    {
        *(mem + i) = rand() % 256;
    }
}



unsigned int get_from_cache(unsigned int address, cache *cacheMemory, void* memory)
{
    unsigned index, tag, offset;

    get_offset(&address, &offset);
    get_set_index(&address, &index);
    get_tag(&address, &tag);

    cacheSet* current_set = cacheMemory->cache[index >> OFFSET_BITS];   

    cacheBlock* current_block = NULL;

    for(int i = 0; i < BLOCKS_IN_SET; i++)
    {
        cacheBlock* temp_block = current_set->sets[i];
        if(temp_block->valid == 1 && temp_block->tag == tag)
        {
            printf("\n HIT!!!");
            current_block = temp_block;
            break;
        }
    }

    if(current_block)
    {
        unsigned char* data = (unsigned char*)current_block->data;

        unsigned char result_byte = data[offset];

        return (unsigned int)result_byte;
    }

    unsigned char* mem = (unsigned char*)memory;
    unsigned char *new_block_address = mem + address;

    current_block = (cacheBlock*)malloc(sizeof(cacheBlock));
    current_block->data = malloc(BLOCK_SIZE);
    current_block->tag = tag;
    current_block->valid = 1;
    current_block->entering_counter = 1;


    for(int i = 0; i < BLOCK_SIZE; i++)
    {
        ((unsigned char*)current_block->data)[i] = ((unsigned char*)new_block_address)[i];
    }

    int result_block_index = -1;

    for(int i = 0; i < BLOCKS_IN_SET; i++)
    {   
        current_set->sets[i]->entering_counter++;
        if(current_set->sets[i]->valid == 0)
        {   
            result_block_index = i;
            break;
        
        }
    }
    unsigned char *data;

    if(result_block_index >= 0)
    {
        current_set->sets[result_block_index] = current_block; 
        data = (unsigned char*)current_block->data;
    }
    else
    {
        int max_counter = current_set->sets[0]->entering_counter;
        result_block_index = 0;
        
        for(int i = 1; i < BLOCKS_IN_SET; i++)
        {
            if(current_set->sets[i]->entering_counter > max_counter)
            {
                max_counter = current_set->sets[i]->entering_counter;
                result_block_index = i;
            }
        }

        current_set->sets[result_block_index] = current_block;
        data = (unsigned char*)current_block->data;
    }

    unsigned char result_byte = data[offset];
    printf("\n MISS!!!");
    return (unsigned int)result_byte;

}

int main()
{
    srand(time(NULL));
    unsigned int address = 0xFAB2E;
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
    index >> 4,
    tag
    );

    cache* cacheMem = initialize_cache();

    void* memory = initialize_memory();
    fill_memory_with_data(memory);
    unsigned int address1 = 0xDDB2A;
    unsigned int address2 = 0x21B2A;
    unsigned int address3 = 0x6BA23;
    unsigned int address4 = 0x76E2B;
    unsigned int address5 = 0x66E2C;


    printf("\n res : %d\n", get_from_cache(address, cacheMem, memory));
    printf("\n res : %d\n", get_from_cache(address1, cacheMem, memory));
    printf("\n res : %d\n", get_from_cache(address2, cacheMem, memory));
    printf("\n res : %d\n", get_from_cache(address3, cacheMem, memory));

    printf("\n res : %d\n", get_from_cache(address4, cacheMem, memory));
    printf("\n res : %d\n", get_from_cache(address5, cacheMem, memory));

    printf("\n");

    printf("\n res : %d\n", get_from_cache(address2, cacheMem, memory));
    printf("\n res : %d\n", get_from_cache(address3, cacheMem, memory));

    printf("\n res : %d\n", get_from_cache(address4, cacheMem, memory));
    printf("\n res : %d\n", get_from_cache(address5, cacheMem, memory));

    
    free(memory);
    return 0;
}