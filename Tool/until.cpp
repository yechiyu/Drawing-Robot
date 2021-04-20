#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
using namespace std;

int main()
{
    string Y,X;
    ifstream fin("data.txt"); 
    const int LINE_LENGTH = 100; 
    char str[LINE_LENGTH];  
    char *p;
	const char *delim = " ";
    while( fin.getline(str,LINE_LENGTH) )
    {    
        cout << str << endl;
        p = strtok(str, delim);
        X = p;
	    while(p) {
            Y = p;
            p = strtok(NULL, delim);
	    }
        cout <<"X:"<< X << endl;
        cout <<"Y:"<< Y << endl;
    }
}
