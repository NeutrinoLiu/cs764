#define TRACE_OUT true
#include "Scan.h"
#include <cstdlib>
#include <ctime>

/*
	just the generator
*/

ScanPlan::ScanPlan (RowCount const count) : _count (count)
{
	TRACE (TRACE_OUT);
} // ScanPlan::ScanPlan

ScanPlan::~ScanPlan ()
{
	TRACE (TRACE_OUT);
} // ScanPlan::~ScanPlan

Iterator * ScanPlan::init () const
{
	TRACE (TRACE_OUT);
	return new ScanIterator (this);
} // ScanPlan::init

ScanIterator::ScanIterator (ScanPlan const * const plan) :
	_plan (plan), _count (0)
{
	TRACE (TRACE_OUT);
} // ScanIterator::ScanIterator

ScanIterator::~ScanIterator ()
{
	TRACE (TRACE_OUT);
	traceprintf ("produced %lu of %lu rows\n",
			(unsigned long) (_count),
			(unsigned long) (_plan->_count));
} // ScanIterator::~ScanIterator

bool ScanIterator::next ()
{
	TRACE (TRACE_OUT);
	// srand(static_cast<unsigned int>(time(0)));

	if (_count >= _plan->_count) {
		return false;
	}

	++ _count;
	return true;
} // ScanIterator::next
