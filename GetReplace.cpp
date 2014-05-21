#include "functions.h"

using namespace std;

void GetReplace(bitset<32> flags,unsigned long int& current_line)
{
    if(t_assoc == direct_mapped)
    {
    }
	else if(t_assoc == full_associative)
    {
    	if(t_replace == Random)
        {
            current_line = rand()/(RAND_MAX/i_num_line+1); // 从所有行中任选一行，进行替换
        }
        else if(t_replace == LRU)
        {
            LruUnhitUnspace();
        }
    }
    else if(t_assoc == set_associative) // 从本组中任选一行，进行替换
    {
        if(t_replace == Random)
        {
            temp = rand()/(RAND_MAX/i_cache_set);
            current_line = current_set*i_cache_set+temp;
        }
        else if(t_replace == LRU)
        {
            LruUnhitUnspace();
        }
    }
    if(cache_item[current_line][29] == true) //dirty位必须为1才写入
    {
        GetWrite(); //写入内存
    }
	#ifndef NDEBUG
	cout << "Update the Content of Cache: " << current_line << endl;
	#endif // NDEBUG
    for(i=31,j=28;i>(31ul-bit_tag);i--,j--) //设置标记
    {
        cache_item[current_line][j] = flags[i];
    }
    cache_item[current_line][30] = true; //设置hit位为true
}
