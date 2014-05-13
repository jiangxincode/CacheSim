//base.cpp

#include "base.h"

using namespace std;

    /******************************************/
    /* for input */
    unsigned int i_cache_size = 0; //cache size
    unsigned int i_cache_line_size = 0; //cacheline size

    ASSOC t_assoc = direct_mapped; //associativity method,default direct_mapped
    REPLACE t_replace = none; //replacement policy,default Random
    WRITE t_write = write_back; //write policy,default write_back
    /* for input */
    /******************************************/

    /******************************************/
    /* for temp */
    unsigned int i_num_line = 0; //How many lines of the cache.
    short unsigned int bit_block = 0; //How many bits of the block.
    short unsigned int bit_line = 0; //How many bits of the line.
    short unsigned int bit_tag = 0; //How many bits of the tag.
    /* for temp */
    /******************************************/

    /******************************************/
    /* for output */
    unsigned long int i_num_access = 0; //Number of cache access
    unsigned long int i_num_load = 0; //Number of cache load
    unsigned long int i_num_store = 0; //Number of cache store

    unsigned long int i_num_hit = 0; //Number of cache hit
    unsigned long int i_num_load_hit = 0; //Number of load hit
    unsigned long int i_num_store_hit = 0; //Number of store hit

    float f_ave_rate = 0.0; //Average cache hit rate
    float f_load_rate = 0.0; //Cache hit rate for loads
    float f_store_rate = 0.0; //Cache hit rate for stores

    unsigned long int i_num_space = 0; //Number of space line
    /* for output */
    /******************************************/
    bitset<10> cache_item[MAX_CACHE_LINE];
    bitset<10> *p_cache_item;



bool GetHitNum(char *address)
{
    bool is_store = false;
    bool is_load = false;
    bool is_space = false;
    bool hit = false;
    switch(address[0])
    {
        case 's':is_store = true;break;
        case 'l':is_load = true;break;
        //case ' ':break; //Waring if a line has nothing,the first of it is a '\0' nor a ' '
        case '\0':is_space = true;break; //In case of space lines
        default:
            cout << "The address[0] is:" <<address[0] << endl;
            cout << "ERROR IN JUDGE!" << endl;return false;
    }
    unsigned long value = strtoul(address+2,NULL,16);
    bitset<32> flags(value);
    cout << flags << endl;
    hit = IsHit();
    if(hit && is_load)
    {
        i_num_access++;
        i_num_load++;
        i_num_load_hit++;
        i_num_hit++;
    }
    else if(hit && is_store)
    {
        i_num_access++;
        i_num_store++;
        i_num_store_hit++;
        i_num_hit++;
    }
    else if(is_load)
    {
        i_num_access++;
        i_num_load++;
    }
    else if(is_store)
    {
        i_num_access++;
        i_num_store++;
    }
    else if(is_space)
    {
        i_num_space++;
    }
    else
    {
        cerr << "Something ERROR" << endl;
        return false;
    }
    if(i_num_space != 0)
    {
        cout << "There have " << i_num_space << "space lines" << endl;
    }
    return true;
}
void GetHitRate()
{
    assert(i_num_access != 0);
    assert(i_num_load != 0);
    assert(i_num_store != 0);
    f_ave_rate = ((double)i_num_hit)/i_num_access; //Average cache hit rate
    f_load_rate = ((double)i_num_load_hit)/i_num_load; //Cache hit rate for loads
    f_store_rate = ((double)i_num_store_hit)/i_num_store; //Cache hit rate for stores
}

bool IsHit()
{
    return false;
}
void GetReplace()
{

}
void GetWrite()
{

}
