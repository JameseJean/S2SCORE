# 第4阶段：参考 BOOM 架构学习工程化设计方法

本阶段目标是学习 Berkeley Out-of-Order Machine（BOOM）开源项目的结构与实现方式，借此对比自己的设计，汲取工程经验，包括模块划分、验证流程、调试工具链、Chisel编码风格等。

---

## 🎯 阶段目标

- [ ] 了解 BOOM 架构的核心模块划分
- [ ] 学习其如何实现乱序执行、分支预测等
- [ ] 学习其流水线调度、ROB、RS、IQ的封装方式
- [ ] 理解 Chisel 编码风格及工程组织方式
- [ ] 对比自身项目，汲取优化思路

---

## 本阶段输出成果

-BOOM 架构笔记（建议写成 Markdown 图文并茂）
-提炼出3~5条可迁移优化点，计划在自己架构中使用
-你对真正工业级开源 CPU 的组织方式有完整理解

---

## ⏱ 建议时间安排（约4~6天）

| 时间 | 任务 |
|------|------|
| Day 1 | 熟悉 BOOM 项目整体架构和模块图 |
| Day 2 | 跟踪 Rename → Dispatch → Execute → Commit 流 |
| Day 3 | 阅读分支预测器、BTB 和 BPD 部分 |
| Day 4 | 阅读 ROB / IQ / LSQ 实现 |
| Day 5 | 学习其调试和测试机制（PlusArgs, Difftest） |
| Day 6 | 输出总结笔记，思考迁移到自己设计的策略 |

---

## 🧱 BOOM 关键架构模块概览

Fetch → Decode → Rename → Dispatch → Issue
↓ ↓ ↓ ↓
BPD MapTbl ROB IQ
↓ ↓
FSB Execution Units
↓
Writeback → Commit


---

## 🛠 推荐 BOOM 路径学习方式

1. **入口**：从 `BoomCore.scala` 看主模块
2. **重命名模块**：`RenameStage.scala`
3. **ROB 结构**：`Rob.scala`
4. **Issue 队列**：`IssueUnit.scala`
5. **分支预测**：`Bpd.scala`, `Btb.scala`
6. **调试接口**：使用 `Printf`, `PlusArgs`, `Difftest`

---

## 🧩 自己项目可以借鉴的点

| BOOM特性 | 可迁移优化 |
|----------|-------------|
| ROB 分多槽按功能分类 | 可以考虑分开 LSU、ALU、BRU槽 |
| Issue 分为 Int/FP/BR | 你可以尝试独立多个队列 |
| 使用 Valid/Ready 信号组合 | 你可以标准化模块接口、便于后续重构 |
| 使用 `Printf` 做仿真日志打印 | 学习 debug 方式，减少 println |

---

## 📚 推荐资料

- [BOOM 源码 GitHub](https://github.com/riscv-boom/riscv-boom)
- [BOOM 官方文档 Wiki](https://github.com/riscv-boom/riscv-boom/wiki)
- [BOOM 架构论文](https://ieeexplore.ieee.org/document/8951873)

---

## 📘 日志模板建议

```markdown
### Day 4 - 阅读 BOOM Issue Queue

- ✅ IssueUnit 设计清晰，分成 Int/FP Queue
- ✅ 每条指令有状态机管理生命周期
- ❗ ROB 和 IQ 是解耦的，但交互复杂
- 💡 我的实现中也应增加 Issue优先级与流水线调度策略
