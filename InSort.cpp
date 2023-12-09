#include "InSort.h"
#include "Tournament.h"

InSortPlan::InSortPlan (Plan * const input) : _input (input)
{
	TRACE (true);
} // InSortPlan::InSortPlan

InSortPlan::~InSortPlan ()
{
	TRACE (true);
	delete _input;
} // InSortPlan::~InSortPlan

Iterator * InSortPlan::init () 
{
	TRACE (true);
	return new InSortIterator (this);
} // InSortPlan::init

InSortIterator::InSortIterator (InSortPlan const * const plan) :
	_plan (plan), _input (plan->_input->init ()),
	_consumed (0), _produced (0),
	_rs(genFileName(0, FILE_PREFIX_RAW)),
	_ws(NULL), _ws_ctr(0)  
{
	TRACE (true);

	while (_input->next ())  ++ _consumed;
	delete _input;

	traceprintf ("consumed %lu rows\n",
			(unsigned long) (_consumed));
} // InSortIterator::InSortIterator

InSortIterator::~InSortIterator ()
{
	TRACE (true);

	traceprintf ("produced %lu of %lu rows\n",
			(unsigned long) (_produced),
			(unsigned long) (_consumed));
} // InSortIterator::~InSortIterator

/* each time read a cache line size 
	instead of a single row size */
bool InSortIterator::next () 
{
	TRACE (true);
	char buff[CACHE_SIZE] = {'\0'};
	int ret = _rs.read(buff, CACHE_SIZE / Row::size * Row::size);
	int numFetchedRow = ret / Row::size;
	_produced += numFetchedRow;
	
	if (numFetchedRow) {
		qsort(buff, numFetchedRow, Row::size, Row::compare);
		_fanInList.push_back(
			new MemQueue(buff, numFetchedRow)
		);
	}

	if (_fanInList.size() == MEM_SIZE / CACHE_SIZE -1) { // memory is full
		TournamentTreePlan* tt = new TournamentTreePlan(_fanInList);
		Iterator* iter = tt->init();
		_ws = new WriteStream(genFileName(_ws_ctr++, FILE_PREFIX_INNER_SORTED));
		while (iter->next()) {
			_ws->write(iter->get(), Row::size);
		}
		resetFanInList();
	} else if (numFetchedRow < CACHE_SIZE / Row::size) { // data is exhausted
		_ws = new WriteStream(genFileName(_ws_ctr++, FILE_PREFIX_INNER_SORTED));
		TournamentTreePlan* tt = new TournamentTreePlan(_fanInList);
		Iterator* iter = tt->init();
		while (iter->next()) {
			_ws->write(iter->get(), Row::size);
		}
		resetFanInList();
		return false;
	}

	return true;
} // InSortIterator::next

void InSortIterator::resetFanInList() 
{
	for (auto i = _fanInList.begin(); i != _fanInList.end(); i++) {
		delete *i;
	}
	_fanInList.clear();
}

int InSortIterator::getNumOfFiles() {
	return _ws_ctr;
}

char* InSortIterator::get() {
	return (char*) NULL;
}