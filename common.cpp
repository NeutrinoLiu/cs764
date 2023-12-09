#include "common.h"

vector<int> Row::COLWIDTH = {15,15,15,5};
int Row::size = 50;

Row::Row(char *base) :
_base(base) {}

char *
Row::col(int index) {
    int offset = 0;
    for (int i = 0; i < index; i++) 
        offset += COLWIDTH[i];
    return _base + offset;
}

char *
Row::hash() {
    return col(COLWIDTH.size()-1);
}

int
Row::compare(const void * a ,const void * b) {
    string aKey((char *)a, Row::COLWIDTH[0]);
    string bKey((char *)b, Row::COLWIDTH[0]);
    return aKey.compare(bKey);
}

string 
Row::genHash (string raw) {
    int offset = 0;
    int xorWidth = COLWIDTH[COLWIDTH.size()-1]; // width of last col as xor width

    for (int i = 0; i < COLWIDTH.size() - 1; i++) 
        offset += COLWIDTH[i];
    string nonHash = raw.substr(0, offset);
    string hash = nonHash.substr(0, xorWidth);
    offset = xorWidth;
    while (offset < nonHash.size()) {
        string snippet = nonHash.substr(offset, xorWidth);
        hash = xorStrings(hash,snippet);
        offset += xorWidth;
    }
    return hash;
}

string xorStrings(const string str1, const string str2) {
    size_t len1 = str1.length();
    size_t len2 = str2.length();
    size_t maxLen = (len1 > len2) ? len1 : len2;
    string paddedStr1 = str1 + string(maxLen - len1, '\0');
    string paddedStr2 = str2 + string(maxLen - len2, '\0');

    string result;
    for (size_t i = 0; i < maxLen; ++i) {
        char xorResult = paddedStr1[i] ^ paddedStr2[i];
        result.push_back(xorResult);
    }
    return result;
}

string
genFileName(int index, string prefix) {
    stringstream ret;
    ret << prefix << "_" << index << ".db";
    return ret.str();
}

void initRandSeed() {
    srand(static_cast<unsigned int>(std::time(NULL)));
}

string
genRandString(int size) {
    string CSETS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string ret;
    for (int i = 0; i < size; ++i) {
        int randomIndex = std::rand() % CSETS.size();
        ret += CSETS[randomIndex];
    }

    return ret;
}
