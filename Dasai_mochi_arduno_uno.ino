#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define EYE_RADIUS 18
#define PUPIL_RADIUS 4
#define LEFT_EYE_X 40
#define RIGHT_EYE_X 88
#define EYE_Y 24 // Mắt cao lên

void drawArc(int x0, int y0, int r, int start_angle, int end_angle) {
  for (int i = start_angle; i <= end_angle; i += 2) {
    float rad = i * 3.1415926 / 180.0;
    int x = x0 + r * cos(rad);
    int y = y0 + r * sin(rad);
    display.drawPixel(x, y, SSD1306_WHITE);
  }
}
void drawEye(int eyeX, int eyeY, int pupilOffsetX, int pupilOffsetY, bool closed=false, bool spiral=false) {
  if (closed) {
    display.drawLine(eyeX - EYE_RADIUS + 2, eyeY, eyeX + EYE_RADIUS - 2, eyeY, SSD1306_WHITE);
  } else if (spiral) {
    for (int r = 3; r < EYE_RADIUS - 2; r += 3) {
      float a = (r % 2 == 0) ? 3.1415926/3 : 0;
      for (float theta = 0; theta < 6.3; theta += 0.3) {
        int x = eyeX + (r) * cos(theta+a);
        int y = eyeY + (r) * sin(theta+a);
        display.drawPixel(x, y, SSD1306_WHITE);
      }
    }
  } else {
    display.drawCircle(eyeX, eyeY, EYE_RADIUS, SSD1306_WHITE);
    display.fillCircle(eyeX + pupilOffsetX, eyeY + pupilOffsetY, PUPIL_RADIUS, SSD1306_WHITE);
  }
}
void drawSmile(bool up) {
  if (up)
    drawArc((LEFT_EYE_X + RIGHT_EYE_X) / 2, EYE_Y + 22, 18, 20, 160);
  else
    drawArc((LEFT_EYE_X + RIGHT_EYE_X) / 2, EYE_Y + 32, 18, 200, 340);
}
void drawSadMouth() {
  for (int x = -15; x <= 15; x++) {
    int y = 4 + (x * x) / 30;
    display.drawPixel((LEFT_EYE_X + RIGHT_EYE_X)/2 + x, EYE_Y + 34 + y, SSD1306_WHITE);
  }
}
void drawFlatMouth() {
  display.drawLine((LEFT_EYE_X + RIGHT_EYE_X)/2 - 10, EYE_Y + 32, (LEFT_EYE_X + RIGHT_EYE_X)/2 + 10, EYE_Y + 32, SSD1306_WHITE);
}
void drawMouthO() {
  display.drawCircle((LEFT_EYE_X + RIGHT_EYE_X)/2, EYE_Y + 28, 7, SSD1306_WHITE);
}
void drawAngryEyebrows() {
  display.drawLine(LEFT_EYE_X - 15, EYE_Y - 20, LEFT_EYE_X + 5, EYE_Y - 10, SSD1306_WHITE);
  display.drawLine(RIGHT_EYE_X - 5, EYE_Y - 10, RIGHT_EYE_X + 15, EYE_Y - 20, SSD1306_WHITE);
}
void drawTongue(int x0, int y0) {
  display.fillCircle(x0, y0, 6, SSD1306_WHITE);
  display.drawCircle(x0, y0, 6, SSD1306_WHITE);
  display.fillRect(x0 - 6, y0 - 6, 12, 4, SSD1306_BLACK);
}
void drawHeart(int x, int y, int size=3) {
  display.fillCircle(x - size, y, size, SSD1306_WHITE);
  display.fillCircle(x + size, y, size, SSD1306_WHITE);
  display.fillTriangle(x - size*2, y, x + size*2, y, x, y + size*2, SSD1306_WHITE);
}
void drawMask(int x0, int y0) {
  display.fillRect(x0 - 20, y0 + 14, 40, 16, SSD1306_WHITE);
  display.drawRect(x0 - 20, y0 + 14, 40, 16, SSD1306_BLACK);
  display.drawLine(x0 - 20, y0 + 14, x0 - 32, y0 + 22, SSD1306_WHITE);
  display.drawLine(x0 + 20, y0 + 14, x0 + 32, y0 + 22, SSD1306_WHITE);
  display.drawLine(x0 - 16, y0 + 21, x0 + 16, y0 + 21, SSD1306_BLACK);
  display.drawLine(x0 - 16, y0 + 26, x0 + 16, y0 + 26, SSD1306_BLACK);
}
void drawThermometer(int x0, int y0) {
  for (int i = 0; i < 7; i++) {
    display.drawPixel(x0 + 21 + i, y0 + 29 + i, SSD1306_WHITE);
  }
  display.fillCircle(x0 + 27, y0 + 35, 3, SSD1306_WHITE);
}
void drawSweat(int x, int y) {
  display.fillCircle(x, y, 2, SSD1306_WHITE);
}
void drawSurpriseLines() {
  for (int i = -10; i <= 10; i += 10) {
    display.drawLine((LEFT_EYE_X + RIGHT_EYE_X)/2 + i, EYE_Y - 25, (LEFT_EYE_X + RIGHT_EYE_X)/2 + i, EYE_Y - 38, SSD1306_WHITE);
  }
}
void drawExclamation(int x, int y) {
  display.fillRect(x-2, y, 4, 14, SSD1306_WHITE);
  display.fillCircle(x, y+17, 3, SSD1306_WHITE);
}

