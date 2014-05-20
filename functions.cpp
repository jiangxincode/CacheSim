/*************************************************
// functions.cpp
// 1.Defination of almost all functions.
*************************************************/

#include "functions.h"
#include "jiangxin.h"

using namespace std;


void InitVariables(void)
{
    temp = i_num_line;
    /******************************************/
    i_cache_size = 32; //cache size
    i_cache_line_size = 16; //cacheline size
    i_num_line = 0; //How many lines of the cache.

    #ifdef DirectMapped_None_WriteBack
    t_assoc = direct_mapped; //associativity method,default direct_mapped
    t_replace = none; //replacement policy,default Random
    t_write = write_back; //write policy,default write_back
    #endif // DirectMapped_None_WriteBack

    #ifdef FullAssociative_Random_WriteBack
    t_assoc = full_associative; //associativity method,default direct_mapped
    t_replace = Random; //replacement policy,default Random
    t_write = write_back; //write policy,default write_back
    #endif // FullAssociative_Random_WriteBack
    /******************************************/

    /******************************************/
    bit_block = 0; //How many bits of the block.
    bit_line = 0; //How many bits of the line.
    bit_tag = 0; //How many bits of the tag.
    /******************************************/

    /******************************************/
    i_num_access = 0; //Number of cache access
    i_num_load = 0; //Number of cache load
    i_num_store = 0; //Number of cache store
    i_num_space = 0; //Number of space line

    i_num_hit = 0; //Number of cache hit
    i_num_load_hit = 0; //Number of load hit
    i_num_store_hit = 0; //Number of store hit

    f_ave_rate = 0.0; //Average cache hit rate
    f_load_rate = 0.0; //Cache hit rate for loads
    f_store_rate = 0.0; //Cache hit rate for stores
    /******************************************/
    for(i=0;i<temp;i++)
    {
    	cache_item[i].reset(); // [31]:valid,[30]:hit,[29]:dirty,[28]-[0]:data
    }
    line = 0; // The line num which is processing
    i=0;j=0; //For loop
    /******************************************/
}
void GetInput(void)
{
    short temp = 0; //for switch

    puts("\nPlease input the number of the cache size(Unit:KB)");
    puts("\n\t(for example:1,2,4,8,16,32,64...2^18)");

// temp
    cin >> i_cache_size;
    while(i_cache_size<1 || i_cache_size>= 262144 || (i_cache_size&(~i_cache_size+1))!=i_cache_size)
    {
        puts("\nPlease input the number of the cache size(Unit:KB)");
        puts("\n\t(for example:1,2,4,8,16,32,64...2^18)");
        cin >> i_cache_size;
    }

    puts("\nPlease input the number of the cacheline size(Unit:Byte)");
    puts("\n\t(for example:1,2,4,8,16,32,64...2^18)");

// temp
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
    //cin >> t_assoc; //for ">>" doesn't overload,so it a error method
// temp
    scanf("%hd",&temp);
    switch(temp)
    {
        case 1:t_assoc = direct_mapped;break;
        case 2:t_assoc = set_associative;break;
        case 3:t_assoc = full_associative;break;
        default:
            cout << "Input Error!Please input again:" << endl;
            goto get_assoc;
    }
    if(t_assoc == direct_mapped) //If the associativity_way is direct_mapped,the replacement polacy can be none only;
    {
        t_replace = none;
        goto get_write;
    }

get_replacement:
    puts("\nPlease input the replacement policy:");
    puts("\n\t FIFO(First In First Out):input 1");
    puts("\n\t LRU(Least Recently Used):input 2");
    puts("\n\t LFU(Least Frequently Used):input 3");
    puts("\n\t Random:input 4");
    //cin >> t_replace; //for ">>" doesn't overload,so it a error method
// temp
    scanf("%hd",&temp);
    switch(temp)
    {
        case 1:t_replace = FIFO;break;
        case 2:t_replace = LRU;break;
        case 3:t_replace = LFU;break;
        case 4:t_replace = Random;break;
        default:
            cout << "Input Error!Please input again:" << endl;
            goto get_replacement;
    }

get_write:
    puts("\nPlease input write policy:");
    puts("\n\t Write through:input 1");
    puts("\n\t Write back:input 2");
    //cin >> t_write; //for ">>" doesn't overload,so it a error method
// temp
    scanf("%hd",&temp);
    switch(temp)
    {
        case 1:t_write = write_through;break;
        case 2:t_write = write_back;break;
        default:
            cout << "Input Error!Please input again:" << endl;
            goto get_write;
    }
}

