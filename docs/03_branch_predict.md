# 第3阶段：分支预测与回滚机制实现

本阶段目标是在乱序执行架构中加入静态与动态分支预测机制，提升控制流密集程序性能，同时支持分支预测失败后的流水线回滚与恢复。

---

## 🎯 阶段目标

- [ ] 理解分支预测基础原理：静态 vs 动态
- [ ] 实现静态预测策略（例如 Always Not Taken）
- [ ] 实现全局动态预测器（例如 1-bit/2-bit BHT）
- [ ] 引入 BTB（Branch Target Buffer）
- [ ] 加入分支回滚机制（flush ROB/RS）
- [ ] 集成预测器和回滚逻辑至 Fetch + Rename 阶段

---

## 本阶段输出成果

-支持静态与动态分支预测器（可配置）
-引入 BTB，实现基本 PC 预测能力
-在预测失误后能正确清除 ROB、RS、重命名表
-使用分支密集测试程序测评预测准确率

---

## ⏱ 建议时间安排（约5~7天）

| 时间 | 任务 |
|------|------|
| Day 1 | 阅读分支预测器设计思路，梳理类型 |
| Day 2 | 实现静态预测 + 分支延迟槽处理 |
| Day 3 | 加入 1-bit 或 2-bit BHT 动态预测器 |
| Day 4 | 加入 BTB（命中目标地址） |
| Day 5 | 集成回滚机制，调通 Flush 路径 |
| Day 6-7 | 编写分支密集程序测试，调试精度与性能 |

---

## 🔧 核心模块组成

┌──────────────┐ ┌────────────┐
│ Branch Pred. │◄───▶│ BTB Table │
└──────┬───────┘ └────────────┘
▼
┌────────────┐
│ Fetch │
└──────┬─────┘
▼
┌────────────┐
│ Rename + RS│ ──▶ ROB
└────────────┘
▼
Exec 分支指令 → 检查是否预测正确？
└─错则 flush → 恢复状态


---

## 🔁 回滚机制关键点

- ROB：支持清除预测错误后的未提交指令
- RS：撤销尚未执行的所有待发射指令
- Rename：恢复重命名映射表
- PC：恢复为实际分支目标地址或 fall-through

---

## 📚 推荐资料

- [Dynamic Branch Prediction – 2-bit predictors](https://danluu.com/branch-prediction/)
- [开源 CPU BHT/BTB 实现参考：YaoBench](https://github.com/yao-jiawei/YaoBench)
- [CS61C Lecture: Branch Prediction](https://cs61c.org)

---

## 🧪 建议测试样例

- [ ] if-else + loop 场景，测试静态预测成功率
- [ ] 多个间隔短跳转场景（回文判定、二分查找）
- [ ] 预测失误后能否 flush 正确、恢复状态

---

## 📘 日志建议模板

```markdown
### Day 5 - 加入动态预测器和 BTB

- ✅ 实现 2-bit 饱和计数器
- ✅ 实现 BTB 结构，记录目标 PC
- ❗ 预测命中但目标错误的恢复逻辑不完整
- 💡 明天完成 flush 路径中 Rename 恢复
