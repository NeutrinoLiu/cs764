#pragma once

#include <stdlib.h>
#include <vector>
#include "defs.h"
#include "consts.h"

struct Row {
    static std::vector<int> _colSize;
    Row(char * base);
    char* col(int columnNum, int &size);
private:
    char * _base;
};

extern void genFileName(int index, char * label, char* const retName);
extern void genSingleRow(char * buff, int size);
