#include <stdlib.h>
#include <vector>

struct Record {
    static std::vector<int> _colSize;
    Record(char * base);
    char* get(int columnNum, int &size);
private:
    char * _base;
};
