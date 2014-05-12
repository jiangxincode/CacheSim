#include "functions.h"

using namespace std;

int main()
{
    #ifdef NDEBUG
    PrintAuthorInfo();
    #endif // NDBUG

    char ch = '\0';
do
{
    InitVariables();

    #ifdef NDEBUG
    GetInput(); // get input information
    #endif // NDEBUG

    CalcInfo();
    FileTest();
    PrintOutput(); // output the result
    cout << "Continue/Exit(C/E)" << endl;
    cin >> ch;
    ch = tolower(ch);
}while(ch != 'e');

    PrintBye();
    return 0;
}
