#include "Filter.h"
#include "InSort.h"
#include "Iterator.h"
#include "Scan.h"
#include "common.h"
#include "eSort.h"

void test(int record_size, size_t record_num) {
    TRACE(true);
    Row::size = record_size;
    int col_sz = (record_size - HASH_SIZE) / 3;
    Row::COLWIDTH = {col_sz, col_sz, col_sz, record_size - 3 * col_sz};

    Plan* const plan =
        new eSortPlan(new InSortPlan(new ScanPlan(record_num)));

    Iterator* const it = plan->init();
    it->run();
    delete it;

    delete plan;
    StorageStat::print();
}

int main(int argc, char* argv[]) {
    // initRandSeed();
    test(64, 3);
}  // main