// -- Animation mini cho cảm xúc chuyển cảnh --
void animateBlink(int delayTime = 80) {
  display.clearDisplay();
  drawEye(LEFT_EYE_X, EYE_Y, 0, 0, true);
  drawEye(RIGHT_EYE_X, EYE_Y, 0, 0, true);
  drawSmile(true);
  display.display();
  delay(delayTime);

  display.clearDisplay();
  drawEye(LEFT_EYE_X, EYE_Y, 0, 0);
  drawEye(RIGHT_EYE_X, EYE_Y, 0, 0);
  drawSmile(true);
  display.display();
  delay(100);
}
void animateWink() {
  display.clearDisplay();
  drawEye(LEFT_EYE_X, EYE_Y, 0, 0);
  drawEye(RIGHT_EYE_X, EYE_Y, 0, 0, true, true);
  drawSmile(true);
  display.display();
  delay(200);

  display.clearDisplay();
  drawEye(LEFT_EYE_X, EYE_Y, 0, 0);
  drawEye(RIGHT_EYE_X, EYE_Y, 0, 0);
  drawSmile(true);
  display.display();
  delay(200);
}
void animateLookLeft() {
  for (int offset = 0; offset >= -6; offset--) {
    display.clearDisplay();
    drawEye(LEFT_EYE_X, EYE_Y, offset, 0);
    drawEye(RIGHT_EYE_X, EYE_Y, offset, 0);
    drawSmile(true);
    display.display();
    delay(35);
  }
}
void animateLookRight() {
  for (int offset = -6; offset <= 6; offset++) {
    display.clearDisplay();
    drawEye(LEFT_EYE_X, EYE_Y, offset, 0);
    drawEye(RIGHT_EYE_X, EYE_Y, offset, 0);
    drawSmile(true);
    display.display();
    delay(35);
  }
}
void animateLookCenter() {
  for (int offset = 6; offset >= 0; offset--) {
    display.clearDisplay();
    drawEye(LEFT_EYE_X, EYE_Y, offset, 0);
    drawEye(RIGHT_EYE_X, EYE_Y, offset, 0);
    drawSmile(true);
    display.display();
    delay(35);
  }
}

