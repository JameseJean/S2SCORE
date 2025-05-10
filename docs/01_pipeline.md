# 第1阶段：五级流水线模拟器实现

本阶段目标是实现一个支持 RISC-V RV32I 指令集的精简 CPU 模拟器，并加入标准的 5 级流水线结构，包括数据冒险处理、简单的控制冒险处理。

---

## 🎯 阶段目标

- [ ] 搭建 RV32I 指令解释执行模型
- [ ] 构建 Fetch / Decode / Execute / Memory / Writeback 五级流水线
- [ ] 加入 Forwarding（数据转发）逻辑
- [ ] 加入 Stall / Bubble（暂停与气泡）处理
- [ ] 加入 PC 跳转逻辑（遇到 branch 时 flush）
- [ ] 用手写汇编程序测试

---

## 本阶段输出成果

-一个支持 RV32I、具备五级流水线的模拟器
-能在控制台加载程序，单步执行或自动运行
-一份结构图 + 模块说明文档（可放 draw.io）

---

## ⏱ 建议时间安排（约1周）

| 时间 | 任务 |
|------|------|
| Day 1 | 设计结构框图，完成 RV32I 指令集 parser |
| Day 2 | 实现 Fetch/Decode/Execute阶段 |
| Day 3 | 实现 Memory/Writeback阶段，基本跑通 |
| Day 4 | 加入 Forwarding / Hazard Detection |
| Day 5 | 加入控制冒险处理（PC 跳转、flush） |
| Day 6-7 | 写汇编程序测试，记录问题，写日志 |

---

## 🧩 模块划分建议

┌────────┐ ┌────────┐ ┌────────┐ ┌────────┐ ┌────────────┐
│ Fetch │ → │ Decode │ → │ Execute│ → │ Memory │ → │ Writeback │
└────────┘ └────────┘ └────────┘ └────────┘ └────────────┘
↓ ↓ ↓ ↓ ↓
PC 寄存器读 ALU运算 访存 写回寄存器


- **Hazard Detection Unit**（检测 RAW 冒险）
- **Forwarding Unit**（转发 EX/MEM/WB 阶段数据）
- **Pipeline Registers**：IF/ID, ID/EX, EX/MEM, MEM/WB

---

## 📚 参考资料

- [RISC-V RV32I 指令集](https://github.com/riscvarchive/riscv-isa-manual/blob/main/src/base.tex)
- [MIPS流水线模拟器讲义](https://zhuanlan.zhihu.com/p/138176874)
- [清华 NEMU 教学 CPU 项目](https://ysyx.oscc.cc/)
- [xv6 RISC-V 结构参考](https://github.com/mit-pdos/xv6-riscv)

---

## 🧪 建议测试样例

用 hand-written 汇编测试以下内容：

- [ ] 算术指令 `add`, `sub`, `addi`
- [ ] 数据转发 `add x3, x1, x2` → `add x4, x3, x2`
- [ ] RAW Hazard 检测和暂停
- [ ] 分支跳转 `beq`, `bne`
- [ ] Load / Store 操作 `lw`, `sw`

你可以用 `objdump` 反汇编 `.elf`，手动写测试数据运行。

---

## 📘 日志建议格式（每次学习后可更新）

```markdown
### Day 1 - 搭建基础结构

- ✅ 阅读 RV32I 基础指令集
- ✅ 设计流水线模块划分
- ❓ 如何处理立即数扩展？
- 💡 明天计划：写 Fetch/Decode 基础逻辑
S2SCORE  //主文件名
|   ├── main.cpp                    // 程序入口，包含加载hex文件并调用CPU执行
│   ├── cpu.h                       // 声明 CPU 类，包括寄存器组、PC 和运行控制函数
│   ├── cpu.cpp                     // 实现 CPU 类的各项功能，如取指、译码、执行等
│   ├── memory.h                    // 声明内存类，用于 load/store 操作
│   ├── memory.cpp                  // 实现内存的读写功能
│   ├── instructions.h             // 定义指令结构体与辅助宏，支持 RV32I
│   ├── instructions.cpp           // 实现指令解析功能（将 opcode 翻译为操作）
│   ├── pipeline.h                 // 声明流水线各阶段结构和流程控制
│   ├── pipeline.cpp               // 实现流水线调度、forward、stall、flush 等逻辑
└── programs
    └── test.hex                   // 示例程序，用于模拟器测试运行