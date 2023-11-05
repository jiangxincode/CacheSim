#include "base.h"

using namespace std;

void PrintOutput(void)
{
    cout << endl;
    cout << "Cache Size:" << i_cache_size << "KB" << endl;
    cout << "Cacheline Size:" << i_cache_line_size << "B" << endl;

    switch(t_assoc)
    {
    case 1:
        cout << "Way of Associativity:direct_mapped" << endl;
        break;

    case 2:
        cout << "Way of Associativity:set_associative" << endl;
        break;

    case 3:
        cout << "Way of Associativity:full_associative" << endl;
        break;

    default:
        cerr << "ERROR ASSOCIATIVITY";
        break;
    }

    switch(t_replace)
    {
    case 0:
        cout << "Way of Replacement:NONE" << endl;
        break;

    case 1:
        cout << "Way of Replacement:FIFO" << endl;
        break;

    case 2:
        cout << "Way of Replacement:LRU" << endl;
        break;

    case 3:
        cout << "Way of Replacement:LFU" << endl;
        break;

    case 4:
        cout << "Way of Replacement:Random" << endl;
        break;

    default:
        cerr << "ERROR REPLACEMENT";
        break;
    }

    switch(t_write)
    {
    case 1:
        cout << "Way of Write:write_through" << endl;
        break;

    case 2:
        cout << "Way of Write:write_back" << endl;
        break;

    default:
        cerr << "ERROR WRITE";
        break;
    }

    cout << endl;
    cout << "Number of cache access:" << i_num_access << endl;
    cout << "Number of cache load:" << i_num_load << endl;
    cout << "Number of cache store:" << i_num_store << endl;
    cout << endl;
    cout << "Average cache hit rate:" << f_ave_rate*100 << "%" << endl;
    cout << "Cache hit rate for loads:" << f_load_rate*100 << "%" << endl;
    cout << "Cache hit rate for stores:" << f_store_rate*100 << "%" << endl;
    cout << endl;
}

