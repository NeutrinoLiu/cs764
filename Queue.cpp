#include "Queue.h"

MemQueue::MemQueue(char * src, int length) :
_ctr(0), _len(length), _size(Row::size) {
    _buff = (char *)malloc(_len * _size);
    if (! _buff) {
        printf("ERROR: memory allocate fails");
    }
    memcpy(_buff, src, _len * _size);
}
MemQueue::~MemQueue() {
    free(_buff);
}
bool MemQueue::next() {
    if (_ctr < _len) {
        _ctr ++;
        return true;
    } else return false;
}
char * MemQueue::get() {
    return _buff + _ctr * _size;
}


// =========

DiskQueue::DiskQueue(string fileName) :
_rs(fileName), _size(Row::size)
{
    _buff = (char *)malloc(_size);
}

DiskQueue::~DiskQueue() {
    free(_buff);
}

char * DiskQueue::get() {
    return _buff;
}

bool DiskQueue::next() {
    memset(_buff, 0, _size);
    int ret = _rs.read(_buff, _size);
    return ret > 0;
}

