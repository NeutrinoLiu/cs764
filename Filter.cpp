#define TRACE_OUT true
#include "Filter.h"

/*
	Just the verifier
*/

FilterPlan::FilterPlan (Plan * const input) : _input (input)
{
	TRACE (TRACE_OUT);
} // FilterPlan::FilterPlan

FilterPlan::~FilterPlan ()
{
	TRACE (TRACE_OUT);
	delete _input;
} // FilterPlan::~FilterPlan

Iterator * FilterPlan::init () const
{
	TRACE (TRACE_OUT);
	return new FilterIterator (this);
} // FilterPlan::init

FilterIterator::FilterIterator (FilterPlan const * const plan) :
	_plan (plan), _input (plan->_input->init ()),
	_consumed (0), _produced (0)
{
	TRACE (TRACE_OUT);
} // FilterIterator::FilterIterator

FilterIterator::~FilterIterator ()
{
	TRACE (TRACE_OUT);

	delete _input;

	traceprintf ("produced %lu of %lu rows\n",
			(unsigned long) (_produced),
			(unsigned long) (_consumed));
} // FilterIterator::~FilterIterator

bool FilterIterator::next ()
{
	TRACE (TRACE_OUT);

	do
	{
		if ( ! _input->next ())  return false;
		++ _consumed;
	} while (_consumed % 2 == 0);

	++ _produced;
	return true;
} // FilterIterator::next
