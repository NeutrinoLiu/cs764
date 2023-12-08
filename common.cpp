#include "common.h"

Row::Row (char * base) :
_base(base) {
}

std::vector<int> Row::_colSize = {12, 13, 25};

char *
Row::col (int columnNum, int &size) {
    Assert(columnNum < _colSize.size(), __FILE__, __LINE__);
    int offSet = 0;
    for (auto i = _colSize.begin(); i <= _colSize.begin() + columnNum; i ++) {
        offSet += *i;
    }
    size = _colSize[columnNum];
    return _base + offSet;
}

/* generate file name by index 
    a single db consists of multiple files */
void genFileName(int index, char * label, char* const retName) {
    snprintf(retName, MAX_FILE_NAME_LENGTH, "%s_%s_%d.db", FLIE_PREFIX, label, index);
}

/* random string generator, with 0 in the end*/
void fillRandString(char *str, size_t size)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
}

/* gen such colomns: key[size/4] value[size/4] check[size/2] 
    check = concat(key, value) for verification
    hence whole row looks like [key:value:key:value] in bytes,
    /0 is overwritten */
void genSingleRow(char * buff, int size) {
    Assert(size %2 == 0, __FILE__, __LINE__); // size expected to be even number
	srand(static_cast<unsigned int>(time(0)));
    int kSize = size / 4; 
    int vSize = size / 2 - kSize;
    // int checkSize = size / 2; 
    fillRandString(buff, kSize);
    fillRandString(buff + kSize, vSize);
    strncpy(buff + kSize + vSize, buff, kSize);
    strncpy(buff + kSize + vSize + kSize, buff + kSize, vSize);
}
