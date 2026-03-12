#include "ipc_handler.hpp"
#include "sandbox_control.hpp"

int main() {
    // 1. 应用资源限制
    Sandbox::apply_limits();

    // 2. 启动消息循环
    IPCHandler handler;
    handler.run_loop();

    return 0;
}