#include "Iterator.h"
#include "Scan.h"
#include "Filter.h"
#include "Sort.h"
#include <iostream>

void print_scaniter(Iterator* const n, int size) {
	for (int i = 0; i < 7; i++) {
		printf("%lu, %lu, %lu, %lu\n", it->table.at(i)->getId(), it->table.at(i)->col1, it->table.at(i)->col2, it->hashes.at(i));
	}
}

int main (int argc, char * argv [])
{
	// TRACE (true);

	Plan * const plan = new ScanPlan (7);
	// new SortPlan ( new FilterPlan ( new ScanPlan (7) ) );

	Iterator * const it = plan->init ();
	it->run ();
	print_scaniter(it, 7)
	delete it;

	delete plan;

	return 0;
} // main
