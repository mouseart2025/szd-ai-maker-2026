# 需求文档：LED 闪烁测试

## 项目名称
LED Blink 环境验证

## 一句话描述
验证 XIAO ESP32S3 的 PlatformIO 开发环境是否正常工作。

## 功能需求

### 功能 1：LED 闪烁
- **输出**：Grove LED 模块（连接在 D0 端口）
- **逻辑**：LED 每隔 500 毫秒切换一次亮灭状态
- **调试**：串口每次切换时输出 "LED ON" 或 "LED OFF"

## 硬件连接
- XIAO ESP32S3 Sense 通过 Grove Base 扩展板连接
- Grove LED 模块接在 D0 端口
- USB-C 连接电脑

## 技术要求
- 使用 PlatformIO + Arduino 框架
- 串口波特率 115200
