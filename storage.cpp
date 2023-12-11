#include "storage.hpp"

#include <algorithm>
#include <cassert>
#include <cstring>

Storage::Storage(std::string file_name, mode_t _mode, dev_type_t _dev_type) : mode(_mode), dev_type(_dev_type) {
    std::string dev_str = dev_type == HDD ? StorageConfig::hdd_dir : StorageConfig::ssd_dir;
    std::string path = StorageConfig::base_dir + dev_str + file_name;
    file = fopen(path.c_str(), mode == READ ? "rb" : "wb");
    if (file == nullptr) 
        perror("Error opening file");
}

Storage::~Storage() {
    if (file) fclose(file);
}

size_t Storage::access(void* buf, size_t sz) {
    // TODO: print access trace/statistics
    if (file == nullptr) return 0;
    if (mode == READ) {
        return fread(buf, sizeof(uint8_t), sz, file);
    } else {
        return fwrite(buf, sizeof(uint8_t), sz, file);
    }
}

size_t Storage::get_size(){
    auto current =  ftell(file);
    fseek(file, 0, SEEK_END);
    auto ret = ftell(file);
    fseek(file, current, SEEK_SET);
    return ret;
}

WriteStream::WriteStream(std::string file_name) : offset(0), buffer_size(StorageConfig::kHDDBlkSz) {
    buffer = std::make_unique<uint8_t[]>(buffer_size);
    hdd = std::make_unique<Storage>(file_name, Storage::WRITE);
}

void WriteStream::write(void* _buf, size_t size) {
    auto buf = (uint8_t*)_buf;
    while (true) {
        auto _off = offset % buffer_size;
        if (_off + size < buffer_size) {
            memcpy(buffer.get() + _off, buf, size);
            offset += size;
            break;
        } else {
            auto len = buffer_size - _off;
            memcpy(buffer.get() + _off, buf, len);
            buf += len;
            offset += len;
            size -= len;
            hdd->access(buffer.get(), buffer_size);  // TODO: error handling
        }
    }
}

WriteStream::~WriteStream() {
    auto _off = offset % buffer_size;
    if (_off) hdd->access(buffer.get(), _off);  // flush the buffer
}

ReadStream::ReadStream(std::string _file_name, bool enable_cache) : offset(0), file_name(_file_name), bCache(enable_cache) {
    buffer_size = enable_cache ? StorageConfig::kSSDBlkSz : StorageConfig::kHDDBlkSz;    
    hdd = std::make_unique<Storage>(file_name, Storage::READ);
}

size_t ReadStream::read(void* _buf, size_t size) {
    if(buffer == nullptr){
        buffer = std::make_unique<uint8_t[]>(buffer_size);
        load_buf();
    }
    size = std::min(hdd->get_size() - offset, size);
    auto ret = size;
    auto buf = (uint8_t*)_buf;
    while (true) {
        auto _off = offset % buffer_size;
        if (_off + size < buffer_size) {
            memcpy(buf, buffer.get() + _off, size);
            offset += size;
            return ret;
        } else {
            auto len = buffer_size - _off;
            memcpy(buf, buffer.get() + _off, len);
            buf += len;
            offset += len;
            size -= len;

            load_buf();
        }
    }
}

void ReadStream::load_buf() {
    if (!bCache) {
        hdd->access(buffer.get(), buffer_size);
        return;
    }

    assert(offset % buffer_size == 0);
    if (offset % StorageConfig::kHDDBlkSz == 0) {
        auto cp_buf = std::make_unique<uint8_t[]>(StorageConfig::kHDDBlkSz);
        auto file_sz = hdd->access(cp_buf.get(), StorageConfig::kHDDBlkSz);

        ssd = std::make_unique<Storage>(file_name, Storage::WRITE, Storage::SSD);
        ssd->access(cp_buf.get(), file_sz);
        ssd = std::make_unique<Storage>(file_name, Storage::READ, Storage::SSD);
    }

    ssd->access(buffer.get(), buffer_size);
}