#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Ball properties
int ballX = 32;
int ballY = 32;
int ballSpeedX = 2;
int ballSpeedY = 2;
int ballRadius = 5;

void setup() 
{
  Wire.begin(14, 12); // SDA, SCL pins for ESP8266
  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;);
  }
  
  display.clearDisplay();
}

void loop() 
{
  display.clearDisplay(); // 1. Clear the frame

  // 2. Draw the figure (a filled circle)
  display.fillCircle(ballX, ballY, ballRadius, SSD1306_WHITE);

  // 3. Push to screen
  display.display();

  // 4. Logic: Update position for the next frame
  ballX += ballSpeedX;
  ballY += ballSpeedY;

  // Bounce logic for walls
  if(ballX + ballRadius >= SCREEN_WIDTH || ballX - ballRadius <= 0) {
    ballSpeedX = -ballSpeedX; 
  }
  if(ballY + ballRadius >= SCREEN_HEIGHT || ballY - ballRadius <= 0) {
    ballSpeedY = -ballSpeedY;
  }

  delay(10); // Adjust for speed
}