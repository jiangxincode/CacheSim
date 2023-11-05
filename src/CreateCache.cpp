#include "base.h"

using namespace std;

void CreateCache()
{
    temp = i_num_line;
#ifndef NDEBUG

    for(i=0; i<100; i++)
    {
        cout << cache_item[i] << endl;
    }

#endif // NDEBUG

    for(i=0; i<temp; i++)
    {
        cache_item[i][31] = true;
    }

#ifndef NDEBUG

    for(i=0; i<100; i++)
    {
        cout << cache_item[i] << endl;
    }

#endif // NDEBUG
}
