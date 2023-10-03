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

class Row
{
public:
	Row (Id_t new_id, Value_t new_col1=0, Value_t new_col2=0);
	// no need for destroyer
	Id_t getId ();
	Value_t col1;
	Value_t col2;
private:
	Id_t _id; // name col0 as _id, not modifiable
};

class Iterator
{
public:
	Iterator ();
	virtual ~Iterator ();
	void run ();	// traverse
	virtual bool next () = 0;

#ifdef BUILTIN_SEQUENTIAL_VECTOR
	std::vector<Row*> table; 
	Row* getRow(Id_t query_id) {
		return table[query_id];
	};
	// Bangya: each element in the table vector is a ptr toward a Row object
#endif

private:
	RowCount _count;
}; // class Iterator
