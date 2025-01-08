#ifndef ADDRESS_UTILS_H
#define ADDRESS_UTILS_H

#include <stdio.h>


#define MEM_SIZE 1024 * 1024 
#define BLOCK_SIZE 16         
#define BLOCKS_IN_SET 4      
#define SETS_IN_CACHE 16      

#define OFFSET_BITS (32 - __builtin_clz(BLOCK_SIZE - 1))   
#define bit_mask_offset ((1 << OFFSET_BITS) - 1)             

#define INDEX_SET_BITS (32 - __builtin_clz(SETS_IN_CACHE - 1)) 
#define bit_mask_set ((1 << INDEX_SET_BITS) << OFFSET_BITS) - 1 - bit_mask_offset 

#define bit_mask_block_start (~bit_mask_offset)  

void get_offset(unsigned int *address, unsigned int* offset);
void get_block_start(unsigned int* address, unsigned int* block_start);
void get_set_index(unsigned int* address, unsigned int* set_index);
void get_tag(unsigned int* address, unsigned int* tag);

#endif 
