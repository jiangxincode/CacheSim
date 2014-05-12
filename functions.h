//functions.h

#ifndef headfiles
#define headfiles
    #include <iostream>
    #include <cstdio>
    #include <cstdlib>
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

void PrintAuthorInfo(void);
void GetInput(int& i_cache_size,int& i_cache_line_size,ASSOC& t_assoc,REPLACE& t_replace,WRITE& t_write);
void PrintOutput(int i_cache_size,int i_cache_line_size,
                 ASSOC t_assoc,REPLACE t_replace,WRITE t_write,
                 int i_num_access,int i_num_load,int i_num_store,
                 float f_ave_rate,float f_load_rate,float f_store_rate);
void PrintBye();
