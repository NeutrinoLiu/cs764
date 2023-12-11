#include "common.h"

#include <cstring>

vector<int> Row::COLWIDTH = {15, 15, 15, 5};
size_t Row::size = 50;

Row::Row(char *base) : _base(base) {}

char *
Row::col(int index) {
    int offset = 0;
    for (int i = 0; i < index; i++)
        offset += COLWIDTH[i];
    return _base + offset;
}

row_hash_t &Row::hash() {
    return *(row_hash_t *)col(COLWIDTH.size() - 1);
}

int Row::compare(const void *_a, const void *_b) {
    Row a((char *)_a), b((char *)_b);
    return memcmp(a.col(0), b.col(0), COLWIDTH[0]);  // first col is the key
}

void Row::genHash() {
    hash() = 0;
    row_hash_t *data = (row_hash_t *)_base;
    row_hash_t _hash = 0;
    size_t length = (Row::size - COLWIDTH[COLWIDTH.size() - 1] + HASH_SIZE - 1) / HASH_SIZE;
    for (size_t i = 0; i < length; i++)
        _hash ^= data[i];
    hash() = _hash;
}

void Row::genCols() {
    size_t length = Row::size - COLWIDTH[COLWIDTH.size() - 1];    
    for (size_t i = 0; i < length; i++)
        _base[i] = std::rand();
}

string
genFileName(int index, string prefix) {
    stringstream ret;
    ret << prefix << "_" << index << ".db";
    return ret.str();
}

void initRandSeed() {
    srand(static_cast<unsigned int>(time(NULL)));
}

