# WayFare-AI-_-C
这是WayFare AI 成员C的代码仓库

- 文件结构
wayfare-cpp/
├── src/
│   ├── main.cpp                # 进程入口，管理生命周期
│   ├── ipc_handler.hpp         # JSON-RPC 解析与 stdout/stdin 交互
│   ├── document_engine.cpp     # 文档哈希与解析逻辑调度
│   ├── sandbox_control.hpp     # 系统权限与资源限制 (Linux Seccomp/rlimit)
│   └── models.hpp              # 定义 API 对应的数据结构
├── include/                    # 存放第三方库头文件 (nlohmann/json 等)
├── CMakeLists.txt              # 跨平台构建脚本
└── scripts/
    └── run_isolated.sh         # 启动受限进程的脚本