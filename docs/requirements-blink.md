# 需求文档：LED 闪烁测试

## 项目名称
板载 LED Blink 环境验证

## 一句话描述
验证 XIAO ESP32S3 的开发环境是否正常工作（用板载 LED）。

## 功能需求

### 功能 1：板载 LED 闪烁
- **输出**：XIAO 板载 LED（`LED_BUILTIN` = GPIO21）
- **逻辑**：LED 每隔 500 毫秒切换一次亮灭状态
- **注意**：板载 LED 是**反逻辑**——`digitalWrite(LED_BUILTIN, LOW)` 点亮，`HIGH` 熄灭
- **调试**：串口每次切换时输出 "LED ON" 或 "LED OFF"

## 硬件连接
- XIAO ESP32S3 Sense 通过 USB-C 连接电脑
- **不需要任何外接 Grove 模块**——板载 LED 在 XIAO 主板上（一颗小黄色 LED）

## 技术要求
- 使用 Arduino 框架 + arduino-cli 编译上传
- 串口波特率 115200
- 项目结构为独立文件夹，包含一个 `.ino` 文件（文件名与文件夹名一致）
