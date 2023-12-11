#pragma once
#include <cstdint>
#include <cstdio>
#include <memory>
#include <string>

struct StorageConfig {
    constexpr static size_t kSSDBlkSz = 8 << 10;
    constexpr static size_t kHDDBlkSz = 2 << 20;
    inline static std::string base_dir = "./";
    inline static std::string ssd_dir = "ssd/";
    inline static std::string hdd_dir = "hdd/";
};

class Storage {
   public:
    enum mode_t {
        READ,
        WRITE
    };
    enum dev_type_t {
        HDD,
        SSD
    };
    Storage(std::string file_name, mode_t _mode, dev_type_t _dev_type = HDD);
    ~Storage();
    size_t access(void* buf, size_t sz);
    size_t get_size();

   protected:
    FILE* file;
    mode_t mode;
    dev_type_t dev_type;
 };

class WriteStream {
   protected:
    std::unique_ptr<Storage> hdd;
    std::unique_ptr<uint8_t[]> buffer;
    size_t offset, buffer_size;

   public:
    WriteStream(std::string file_name);
    ~WriteStream();
    void write(void* buf, size_t size);
};

class ReadStream {
   protected:
    std::unique_ptr<Storage> hdd, ssd;
    std::unique_ptr<uint8_t[]> buffer;
    size_t offset, buffer_size;
    std::string file_name;
    bool bCache;
    void load_buf();

   public:
    ReadStream(std::string file_name, bool enable_cache = true);
    size_t read(void* buf, size_t size);
};