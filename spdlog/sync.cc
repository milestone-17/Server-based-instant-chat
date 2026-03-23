#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/fmt.h>

int main() {
    // 定义日志器名称
    const char* logger_name = "console_logger";
    
    // 创建同步彩色控制台日志器
    auto logger = spdlog::stdout_color_mt(logger_name);
    
    // 设置日志输出格式
    logger->set_pattern("[%H:%M:%S][%t][%-7l - %v]");///%v 日志实际输出内容
    
    // 不同等级的日志输出
    logger->debug(fmt::format("你好,{}", "milestone"));
    logger->trace(fmt::format("你好,{}", "milestone"));
    logger->info(fmt::format("你好,{}", "milestone"));
    logger->error(fmt::format("你好,{}", "milestone"));
    
    std::cout << "日志输出完毕" << std::endl;
    return 0;
}