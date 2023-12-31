#include<cstdint>
// static std::vector<int> ROW_STRUCTURE = {15,15,15,5};

const char FILE_PREFIX_RAW[] = "RAW";
const char FILE_PREFIX_INNER_SORTED[] = "QSORTED";
const char FILE_PREFIX_MERGE_SORTED[] = "MERGED";
const int CACHE_SIZE = 1 << 20;
const int MEM_SIZE = 100 * 1 << 20;

typedef uint32_t row_hash_t;
constexpr static uint64_t HASH_SIZE = sizeof(row_hash_t);