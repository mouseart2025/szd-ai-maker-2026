/**
 * 示例 01：Grove LED 闪烁
 *
 * 硬件：XIAO ESP32S3 Sense + Grove Base + Grove LED (D0)
 * 功能：LED 每 500ms 闪烁一次，验证开发环境
 */


const int LED_PIN = D0;  // Grove LED 接在 D0 端口

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    Serial.println("LED Blink 示例启动");
}

void loop() {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED: ON");
    delay(500);

    digitalWrite(LED_PIN, LOW);
    Serial.println("LED: OFF");
    delay(500);
}