// -- Bộ hiệu ứng "playlist" chỉ còn mỗi mood đúng 1 lần --
//mặt cười kèm hiệu ứng.
void effectHappyAnimated(int repeat = 8) {
  for (int i = 0; i < repeat; i++) {
    int action = random(0, 6); // Đổi số ở đây sẽ random thêm nhiều hiệu ứng hơn tuỳ bạn
    display.clearDisplay();
    if (action == 0) { // Nhìn thẳng
      drawEye(LEFT_EYE_X, EYE_Y, 0, 0);
      drawEye(RIGHT_EYE_X, EYE_Y, 0, 0);
    } else if (action == 1) { // Đảo trái
      drawEye(LEFT_EYE_X, EYE_Y, -6, 0);
      drawEye(RIGHT_EYE_X, EYE_Y, -6, 0);
    } else if (action == 2) { // Đảo phải
      drawEye(LEFT_EYE_X, EYE_Y, 6, 0);
      drawEye(RIGHT_EYE_X, EYE_Y, 6, 0);
    } else if (action == 3) { // Wink phải
      drawEye(LEFT_EYE_X, EYE_Y, 0, 0);
      drawEye(RIGHT_EYE_X, EYE_Y, 0, 0, true);
    } else if (action == 4) { // Wink trái
      drawEye(LEFT_EYE_X, EYE_Y, 0, 0, true);
      drawEye(RIGHT_EYE_X, EYE_Y, 0, 0);
    } else { // Chớp cả hai
      drawEye(LEFT_EYE_X, EYE_Y, 0, 0, true);
      drawEye(RIGHT_EYE_X, EYE_Y, 0, 0, true);
    }
    drawSmile(true);
    display.display();
    delay(random(120, 320));
  }
  // Kết thúc mặt cười tươi
  display.clearDisplay();
  drawEye(LEFT_EYE_X, EYE_Y, 0, 0);
  drawEye(RIGHT_EYE_X, EYE_Y, 0, 0);
  drawSmile(true);
  display.display();
  delay(400);
}

