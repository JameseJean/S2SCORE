// ===========================
// 文件：cpu.cpp
// 功能：实现 CPU 类的构造、step 执行、各阶段函数（占位）
// ===========================

#include "cpu.h"
#include <iostream>

// 构造函数：初始化寄存器和 PC
CPU::CPU(Memory* mem) : memory(mem), pc(0), halted(false) {
    for (int i = 0; i < 32; ++i) regs[i] = 0;
    if_id_inst = 0;
}

// 判断是否停止运行
bool CPU::is_halted() const {
    return halted;
}

// 执行一个流水线周期
void CPU::step() {
    write_back();
    memory_access();
    execute();
    decode();
    fetch();
}

// IF 阶段：从内存中取出当前 PC 指向的指令
void CPU::fetch() {
    if_id_inst = memory->read_word(pc);
    std::cout << "[IF] PC: 0x" << std::hex << pc << " 指令: 0x" << if_id_inst << std::dec << std::endl;
    pc += 4; // 默认顺序执行，后续加入分支预测等改动 PC
}

// ID 阶段：简单解析指令字段（仅支持 R、I 型指令的部分字段）
void CPU::decode() {
    uint32_t inst = if_id_inst;
    uint32_t opcode = inst & 0x7F;
    uint32_t rd     = (inst >> 7) & 0x1F;
    uint32_t funct3 = (inst >> 12) & 0x7;
    uint32_t rs1    = (inst >> 15) & 0x1F;
    uint32_t rs2    = (inst >> 20) & 0x1F;
    uint32_t funct7 = (inst >> 25) & 0x7F;

    std::cout << "[ID] opcode: " << opcode << " rd: x" << rd
              << " rs1: x" << rs1 << " rs2: x" << rs2 << " funct3: " << funct3 << " funct7: " << funct7 << std::endl;

    // TODO: 记录 decode 信息，传递到 execute 阶段
}

void CPU::execute() {
    // TODO: 执行 ALU 运算
}

void CPU::memory_access() {
    // TODO: 执行 load/store 操作
}

void CPU::write_back() {
    // TODO: 将结果写回寄存器堆
}