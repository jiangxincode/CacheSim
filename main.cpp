#include "functions.h"

using namespace std;

int main()
{
    /******************************************/
    /* for input */
    int i_cache_size; //cache size
    int i_cache_line_size; //cacheline size
    ASSOC t_assoc; //associativity method
    REPLACE t_replace; //replacement policy
    WRITE t_write; //write policy
    /* for input */
    /******************************************/

    /******************************************/
    /* for output */
    int i_num_access = 0; //Number of cache access
    int i_num_load = 0; //Number of cache load
    int i_num_store = 0; //Number of cache store
    float f_ave_rate = 0.0; //Average cache hit rate
    float f_load_rate = 0.0; //Cache hit rate for loads
    float f_store_rate = 0.0; //Cache hit rate for stores
    /* for output */
    /******************************************/

    PrintAuthorInfo();
    GetInput(i_cache_size,i_cache_line_size,t_assoc,t_replace,t_write); // get input information
    PrintOutput(i_cache_size,i_cache_line_size,
                t_assoc,t_replace,t_write,
                i_num_access,i_num_load,i_num_store,f_ave_rate,f_load_rate,f_store_rate
                ); // output the result
    PrintBye();
    return 0;
}
