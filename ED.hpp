#ifndef _ED
#define _ED
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
class ED 
{
    public:
    char** traceMatx;
    int** alMatx;
    int X, Y;
    char yholder,xholder;
    int case1,case2,case3;
    int minHolder;
    int caseHolder;
    int counter, xc,yc;
    int editDistance;
    string xString, yString;
    string answer;
    ED(string s1, string s2);
    static int penalty(char a, char b);
    static int min(int a, int b, int c);
    int OptDistance();
    string Alignment();
    void coutEditDist();
    ~ED();
};
 
#endif
