# 🚀 OoOCpu: 从零构建一个乱序执行CPU（学习型项目）

本项目是一个教学型 RISC-V 架构乱序执行 CPU 实现，旨在通过动手构建简化版 OoO Pipeline，深入理解现代 CPU 微架构设计（包括乱序调度、ROB、分支预测等）核心原理。适合作为求职兆芯、海光、寒武纪等公司芯片相关岗位的展示项目或学习实践材料。

---

## 🧠 核心特性

- ✅ 简化 RISC-V 指令支持（RV32I）
- ✅ 支持乱序执行（Out-of-Order）
- ✅ 支持指令重命名（Register Renaming）
- ✅ 实现 ROB（Reorder Buffer）
- ✅ 多发射 Issue Queue（支持基本调度）
- ✅ 动态分支预测（基于简单 BHT+BTB）
- ✅ 可扩展的 Chisel/Verilog 模块结构
- ✅ 学习分阶段文档完整可读

---

## 🧱 架构总览（简化）

```mermaid
graph TD
  IF[IF: 指令取指] --> ID[ID: 解码]
  ID --> RN[RN: 重命名]
  RN --> DIS[Dispatch]
  DIS --> IQ[Issue Queue]
  IQ --> EX[执行单元]
  EX --> WB[写回]
  WB --> COM[提交]
  COM --> ROB[ROB: Reorder Buffer]
  RN -->|更新| ROB
  EX -->|结果| ROB
  COM -->|提交顺序| RegFile

📘 分阶段文档
文档位于 docs/ 文件夹，记录了从设计到实现的完整学习过程：

阶段	内容	文档
01	构建顺序执行 baseline	01_baseline.md
02	增加乱序执行 + ROB + IQ	02_reorder.md
03	增加分支预测单元	03_branch_predict.md
04	学习 BOOM 架构	04_boom_study.md
05	项目重构与开源准备	05_refactor_and_doc.md

🧪 示例程序
教学 demo（位于 test/programs/）：

fib.S：斐波那契数列

sort.S：冒泡排序

loop.S：分支预测测试

后续将支持二进制加载或更高级指令集扩展

⚙️ 构建 & 仿真
支持 Chisel / Verilog 仿真：

bash
复制
编辑
# 进入项目根目录
cd my-S2SCORE

# 编译并仿真执行 demo 程序
make run PROGRAM=fib

# 或使用 verilator
make verilate
./obj_dir/Vtop +program=test/programs/fib.hex

🙋‍♂️ 作者说明
