#include "Scan.h"
#include <cstdlib>
#include <ctime>

/*
	just the generator
*/

ScanPlan::ScanPlan (RowCount const count) : _count (count)
{
	// TRACE (true);
} // ScanPlan::ScanPlan

ScanPlan::~ScanPlan ()
{
	// TRACE (true);
} // ScanPlan::~ScanPlan

Iterator * ScanPlan::init () const
{
	// TRACE (true);
	return new ScanIterator (this);
} // ScanPlan::init

ScanIterator::ScanIterator (ScanPlan const * const plan) :
	_plan (plan), _count (0)
{
	// TRACE (true);
	_count = 0;
} // ScanIterator::ScanIterator

ScanIterator::~ScanIterator ()
{
	// TRACE (true);
	// traceprintf ("produced %lu of %lu rows\n",
	// 		(unsigned long) (_count),
	// 		(unsigned long) (_plan->_count));
} // ScanIterator::~ScanIterator

bool ScanIterator::next ()
{
	// TRACE (true);
	srand(static_cast<unsigned int>(time(0)));

	if (_count >= _plan->_count) {
		return false;
	} else {
		Row r = Row((Id_t) _count, (Value_t) rand(), (Value_t) rand());
		table.push_back(&r);
		hashes.push_back(r.getHash());
	}

	// ++ _count;
	return true;
} // ScanIterator::next
