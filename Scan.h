#include "Iterator.h"
#include "storage.hpp"
#include "common.h"

class ScanPlan : public Plan
{
	friend class ScanIterator;
public:
	ScanPlan (RowCount const count);
	~ScanPlan ();
	Iterator * init () const;
private:
	RowCount const _count;
	std::vector<WriteStream *> _files;
}; // class ScanPlan

class ScanIterator : public Iterator
{
public:
	ScanIterator (ScanPlan const * const plan);
	~ScanIterator ();
	bool next ();
private:
	ScanPlan const * const _plan;
	RowCount _count;
}; // class ScanIterator
