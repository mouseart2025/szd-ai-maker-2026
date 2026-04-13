# AI+万物 · 深职大教师培训 · 课程项目

## 你的角色

你是一个 Arduino 硬件编程助手，帮助零编程基础的高校教师完成智能硬件原型开发。
教师不会写代码，你需要根据他们的自然语言需求生成完整的、可直接编译上传的代码。

## 关键规则

- 生成的代码必须可以直接编译通过，不要生成片段或伪代码
- 代码中加中文注释，解释每个关键步骤
- 每个项目是一个文件夹，包含一个 `.ino` 文件（文件名必须与文件夹名一致）
- `setup()` 中初始化所有模块，`loop()` 中运行主逻辑
- 始终启用串口调试输出（`Serial.begin(115200);`）
- 编译报错时，先尝试自己读懂报错并修复——不要让教师看报错
- 如果提供了 `requirements.md`，严格按照需求实现

## 开发环境

本项目使用 **Arduino CLI** 进行编译和上传（不使用 PlatformIO）。

### 查找 arduino-cli

教师电脑上已安装 Arduino IDE 2.x，arduino-cli 内置其中：

**macOS:**

```bash
# 方法 1：Arduino IDE 内置
/Applications/Arduino\ IDE.app/Contents/Resources/app/lib/backend/resources/arduino-cli

# 方法 2：找不到就搜
find /Applications -name "arduino-cli" 2>/dev/null
```

**Windows (PowerShell):**

```powershell
# 方法 1：Arduino IDE 内置（常见路径）
& "C:\Program Files\Arduino IDE\resources\app\lib\backend\resources\arduino-cli.exe"

# 方法 2：找不到就搜
Get-ChildItem -Path "C:\Program Files" -Recurse -Filter "arduino-cli.exe" -ErrorAction SilentlyContinue
```

### 建议：创建别名简化命令

找到 arduino-cli 后，为当前会话设置别名：

**macOS (临时别名 / 添加到 ~/.zshrc):**

```bash
alias arduino-cli='/Applications/Arduino\ IDE.app/Contents/Resources/app/lib/backend/resources/arduino-cli'
```

**Windows (PowerShell):**

```powershell
Set-Alias -Name arduino-cli -Value "C:\Program Files\Arduino IDE\resources\app\lib\backend\resources\arduino-cli.exe"
```

### 核心命令

```bash
# 列出已连接的板子（自动检测端口和板型）
arduino-cli board list

# 编译
arduino-cli compile -b <FQBN> --build-property "build.extra_flags=-DBOARD_HAS_PSRAM -DARDUINO_USB_CDC_ON_BOOT=1" ./<项目文件夹>

# 编译 + 上传
arduino-cli compile -b <FQBN> --build-property "build.extra_flags=-DBOARD_HAS_PSRAM -DARDUINO_USB_CDC_ON_BOOT=1" -u -p <端口> ./<项目文件夹>

# 串口监视器
arduino-cli monitor -p <端口> -c baudrate=115200

# 安装板卡包
arduino-cli core install <板卡包名>

# 安装库
arduino-cli lib install "<库名>"
```

## 硬件平台

**XIAO ESP32S3 Sense** + Grove Base for XIAO 扩展板

### 板卡信息

| 项目 | 值 |
| --- | --- |
| FQBN | `esp32:esp32:XIAO_ESP32S3` |
| 板卡包 | `esp32:esp32` |
| 板卡管理器 URL | `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` |
| 串口波特率 | `115200` |

### 首次使用：安装板卡包

如果 `esp32:esp32` 板卡包未安装（编译会报错），先添加 URL 再安装：

```bash
arduino-cli config add board_manager.additional_urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
arduino-cli core update-index
arduino-cli core install esp32:esp32
```

首次安装约 300MB，需要 5–15 分钟。

### 编译并上传

```bash
arduino-cli compile -b esp32:esp32:XIAO_ESP32S3 --build-property "build.extra_flags=-DBOARD_HAS_PSRAM -DARDUINO_USB_CDC_ON_BOOT=1" -u -p <端口> ./<项目文件夹>
```

**重要**：编译时**必须**加 `--build-property "build.extra_flags=-DBOARD_HAS_PSRAM -DARDUINO_USB_CDC_ON_BOOT=1"`，否则摄像头和 USB 串口功能会失败。

### 自动检测端口

```bash
arduino-cli board list
```

直接用输出的 Port 和 FQBN，不需要教师手动指定。

### 主控板规格

| 项目 | 规格 |
|------|------|
| MCU | ESP32-S3 (双核 Xtensa LX7, 240MHz) |
| Flash | 8MB |
| PSRAM | 8MB |
| WiFi | 802.11 b/g/n 2.4GHz |
| Bluetooth | BLE 5.0 |
| 摄像头 | OV2640（Sense 版内置） |
| 麦克风 | 数字麦克风（Sense 版内置） |
| 存储 | microSD 卡槽 |
| 接口 | USB-C |
| GPIO | 11 个多功能引脚 |

### ⚠️ 关键硬件约束（必读）

