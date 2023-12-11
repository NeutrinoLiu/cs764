#include "common.h"
#include "Iterator.h"
#include "Scan.h"
#include "Filter.h"
#include "InSort.h"
#include "eSort.h"

int main (int argc, char * argv [])
{
	// StorageConfig::base_dir = "test/";
	TRACE (true);
	initRandSeed();
	
	Plan * const plan = 
	new eSortPlan( new InSortPlan( new ScanPlan (7)));

	Iterator * const it = plan->init ();
	it->run ();
	delete it;

	delete plan;

	return 0;
} // main
