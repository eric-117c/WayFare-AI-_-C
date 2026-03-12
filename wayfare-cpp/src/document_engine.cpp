#include <fstream>
#include <thread>
#include <vector>
#include <iostream>
#include "picosha2.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;


class DocumentEngine {
public:
    // 计算文档哈希 (符合 docHash 要求)
    std::string calculate_hash(const std::string& path) {
        std::ifstream f(path, std::ios::binary);
        if (!f) return "";
        std::vector<unsigned char> hash(32);
        picosha2::hash256(f, hash.begin(), hash.end());
        return picosha2::bytes_to_hex_string(hash.begin(), hash.end());
    }

    // 模拟异步解析
    void async_parse(const std::string& path, const std::string& docHash) {
        std::thread([this, path, docHash]() {
            // 1. 模拟处理耗时
            std::this_thread::sleep_for(std::chrono::seconds(3));
            
            // 2. 构造通知消息 (Notification)
            json notify = {
                {"type", "notification"},
                {"data", {
                    {"type", "parse_completed"},
                    {"docHash", docHash},
                    {"status", "completed"},
                    {"segmentCount", 100} // 模拟数据
                }}
            };
            
            // 3. 直接输出到 stdout
            std::cout << notify.dump() << std::endl;
        }).detach();
    }
};