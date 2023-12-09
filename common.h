#pragma once

#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>

#include "const.h"
#include "storage.hpp"

using namespace std;

struct Row {
    friend class MemQueue;
    static string genHash(string raw);
    static int size;
    static int compare(const void * a, const void * b);
    static vector<int> COLWIDTH;
private:
    char * _base;
public:
    Row(char * base);
    char * col(int index);
    char * hash();
    void setColMap(vector<int> colMap);
};

string xorStrings(const string str1, const string str2);
extern string genFileName(int index, string prefix);
extern void initRandSeed();
extern string genRandString(int size);