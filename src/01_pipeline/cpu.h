
// ===========================
// 文件：cpu.h
// 功能：声明 CPU 类，包括寄存器、PC、流水线阶段和控制函数
// ===========================

#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include "memory.h"

class CPU {
public:
    CPU(Memory* mem);
    void step();               // 执行一个时钟周期
    bool is_halted() const;    // 模拟器是否停止运行

    void dump_registers() const;     // ✅ 打印寄存器
    void dump_memory(uint32_t start, uint32_t size) const; // ✅ 打印内存段

private:
    void fetch();              // IF 阶段：取指
    void decode();             // ID 阶段：译码
    void execute();            // EX 阶段：执行
    void memory_access();      // MEM 阶段：访问内存
    void write_back();         // WB 阶段：写回寄存器

    uint32_t pc;               // 程序计数器
    uint32_t regs[32];         // 32 个通用寄存器
    bool halted;               // 是否停止

    Memory* memory;            // 指向主存的指针

    uint32_t if_id_inst;       // IF/ID 间寄存器，保存取到的指令

    // ID/EX 暂存寄存器字段
    uint32_t id_ex_opcode;
    uint32_t id_ex_rd;
    uint32_t id_ex_rs1_val;
    uint32_t id_ex_rs2_val;
    uint32_t id_ex_funct3;
    uint32_t id_ex_funct7;
    int32_t  id_ex_imm;        // 新增：立即数

    // EX/MEM 暂存字段
    uint32_t ex_mem_alu_result;
    uint32_t ex_mem_rd;
    uint32_t ex_mem_opcode;
    uint32_t ex_mem_rs2_val;   // 新增：写内存时使用

    // MEM/WB 暂存字段
    uint32_t mem_wb_data;      // 写回数据
    uint32_t mem_wb_rd;        // 写回目的寄存器
    uint32_t mem_wb_opcode;    // 写回操作类型
};

#endif


// ===========================
// 文件：cpu.cpp
// 功能：实现 CPU 类的构造、step 执行、Fetch、Decode、Execute 阶段
// ===========================

#include "cpu.h"
#include <iostream>
#include <iomanip>

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
    if (if_id_inst == 0x0000006f) halted = true; // 支持 ECALL = JAL x0, 0
    pc += 4; // 默认顺序执行，后续加入分支预测等改动 PC
}

// ID 阶段：解析 R/I/S 型指令字段并计算立即数
void CPU::decode() {
    uint32_t inst = if_id_inst;
    uint32_t opcode = inst & 0x7F;
    uint32_t rd     = (inst >> 7) & 0x1F;
    uint32_t funct3 = (inst >> 12) & 0x7;
    uint32_t rs1    = (inst >> 15) & 0x1F;
    uint32_t rs2    = (inst >> 20) & 0x1F;
    uint32_t funct7 = (inst >> 25) & 0x7F;

    id_ex_opcode = opcode;
    id_ex_rd = rd;
    id_ex_rs1_val = regs[rs1];
    id_ex_rs2_val = regs[rs2];
    id_ex_funct3 = funct3;
    id_ex_funct7 = funct7; 

    // I 型立即数提取（符号扩展）
    if (opcode == 0x13 || opcode == 0x03) {
        int32_t imm = static_cast<int32_t>(inst) >> 20;
        id_ex_imm = imm;
    } else if (opcode == 0x23) { // S 型立即数提取
        int32_t imm = ((inst >> 25) << 5) | ((inst >> 7) & 0x1F);
        if (imm & 0x800) imm |= 0xFFFFF000; // 符号扩展
        id_ex_imm = imm;
    }

    std::cout << "[ID] opcode: " << opcode << " rd: x" << rd
              << " rs1_val: " << id_ex_rs1_val << " rs2_val: " << id_ex_rs2_val
              << " funct3: " << funct3 << " funct7: " << funct7 << std::endl;
}

// EX 阶段：支持 R 型 add/sub，以及 I 型 addi
void CPU::execute() {
    ex_mem_opcode = id_ex_opcode;
    ex_mem_rd = id_ex_rd;
    ex_mem_rs2_val = id_ex_rs2_val; // 保存 rs2 用于 store

    if (id_ex_opcode == 0x33) { // R-type
        switch ((id_ex_funct3 << 3) | (id_ex_funct7 >> 5)) {
            case 0x00: // add
                ex_mem_alu_result = id_ex_rs1_val + id_ex_rs2_val;
                break;
            case 0x20: // sub
                ex_mem_alu_result = id_ex_rs1_val - id_ex_rs2_val;
                break;
            default:
                std::cerr << "[EX] 未实现的 R 型指令 funct3/funct7" << std::endl;
                ex_mem_alu_result = 0;
        }
        std::cout << "[EX] R型 ALU结果: " << ex_mem_alu_result << std::endl;
    } else if (id_ex_opcode == 0x13) { // I-type addi
        if (id_ex_funct3 == 0x0) {
            ex_mem_alu_result = id_ex_rs1_val + id_ex_imm;
            std::cout << "[EX] I型 ALU结果: " << ex_mem_alu_result << std::endl;
        }
    } else if (id_ex_opcode == 0x03 || id_ex_opcode == 0x23) { // Load / Store
        ex_mem_alu_result = id_ex_rs1_val + id_ex_imm; // 地址计算
        std::cout << "[EX] Load/Store地址: " << ex_mem_alu_result << std::endl;
    } else {
        std::cout << "[EX] 暂不支持的 opcode: " << id_ex_opcode << std::endl;
    }
}

// MEM 阶段：执行 Load/Store 操作
void CPU::memory_access() {
    mem_wb_opcode = ex_mem_opcode;
    mem_wb_rd = ex_mem_rd;

    if (ex_mem_opcode == 0x03) { // Load
        mem_wb_data = memory->read_word(ex_mem_alu_result);
        std::cout << "[MEM] Load 数据: " << mem_wb_data << std::endl;
    } else if (ex_mem_opcode == 0x23) { // Store
        memory->write_word(ex_mem_alu_result, ex_mem_rs2_val);
        std::cout << "[MEM] Store 数据: " << ex_mem_rs2_val << std::endl;
    } else {
        mem_wb_data = ex_mem_alu_result; // 对于 R/I 型直接传递
    }
}

// WB 阶段：写回寄存器堆
void CPU::write_back() {
    if (mem_wb_opcode != 0x23 && mem_wb_rd != 0) { // 非 store 且不写 x0
        regs[mem_wb_rd] = mem_wb_data;
        std::cout << "[WB] 写回 x" << mem_wb_rd << " = " << mem_wb_data << std::endl;
    }
}

// ✅ 打印寄存器状态
void CPU::dump_registers() const {
    std::cout << "\n==== 寄存器状态 ====\n";
    for (int i = 0; i < 32; ++i) {
        std::cout << "x" << i << ": " << std::dec << regs[i] << "\t";
        if ((i + 1) % 4 == 0) std::cout << std::endl;
    }
}

// ✅ 打印指定内存范围的内容
void CPU::dump_memory(uint32_t start, uint32_t size) const {
    std::cout << "\n==== 内存内容 [0x" << std::hex << start << " - 0x" << (start + size) << "] ====\n";
    for (uint32_t addr = start; addr < start + size; addr += 4) {
        uint32_t val = memory->read_word(addr);
        std::cout << "0x" << std::setw(8) << std::setfill('0') << addr << ": 0x"
                  << std::setw(8) << std::setfill('0') << val << std::endl;
    }
}