void effectSad() {
  display.clearDisplay();
  drawEye(LEFT_EYE_X, EYE_Y, 0, 4);
  drawEye(RIGHT_EYE_X, EYE_Y, 0, 4);
  drawSadMouth();
  display.display();
  delay(700);
}
void effectAngry() {
  display.clearDisplay();
  drawEye(LEFT_EYE_X, EYE_Y, -4, -2);
  drawEye(RIGHT_EYE_X, EYE_Y, 4, -2);
  drawAngryEyebrows();
  drawSadMouth();
  display.display();
  delay(700);
}
void effectCry(int times=4) {
  int tearLength = 26;
  int startY = EYE_Y + 8;
  int endY = EYE_Y + tearLength;
  int frameDelay = 80;
  int blinkRate = 8;
  for (int round = 0; round < times; round++) {
    bool eyesClosed = false;
    for (int y = startY, frame = 0; y <= endY; y += 2, frame++) {
      display.clearDisplay();
      if (frame % blinkRate == 0) {
        eyesClosed = random(0, 2) == 0;
      }
      if (!eyesClosed) {
        drawEye(LEFT_EYE_X, EYE_Y, 0, 4);
        drawEye(RIGHT_EYE_X, EYE_Y, 0, 4);
      } else {
        drawEye(LEFT_EYE_X, EYE_Y, 0, 0, true);
        drawEye(RIGHT_EYE_X, EYE_Y, 0, 0, true);
      }
      drawSadMouth();
      int tearOffset = random(-1, 2);
      display.fillCircle(LEFT_EYE_X + tearOffset, y, 3, SSD1306_WHITE);
      display.fillCircle(RIGHT_EYE_X - tearOffset, y, 3, SSD1306_WHITE);
      if (y == endY) {
        display.fillCircle(LEFT_EYE_X + tearOffset, y + 6, 2, SSD1306_WHITE);
        display.fillCircle(RIGHT_EYE_X - tearOffset, y + 6, 2, SSD1306_WHITE);
      }
      display.display();
      delay(frameDelay);
    }
    delay(150);
  }
  display.clearDisplay();
  drawEye(LEFT_EYE_X, EYE_Y, 0, 0, true);
  drawEye(RIGHT_EYE_X, EYE_Y, 0, 0, true);
  drawSadMouth();
  display.display();
  delay(600);
}
void effectSurprise() {
  display.clearDisplay();
  drawEye(LEFT_EYE_X, EYE_Y, 0, -6);
  drawEye(RIGHT_EYE_X, EYE_Y, 0, -6);
  drawMouthO();
  drawSurpriseLines();
  display.display();
  delay(900);
}
void effectSleep(int cycles = 2) {
  for (int i = 0; i < cycles; i++) {
    display.clearDisplay();
    drawEye(LEFT_EYE_X, EYE_Y, 0, 0, true);
    drawEye(RIGHT_EYE_X, EYE_Y, 0, 0, true);
    drawSmile(true);
    for (int b = 0; b < 8; b += 2) {
      display.fillCircle(RIGHT_EYE_X + 15, EYE_Y - 8 - b, b / 2, SSD1306_WHITE);
      display.display();
      delay(120);
      display.fillCircle(RIGHT_EYE_X + 15, EYE_Y - 8 - b, b / 2, SSD1306_BLACK);
    }
    delay(120);
  }
  display.clearDisplay();
  drawEye(LEFT_EYE_X, EYE_Y, 0, 0, true);
  drawEye(RIGHT_EYE_X, EYE_Y, 0, 0, true);
  drawSmile(true);
  display.display();
  delay(600);
}
void effectSpiral(int cycles=10) {
  for (int i = 0; i < cycles; i++) {
    display.clearDisplay();
    drawEye(LEFT_EYE_X, EYE_Y, 0, 0, false, true);
    drawEye(RIGHT_EYE_X, EYE_Y, 0, 0, false, true);
    drawFlatMouth();
    display.display();
    delay(100);
  }
  display.clearDisplay();
  drawEye(LEFT_EYE_X, EYE_Y, 0, 0, false, true);
  drawEye(RIGHT_EYE_X, EYE_Y, 0, 0, false, true);
  drawFlatMouth();
  display.display();
  delay(600);
}
void effectHeart(int cycles = 5) {
  for (int i = 0; i < cycles; i++) {
    display.clearDisplay();
    drawEye(LEFT_EYE_X, EYE_Y, 0, -1);
    drawEye(RIGHT_EYE_X, EYE_Y, 0, -1);
    drawSmile(true);
    drawHeart((LEFT_EYE_X + RIGHT_EYE_X)/2, EYE_Y + 18 - i*5, 3);
    display.display();
    delay(120);
  }
  display.clearDisplay();
  drawEye(LEFT_EYE_X, EYE_Y, 0, -1);
  drawEye(RIGHT_EYE_X, EYE_Y, 0, -1);
  drawSmile(true);
  drawHeart((LEFT_EYE_X + RIGHT_EYE_X)/2, EYE_Y - 6, 3);
  display.display();
  delay(700);
}
void effectTroll() {
  display.clearDisplay();
  drawEye(LEFT_EYE_X, EYE_Y, 6, 4);
  drawEye(RIGHT_EYE_X, EYE_Y, -6, 4);
  drawSmile(true);
  drawTongue((LEFT_EYE_X + RIGHT_EYE_X) / 2, EYE_Y + 34);
  display.display();
  delay(1000);
}
void effectShock() {
  display.clearDisplay();
  drawEye(LEFT_EYE_X, EYE_Y, 0, 0);
  drawEye(RIGHT_EYE_X, EYE_Y, 0, 0);
  drawFlatMouth();
  drawExclamation(SCREEN_WIDTH - 16, 8);
  display.display();
  delay(950);
}

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}

void loop() {
  effectHappyAnimated();  // Hiệu ứng vui vẻ
  animateBlink();         // Nháy mắt
  effectSad();            // Hiệu ứng buồn
  animateLookLeft();      // Nhìn sang trái
  delay(400);
  effectAngry();          // Hiệu ứng giận dữ
  animateWink();          // Nháy mắt một bên
  effectCry(8);           // Hiệu ứng khóc dữ lội số càng cao càng khóc nhiều
  
  effectSurprise();       // Hiệu ứng ngạc nhiên  
  effectSleep(2);         // Hiệu ứng ngủ
  effectSpiral(10);       // Hiệu ứng xoáy mắt
  effectHeart(5);         // Hiệu ứng trái tim
  effectTroll();          // Hiệu ứng troll
  effectShock();          // Hiệu ứng sốc
}
