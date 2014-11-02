/*********************************************
// base.cpp
// 1.definition of almost all globle variables.
*********************************************/

#include "base.h"

using namespace std;

/******************************************/
unsigned int long i_cache_size = 0; //cache size
unsigned int long i_cache_line_size = 0; //cacheline size
unsigned int long i_cache_set = 0; //cache set

unsigned int long i_num_line = 0; //How many lines of the cache.
unsigned int long i_num_set = 0; //How many sets of the cache.

ASSOC t_assoc = direct_mapped; //associativity method,default direct_mapped
REPLACE t_replace = none; //replacement policy,default Random
WRITE t_write = write_back; //write policy,default write_back
/******************************************/

/******************************************/
short unsigned int bit_block = 0; //How many bits of the block.
short unsigned int bit_line = 0; //How many bits of the line.
short unsigned int bit_tag = 0; //How many bits of the tag.
short unsigned int bit_set = 0; //How many bits of the set.
/******************************************/

/******************************************/
unsigned long int i_num_access = 0; //Number of cache access
unsigned long int i_num_load = 0; //Number of cache load
unsigned long int i_num_store = 0; //Number of cache store
unsigned long int i_num_space = 0; //Number of space line

unsigned long int i_num_hit = 0; //Number of cache hit
unsigned long int i_num_load_hit = 0; //Number of load hit
unsigned long int i_num_store_hit = 0; //Number of store hit

float f_ave_rate = 0.0; //Average cache hit rate
float f_load_rate = 0.0; //Cache hit rate for loads
float f_store_rate = 0.0; //Cache hit rate for stores
/******************************************/

bitset<32> cache_item[MAX_CACHE_LINE]; // [31]:valid,[30]:hit,[29]:dirty,[28]-[0]:data
unsigned long int LRU_priority[MAX_CACHE_LINE]; //For LRU policy's priority
unsigned long int current_line = 0; // The line num which is processing
unsigned long int current_set = 0; // The set num which is processing
unsigned long int i=0,j=0; //For loop
unsigned long int temp = 0; //A temp varibale


