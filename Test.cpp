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
        new FilterPlan(new eSortPlan(new InSortPlan(new ScanPlan(record_num))));

    Iterator* const it = plan->init();
    it->run();
    delete it;

    delete plan;
    StorageStat::print();
}

int main(int argc, char* argv[]) {
    initRandSeed();
    puts("\n\nTest 1M x 50B\n");
    test(50, 1 << 20);
    puts("\n\nTest 2.5M x 50B\n");
    test(50, (2048 + 512) << 10);
    puts("\n\nTest 12M x 1KB\n");
    test(1024, 12 << 20);
    puts("\n\nTest 120M x 1KB\n");
    test(1024, 120 << 20);
}  // main
