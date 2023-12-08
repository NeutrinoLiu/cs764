#define TRACE_OUT true
#include "Sort.h"

SortPlan::SortPlan (Plan * const input) : _input (input)
{
	TRACE (TRACE_OUT);
} // SortPlan::SortPlan

SortPlan::~SortPlan ()
{
	TRACE (TRACE_OUT);
	delete _input;
} // SortPlan::~SortPlan

Iterator * SortPlan::init () const
{
	TRACE (TRACE_OUT);
	return new SortIterator (this);
} // SortPlan::init

SortIterator::SortIterator (SortPlan const * const plan) :
	_plan (plan), _input (plan->_input->init ()),
	_consumed (0), _produced (0)
{
	TRACE (TRACE_OUT);

	while (_input->next ())  ++ _consumed;
	delete _input;

	int numOfFiles = _consumed / NUM_ROW_PER_FILE;
	for (int i=0; i < numOfFiles; i++ ) {
		char fileNamebuff[MAX_FILE_NAME_LENGTH];
		genFileName(i, "scan", fileNamebuff);
		_inFiles.push_back(new ReadStream(fileNamebuff));
		genFileName(i, "scan", fileNamebuff);
		_inFiles.push_back(new ReadStream(fileNamebuff));
	}

	// TODO init with in memory sorting 

	traceprintf ("consumed %lu rows\n",
			(unsigned long) (_consumed));
} // SortIterator::SortIterator

SortIterator::~SortIterator ()
{
	TRACE (TRACE_OUT);

	traceprintf ("produced %lu of %lu rows\n",
			(unsigned long) (_produced),
			(unsigned long) (_consumed));
} // SortIterator::~SortIterator

bool SortIterator::next ()
{
	TRACE (TRACE_OUT);

	if (_produced >= _consumed)  return false;

	++ _produced;
	return true;
} // SortIterator::next
