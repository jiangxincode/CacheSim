// libjiangxin.cpp

#include "stdio.h"
#include "ctype.h"
#include "stdlib.h"
#include "jiangxin.h"

char jx_getchar(short option)
{
    char ch,temp;
    ch = getchar();
    if(ch == '\n') //直接输入回车，返回'\n'
        return '\n';
    else if((temp=getchar())!='\n') //输入一些字符（不止一个），然后回车，清除所有字符后返回'\n'
    {
        while((temp=getchar())!='\n' && temp!=EOF);
        return '\n';
    }
    else //输入一个字符，软后回车，无须清除，大小写转换后直接返回
    {
        switch(option)
        {
            case 1:ch = tolower(ch);break;
            case 2:ch = toupper(ch);break;
            default:
                perror("Error Argument:option\n");
                break;
        }
        return ch;
    }
}
void jx_PrintBye(void)
{
    puts("\nThanks for your use!");
}
void jx_PrintAuthorInfo()
{
    puts("Do you want to see the detail infomation about the program(Y/N):");
    char ch = jx_getchar((short)1);
    while((ch!='y') && (ch!= 'n'))
    {
        puts("Invalid Input,Please Input Again!");
        ch = jx_getchar((short)1);
    }
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
