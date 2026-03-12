#!/bin/bash
# 赋予执行权限：chmod +x run_isolated.sh

# 限制内存 512MB
ulimit -v 524288

# 启动程序并将错误重定向到 stderr (不污染 stdout 的 JSON)
# stdbuf -oL 确保行缓冲，前端能即时接收数据
stdbuf -oL ./build/wayfare_sidecar 2> error.log