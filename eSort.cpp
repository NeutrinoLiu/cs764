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

Iterator * eSortPlan::init () const
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
		_fanInList.emplace_back(
			genFileName(i, FILE_PREFIX_INNER_SORTED)
		);
	}
	_tt = TournamentTree(_fanInList);

	traceprintf ("consumed %lu rows\n",
			(unsigned long) (_consumed));
} // eSortIterator::eSortIterator

eSortIterator::~eSortIterator ()
{
	TRACE (true);

	_fanInList.clear(); // actually you dont need to
	
	traceprintf ("produced %lu of %lu rows\n",
			(unsigned long) (_produced),
			(unsigned long) (_consumed));
} // eSortIterator::~eSortIterator

bool eSortIterator::next ()
{
	TRACE (true);

	if (tt.next()) {
		_ws.write(tt.get(), Row::size);
		++ _produced;
		return true;
	} else {
		return false;
	}
} // eSortIterator::next
