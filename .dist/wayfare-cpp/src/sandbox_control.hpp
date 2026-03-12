#ifndef SANDBOX_CONTROL_HPP
#define SANDBOX_CONTROL_HPP

#ifndef _WIN32
#include <sys/resource.h>
#endif
#include <iostream>

class Sandbox {
public:
    static void apply_limits() {
#ifndef _WIN32
        struct rlimit limit;
        // 限制虚拟内存为 512MB
        limit.rlim_cur = 512 * 1024 * 1024;
        limit.rlim_max = 512 * 1024 * 1024;
        setrlimit(RLIMIT_AS, &limit);

        // 限制 CPU 时间为 300 秒
        limit.rlim_cur = 300;
        limit.rlim_max = 300;
        setrlimit(RLIMIT_CPU, &limit);
        
        std::cerr << "[Sandbox] Linux resource limits applied." << std::endl;
#else
        std::cerr << "[Sandbox] Windows environment, skipping rlimit." << std::endl;
#endif
    }
};

#endif