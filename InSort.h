#include "Iterator.h"
#include "common.h"
#include "Queue.h"

class InSortPlan : public Plan
{
	friend class InSortIterator;
public:
	InSortPlan (Plan * const input);
	~InSortPlan ();
	Iterator * init ();
private:
	Plan * const _input;
}; // class InSortPlan

class InSortIterator : public Iterator
{
public:
	InSortIterator (InSortPlan const * const plan);
	~InSortIterator ();
	bool next ();
	char* get();
	void resetFanInList();
	int getNumOfFiles();
private:
	InSortPlan const * const _plan;
	Iterator * const _input;
	RowCount _consumed, _produced;
	ReadStream _rs;
	int _ws_ctr;
	vector<Queue *> _fanInList;
	size_t _numFetchedRow;
	void dump();

}; // class InSortIterator
