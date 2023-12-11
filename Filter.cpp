#include "Filter.h"
#include "common.h"
#include <cstring>
#include <memory>

FilterPlan::FilterPlan (Plan * const input) : _input (input)
{
	TRACE (true);
} // FilterPlan::FilterPlan

FilterPlan::~FilterPlan ()
{
	TRACE (true);
	delete _input;
} // FilterPlan::~FilterPlan

Iterator * FilterPlan::init ()
{
	TRACE (true);
	return new FilterIterator (this);
} // FilterPlan::init

FilterIterator::FilterIterator (FilterPlan const * const plan) :
	_plan (plan), _input (plan->_input->init ()),
	_consumed (0), _produced (0),
	_rs(genFileName(0, FILE_PREFIX_MERGE_SORTED), false), // FILE_PREFIX_INNER_SORTED
	_verifyOrder(false)
{
	TRACE (true);
	_row = new char[Row::size];

	while (_input->next ())  ++ _consumed;
	delete _input;

	traceprintf ("consumed %lu rows\n",
			(unsigned long) (_consumed));
} // FilterIterator::FilterIterator

FilterIterator::~FilterIterator ()
{
	TRACE (true);

	delete[] _row;

	traceprintf ("produced %lu of %lu rows\n",
			(unsigned long) (_produced),
			(unsigned long) (_consumed));
} // FilterIterator::~FilterIterator

bool FilterIterator::next ()
{
	TRACE (false);
	auto prev = std::make_unique<char[]>(Row::size);
	memcpy(prev.get(),_row, Row::size);
	

	if(_rs.read(_row, Row::size) != Row::size) return false;
	Row row(_row);
	row_hash_t h =row.hash();
	row.genHash();
	if(h!= row.hash())
		puts("hash mismatch!");	

	if(_verifyOrder){
		if(Row::compare(prev.get(), _row) > 0)
			puts("incorrect order!");
	}
	_verifyOrder = true;

	++ _produced;
	return true;
} // FilterIterator::next

char* FilterIterator::get() {
	return _row;
}