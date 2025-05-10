# 第5阶段：代码结构优化、完整文档编写与开源发布准备

本阶段目标是将前面完成的功能整理打包，优化代码结构、接口模块、文档说明，并以教育用途开源，方便他人学习使用，也作为个人IP展示材料。

---

## 🎯 阶段目标

- [ ] 完善顶层 README 和项目结构说明
- [ ] 统一代码风格、模块命名、信号规范
- [ ] 整理每阶段文档，发布到 docs/
- [ ] 制作一份 Markdown + 图片的“架构介绍”PPT文稿
- [ ] 添加一个教学 demo（例：fib、bubble sort）
- [ ] 准备项目展示页（GitHub Pages / Notion 均可）

---

## 本阶段输出成果

-项目顶层 README（包含架构图 + 特性）
-每阶段学习笔记与源码对应关系
-教学样例程序（包含编译脚本）
-GitHub 项目页（或个人展示页）上线
-可作为你应聘/面试时展示的项目材料

---

## ⏱ 建议时间安排（约5~7天）

| 时间 | 任务 |
|------|------|
| Day 1 | 统一模块接口（Valid/Ready、控制信号） |
| Day 2 | 整理 `src/`，分阶段放入 `pipeline/`, `core/`, `test/` |
| Day 3 | 完善顶层 `README.md`：架构图 + 项目背景 |
| Day 4 | 整合 `docs/` 目录下每阶段文档，内链跳转 |
| Day 5 | 用 mermaid / draw.io 绘制顶层执行路径和数据流图 |
| Day 6 | 准备 2~3 个教学样例程序，并编写使用说明 |
| Day 7 | 部署 GitHub Pages 或 Notion，开源项目 |

---

## 🧱 推荐项目结构
S2SCORE/
├── src/
│ ├── top.sv
│ ├── core/
│ ├── pipeline/
│ └── predictor/
├── test/
│ └── programs/
├── docs/
│ ├── 01_baseline.md
│ ├── 02_reorder.md
│ ├── 03_branch_predict.md
│ ├── 04_boom_study.md
│ └── 05_refactor_and_doc.md
├── README.md
└── Makefile / run.sh


---

## 📚 可借鉴项目文档风格

- [MiniRV: 清晰的项目结构和 markdown 图文说明](https://github.com/kiwi0fruit/minirv)
- [YaoBench: 教学导向的开源乱序CPU](https://github.com/yao-jiawei/YaoBench)
- [BOOM wiki：以模块为单位，配合图示文档](https://github.com/riscv-boom/riscv-boom/wiki)

---

## 🎁 Bonus（选做）

- [ ] 尝试使用 mkdocs 或 docsify 构建文档网页
- [ ] 录屏演示 + 简要讲解视频（加字幕）
- [ ] 和 ChatGPT 生成“技术讲解”PPT用于应聘展示

---

## 📘 日志建议模板

```markdown
### Day 2 - 重构项目结构

- ✅ 将 pipeline 拆分到独立目录
- ✅ 修改 module 名统一格式如 OoocpuFetch
- ❗ 文档跳转链接未完成，明天处理
- 💡 README 用 AI 生成初稿后润色，效率高
