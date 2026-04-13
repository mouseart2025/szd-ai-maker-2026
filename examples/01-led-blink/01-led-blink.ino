/**
 * 示例 01：板载 LED 闪烁
 *
 * 硬件：XIAO ESP32S3 Sense 板载 LED (LED_BUILTIN = GPIO21)
 * 功能：板载小黄色 LED 每 500ms 闪烁一次, 验证开发环境
 *
 * 注意：XIAO 板载 LED 是反逻辑——LOW 点亮, HIGH 熄灭。
 */

void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.println("LED Blink 示例启动");
}

void loop() {
    digitalWrite(LED_BUILTIN, LOW);   // 反逻辑：LOW 点亮
    Serial.println("LED: ON");
    delay(500);

    digitalWrite(LED_BUILTIN, HIGH);  // HIGH 熄灭
    Serial.println("LED: OFF");
    delay(500);
}
