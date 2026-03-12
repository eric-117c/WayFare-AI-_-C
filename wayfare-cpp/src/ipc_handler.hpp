#ifndef IPC_HANDLER_HPP
#define IPC_HANDLER_HPP

#include <iostream>
#include "models.hpp"
#include "document_engine.cpp"

class IPCHandler {
    DocumentEngine engine;
public:
    void run_loop() {
        std::string line;
        while (std::getline(std::cin, line)) {
            if (line.empty()) continue;
            try {
                auto req_json = json::parse(line);
                IPCRequest req = req_json;
                handle_method(req);
            } catch (std::exception& e) {
                send_error("null", 0, e.what());
            }
        }
    }

private:
    void handle_method(const IPCRequest& req) {
        if (req.method == "parse") {
            std::string path = req.params.value("path", "");
            std::string hash = engine.calculate_hash(path);
            
            if (hash.empty()) {
                send_error(req.id, req.seq, "File not found");
                return;
            }

            engine.async_parse(path, hash);
            send_response(req.id, req.seq, {{"docHash", hash}, {"status", "processing"}});
        } 
        else if (req.method == "config") {
            send_response(req.id, req.seq, {{"updated", true}});
        }
        else {
            send_error(req.id, req.seq, "Method not supported");
        }
    }

    void send_response(const std::string& id, int seq, const json& data) {
        json resp = {{"id", id}, {"seq", seq}, {"success", true}, {"data", data}};
        std::cout << resp.dump() << std::endl;
    }

    void send_error(const std::string& id, int seq, const std::string& err) {
        json resp = {{"id", id}, {"seq", seq}, {"success", false}, {"error", err}};
        std::cout << resp.dump() << std::endl;
    }
};

#endif