#include "functions.h"

using namespace std;

int main()
{
    PrintAuthorInfo();
    char ch = '\0';
do
{
    InitVariables();
    GetInput(); // get input information
    FileTest();
    PrintOutput(); // output the result
    cout << "Continue/Exit(C/E)" << endl;
    cin >> ch;
    ch = tolower(ch);
}while(ch != 'e');

    PrintBye();
    return 0;
}
