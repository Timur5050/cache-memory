#include "address_utils.h"


void get_offset(unsigned int *address, unsigned int* offset)
{
    *offset = *address & bit_mask_offset;
}

void get_block_start(unsigned int* address, unsigned int* block_start)
{
    *block_start = *address & bit_mask_block_start;
}

void get_set_index(unsigned int* address, unsigned int* set_index) 
{
    *set_index = *address & bit_mask_set;
}

void get_tag(unsigned int* address, unsigned int* tag)
{
    *tag = *address >> (OFFSET_BITS + INDEX_SET_BITS);
}