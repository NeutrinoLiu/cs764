#include "eSort.h"
#include "InSort.h"

eSortPlan::eSortPlan (Plan * const input) : _input (input)
{
	TRACE (true);
} // eSortPlan::eSortPlan

eSortPlan::~eSortPlan ()
{
	TRACE (true);
	delete _input;
} // eSortPlan::~eSortPlan

Iterator * eSortPlan::init () 
{
	TRACE (true);
	return new eSortIterator (this);
} // eSortPlan::init

eSortIterator::eSortIterator (eSortPlan const * const plan) :
	_plan (plan), _input (plan->_input->init ()),
	_consumed (0), _produced (0),
	_ws(genFileName(0, FILE_PREFIX_MERGE_SORTED))
{
	TRACE (true);

	while (_input->next ())  ++ _consumed;
	int numOfReadStream = /* since a esort usually follows a insort*/
		dynamic_cast<InSortIterator *>(_input)->getNumOfFiles();
	delete _input;

	for (int i=0; i < numOfReadStream; i++) {
		_fanInList.push_back(
			new DiskQueue(genFileName(i, FILE_PREFIX_INNER_SORTED)) 
		);
	}
	TournamentTreePlan* tt = new TournamentTreePlan(_fanInList);
	_iter = tt->init();

	traceprintf ("consumed %lu rows\n",
			(unsigned long) (_consumed));
} // eSortIterator::eSortIterator

eSortIterator::~eSortIterator ()
{
	TRACE (true);

	for (auto i = _fanInList.begin(); i != _fanInList.end(); i++) {
		delete *i;
	}
	_fanInList.clear();
	
	traceprintf ("produced %lu of %lu rows\n",
			(unsigned long) (_produced),
			(unsigned long) (_consumed));
} // eSortIterator::~eSortIterator

bool eSortIterator::next ()
{
	TRACE (true);

	if (_iter->next()) {
		_ws.write(_iter->get(), Row::size);
		++ _produced;
		return true;
	} else {
		return false;
	}
} // eSortIterator::next

char* eSortIterator::get() {
	return (char*) NULL;
}