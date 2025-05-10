
# RISC-V CPU 学习与实现路线

本项目旨在通过逐步动手构建简化的 RISC-V CPU 实现，深入理解指令集、流水线、乱序执行等微架构关键技术，为广大爱好CPU/GPU的同志入门学习

---

## 📌 阶段目标总览（约3~5周）

### ✅ 第1阶段：基础 ISA 解释器 + 五级流水线（Week 1）
- 了解 RISC-V RV32I 指令集
- 实现一个支持流水线执行的 RV32I CPU 模拟器
- 实现基本的数据冒险转发、控制冒险处理

🔗 推荐资料：
- RISC-V 手册（《The RISC-V Reader》）
- [NEMU / y86](https://ysyx.oscc.cc/)
- [MIPS流水线模拟器讲义](https://zhuanlan.zhihu.com/p/138176874)

---

### ✅ 第2阶段：加入乱序执行模型（Week 2~3）
- 理解 Tomasulo 算法（保留站 + 重命名）
- 实现 ROB（Reorder Buffer）
- 支持乱序发射、乱序执行、有序提交

🔗 推荐资料：
- [Tomasulo 乱序调度讲解](https://www.youtube.com/watch?v=Db4I2MrG6TY)
- [RVCoreP](https://github.com/AnonymousX1024/RVCoreP)
- [MIT 6.004 Lab](https://6004.mit.edu/)

---

### ✅ 第3阶段：加入分支预测机制（Week 4）
- 实现静态预测 + 动态预测（1-bit/2-bit predictor）
- 实现 BTB（Branch Target Buffer）结构
- 探索 Return Address Stack 预测器（可选）

---

### ✅ 第4阶段：学习 BOOM 架构（Week 5）
- 阅读 BOOM 项目架构文档与关键模块
- 梳理从 Fetch → Decode → Rename → Issue → Execute → Commit 的数据通路
- 对比你自己的模拟器实现，提炼共通架构思想

🔗 BOOM 链接：
- https://github.com/riscv-boom/riscv-boom
- https://docs.boom-core.org/en/latest/

---

## 💡 项目输出成果

- 支持 RV32I 的简化版乱序 CPU 模拟器（可命令行交互，支持调试）
- 每阶段都有独立文档记录设计、测试与学习心得
- 生成清晰的模块图（支持用 Mermaid、draw.io 或笔手图）

---

## 📂 项目结构建议

```bash
/S2SCORE
├── README.md
├── docs/
│   ├── 00_overview.md
│   ├── 01_pipeline.md
│   ├── 02_oOO.md
│   ├── 03_branch_predict.md
│   └── 04_boom_study.md
├── src/                    # 模拟器代码实现
│   ├── stage1_pipeline/
│   ├── stage2_ooo/
│   ├── stage3_predictor/
├── tests/                  # 自定义测试程序和输出结果
└── notes/
    └── todo.md             # 遇到的问题、计划、调研草稿
