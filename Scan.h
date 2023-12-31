#include "Iterator.h"
#include "common.h"

class ScanPlan : public Plan
{
	friend class ScanIterator;
public:
	ScanPlan (RowCount const count);
	~ScanPlan ();
	Iterator * init ();
private:
	RowCount const _count;
}; // class ScanPlan

class ScanIterator : public Iterator
{
public:
	ScanIterator (ScanPlan const * const plan);
	~ScanIterator ();
	bool next ();
	char* get();
private:
	ScanPlan const * const _plan;
	RowCount _count;
	WriteStream _ws;
}; // class ScanIterator
