#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

#define led_num 106//160
#define ws2812_pin 15
#define adc_pin A2
#define charge_detect 0
#define charge_status 22
#define charge_done 16

#define program_count 21  // ← 修改为 21 个模式

Adafruit_NeoPixel pixels(led_num, ws2812_pin, NEO_GRB + NEO_KHZ800);

unsigned int program ;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(charge_detect,INPUT);
  pinMode(charge_status,INPUT_PULLUP);
  pinMode(charge_done,INPUT_PULLUP);
  Serial.begin(115200);
  EEPROM.begin(256);
  pixels.begin();

  program = EEPROM.read(1);
  if (program >= program_count) program = 0;

  Serial.print("Program: ");
  Serial.println(program);

  EEPROM.write(1, (program + 1) % program_count);
  EEPROM.commit();

  switch (program) {
    case 0: program0(); break;
    case 1: program1(); break;
    case 2: program2(); break;
    case 3: program3(); break;
    case 4: program4(); break;
    case 5: program5(); break;
    case 6: program6(); break;
    case 7: program7(); break;
    case 8: program8(); break;
    case 9: program9(); break;
    case 10: program10(); break;
    case 11: program11(); break;
    case 12: program12(); break;
    case 13: program13(); break;
    case 14: program14(); break;
    case 15: program15(); break;
    case 16: program16(); break;
    case 17: program17(); break;
    case 18: program18(); break;
    case 19: program19(); break;
    case 20: program20(); break;
    default: program0(); break;
  }
}

void loop() {}
void setup1()
{
  delay(500);
}
void loop1()
{
  if (BOOTSEL)
  {
    delay(500);
    rp2040.reboot();
  }
    Serial.print("Program: ");
  Serial.println(program);
}
// ========== 原有灯效 ==========
// （保持不变）
// 红色呼吸
void program0() {
  while (1) {
    for (int i = 0; i < 255; i++) { setAll(pixels.Color(i, 0, 0)); delay(8); }
    for (int i = 254; i >= 0; i--) { setAll(pixels.Color(i, 0, 0)); delay(8); }
  }
}

// 绿色呼吸
void program1() {
  while (1) {
    for (int i = 0; i < 255; i++) { setAll(pixels.Color(0, i, 0)); delay(8); }
    for (int i = 254; i >= 0; i--) { setAll(pixels.Color(0, i, 0)); delay(8); }
  }
}

// 蓝色呼吸
void program2() {
  while (1) {
    for (int i = 0; i < 255; i++) { setAll(pixels.Color(0, 0, i)); delay(8); }
    for (int i = 254; i >= 0; i--) { setAll(pixels.Color(0, 0, i)); delay(8); }
  }
}

// 红色纯亮
void program3() { setAll(pixels.Color(255, 0, 0)); while (1) delay(1000); }
// 白光台灯
void program4() { setAll(pixels.Color(255, 255, 255)); while (1) delay(1000); }
// 暖黄光台灯
void program5() { setAll(pixels.Color(255, 180, 60)); while (1) delay(1000); }
// 彩虹流动
void program6() {
  int wait = 20;
  while (1) {
    for (int k = 0; k < 256; k++) {
      for (int i = 0; i < led_num; i++) {
        int color = (i + k) & 255;
        pixels.setPixelColor(i, Wheel(color));
      }
      pixels.show();
      delay(wait);
    }
  }
}
// 火焰
void program7() {
  while (1) {
    for (int i = 0; i < led_num; i++) {
      int flicker = random(120, 255);
      pixels.setPixelColor(i, pixels.Color(flicker, (int)(flicker * 0.36), 0));
    }
    pixels.show();
    delay(random(40, 80));
  }
}
// 刀光扫动
void program8() {
  while (1) {
    for (int i = 0; i < led_num; i++) {
      pixels.clear();
      pixels.setPixelColor(i, pixels.Color(255, 255, 255));
      pixels.show();
      delay(10);
    }
    for (int i = led_num - 1; i >= 0; i--) {
      pixels.clear();
      pixels.setPixelColor(i, pixels.Color(255, 255, 255));
      pixels.show();
      delay(10);
    }
  }
}
// 雷光闪烁
void program9() {
  while (1) {
    for (int i = 0; i < led_num; i++) {
      if (random(10) > 7)
        pixels.setPixelColor(i, pixels.Color(200, 200, 255));
      else
        pixels.setPixelColor(i, 0);
    }
    pixels.show();
    delay(random(40, 150));
  }
}
// 能量充能
void program10() {
  while (1) {
    for (int c = 0; c < 128; c++) {
      int center = led_num / 2;
      for (int i = 0; i < led_num; i++) {
        int dist = abs(i - center);
        int v = max(0, 255 - dist * 8);
        pixels.setPixelColor(i, pixels.Color(v / 2, 0, v));
      }
      pixels.show();
      delay(30);
    }
    delay(1000);
  }
}
// 战斗斩击
void program11() {
  while (1) {
    for (int i = 0; i < led_num; i++) {
      pixels.clear();
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      pixels.show();
      delay(3);
    }
    for (int j = 0; j < 3; j++) {
      setAll(pixels.Color(255, 255, 255)); delay(40);
      setAll(pixels.Color(255, 0, 0)); delay(40);
    }
    delay(500);
  }
}
// 蓝白渐变恢复
void program12() {
  while (1) {
    for (int i = 0; i < 255; i++) { setAll(pixels.Color(i / 4, i / 4, i)); delay(10); }
    for (int i = 254; i >= 0; i--) { setAll(pixels.Color(i / 4, i / 4, i)); delay(10); }
  }
}

