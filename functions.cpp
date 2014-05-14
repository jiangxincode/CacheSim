//functions.cpp
#include "functions.h"

using namespace std;

void PrintAuthorInfo(void)
{
    cout << "NAME:CacheSim" << endl;
    cout << "FUNCTION:Simulate the functions of Cache" << endl;
    cout << "VERAION:0.01" << endl;
    cout << "AUTHOR:jiangxin" << endl;
    cout << "Copyright (c) 2014, jiangxin" << endl;
    cout << "All rights reserved." << endl;
    cout << endl;

    cout << "Do you want to see the detail infomation about the program(Y/N):" << endl;
    char ch = tolower(getchar());
    if(ch == 'y')
    {
        #ifdef _windows_
            system("notepad.exe README.txt");
        #endif
        #ifdef _linux_
            system("vim README.txt");
        #endif
    }
}
void InitVariables(void)
{
    /******************************************/
    /* for input */
    i_cache_size = 32; //cache size
    i_cache_line_size = 16; //cacheline size

    t_assoc = direct_mapped; //associativity method,default direct_mapped
    t_replace = none; //replacement policy,default Random
    t_write = write_back; //write policy,default write_back
    /* for input */
    /******************************************/

    /******************************************/
    /* for temp */
    i_num_line = 0; //How many lines of the cache.
    bit_block = 0; //How many bits of the block.
    bit_line = 0; //How many bits of the line.
    bit_tag = 0; //How many bits of the tag.
    /* for temp */
    /******************************************/

    /******************************************/
    /* for output */
    i_num_access = 0; //Number of cache access
    i_num_load = 0; //Number of cache load
    i_num_store = 0; //Number of cache store

    i_num_hit = 0; //Number of cache hit
    i_num_load_hit = 0; //Number of load hit
    i_num_store_hit = 0; //Number of store hit

    f_ave_rate = 0.0; //Average cache hit rate
    f_load_rate = 0.0; //Cache hit rate for loads
    f_store_rate = 0.0; //Cache hit rate for stores

    i_num_space = 0; //Number of space line
    /* for output */

    p_cache_item = cache_item;
    /******************************************/
}
void GetInput(void)
{
    int temp = 0; //for switch
    puts("\nPlease input the number of the cache size(Unit:KB):(for example:32)");
    cin >> i_cache_size;

    puts("\nPlease input the number of the cacheline size(Unit:Byte):(for example:16)");
    cin >> i_cache_line_size;

get_assoc:
    puts("\nPlease input the method of assoiativity between main memory and cache:");
    puts("\n\t directive_mapped:input 1");
    puts("\n\t set_associative:input 2");
    puts("\n\t full_associative:input 3");
    //cin >> t_assoc; //for ">>" doesn't overload,so it a error method
    scanf("%d",&temp);
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
    //cin >> t_replace;
    scanf("%d",&temp);
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
    //cin >> t_write;
    scanf("%d",&temp);
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

    assert(i_cache_line_size != 0);
    i_num_line = (i_cache_size<<10)/i_cache_line_size;
    unsigned long int temp = i_cache_line_size;
    while(temp)
    {
        temp >>= 1;
        bit_block++;
    }
    bit_block--; //warning
    temp = i_num_line;
    while(temp)
    {
        temp >>= 1;
        bit_line++;
    }
    bit_line--; //warning
    bit_tag = 32ul - bit_block - bit_line;
    cout << "bit_block:" << bit_block << endl;
    cout << "bit_line:" << bit_line << endl;
    cout << "bit_tag:" << bit_tag << endl;
}
void CreateCache()
{
    unsigned long int temp = i_num_line;
    cout << "temp = " << temp <<endl;
    for(unsigned long i=0;i<temp;i++)
    {
        //cout << cache_item[i] << endl;
    }
    for(unsigned long i=0;i<temp;i++)
    {
        cache_item[i][31] = true;
    }
    for(unsigned long i=0;i<temp;i++)
    {
        //cout << cache_item[i] << endl;
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
    while(!in_file.eof())
    {
        in_file.getline(address,13);
        bool __attribute__((unused)) is_success = false; //in case of the warning of "Wunused-but-set-variable"
        is_success = GetHitNum(address);
        assert(is_success);

        //cout << address << endl;
    }
    GetHitRate();

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
void PrintBye(void)
{
    puts("\nThanks for your use!");
}
