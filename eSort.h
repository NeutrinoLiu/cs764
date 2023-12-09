#include "Iterator.h"
#include "common.h"
#include "Queue.h"

class eSortPlan : public Plan
{
	friend class eSortIterator;
public:
	eSortPlan (Plan * const input);
	~eSortPlan ();
	Iterator * init () const;
private:
	Plan * const _input;
}; // class eSortPlan

class eSortIterator : public Iterator
{
public:
	eSortIterator (eSortPlan const * const plan);
	~eSortIterator ();
	bool next ();
private:
	eSortPlan const * const _plan;
	Iterator * const _input;
	RowCount _consumed, _produced;
	WriteStream _ws;
	vector<Queue *> _fanInList;
	TournamentTree _tt;
}; // class eSortIterator
