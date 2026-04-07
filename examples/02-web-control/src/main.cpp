/**
 * 示例 02：WiFi Web 控制 LED + 风扇
 *
 * 硬件：XIAO ESP32S3 Sense + Grove Base + Grove LED (D0) + Grove Fan (D1)
 * 功能：XIAO 作为 WiFi 热点，手机连接后通过网页控制 LED 和风扇
 *
 * 使用方式：
 *   1. 上传程序
 *   2. 手机 WiFi 连接 "XIAO-Lab"（密码 12345678）
 *   3. 浏览器打开 192.168.4.1
 */

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const int LED_PIN = D0;
const int FAN_PIN = D1;
const char* ssid = "XIAO-Lab";
const char* password = "12345678";

WebServer server(80);
bool ledState = false;
bool fanState = false;

// HTML 页面（适配手机屏幕）
const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>XIAO Control</title>
  <style>
    body { font-family: Arial; text-align: center; margin: 20px; background: #1a1a2e; color: #fff; }
    h1 { color: #e94560; }
    .btn { display: inline-block; width: 200px; padding: 20px; margin: 10px;
           border: none; border-radius: 12px; font-size: 18px; color: #fff; cursor: pointer; }
    .led-on { background: #16c47f; }
    .led-off { background: #4a4a6a; }
    .fan-on { background: #0096c7; }
    .fan-off { background: #4a4a6a; }
    .status { font-size: 14px; color: #aaa; margin-top: 5px; }
  </style>
</head>
<body>
  <h1>XIAO Control Panel</h1>
  <p><a href="/led"><button class="btn %LED_CLASS%">LED: %LED_STATE%</button></a></p>
  <p><a href="/fan"><button class="btn %FAN_CLASS%">Fan: %FAN_STATE%</button></a></p>
  <p class="status">AI Generated - Vibe Coding Demo</p>
</body>
</html>
)rawliteral";

String getPage() {
    String page = String(htmlPage);
    page.replace("%LED_STATE%", ledState ? "ON" : "OFF");
    page.replace("%LED_CLASS%", ledState ? "led-on" : "led-off");
    page.replace("%FAN_STATE%", fanState ? "ON" : "OFF");
    page.replace("%FAN_CLASS%", fanState ? "fan-on" : "fan-off");
    return page;
}

void handleRoot() {
    server.send(200, "text/html", getPage());
}

void handleLed() {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    Serial.println(ledState ? "LED: ON" : "LED: OFF");
    server.sendHeader("Location", "/");
    server.send(303);
}

void handleFan() {
    fanState = !fanState;
    digitalWrite(FAN_PIN, fanState ? HIGH : LOW);
    Serial.println(fanState ? "Fan: ON" : "Fan: OFF");
    server.sendHeader("Location", "/");
    server.send(303);
}

void setup() {
    Serial.begin(115200);

    // 初始化 GPIO
    pinMode(LED_PIN, OUTPUT);
    pinMode(FAN_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    digitalWrite(FAN_PIN, LOW);

    // 启动 WiFi AP
    WiFi.softAP(ssid, password);
    Serial.println("=== XIAO Web Control ===");
    Serial.print("WiFi SSID: ");
    Serial.println(ssid);
    Serial.print("Password: ");
    Serial.println(password);
    Serial.print("Open browser: http://");
    Serial.println(WiFi.softAPIP());

    // 注册路由
    server.on("/", handleRoot);
    server.on("/led", handleLed);
    server.on("/fan", handleFan);
    server.begin();
    Serial.println("Server started!");
}

void loop() {
    server.handleClient();
}
