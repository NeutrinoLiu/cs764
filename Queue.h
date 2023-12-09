#pragma once
#include "common.h"

struct Queue {
    virtual bool next() = 0;
    virtual char * get() = 0;
    virtual ~Queue();
};

struct MemQueue : public Queue{
    MemQueue(char * base, int length);
    ~MemQueue();
    bool next();
    char * get();
private:
    char * _buff;
    int _ctr, _len, _size;
};

struct DiskQueue : public Queue{
    DiskQueue(string fileName);
    ~DiskQueue(); 
    bool next();
    char * get();
private:
    ReadStream _rs;
    char * _buff;
    int _size;
};