void CalcInfo()
{
    if(t_assoc == full_associative)
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

        bit_tag = 32ul - bit_block;
        cout << "bit_block:" << bit_block << endl;
        cout << "bit_line: NULL" << endl;
        cout << "bit_tag:" << bit_tag << endl;
    }
}
void CreateCache()
{

	if(t_assoc == full_associative)
    {
        temp = i_num_line;

        #ifndef NDEGUG
        cout << "temp = " << temp <<endl;
        #endif // NDEGUG

        for(i=0;i<100;i++)
        {
            cout << cache_item[i] << endl;
        }
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
    int tempory = 0;
    //ofstream out_put;
    //out_put.open("log",ios::out);
    while(!in_file.eof())
    {
        in_file.getline(address,13);
        bool __attribute__((unused)) is_success = GetHitNum(address); //in case of the warning of "Wunused-but-set-variable"
        assert(is_success);
        tempory++;

        //out_put << tempory << endl;

        //cout << address << endl;
    }
    //out_put.close();
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
    unsigned long value = strtoul(address+2,NULL,16);
    bitset<32> flags(value);

    #ifndef NDEBUG
    cout << flags << endl;
    #endif // NDEBUG

    hit = IsHit(flags,line);

	if(t_assoc == full_associative)
    {
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
            cache_item[line][29] = true; //设置dirty为true
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
            cache_item[line][29] = true; //设置dirty为true
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
    }
    return true;
}

bool IsHit(bitset<32> flags,unsigned long int& line)
{
    clock_t start,end;
    start = clock();
    bool ret = false;
	if(t_assoc == full_associative)
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
                line = temp;
                break;
            }
        }

    }
    end = clock();
    //cout << "IsHis time is: " << (end - start) << endl;
    return ret;
}

void GetRead(bitset<32> flags)
{
	clock_t start,end;
	start = clock();
	if(t_assoc == full_associative)
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
            #ifndef NDEBUG
            cout << "Read from Main Memory to Cache!" << endl;
            #endif // NDEBUG
            for(i=31,j=28;i>(31ul-bit_tag);i--,j--) //设置标记
            {
                cache_item[temp][j] = flags[i];
            }
            cache_item[temp][30] = true; //设置hit位为true.
        }
        else
        {
            GetReplace(flags,line);
        }
    }
    end = clock();
    //cout << "GetRead time is:" << (start-end) << endl;
}

void GetReplace(bitset<32> flags,unsigned long int& line)
{
	clock_t start,end;
	start = clock();
	if(t_assoc == full_associative)
    {
    	temp = rand()/(RAND_MAX/i_num_line+1);
        line = temp;
    	#ifndef NDEBUG
    	cout << "Replace the Content of Cache: " << temp << endl;
    	#endif // NDEBUG
        if(cache_item[temp][29] == true) //dirty位必须同时为1才写入
        {
            GetWrite(); //写入内存
        }
        for(i=31,j=28;i>(31ul-bit_tag);i--,j--) //设置标记
        {
            cache_item[temp][j] = flags[i];
        }
        cache_item[temp][30] = true; //设置hit位为true
    }
    end = clock();
    //cout << "GetReplace time is: " << (end-start) << endl;
}

void GetWrite() //写入内存
{
    #ifndef NDEBUG
    cout << "Writing to the Main Memory!" <<endl;
    #endif
    cache_item[line][29] = false; //设置dirty为false
    cache_item[line][30] = false; //设置hit为false
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

void PrintOutput(void)
{
    cout << endl;
    cout << "Cache Size:" << i_cache_size << endl;
    cout << "Cacheline Size:" << i_cache_line_size << endl;
    switch(t_assoc)
    {
        case 1:cout << "Way of Associativity:direct_mapped" << endl;break;
        case 2:cout << "Way of Associativity:set_associative" << endl;break;
        case 3:cout << "Way of Associativity:full_associative" << endl;break;
        default:
            cerr << "ERROR ASSOCIATIVITY";break;
    }
    switch(t_replace)
    {
        case 0:cout << "Way of Replacement:NONE" << endl;break;
        case 1:cout << "Way of Replacement:FIFO" << endl;break;
        case 2:cout << "Way of Replacement:LRU" << endl;break;
        case 3:cout << "Way of Replacement:LFU" << endl;break;
        case 4:cout << "Way of Replacement:Random" << endl;break;
        default:
            cerr << "ERROR REPLACEMENT";break;
    }
    switch(t_write)
    {
        case 1:cout << "Way of Write:write_through" << endl;break;
        case 2:cout << "Way of Write:write_back" << endl;break;
        default:
            cerr << "ERROR WRITE";break;
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
