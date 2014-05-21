/*************************************************
// functions.cpp
// 1.Defination of almost all functions.
*************************************************/

#include "functions.h"

using namespace std;

void CalcInfo()
{
    assert(i_cache_line_size != 0);
    i_num_line = (i_cache_size<<10)/i_cache_line_size;

    temp = i_cache_line_size;
    while(temp)
    {
        temp >>= 1;
        bit_block++;
    }
    bit_block--; //warning
    if(t_assoc == direct_mapped)
    {
        bit_set = 0; // for direct_mapped,the bit_set is 0
        temp = i_num_line;
        while(temp)
        {
            temp >>= 1;
            bit_line++;
        }
        bit_line--; //warning
    }
    else if(t_assoc == full_associative)
    {
        bit_line = 0; // for full_associative,the bit_line is 0
        bit_set = 0; // for full_associative,the bit_set is 0
    }
    else if(t_assoc == set_associative)
    {
        bit_line = 0; // for set_associative,the bit_line is 0
        assert(i_cache_set != 0);
        assert(i_num_line > i_cache_set);
        i_num_set = i_num_line/i_cache_set;
        temp = i_num_set;
        while(temp)
        {
            temp >>= 1;
            bit_set++;
        }
        bit_set--;
    }

    bit_tag = 32ul - bit_block - bit_line - bit_set;
    assert(bit_tag <= 29); //32-valid-hit-dirty
    cout << "i_cache_line_size: " << i_cache_line_size << "B" << endl; // 显示块大小
    cout << "i_cache_size: " << i_cache_size << "KB" << endl; // 显示cache数据区总容量
    if(t_assoc == set_associative) // 如果为组相联，显示是几路组相联
    {
        cout << "i_cache_set: " << i_cache_set << " lines each set" << endl;
    }
    cout << "i_num_line: " << i_num_line << endl; // 显示共有多少行
    if(t_assoc == set_associative) // 如果为组相联，显示共有几组
    {
        cout << "i_num_set: " << i_num_set << endl;
    }
    cout << "bit_block: " << bit_block << endl; // 显示块内地址所需位数
    if(t_assoc == direct_mapped) // 如果为直接映射，显示行号所需位数
    {
        cout << "bit_line: " << bit_line << endl;
    }
    if(t_assoc == set_associative) // 如果为组相联，显示组号所需位数
    {
        cout << "bit_set: " << bit_set << endl;
    }
    cout << "bit_tag: " << bit_tag << endl; // 显示标志位所需位数
}
void CreateCache()
{
    temp = i_num_line;

    #ifndef NDEBUG
    for(i=0;i<100;i++)
    {
        cout << cache_item[i] << endl;
    }
    #endif // NDEBUG

    for(i=0;i<temp;i++)
    {
        cache_item[i][31] = true;
    }
    #ifndef NDEBUG

    for(i=0;i<100;i++)
    {
        cout << cache_item[i] << endl;
    }
    #endif // NDEBUG
}
void FileTest(void)
{
    char filepath[100];
    ifstream in_file;
    char address[13];
    cout << "\nPlease input the path and name that you want to test!" << endl;
    cout << "\n\t C:\\temp\\myfile.trace" << endl;
    cout << "\n\t myfile.trace" << endl;
    cin >> filepath;
    in_file.open(filepath,ios::in);
    while(in_file.fail())
    {
        cout << "Open ERROR! Please Check the Path and Name, and Input again!" << endl;
        cin >> filepath;
        in_file.open(filepath,ios::in);
    }

    #ifdef OUTPUT
    int i_line_proceded = 0;
    ofstream out_put;
    out_put.open("test.log",ios::out);
    #endif // OUTPUT

    while(!in_file.eof())
    {
        in_file.getline(address,13);
        bool __attribute__((unused)) is_success = GetHitNum(address); //in case of the warning of "Wunused-but-set-variable"
        assert(is_success);

        #ifdef OUTPUT
        i_line_proceded++;
        out_put << i_line_proceded << endl;
        cout << address << endl;
        #endif // OUTPUT
    }

    #ifdef OUTPUT
    out_put.close();
    #endif // OUTPUT

    in_file.close();
    GetHitRate();
}

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
    temp = strtoul(address+2,NULL,16);
    bitset<32> flags(temp); // flags if the binary of address

    #ifndef NDEBUG
    cout << flags << endl;
    #endif // NDEBUG

    hit = IsHit(flags,current_line);
    if(hit && is_load)
    {
        i_num_access++;
        i_num_load++;
        i_num_load_hit++;
        i_num_hit++;

        #ifndef NDEBUG
        cout << "Loading" << endl;
        cout << "Hit" << endl;
        cout << "Read from Cache!" << endl;
        #endif // NDEBUG
        if(t_replace == LRU)
        {
            LruHitProcess();
        }

    }
    else if(hit && is_store)
    {
        i_num_access++;
        i_num_store++;
        i_num_store_hit++;
        i_num_hit++;

        #ifndef NDEBUG
        cout << "Storing" << endl;
        cout << "Hit" << endl;
        cout << "Write to Cache" << endl;
        #endif // NDEBUG
        cache_item[current_line][29] = true; //设置dirty为true
        if(t_replace == LRU)
        {
            LruHitProcess();
        }

    }
    else if(is_load)
    {
        i_num_access++;
        i_num_load++;

        #ifndef NDEBUG
        cout << "Loading" << endl;
        cout << "Not Hit" << endl;
        #endif // NDEBUG

        GetRead(flags);

        #ifndef NDEBUG
        cout << "Read from Cache!" << endl;
        #endif // NDEBUG
        if(t_replace == LRU)
        {
            LruUnhitSpace();
        }

    }
    else if(is_store)
    {
        i_num_access++;
        i_num_store++;

        #ifndef NDEBUG
        cout << "Storing" << endl;
        cout << "Not Hit" << endl;
        #endif // NDEBUG

        GetRead(flags);

        #ifndef NDEBUG
        cout << "Write to Cache" << endl;
        #endif // NDEBUG
        cache_item[current_line][29] = true; //设置dirty为true
        if(t_replace == LRU)
        {
            LruUnhitSpace();
        }
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
        #ifndef NDEBUG
        cout << "There have " << i_num_space << " space lines" << endl;
        #endif // NDEBUG
    }

    return true;
}

