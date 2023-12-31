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
	_rs(genFileName(0, FILE_PREFIX_RAW), false),
	_ws_ctr(0), _numFetchedRow(0)  
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
	TRACE (false);
	if(_numFetchedRow > 0){
		_numFetchedRow--; 
		_produced++;
		return true;
	}

	char _buff[CACHE_SIZE], *buff = _buff;
	int ret = _rs.read(buff, CACHE_SIZE/Row::size * Row::size);
	_numFetchedRow = ret / Row::size;
	if(_numFetchedRow == 0) {
		if(!_fanInList.empty()) dump();
		return false;	
	}else {
		qsort(buff, _numFetchedRow, Row::size, Row::compare);
		_fanInList.push_back(
			new MemQueue(buff, _numFetchedRow)
		);
	}

	if (_fanInList.size() == MEM_SIZE / CACHE_SIZE -1)  // memory is full 
		dump();

	_numFetchedRow--; 
	_produced++;
	return true;
} // InSortIterator::next

void InSortIterator::dump(){
	TournamentTreePlan* tt = new TournamentTreePlan(_fanInList);
	Iterator* iter = tt->init();
	WriteStream _ws(genFileName(_ws_ctr++, FILE_PREFIX_INNER_SORTED));
	while (iter->next()) {
		auto p = iter->get();
		_ws.write(p, Row::size);
	}
	resetFanInList();
	delete iter;
	delete tt;	
}

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