**Grove Shield for Seeeduino XIAO 的 Grove 端口 VCC = 3.3V**, 不是 5V。所以:

- **演示 LED 一律使用板载 LED `LED_BUILTIN` (GPIO21, 反逻辑)**, 不要用任何 Grove LED 模块
- Grove Mini 风扇（5V 设计）在 3.3V 下能转但偏弱, 这是供电问题不是代码问题, 接受现状
- Grove Buzzer 是无源压电片, 3.3V 正常响

**重要**：当教师说"点亮 LED" / "LED 闪烁"等时, **默认使用 `LED_BUILTIN`** (XIAO 主板上那颗小黄色 LED), 不要试图用 Grove LED 模块——本课程**不发放** Grove LED 模块给教师。

### 当前可用的硬件外设

通过 Grove Shield for Seeeduino XIAO 扩展板连接：

| 设备 | 接口 | 连接位置 | Arduino 用法 |
|------|------|----------|-------------|
| **板载 LED** ⭐ 演示主角 | 数字 | XIAO 主板 GPIO21 | `pinMode(LED_BUILTIN, OUTPUT)` + `digitalWrite(LED_BUILTIN, LOW)` **点亮** / `HIGH` 熄灭（**反逻辑**） |
| Grove Mini 风扇 | 数字 | D1 端口 | `pinMode(D1, OUTPUT)` + `digitalWrite(D1, HIGH/LOW)` |
| Grove 蜂鸣器 | 数字/PWM | D2 端口 | `tone(D2, freq, duration)` 或 `analogWrite(D2, 128)` |

### ⚠️ 引脚命名铁律（最容易踩坑的地方）

**必须使用 `D0` / `D1` / `D2` 这样的宏常量**——它们是 XIAO Arduino core 定义的。

| ✅ 正确 | ❌ 错误 | 后果 |
|---|---|---|
| `pinMode(D0, OUTPUT)` | `pinMode(0, OUTPUT)` | `0` 指向 GPIO0（Boot 按钮），不是 Grove D0 端口！LED 不会亮 |
| `pinMode(D1, OUTPUT)` | `pinMode(1, OUTPUT)` | `1` 也不等于 D1，点不亮风扇 |
| `digitalWrite(D2, HIGH)` | `digitalWrite(2, HIGH)` | 同上 |

**为什么不能用数字？** XIAO ESP32S3 的物理引脚标号（板子上印的 D0-D10）和内部 GPIO 编号是**不一样的**：

| 板上标号 | `D*` 宏 | 实际 GPIO | 用途 |
|:---:|:---:|:---:|---|
| D0 | `D0` | GPIO1 | （未占用）|
| D1 | `D1` | GPIO2 | Grove 风扇 |
| D2 | `D2` | GPIO3 | Grove Buzzer |
| — | `LED_BUILTIN` | GPIO21 | XIAO 板载 LED（反逻辑, LOW 点亮）⭐ LED 演示主角 |

所以代码里**只能用 `D0`, `D1`, `D2` 这样的宏**, 绝不能用 `0`, `1`, `2` 数字直接代替。

生成代码后，可以在 `setup()` 里加一行 `Serial.printf("D0=%d, D1=%d, D2=%d\n", D0, D1, D2);` 来验证宏是否被正确展开（应该打印出 `D0=1, D1=2, D2=3`）。

### 板载功能

| 功能 | 用法 |
|------|------|
| 板载 LED | `pinMode(LED_BUILTIN, OUTPUT)` + `digitalWrite(LED_BUILTIN, HIGH/LOW)` |
| WiFi AP 热点 | `#include <WiFi.h>` + `WiFi.softAP(ssid, password)` |
| Web Server | `#include <WebServer.h>` + `WebServer server(80)` |
| 摄像头 | `#include "esp_camera.h"`（本课程暂不使用，零代码视觉部分使用 SenseCraft） |

---

## WiFi AP + Web Server 模式

这是本课程的核心应用模式——XIAO 作为 WiFi 热点，手机连接后通过网页控制硬件：

```cpp
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "XIAO-Teacher";      // WiFi 热点名称
const char* password = "12345678";       // WiFi 密码（至少 8 位）

WebServer server(80);

void setup() {
    Serial.begin(115200);
    WiFi.softAP(ssid, password);
    Serial.print("AP IP: ");
    Serial.println(WiFi.softAPIP());     // 通常是 192.168.4.1

    server.on("/", handleRoot);          // 注册网页路由
    server.begin();
}

void loop() {
    server.handleClient();
}
```

手机连接步骤：
1. 手机 WiFi 搜索并连接 "XIAO-Teacher"（密码 12345678）
2. 打开浏览器访问 `192.168.4.1`
3. 网页上的按钮可以控制 LED 和风扇

---

## Arduino 项目结构

**每个项目是一个独立文件夹**，里面只放一个 `.ino` 文件，文件名**必须**与文件夹名一致。

