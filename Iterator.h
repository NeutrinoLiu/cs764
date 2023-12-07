#pragma once
#define BUILTIN_SEQUENTIAL_VECTOR
#include "defs.h"
#include <vector>

typedef uint64_t RowCount;
typedef uint64_t Id_t; // 8 Byte for id
typedef uint64_t Value_t; // 8 Byte per column value

class Plan
{
	friend class Iterator;
public:
	Plan ();
	virtual ~Plan ();
	virtual class Iterator * init () const = 0;
private:
}; // class Plan

class Iterator
{
public:
	Iterator ();
	virtual ~Iterator ();
	void run ();	// traverse
	virtual bool next () = 0;
}; // class Iterator
