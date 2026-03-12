#!/bin/bash

# --- 1. 路径配置 ---
# 获取脚本所在目录的上一级，确保在任何地方运行都能找到二进制文件
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BINARY="$PROJECT_ROOT/build/wayfare_sidecar"
LOG_FILE="$PROJECT_ROOT/backend_errors.log"

# 检查二进制文件是否存在
if [ ! -f "$BINARY" ]; then
    echo "错误: 找不到二进制文件 $BINARY，请先在 build 目录编译项目。" >&2
    exit 1
fi

# --- 2. 资源隔离 (体现“谨慎权限”原则) ---
# 限制虚拟内存为 512MB (防止处理超大 PDF 或内存泄漏耗尽系统资源)
ulimit -v 524288

# 限制 CPU 时间为 300 秒 (防止算法死循环或恶意逻辑占用过高 CPU)
ulimit -t 300

# 限制单个文件写入大小为 50MB (防止日志文件无限增长撑爆磁盘)
ulimit -f 51200

# 限制最大进程数/子线程数 (防止 fork 炸弹)
ulimit -u 50

# --- 3. 启动进程 ---
# 使用 stdbuf -oL 强制开启行缓冲 (Line Buffering)
# 这样 C++ 打印的每一行 JSON 响应都能立刻被前端感知，不会积压在缓冲区
# 2> 将错误信息重定向到日志文件，确保 stdout 只有纯净的 JSON 数据流

echo "[Host] 正在以隔离模式启动 WayFare AI 后端..." >&2

stdbuf -oL -eL "$BINARY" 2> "$LOG_FILE"