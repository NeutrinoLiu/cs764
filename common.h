#pragma once

#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>

#include "const.h"

using namespace std;

struct Row {
    static string genHash(string raw);
    static vector<int> COLMAP;
private:
    char * _base;
public:
    Row(char * base);
    char * col(int index, int &size);
    char * hash(int &size);
    void setColMap(vector<int> colMap);
};

string xorStrings(const string str1, const string str2);
extern string genFileName(int index, string prefix);
extern void initRandSeed();
extern string genRandString(int size);