// ========== 新增灯效 ==========

// 彩色呼吸
void program13() {
  uint8_t colors[][3] = {
    {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {128, 0, 255}
  };
  while (1) {
    for (int c = 0; c < 4; c++) {
      for (int i = 0; i < 255; i++) {
        setAll(pixels.Color(colors[c][0] * i / 255, colors[c][1] * i / 255, colors[c][2] * i / 255));
        delay(6);
      }
      for (int i = 254; i >= 0; i--) {
        setAll(pixels.Color(colors[c][0] * i / 255, colors[c][1] * i / 255, colors[c][2] * i / 255));
        delay(6);
      }
    }
  }
}

// 警戒模式（红蓝闪）
void program14() {
  while (1) {
    setAll(pixels.Color(255, 0, 0)); delay(150);
    setAll(pixels.Color(0, 0, 255)); delay(150);
  }
}

// 能量脉冲
void program15() {
  while (1) {
    int center = led_num / 2;
    for (int r = 0; r < center; r++) {
      for (int i = 0; i < led_num; i++) {
        int dist = abs(i - center);
        int v = max(0, 255 - abs(dist - r) * 32);
        pixels.setPixelColor(i, pixels.Color(v / 3, v / 3, v));
      }
      pixels.show();
      delay(25);
    }
  }
}

// 流星雨
void program16() {
  while (1) {
    for (int i = 0; i < led_num; i++) {
      pixels.clear();
      for (int t = 0; t < 10; t++) {
        int idx = i - t;
        if (idx >= 0) {
          int b = 255 - t * 25;
          pixels.setPixelColor(idx, pixels.Color(b, b, b));
        }
      }
      pixels.show();
      delay(20);
    }
  }
}

// 等离子光波
void program17() {
  while (1) {
    for (int phase = 0; phase < 360; phase++) {
      for (int i = 0; i < led_num; i++) {
        int wave = (sin((i + phase) * 0.1) + 1) * 127;
        pixels.setPixelColor(i, pixels.Color(wave / 2, 0, wave));
      }
      pixels.show();
      delay(20);
    }
  }
}

// 心跳红光
void program18() {
  while (1) {
    setAll(pixels.Color(255, 0, 0)); delay(80);
    setAll(pixels.Color(60, 0, 0)); delay(80);
    setAll(pixels.Color(255, 0, 0)); delay(80);
    setAll(pixels.Color(0, 0, 0)); delay(600);
  }
}

// 日蚀模式（慢亮快灭）
void program19() {
  while (1) {
    for (int i = 0; i < 255; i++) { setAll(pixels.Color(i, i / 4, 0)); delay(10); }
    for (int i = 255; i >= 0; i--) { setAll(pixels.Color(i, i / 4, 0)); delay(3); }
    delay(400);
  }
}

// 圣光闪烁
void program20() {
  while (1) {
    for (int i = 0; i < led_num; i++) {
      int b = random(150, 255);
      pixels.setPixelColor(i, pixels.Color(b, b, b));
    }
    pixels.show();
    delay(random(50, 120));
  }
}

// ========== 辅助函数 ==========
void setAll(uint32_t color) {
  for (int j = 0; j < led_num; j++) pixels.setPixelColor(j, color);
  pixels.show();
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