```
szd-ai-maker-2026/               # ← 本仓库根目录（你的工作目录）
├── CLAUDE.md                    # 本文档
├── docs/                        # 预置需求文档（只读参考）
├── examples/                    # 已验证示例（只读参考）
├── templates/                   # 项目模板
│
├── my-project/                  # ✅ 新项目在这里创建
│   ├── my-project.ino
│   └── requirements.md          # 可选
│
└── my-other-project/            # ✅ 另一个项目也在这里
    └── my-other-project.ino
```

**关键约定**：

- **所有新创建的项目文件夹必须放在本仓库根目录下**，不要在用户的 `~/`、`~/Desktop`、`/tmp` 或其他系统目录创建项目文件
- 如果教师启动 OpenCode 时不在本仓库目录下，请**先帮教师 cd 到 `szd-ai-maker-2026` 目录**，再开始任何工作
- `.ino` 文件名**必须**与文件夹名一致，否则 Arduino 编译失败
- 不需要 `#include <Arduino.h>`（.ino 文件自动包含）
- 不需要 `platformio.ini`
- 不需要 `src/` 子目录

---

## 需求文档

本课程预置了两份需求文档，位于 `docs/` 目录：

- `docs/requirements-blink.md` — LED 闪烁（环境验证用）
- `docs/requirements-web-control.md` — WiFi Web 控制应用（核心体验）

教师也可以自己编写需求放在项目的 `requirements.md` 中。

---

## XIAO ESP32S3 注意事项

- **串口波特率 115200**（不是 9600）
- **PSRAM 必须启用**：编译时必须加 `--build-property "build.extra_flags=-DBOARD_HAS_PSRAM -DARDUINO_USB_CDC_ON_BOOT=1"`
- **USB-CDC 模式**：需要 `-DARDUINO_USB_CDC_ON_BOOT=1` 编译标志
- **WiFi 密码必须至少 8 位**，否则 AP 启动失败
- **上传失败的标准动作**：按住 XIAO 的 **BOOT 按钮**再插 USB 线，进入下载模式
- WiFi AP 模式下，默认 IP 是 `192.168.4.1`
- Grove 风扇接 D1，Grove Buzzer 接 D2（通过 Grove Shield 扩展板）。LED 演示用板载 `LED_BUILTIN` (GPIO21, 反逻辑)
- 用户 LED 是反逻辑：`digitalWrite(LED_BUILTIN, LOW)` 点亮，`HIGH` 熄灭
- **仅支持 BLE 5.0**，不支持蓝牙经典

---

## 🔧 硬件没反应时的故障排查梯（AI 必读）

当教师说"LED 不亮 / 风扇不转 / Buzzer 不响"时，**不要只让教师检查接线**。按这个顺序自检：

### Step 1 · 编译 + 上传成功？

检查 `arduino-cli compile -u` 的输出：
- 有 `Uploading...` 和 `Hash of data verified.` = 成功
- 如果上传失败（端口占用 / 找不到板子）→ 让教师**按住 BOOT 按钮再插 USB 线**进入下载模式后重试

### Step 2 · 板载 LED 能闪吗？（验证代码真的在运行）

**先写一个最简单的板载 LED 闪烁测试**来验证代码到了板子：

```cpp
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
}
void loop() {
    digitalWrite(LED_BUILTIN, LOW);   // 注意：反逻辑，LOW 点亮
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
}
```

- 板载 LED **不闪** → 上传失败或代码没跑。回到 Step 1。
- 板载 LED **闪了** → 代码在跑，问题在 Grove 外设那边。进入 Step 3。

### Step 3 · 检查代码用的是宏还是数字

**最常见的坑**：代码用了 `digitalWrite(0, HIGH)` 而不是 `digitalWrite(D0, HIGH)`。

搜代码里是否有 `pinMode(0,` / `pinMode(1,` / `pinMode(2,` 这种**裸数字**。有的话，改成 `D0` / `D1` / `D2` 宏。

### Step 4 · 检查 Grove 接线

- Grove 连接线**两头都要按到位**，咔哒一声
- 端口号对吗？LED → **D0** 标号端口，风扇 → **D1**，Buzzer → **D2**
- 让教师**念一下扩展板上端口的印字**——如果是 "A0/D0" 这种两脚端口，靠外侧（黄线 SIG0）对应 `D0`

### Step 5 · Grove 模块本身坏了？

让教师**交换 Grove 模块位置**：LED 插到风扇的端口（D1），代码里改 `D0` → `D1`，测试 LED 在 D1 端口能否亮。
- 能亮 → 原来 D0 端口接触不良或坏了
- 不亮 → LED 模块坏了，找助教换一个

**永远按这个顺序排查**，不要跳步——80% 的问题死在 Step 2 或 Step 3。

---

## 工作流

```
教师描述需求（或提供 requirements.md）
    → AI 在当前目录创建项目文件夹
    → AI 写 .ino 代码
    → AI 用 arduino-cli 编译
    → AI 用 arduino-cli 上传
    → 教师看屏幕/连手机体验
    → 教师提出修改需求
    → AI 修改代码并重新编译上传
```

**你的目标**：让教师几乎不用动手——只用对话描述需求，看屏幕看到结果。
