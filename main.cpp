#include "functions.h"
#include "jiangxin.h"

using namespace std;

int main()
{
    #ifdef NDEBUG
    jx_PrintAuthorInfo();
    #endif // NDBUG

    char ch = '\0';
do
{
    InitVariables();

    #ifdef NDEBUG
    GetInput(); // get input information
    #endif // NDEBUG

    CalcInfo();
    CreateCache();
    FileTest();
    PrintOutput(); // output the result
    cout << "Continue/Exit(C/E)" << endl;
    cin >> ch;
    ch = tolower(ch);
}while(ch != 'e');

    jx_PrintBye();
    return 0;
}
