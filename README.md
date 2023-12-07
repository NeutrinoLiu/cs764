# External Merge Sort Project

## Starter Code Walk

```
├── Assert.cpp		# assert macro
├── Filter.cpp		# Filter plan&iterator
├── Filter.h
├── Iterator.cpp	# base plan&iterator
├── Iterator.h
├── Makefile		# Makefile
├── Scan.cpp		# scan plan&iterator
├── Scan.h
├── Sort.cpp		# sort plan&iterator
├── Sort.h
├── Tasks.txt		# TODOs
├── Test.cpp		# entry point
├── defs.cpp		# macros and utils for logging
└── defs.h
```

## Tasks.txt

- Trace existing code
- Disable (not remove!) excessive tracing output
- Define class for data records
- Add data records class def (incl mem mgmt) to iterators	// Bangya
- Add data generation (random values) in ScanIterator // Yiwei
- Test with simple table class -- scan only
- Add predicate evaluation to verifyIterator
- Test with moderate table -- scan & verify
- Add in-memory sorting -- eg 10, 100, 1000 rows
- Test with moderate table -- scan & sort
- Add table & Iterator that verify a sort order
- Test with 0 rows and with 1 row, also 2, 3, 7 rows
- Add table & Iterator that verify a set of rows
- Test with 0, 1, 2, 3, 10, 29, 100, 576, 1000 rows

## Additional Notes

- Plan: some actions that need to be completed (no need to change ScanPlan and Plan)
- Latency is only used to suggest how to utilize devices efficiently (no need to emulate somehow) eg. 10ms latency -> 100 requests / second
- Merge cache-size mini-runs into memory-size runs, then merge memory-size runs into disk-size run (with latency & bandwidth in mind, a.k.a. device-optimized page sizes)
    - The tournament tree should be fit in the cache
- Prioritized Techniques
    - 2+5
    - 10
    - 9+15 (eg. how to evenly divide input into similar size runs w.r.t. value distribution)
    - other with grade
    - `?` (optional)
- `-s 1000`: 333+333+334
- ScanPlan should write to HDD file first
- Filter not graded (just for understanding codebase)