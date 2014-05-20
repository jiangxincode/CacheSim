/*************************************************
// functions.h
// 1.Declaration of almost all functions.
*************************************************/
#include "base.h"

bool GetHitNum(char *address);
void GetHitRate(void);
bool IsHit(std::bitset<32> flags,unsigned long int& current_line);
void GetReplace(std::bitset<32> flags,unsigned long int& current_line);
void GetRead(std::bitset<32> flags);
void GetWrite();

void InitVariables(void);
void GetInput(void);
void CalcInfo(void);
void CreateCache(void);
void FileTest(void);
void PrintOutput(void);