bool IsHit(bitset<32> flags,unsigned long int& current_line)
{
    bool ret = false;
    if(t_assoc == direct_mapped)
    {
        bitset<32> flags_line;
        for(j=0,i=(bit_block);i<(bit_block+bit_line);j++,i++) //判断在cache多少行
        {
            flags_line[j] = flags[i];
        }
        current_line = flags_line.to_ulong();

        assert(cache_item[current_line][31] == true);

        if(cache_item[current_line][30]==true) //判断hit位是否为真
        {
            ret = true;
            for(i=31,j=28;i>(31ul-bit_tag);i--,j--) //判断标记是否相同,i:address,j:cache
            {
                if(flags[i] != cache_item[current_line][j])
                {
                    ret = false;
                    break;
                }
            }
        }
    }
	else if(t_assoc == full_associative)
    {
        for(temp=0;temp<i_num_line;temp++)
        {
            if(cache_item[temp][30]==true) //判断hit位是否为真
            {
                ret = true;
                for(i=31,j=28;i>(31ul-bit_tag);i--,j--) //判断标记是否相同,i:address,j:cache
                {

                    if(flags[i] != cache_item[temp][j])
                    {
                        ret = false;
                        break;
                    }
                }
            }
            if(ret == true)
            {
                current_line = temp;
                break;
            }
        }

    }
    else if(t_assoc == set_associative)
    {
        bitset<32> flags_set;
        for(j=0,i=(bit_block);i<(bit_block+bit_set);j++,i++) //判断在cache多少组
        {
            flags_set[j] = flags[i];
        }
        current_set = flags_set.to_ulong();
        for(temp=(current_set*i_cache_set);temp<((current_set+1)*i_cache_set);temp++)
        {
            if(cache_item[temp][30]==true) //判断hit位是否为真
            {
                ret = true;
                for(i=31,j=28;i>(31ul-bit_tag);i--,j--) //判断标记是否相同,i:address,j:cache
                {

                    if(flags[i] != cache_item[temp][j])
                    {
                        ret = false;
                        break;
                    }
                }
            }
            if(ret == true)
            {
                current_line = temp;
                break;
            }
        }

        //assert(cache_item[current_line][31] == true);
    }
    return ret;
}

void GetRead(bitset<32> flags)
{
    if(t_assoc == direct_mapped)
    {
        if(cache_item[current_line][30] == false) //hit is false
        {
            #ifndef NDEBUG
            cout << "Read from Main Memory to Cache!" << endl;
            #endif // NDEBUG
            for(i=31,j=28;i>(31ul-bit_tag);i--,j--) //设置标记
            {
                cache_item[current_line][j] = flags[i];
            }
            cache_item[current_line][30] = true; //设置hit位为true
        }
        else
        {
            GetReplace(flags,current_line);
        }
    }
	else if(t_assoc == full_associative)
    {
        bool space = false;
        for(temp=0;temp<i_num_line;temp++)
        {
            if(cache_item[temp][30] == false) //find a space line
            {
                space = true;
                break;
            }
        }

        if(space == true)
        {
            current_line = --temp;
            #ifndef NDEBUG
            cout << "Read from Main Memory to Cache!" << endl;
            #endif // NDEBUG
            for(i=31,j=28;i>(31ul-bit_tag);i--,j--) //设置标记
            {
                cache_item[temp][j] = flags[i];
            }
            cache_item[temp][30] = true; //设置hit位为true.
            if(t_replace == LRU)
            {
                LruUnhitSpace();
            }

        }
        else
        {
            GetReplace(flags,current_line);
        }
    }
    else if(t_assoc == set_associative)
    {
        bool space = false;
        for(temp=(current_set*i_cache_set);temp<((current_set+1)*i_cache_set);temp++)
        {
            if(cache_item[temp][30] == false) //find a space line
            {
                space = true;
                break;
            }
        }
        if(space == true)
        {
            current_line = --temp;
            #ifndef NDEBUG
            cout << "Read from Main Memory to Cache!" << endl;
            #endif // NDEBUG
            for(i=31,j=28;i>(31ul-bit_tag);i--,j--) //设置标记
            {
                cache_item[temp][j] = flags[i];
            }
            cache_item[temp][30] = true; //设置hit位为true.
            if(t_replace == LRU)
            {
                LruUnhitSpace();
            }
        }
        else
        {
            GetReplace(flags,current_line);
        }
    }
}


void GetWrite() //写入内存
{
    #ifndef NDEBUG
    cout << "Writing to the Main Memory!" <<endl;
    #endif
    cache_item[current_line][29] = false; //设置dirty为false
    cache_item[current_line][30] = false; //设置hit为false
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

