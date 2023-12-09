#include <cassert>

#include "storage.hpp"
int main() {
    StorageConfig::base_dir = "test/";
    size_t record_sz = 1000, num = 10000;
    auto record = std::make_unique<uint8_t[]>(record_sz);
    {
        WriteStream writer("1");
        for (size_t i = 0; i < num; i++) {
            for (size_t j = 0; j < record_sz / sizeof(uint64_t); j++)
                *((uint64_t *)record.get() + j) = i * j;
            writer.write(record.get(), record_sz);
        }
    }
    for (size_t bCache = 0; bCache < 2; bCache++) {
        {
            ReadStream reader("1", bCache);
            for (size_t i = 0; i < num; i++) {
                reader.read(record.get(), record_sz);
                for (size_t j = 0; j < record_sz / sizeof(uint64_t); j++)
                    assert(*((uint64_t *)record.get() + j) == i * j);
            }
            assert(reader.read(nullptr, UINT32_MAX) == 0);
        }
        {
            auto records = std::make_unique<uint8_t[]>(record_sz * num);
            ReadStream reader("1", bCache);
            auto ret = reader.read(records.get(), UINT32_MAX);
            assert(ret == record_sz * num);
            for (size_t i = 0; i < num; i++) {
                for (size_t j = 0; j < record_sz / sizeof(uint64_t); j++)
                    assert(*((uint64_t *)(records.get() + i * record_sz) + j) == i * j);
            }
        }
    }
}