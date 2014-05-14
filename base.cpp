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
    bitset<32> cache_item[MAX_CACHE_LINE];
    // cache_item[0]:hit,cache item[1]:dirty,
    bitset<32> *p_cache_item;
    unsigned long int line;
    unsigned long int i=0,j=0;



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

    #ifndef NDEBUG
    cout << flags << endl;
    #endif // NDEBUG


    hit = IsHit(flags);
    if(hit && is_load)
    {
        i_num_access++;
        i_num_load++;
        i_num_load_hit++;
        i_num_hit++;

        #ifndef NDEBUG
        cout << "i_num_load_hit: " << i_num_load_hit << endl;
        cout << "i_num_load: " << i_num_load << endl;
        cout << "Loading" << endl;
        cout << "Hit" << endl;
        cout << "Read from Cache!" << endl;
        #endif // NDEBUG

    }
    else if(hit && is_store)
    {
        i_num_access++;
        i_num_store++;
        i_num_store_hit++;
        i_num_hit++;

        #ifndef NDEBUG
        cout << "i_num_store_hit: " << i_num_store_hit << endl;
        cout << "i_num_store: " << i_num_store << endl;
        cout << "Storing" << endl;
        cout << "Hit" << endl;
        cout << "Write to Cache" << endl;
        #endif // NDEBUG
    }
    else if(is_load)
    {
        i_num_access++;
        i_num_load++;

        #ifndef NDEBUG
        cout << "Loading" << endl;
        cout << "Not Hit" << endl;
        cout << "Read from Main Memory to Cache!" << endl;
        #endif // NDEBUG

        GetReplace(flags);

        #ifndef NDEBUG
        cout << "Read from Cache!" << endl;
        #endif // NDEBUG
    }
    else if(is_store)
    {
        i_num_access++;
        i_num_store++;

        #ifndef NDEBUG
        cout << "Storing" << endl;
        cout << "Not Hit" << endl;
        #endif // NDEBUG

        GetWrite(); //写入内存

        #ifndef NDEBUG
        cout << "Read from Main Memory to Cache!" << endl;
        #endif // NDEBUG

        GetReplace(flags);
        #ifndef NDEBUG
        cout << "Write to Cache" << endl;
        #endif // NDEBUG
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
        cout << "There have " << i_num_space << " space lines" << endl;
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

bool IsHit(bitset<32> flags)
{
    bool ret = false;
    bitset<32> flags_line;
    for(j=0,i=(bit_block);i<(bit_block+bit_line);j++,i++) //判断在cache多少行
    {
        flags_line[j] = flags[i];
        //cout << "i is: " << i << endl;
    }
    line = flags_line.to_ulong();
    //cout << "line is: " << line << endl;
    if(cache_item[line][31]==false) //判断是否超出cache的有效行数
    {
        cerr << "There is a error! Beyond the range!!" << endl;
        cout << "Line is: " << line << endl;
    }
    if(cache_item[line][30]==true) //判断hit位是否为真
    {
        for(i=31,j=28;i>(31ul-bit_tag);i--,j--) //判断标记是否相同
        {
            ret = true;
            if(flags[i] != cache_item[line][j])
            {
                ret = false;
            }
        }
    }

    return ret;
}
void GetReplace(bitset<32> flags)
{
    for(i=31,j=28;i>(31ul-bit_tag);i--,j--) //设置标记
    {
        cache_item[line][j] = flags[i];
    }
    cache_item[line][30] = true; //设置hit位为true
}
void GetWrite() //写入内存
{
    if(cache_item[line][30] == true && cache_item[line][29] == true) //hit位和dirty位必须同时为1才写入
    {
        cout << "Writing to the Main Memory!" <<endl;
    }
    cache_item[line][29] = false; //设置dirty为false
}
