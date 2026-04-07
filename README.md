# AI+万物 · 教师培训课程仓库

> 深圳职业技术大学 × 柴火创客学院 | 2026 春季

## 这是什么？

这是「AI+万物：从 AI 自主编程到零代码视觉实战」教师培训的课程仓库。使用 AI CLI 工具（OpenCode 等）在本仓库中完成硬件编程项目。

AI 工具启动后会自动读取 `CLAUDE.md`，获得完整的硬件信息和开发规范，然后根据需求文档直接生成可编译运行的代码。

## 快速开始

```bash
# 1. 启动 AI CLI 工具
opencode

# 2. 告诉 AI 完成环境准备
> 请帮我完成以下准备工作：
> 1. 克隆课程仓库 https://github.com/mouseart2025/szd-ai-maker-2026.git
> 2. 切换到 szd-ai-maker-2026 目录
> 3. 阅读 CLAUDE.md，告诉我这个项目支持什么硬件
> 4. 进入 examples/01-led-blink，编译并上传到开发板
```

## 仓库结构

```
szd-ai-maker-2026/
├── CLAUDE.md                        # AI 上下文（硬件信息 + 开发规范）
├── docs/                            # 预置需求文档
│   ├── requirements-blink.md        # LED 闪烁（环境验证）
│   └── requirements-web-control.md  # WiFi Web 控制（核心体验）
├── examples/                        # 已验证的示例项目
│   ├── 01-led-blink/                # LED 闪烁
│   └── 02-web-control/             # WiFi Web 控制 LED+风扇
├── templates/                       # 项目模板
│   └── xiao-project/
└── hardware/                        # 硬件参考文档（待补充）
```

## 硬件套件

| 组件 | 说明 |
|---|---|
| XIAO ESP32S3 Sense | 主控，内置摄像头+麦克风，支持 WiFi/BLE |
| Grove Base for XIAO | 扩展板，方便连接 Grove 模块 |
| Grove LED 模块 | 接 D0 端口 |
| Grove 风扇模块 | 接 D1 端口 |
| USB-C 数据线 | 连接电脑 |

## 工作流

```
阅读需求文档 → AI 生成代码 → 编译上传 → 手机连 WiFi → 网页控制硬件 → 迭代
```

## 培训讲师

冯磊 + 助教团队 | 柴火创客空间
