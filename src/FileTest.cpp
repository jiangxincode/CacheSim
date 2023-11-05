#include "base.h"

using namespace std;

void FileTest(void)
{
    char filepath[100];
    ifstream in_file;
    char address[13];
    cout << "\nPlease input the path and name that you want to test!" << endl;
    cout << "\n\t C:\\temp\\myfile.trace" << endl;
    cout << "\n\t myfile.trace" << endl;
    cin >> filepath;
    in_file.open(filepath,ios::in);

    while(in_file.fail())
    {
        cout << "Open ERROR! Please Check the Path and Name, and Input again!" << endl;
        cin >> filepath;
        in_file.open(filepath,ios::in);
    }

#ifdef OUTPUT
    int i_line_proceded = 0;
    ofstream out_put;
    out_put.open("test.log",ios::out);
#endif // OUTPUT

    while(!in_file.eof())
    {
        in_file.getline(address,13);
#ifdef __GNUC__
        bool __attribute__((unused)) is_success = GetHitNum(address); //in case of the warning of "Wunused-but-set-variable"
#endif
#ifndef __GNUC__
        bool is_success = GetHitNum(address);
#endif
        assert(is_success);
#ifdef OUTPUT
        i_line_proceded++;
        out_put << i_line_proceded << endl;
        cout << address << endl;
#endif // OUTPUT
    }

#ifdef OUTPUT
    out_put.close();
#endif // OUTPUT
    in_file.close();
    GetHitRate();
}
