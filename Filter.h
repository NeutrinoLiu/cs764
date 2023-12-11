#include "Iterator.h"
#include "storage.hpp"

class FilterPlan : public Plan
{
	friend class FilterIterator;
public:
	FilterPlan (Plan * const input);
	~FilterPlan ();
	Iterator * init ();
private:
	Plan * const _input;
}; // class FilterPlan

class FilterIterator : public Iterator
{
public:
	FilterIterator (FilterPlan const * const plan);
	~FilterIterator ();
	bool next ();
	char* get();
private:
	FilterPlan const * const _plan;
	Iterator * const _input;
	RowCount _consumed, _produced;
	ReadStream _rs;
	char * _row;
	bool _verifyOrder;
}; // class FilterIterator
