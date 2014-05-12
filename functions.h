//functions.h

#define _windows_

#ifndef headfiles
#define headfiles
    #include <iostream>
    #include <cstdio>
    #include <cstdlib>
    #include <cctype>
#endif

#ifndef types
#define types
    // 内存地址与Cache地址的关联方式：直接映射、组相联、全相联
    enum associativity_way{direct_mapped=1,set_associative,full_associative};
    // 替换策略：FIFO（先进先出算法），LRU（最近最少用算法），LFU（最不经常用算法），Random（随机替换算法）
    enum replacement_way{FIFO=1,LRU,LFU,Random};
    // 写策略：write_through（全写法），write_back（回写法）
    enum write_way{write_through=1,write_back};

    typedef enum associativity_way ASSOC;
    typedef enum replacement_way REPLACE;
    typedef enum write_way WRITE;
#endif // types

    /******************************************/
    /* for input */
    extern int i_cache_size; //cache size
    extern int i_cache_line_size; //cacheline size
    extern ASSOC t_assoc; //associativity method
    extern REPLACE t_replace; //replacement policy
    extern WRITE t_write; //write policy
    /* for input */
    /******************************************/

    /******************************************/
    /* for output */
    extern int i_num_access; //Number of cache access
    extern int i_num_load; //Number of cache load
    extern int i_num_store; //Number of cache store
    extern float f_ave_rate; //Average cache hit rate
    extern float f_load_rate; //Cache hit rate for loads
    extern float f_store_rate; //Cache hit rate for stores
    /* for output */
    /******************************************/

void PrintAuthorInfo(void);
void InitVariables(void);
void GetInput(void);
void PrintOutput(void);
void PrintBye(void);
