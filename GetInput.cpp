#include "base.h"

using namespace std;

void GetInput(void)
{
    short temp = 0; //for switch
    puts("\nPlease input the number of the cache size(Unit:KB)");
    puts("\n\t(for example:1,2,4,8,16,32,64...2^18)");
    cin >> i_cache_size;

    while(i_cache_size<1 || i_cache_size>= 262144 || (i_cache_size&(~i_cache_size+1))!=i_cache_size)
    {
        puts("\nPlease input the number of the cache size(Unit:KB)");
        puts("\n\t(for example:1,2,4,8,16,32,64...2^18)");
        cin >> i_cache_size;
    }

    puts("\nPlease input the number of the cacheline size(Unit:Byte)");
    puts("\n\t(for example:1,2,4,8,16,32,64...2^18)");
    cin >> i_cache_line_size;

    while(i_cache_line_size<1 || i_cache_line_size>= 262144 || (i_cache_line_size&(~i_cache_line_size+1))!=i_cache_line_size)
    {
        puts("\nPlease input the number of the cache size(Unit:KB)");
        puts("\n\t(for example:1,2,4,8,16,32,64...2^18)");
        cin >> i_cache_line_size;
    }

get_assoc:
    puts("\nPlease input the method of assoiativity between main memory and cache:");
    puts("\n\t directive_mapped:input 1");
    puts("\n\t set_associative:input 2");
    puts("\n\t full_associative:input 3");
    cin >> temp;

    switch(temp)
    {
    case 1:
        t_assoc = direct_mapped;
        break;

    case 2:
        t_assoc = set_associative;
        break;

    case 3:
        t_assoc = full_associative;
        break;

    default:
        cout << "Input Error!Please input again:" << endl;
        goto get_assoc;
    }

    if(t_assoc == direct_mapped) //If the associativity_way is direct_mapped,the replacement polacy can be none only;
    {
        t_replace = none;
        goto get_write;
    }
    else if(t_assoc == full_associative)
    {
        goto get_replacement;
    }
    else
    {
        puts("\nInput the how many lines in each set:");
        puts("\n\t(for example:1,2,4,8,16,32,64...2^18)");
        cin >> i_cache_set;

        while(i_cache_set<1 || i_cache_set>= 262144 || (i_cache_set&(~i_cache_set+1))!=i_cache_set)
        {
            puts("\nInput the how many lines in each set:");
            puts("\n\t(for example:1,2,4,8,16,32,64...2^18)");
            cin >> i_cache_set;
        }
    }

get_replacement:
    puts("\nPlease input the replacement policy:");
    puts("\n\t FIFO(First In First Out):input 1");
    puts("\n\t LRU(Least Recently Used):input 2");
    puts("\n\t LFU(Least Frequently Used):input 3");
    puts("\n\t Random:input 4");
    cin >> temp;

    switch(temp)
    {
    case 1:
        t_replace = FIFO;
        break;

    case 2:
        t_replace = LRU;
        break;

    case 3:
        t_replace = LFU;
        break;

    case 4:
        t_replace = Random;
        break;

    default:
        cout << "Input Error!Please input again:" << endl;
        goto get_replacement;
    }

get_write:
    puts("\nPlease input write policy:");
    puts("\n\t Write through:input 1");
    puts("\n\t Write back:input 2");
    cin >> temp;

    switch(temp)
    {
    case 1:
        t_write = write_through;
        break;

    case 2:
        t_write = write_back;
        break;

    default:
        cout << "Input Error!Please input again:" << endl;
        goto get_write;
    }
}
