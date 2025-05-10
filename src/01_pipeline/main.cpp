// ===========================
// 文件：main.cpp
// 功能：程序入口，加载 test.hex，初始化 CPU，运行模拟主循环。
//1加载测试程序（如 programs/test.hex）到模拟内存中；
//2初始化内存与 CPU；
//3启动主执行循环，每次调用 CPU 的 step() 方法模拟一个周期的流水线推进；
//4结束后打印提示。
// ===========================

#include <iostream>
#include <fstream>
#include <vector>
#include "cpu.h"
#include "memory.h"

using namespace std;

int main(int argc, char** argv) {
    // 加载指令文件（默认为 programs/test.hex）
    string program_path = "../programs/test.hex";
    if (argc > 1) {
        program_path = argv[1];
    }

    // 创建内存对象，初始化内存大小为 4KB
    Memory memory(4096);

    // 打开指令文件
    ifstream infile(program_path);
    if (!infile.is_open()) {
        cerr << "无法打开程序文件: " << program_path << endl;
        return 1;
    }

    // 将十六进制指令加载到内存（假设每行是 32bit 一条）
    string line;
    uint32_t addr = 0;
    while (getline(infile, line)) {
        uint32_t inst = stoul(line, nullptr, 16);
        memory.write_word(addr, inst);
        addr += 4; // 一条指令 4 字节
    }
    infile.close();

    // 初始化 CPU 并加载内存
    CPU cpu(&memory);

    // 执行循环（后续支持单步执行）
    while (!cpu.is_halted()) {
        cpu.step(); // 执行一个周期（流水线推进）
    }

    cpu.dump_registers();      // ✅ 打印寄存器
    cpu.dump_memory(0, 64);    // ✅ 打印前 64 字节内存

    cout << "模拟器运行结束。" << endl;
    return 0;
}