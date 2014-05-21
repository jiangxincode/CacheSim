#include "functions.h"

using namespace std;

void LruUnhitUnspace()
{
    assert(t_replace == LRU);
    cout << "test" << endl;
    unsigned long int temp;
    if(t_assoc == full_associative)
    {
        temp = LRU_priority[0];
        for(i=0;i<i_num_line;i++)
        {
            if(LRU_priority[i]>temp)
            {
                temp = LRU_priority[i];
                j = i;
            }
        }
        current_line = j;
    }
    if(t_assoc == set_associative)
    {
        temp = LRU_priority[current_set*i_cache_set];
        for(i=(current_set*i_cache_set);i<((current_set+1)*i_cache_set);i++)
        {
            if(LRU_priority[i]>temp)
            {
                temp = LRU_priority[i];
                j = i;
            }
        }
        current_line = j;
    }

}
