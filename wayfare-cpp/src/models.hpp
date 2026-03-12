#ifndef MODELS_HPP
#define MODELS_HPP

#include "nlohmann/json.hpp"
#include <string>

using json = nlohmann::json;

struct IPCRequest {
    std::string id;
    int seq;
    std::string method;
    json params;
};

// JSON 转换逻辑
inline void from_json(const json& j, IPCRequest& r) {
    j.at("id").get_to(r.id);
    j.at("seq").get_to(r.seq);
    j.at("method").get_to(r.method);
    if (j.contains("params")) r.params = j.at("params");
}

#endif