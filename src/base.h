/*********************************************
// base.h
// 1.declaration of almost all global variables.
// 2.definition of almost all structures.
// 3.description of almost all compiler options.
// 4.declaration of almost all functions.
*********************************************/

#define NDEBUG // For NDEBUG pattern

#define QUICK // For testing the program quickly

//#define OUTPUT // For writing the information to the test.log

//#define DirectMapped_None_WriteBack
//#define FullAssociative_Random_WriteBack
#define SetAssociative_Random_WriteBack

#include <iostream>
#include <fstream>
#include <bitset>

#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <ctime>


#ifdef QUICK
#define MAX_CACHE_LINE 65536 // 2^16
#endif
#ifndef QUICK
#define MAX_CACHE_LINE 268435456 // The max num of gcc array support 268435456(2^28)
#endif


#ifndef STRUCT_TYPE
#define STRUCT_TYPE
// 内存地址与Cache地址的关联方式：直接映射、组相联、全相联
enum associativity_way {direct_mapped=1,set_associative,full_associative};

// 替换策略：none（直接替换），FIFO（先进先出算法），LRU（最近最少用算法），LFU（最不经常用算法），Random（随机替换算法）
enum replacement_way {none,FIFO=1,LRU,LFU,Random};

// 写策略：write_through（全写法），write_back（回写法）
enum write_way {write_through=1,write_back};
#endif // STRUCT_TYPE


typedef enum associativity_way ASSOC;
typedef enum replacement_way REPLACE;
typedef enum write_way WRITE;

/******************************************/
extern unsigned int long i_cache_size; //cache size
extern unsigned int long i_cache_line_size; //cache line size
extern unsigned int long i_cache_set; //cache set

extern unsigned int long i_num_line; //How many lines of the cache.
extern unsigned int long i_num_set; //How many sets of the cache.

extern ASSOC t_assoc; //associativity method
extern REPLACE t_replace; //replacement policy
extern WRITE t_write; //write policy
/******************************************/

/******************************************/
extern short unsigned int bit_block; //How many bits of the block.
extern short unsigned int bit_line; //How many bits of the line.
extern short unsigned int bit_tag; //How many bits of the tag.
extern short unsigned int bit_set; //How many bits of the set.
/******************************************/

/******************************************/
extern unsigned long int i_num_access; //Number of cache access
extern unsigned long int i_num_load; //Number of cache load
extern unsigned long int i_num_store; //Number of cache store
extern unsigned long int i_num_space; //Number of space line

extern unsigned long int i_num_hit; //Number of cache hit
extern unsigned long int i_num_load_hit; //Number of load hit
extern unsigned long int i_num_store_hit; //Number of store hit

extern float f_ave_rate; //Average cache hit rate
extern float f_load_rate; //Cache hit rate for loads
extern float f_store_rate; //Cache hit rate for stores
/******************************************/

extern std::bitset<32> cache_item[MAX_CACHE_LINE]; // [31]:valid,[30]:hit,[29]:dirty,[28]-[0]:data
extern unsigned long int LRU_priority[MAX_CACHE_LINE]; //For LRU policy's priority
extern unsigned long int current_line; // The line num which is processing
extern unsigned long int current_set; // The set num which is processing
extern unsigned long int i,j; //For loop
extern unsigned long int temp; //A temp variable


bool GetHitNum(char *address);
void GetHitRate();
bool IsHit(std::bitset<32> flags);
void GetReplace(std::bitset<32> flags);
void GetRead(std::bitset<32> flags);
void GetWrite();

void InitVariables();

/**
 * get input information
 */
void GetInput();
void CalcInfo();
void CreateCache();
void FileTest();

/**
 * output the result
 */
void PrintOutput();

void LruHitProcess();
void LruUnhitSpace();
void LruUnhitUnspace();
