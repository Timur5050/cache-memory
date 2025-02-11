# cache-memory

## mem

8MB - memory


-----

### 4-way set-associative cache

block size - 16 bytes 

blocks in set - 4 blocks

sets in cache - 16 sets

-----

so that, total cash memory:

16 sets * 4 blocks * 16 bytes = 1024 bytes

cash memory - 1KB

----- 

### address mapping to bits:

offset - 4 bits             (block size 16 byte)

set index - 4 bits          (sets in cache 16 sets)

tag - 20-4-4 = 12 bits      (diff from address size and offset size + set index)

-----


## CPU

memory is 8BM, so that CPU address request - 20 bits

max address - 0xFFFFF
