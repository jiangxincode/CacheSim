#include "functions.h"

using namespace std;

void LruUnhitSpace()
{
    assert(t_replace == LRU);
    cout << "test" << endl;
    if(t_assoc == full_associative)
    {
        for(i=0;i<i_num_line;i++)
        {
            LRU_priority[i]++;
        }
        LRU_priority[current_line] = 0;
    }
    else if(t_assoc == set_associative)
    {
        for(i=(current_set*i_cache_set);i<((current_set+1)*i_cache_set);i++)
        {
            LRU_priority[i]++;
        }
        LRU_priority[current_line] = 0;
    }
}
