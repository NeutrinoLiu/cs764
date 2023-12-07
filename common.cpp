#include "common.h"

Record::Record (char * base) :
_base(base) {}

char *
Record::get (int columnNum, int &size) {
    int offSet = 0;
    for (auto i = _colSize.begin(); i <= _colSize.begin() + columnNum; i ++) {
        offSet += *i;
    }
    size = _colSize[columnNum];
    return _base + offSet;
}

