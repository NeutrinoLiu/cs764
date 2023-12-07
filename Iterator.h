#pragma once
#include "defs.h"
#include "common.h"

typedef uint64_t RowCount;

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
private:
	RowCount _count;
}; // class Iterator
