#include "functions.h"

using namespace std;

void InitVariables(void)
{
    for(i=0; i<i_num_line; i++)
    {
        cache_item[i].reset(); // [31]:valid,[30]:hit,[29]:dirty,[28]-[0]:data

        if(t_replace == LRU)
        {
            LRU_priority[i] = 0; //For LRU policy's priority
        }
    }

    /******************************************/
    i_cache_size = 64; //cache size
    i_cache_line_size = 32; //cacheline size
#ifdef SetAssociative_Random_WriteBack
    i_cache_set = 4; //cache set
#endif // SetAssociative_Random_WriteBack
    i_cache_set = 0; //cache set
    i_num_line = 0; //How many lines of the cache.
    i_num_set = 0; //How many sets of the cache.
#ifdef DirectMapped_None_WriteBack
    t_assoc = direct_mapped; //associativity method,default direct_mapped
    t_replace = none; //replacement policy,default Random
    t_write = write_back; //write policy,default write_back
#endif // DirectMapped_None_WriteBack
#ifdef FullAssociative_Random_WriteBack
    t_assoc = full_associative; //associativity method,default full_associative
    t_replace = Random; //replacement policy,default Random
    t_write = write_back; //write policy,default write_back
#endif // FullAssociative_Random_WriteBack
    /******************************************/
#ifdef SetAssociative_Random_WriteBack
    t_assoc = set_associative; //associativity method,default set_associative
    t_replace = Random; //replacement policy,default Random
    t_write = write_back; //write policy,default write_back
#endif // SetAssociative_Random_WriteBack
    /******************************************/
    /******************************************/
    bit_block = 0; //How many bits of the block.
    bit_line = 0; //How many bits of the line.
    bit_tag = 0; //How many bits of the tag.
    bit_set = 0; //How many bits of the set.
    /******************************************/
    /******************************************/
    i_num_access = 0; //Number of cache access
    i_num_load = 0; //Number of cache load
    i_num_store = 0; //Number of cache store
    i_num_space = 0; //Number of space line
    i_num_hit = 0; //Number of cache hit
    i_num_load_hit = 0; //Number of load hit
    i_num_store_hit = 0; //Number of store hit
    f_ave_rate = 0.0; //Average cache hit rate
    f_load_rate = 0.0; //Cache hit rate for loads
    f_store_rate = 0.0; //Cache hit rate for stores
    /******************************************/
    current_line = 0; // The line num which is processing
    current_set = 0; // The set num which is processing
    i=0;
    j=0; //For loop
    /******************************************/
}
