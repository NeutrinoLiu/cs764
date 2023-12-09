#include "Scan.h"

ScanPlan::ScanPlan (RowCount const count) : 
_count (count)
{
	TRACE (true);
} // ScanPlan::ScanPlan

ScanPlan::~ScanPlan ()
{
	TRACE (true);
} // ScanPlan::~ScanPlan

Iterator * ScanPlan::init () 
{
	TRACE (true);
	return new ScanIterator (this);
} // ScanPlan::init

ScanIterator::ScanIterator (ScanPlan const * const plan) :
	_plan (plan), _count (0), _ws(genFileName(0, FILE_PREFIX_RAW))
{
	TRACE (true);
} // ScanIterator::ScanIterator

ScanIterator::~ScanIterator ()
{
	TRACE (true);
	traceprintf ("produced %lu of %lu rows\n",
			(unsigned long) (_count),
			(unsigned long) (_plan->_count));
} // ScanIterator::~ScanIterator

bool ScanIterator::next ()
{
	TRACE (true);

	if (_count >= _plan->_count)
		return false;

	// gen new row
	string row;
	for (int i = 0; i < Row::COLWIDTH.size() - 1; i++) {
		row += genRandString(Row::COLWIDTH[i]);
	}
	row += Row::genHash(row);
	// traceprintf("generate a new row: %s with length %zu \n", row.c_str(), row.size());
	_ws.write((void *)row.c_str(), row.size());

	++ _count;
	return true;
} // ScanIterator::next

char* ScanIterator::get() {
	return (char*) NULL;
}