#include "Iterator.h"

/*
	Plan is just a table
*/

// ========== PLAN

Plan::Plan ()
{
	// TRACE (true);
} // Plan::Plan

Plan::~Plan ()
{
	// TRACE (true);
} // Plan::~Plan

// ========== ROW

Row::Row(Id_t new_id, Value_t new_col1, Value_t new_col2) :
	_id(new_id),
	col1(new_col1),
	col2(new_col2)	
{}

Id_t Row::getId ()
{
	// TRACE (true);
	return _id;
}

// dummy hash function
size_t Row::getHash()
{
	return static_cast<size_t>(getId()) ^ static_cast<size_t>(col1) ^ static_cast<size_t>(col2);
}

// ========== ITER

Iterator::Iterator () : _count (0)
{
	// TRACE (true);
} // Iterator::Iterator

Iterator::~Iterator ()
{
	// TRACE (true);

#ifdef BUILTIN_SEQUENTIAL_VECTOR
	for(int i = 0; i < table.size(); i++) delete table[i];
	// Bangya: you might want to free mem of rows
#endif

} // Iterator::~Iterator


void Iterator::run ()
{
	// TRACE (true);

	while (next ())  ++ _count;

	// traceprintf ("entire plan produced %lu rows\n",
			// (unsigned long) _count);
} // Iterator::run
