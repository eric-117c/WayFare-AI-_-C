# WayFare-AI-_-C
这是WayFare AI 成员C的代码仓库

- 文件结构
wayfare-py/
├── core/                   # C++ 底层核心 (高性能/安全)
│   ├── sandbox/            # C++ 编写的受限执行沙箱 (Linux Namespaces/Seccomp)
│   ├── vector_engine/      # C++ 绑定的向量计算优化 (如调用 ONNX Runtime)
│   └── CMakeLists.txt      # 构建脚本
├── wayfare_ai/             # Python 业务逻辑层 (主要的 Sidecar 实现)
│   ├── ipc.py              # 【核心】处理 stdin/stdout 的 JSON-RPC 调度器
│   ├── document_parser.py  # 文档解析、BLAKE3 哈希生成、切块逻辑
│   ├── annotation_gen.py   # 对接 LLM (DeepSeek) 的批注生成逻辑
│   ├── db.py               # ChromaDB (向量) 与本地 SQLite (关系型) 管理
│   └── config.py           # 动态配置加载 (API Keys, 阈值)
├── scripts/                # 自动化脚本
│   └── setup_env.sh        # 环境隔离与依赖安装脚本
├── main.py                 # 程序的入口点 (由成员 A 的程序拉起)
└── requirements.txt        # Python 依赖清单