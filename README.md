# AI+万物 · 教师培训课程仓库

> 深圳职业技术大学 × 柴火创客学院 | 2026 春季

## 这是什么？

这是「AI+万物：从 AI 自主编程到零代码视觉实战」教师培训的课程仓库。使用 AI CLI 工具（OpenCode 等）在本仓库中完成硬件编程项目。

AI 工具启动后会自动读取 `CLAUDE.md`，获得完整的硬件信息和开发规范，然后根据你的需求直接生成可编译运行的代码。**你不需要写代码，也不需要打开编辑器**。

## 快速开始

```bash
# 1. 启动 AI CLI 工具 (在任意目录)
opencode

# 2. 告诉 AI 拉仓库并认识项目
> 请帮我做以下事情：
>
> 1. 把课程仓库下载到我的桌面 (szd-ai-maker-2026 目录)。
>    仓库地址: https://github.com/mouseart2025/szd-ai-maker-2026
>
>    ⚠️ 中国大陆终端访问 GitHub 经常不稳定（但浏览器一般可以）。请按顺序试，
>    每种最多试 30 秒，不行立刻换下一个：
>    A. git clone
>    B. gh repo clone mouseart2025/szd-ai-maker-2026
>    C. curl 下载 ZIP（codeload.github.com）
>    D. gh api 逐文件拉
>    E. **A-D 全失败 → 提示我用浏览器手动下载 ZIP，告诉你解压路径**
>    F. 浏览器也不通 → 提示我找助教 U 盘
>
> 2. cd 进入 szd-ai-maker-2026 目录（或我告诉你的解压路径）
> 3. 阅读 CLAUDE.md
> 4. 找到 arduino-cli 路径（内置在 Arduino IDE 里，CLAUDE.md 有说明），运行 `arduino-cli version` 验证可用
> 5. 告诉我项目支持什么硬件、arduino-cli 是否可用
>
> 我的系统是 [macOS / Windows]。
>
> **重要**：今天所有项目文件都在 szd-ai-maker-2026 这个目录下创建，请把它当作工作目录。
```

成功后，AI 会知道项目用的是 XIAO ESP32S3 + Grove Base + LED/风扇/Buzzer，接下来你直接和它对话让它做任何硬件项目就行。

## 仓库结构

```
szd-ai-maker-2026/
├── CLAUDE.md                        # AI 上下文（硬件信息 + 开发规范）
├── 学员文档.md                       # 学员课上/课后参考手册
├── docs/                            # 可选：预置需求文档（一次性生成方案用）
│   ├── requirements-blink.md        # LED 闪烁（环境验证）
│   └── requirements-web-control.md  # WiFi Web 控制（v1 一次性生成方式）
├── examples/                        # 已验证的示例项目（Arduino .ino 格式）
│   ├── 01-led-blink/
│   │   └── 01-led-blink.ino
│   └── 02-web-control/
│       └── 02-web-control.ino
├── templates/                       # 空项目模板
│   └── xiao-project/
│       └── requirements.md
└── README.md
```

## 硬件套件

| 组件 | 说明 |
|---|---|
| XIAO ESP32S3 Sense | 主控，内置摄像头 + 麦克风，支持 WiFi/BLE · **板载 LED 在 GPIO21**（反逻辑, LOW 点亮）|
| Grove Shield for XIAO | 扩展板，免焊接连接 Grove 模块（Grove 端口 VCC = 3.3V）|
| Grove Mini 风扇模块 | 接 **D1** 端口 |
| Grove Buzzer 模块 | 接 **D2** 端口 |
| USB-C 数据线 | 连接电脑 |

**端口口诀**：D1 = 风扇 · D2 = Buzzer · **LED 演示用板载 `LED_BUILTIN` (GPIO21, 反逻辑)**

## 培训当天的核心体验

1. **讲师 Demo**（看）：LED Blink → Buzzer + LED 同步 → SOS 莫尔斯电码
2. **实践任务 3 步走**（你动手）：点亮 LED → 加 Buzzer → 加风扇
3. **BMAD 实战**（高潮）：让 AI 扮演 PM → UX → 架构师 → 开发者，生成手机网页控制硬件的完整应用
4. **零代码 AI 视觉**：用 SenseCraft AI 训练自己的视觉模型
5. **反思实践**：和 AI 聊"我自己的课怎么用这套方法"

详细流程见 [`学员文档.md`](学员文档.md)。

## 工作流

```
教师说"我想做 ___"
    → AI 读 CLAUDE.md 和 examples/ 学习项目规范
    → AI 自动创建项目、写代码、编译、上传
    → 教师看硬件反应
    → 教师说"改成 ___"
    → AI 修改代码并重新上传
    → 迭代直到满意
```

## 关于 docs/ 和 examples/

- **docs/requirements-\*.md**: 预置的需求文档（v1 方式）。可以让 AI 一次性读完生成代码。v2 培训现场**主要用 BMAD 4 步**（PM → UX → 架构师 → 开发者）替代，但这些文档保留作为**参考和备选方案**。
- **examples/\*.ino**: 讲师已验证的示例代码。AI 遇到类似需求可以参考这些作为模板，但不应直接复制——应该根据教师的具体需求重新生成。

## 培训讲师

冯磊 + 助教团队 | 柴火创客空间

- 培训时间：2026/4/14 周一 14:00–17:00
- 培训地点：深圳职业技术大学校内
- 官网：[seeedstudio.com](https://www.seeedstudio.com/)
