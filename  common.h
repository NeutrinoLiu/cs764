#include <stdlib.h>
#include <vector>

struct Record {
    static std::vector<int> COL_SIZE;
    Record(char * base);
    char* get(int columnNum, int &size);
private:
    char * base;
};