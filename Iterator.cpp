#define TRACE_OUT true
#include "Iterator.h"

/*
	Plan is just a table
*/

// ========== PLAN

Plan::Plan ()
{
	TRACE (TRACE_OUT);
} // Plan::Plan

Plan::~Plan ()
{
	TRACE (TRACE_OUT);
} // Plan::~Plan

// ========== ITER

Iterator::Iterator ()
{
	TRACE (TRACE_OUT);
} // Iterator::Iterator

Iterator::~Iterator ()
{
	TRACE (TRACE_OUT);
} // Iterator::~Iterator


void Iterator::run ()
{
	TRACE (TRACE_OUT);
	while (next ()) ++ _count;
	traceprintf ("entire plan produced %lu rows\n",
			(unsigned long) _count);
} // Iterator::run
