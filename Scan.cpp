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
	// init has been decorated with const, cant open file stream over there
	int numOfFiles = _count / NUM_ROW_PER_FILE;
	for (int i=0; i < numOfFiles; i++ ) {
		char fileNamebuff[MAX_FILE_NAME_LENGTH];
		genFileName(i, "scan", fileNamebuff);
		_files.push_back(new WriteStream(fileNamebuff));
	}
} // ScanPlan::ScanPlan

ScanPlan::~ScanPlan ()
{
	TRACE (TRACE_OUT);
	// release write stream
	int numOfFiles = _count / NUM_ROW_PER_FILE;
	for (auto i = _files.begin(); i != _files.end(); i++ ) {
		delete *i;
	}
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

	if (_count >= _plan->_count) {
		return false;
	}
	WriteStream * ws = _plan->_files[_count / NUM_ROW_PER_FILE];
	char rowBuff[ROW_SIZE];
	genSingleRow(rowBuff, ROW_SIZE);
	ws->write(rowBuff, ROW_SIZE);
	/* there is only a global ctr _count, no ctr for each file
		but file write is sequential so it doesnt matters */
	++ _count;
	return true;
} // ScanIterator::next
