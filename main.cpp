#include "functions.h"

using namespace std;

int main()
{
    #ifdef NDBUG
    PrintAuthorInfo();
    #endif // NDBUG

    char ch = '\0';
do
{
    InitVariables();

    #ifdef NDEBUG
    GetInput(); // get input information
    #endif // NDEBUG

    FileTest();
    PrintOutput(); // output the result
    cout << "Continue/Exit(C/E)" << endl;
    cin >> ch;
    ch = tolower(ch);
}while(ch != 'e');

    PrintBye();
    return 0;
}
