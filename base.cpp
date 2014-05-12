//base.cpp

#include "base.h"

using namespace std;

    /******************************************/
    /* for input */
    int i_cache_size = 0; //cache size
    int i_cache_line_size = 0; //cacheline size
    ASSOC t_assoc = direct_mapped; //associativity method,default direct_mapped
    REPLACE t_replace = Random; //replacement policy,default Random
    WRITE t_write = write_back; //write policy,default write_back
    /* for input */
    /******************************************/

    /******************************************/
    /* for output */
    long int i_num_access = 0; //Number of cache access
    long int i_num_load = 0; //Number of cache load
    long int i_num_store = 0; //Number of cache store
    float f_ave_rate = 0.0; //Average cache hit rate
    float f_load_rate = 0.0; //Cache hit rate for loads
    float f_store_rate = 0.0; //Cache hit rate for stores
    /* for output */
    /******************************************/

bool SumCache(char *address)
{
    switch(address[0])
    {
        case 's':i_num_store++;break;
        case 'l':i_num_load++;break;
        //case ' ':break; //Waring if a line has nothing,the first of it is a '\0' nor a ' '
        case '\0':break; //In case of space lines
        default:
            cout << "The address[0] is:" <<address[0] << endl;
            cout << "ERROR IN SUM!" << endl;return false;
    }
    //i_num_access++; //if there has a space line,it will be wrong.
    i_num_access = i_num_load + i_num_store;
    return true;
}
