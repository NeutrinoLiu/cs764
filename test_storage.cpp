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
    {
        ReadStream reader("1", false);
        for (size_t i = 0; i < num; i++) {
            reader.read(record.get(), record_sz);
            for (size_t j = 0; j < record_sz / sizeof(uint64_t); j++)
                assert(*((uint64_t *)record.get() + j) == i * j);
        }
    }
}