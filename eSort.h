#include "Iterator.h"
#include "common.h"
#include "Queue.h"
#include "Tournament.h"

class eSortPlan : public Plan
{
	friend class eSortIterator;
public:
	eSortPlan (Plan * const input);
	~eSortPlan ();
	Iterator * init () ;
private:
	Plan * const _input;
}; // class eSortPlan

class eSortIterator : public Iterator
{
public:
	eSortIterator (eSortPlan const * const plan);
	~eSortIterator ();
	bool next ();
	char* get();
private:
	eSortPlan const * const _plan;
	Iterator * const _input;
	RowCount _consumed, _produced;
	WriteStream _ws;
	vector<Queue *> _fanInList;
	TournamentTreePlan* _tt;
	Iterator* _iter;
}; // class eSortIterator
