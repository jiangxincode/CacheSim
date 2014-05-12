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
//    puts("Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:");
//    puts("Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.");
//    puts("Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.");
//    puts("Neither the name of the jiangxin nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.");
//    puts("THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.");
    cout << endl;
}
void InitVariable(void)
{

}
void GetInput(int& i_cache_size,int& i_cache_line_size,ASSOC& t_assoc,REPLACE& t_replace,WRITE& t_write)
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
void PrintOutput(int i_cache_size,int i_cache_line_size,
                 ASSOC t_assoc,REPLACE t_replace,WRITE t_write,
                 int i_num_access,int i_num_load,int i_num_store,
                 float f_ave_rate,float f_load_rate,float f_store_rate)
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
    cout << "Number of cache store" << i_num_store << endl;
    cout << endl;
    cout << "Average cache hit rate:" << f_ave_rate/100 << "%" << endl;
    cout << "Cache hit rate for loads:" << f_load_rate/100 << "%" << endl;
    cout << "Cache hit rate for stores:" << f_store_rate/100 << "%" << endl;
    cout << endl;
}
void PrintBye()
{
    puts("\nThanks for your use!");
}
