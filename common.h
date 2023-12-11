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
    static size_t size;
    static int compare(const void * a, const void * b);
    static vector<int> COLWIDTH;
private:
    char * _base;
public:
    Row(char * base);
    char * col(int index);
    row_hash_t & hash();
    void genHash();
    void genCols();
    void setColMap(vector<int> colMap);
};

extern string genFileName(int index, string prefix);
extern void initRandSeed();