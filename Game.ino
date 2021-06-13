#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD


LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4); // Change to (0x27,20,4) for 20x4 LCD.
int xdata;
int ydata;
int xmap;
int ymap;

int appleh = 15;
int applev = 2;

int snakelength;

int direct = 0;


int snakever[79];
int snakehor[79];
int snakeheadH = 3;
int snakeheadV = 2;


int score = 0;

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  lcd.init();
  lcd.backlight();

  snakever[0] = 2;
  snakehor[0] = 2;

  snakelength = 1;
}
void loop() {

  snakemove();
  xdata = analogRead(A0);
  ydata = analogRead(A1);

  xmap = map(xdata, 0, 1023, 0, 255);
  ymap = map(ydata, 0 , 1023, 0, 255);

  if (xmap < 90) {
    snakeheadV++;
  }
  else if (xmap > 170) {
    snakeheadV--;
  }
  else if (ymap > 150) {
    snakeheadH++;
  }
  else if (ymap < 90) {
    snakeheadH--;
  }

  if (snakeheadH < 0 || snakeheadH > 19 || snakeheadV < 0 || snakeheadV > 3) {
    lcd.clear();
    while (1 == 1) {
      lcd.setCursor(2, 1);
      lcd.print("YOU SUCK ASS");
    }
  }
  snakeapple();
  printapple();
  printsnake();


  delay(250);

  lcd.clear();
}


void printapple() {
  lcd.setCursor(appleh, applev);
  lcd.print("#");

  lcd.setCursor(0, 0);
  lcd.print(score);
}

void snakeapple() {
  if (snakeheadH == appleh && snakeheadV == applev) {
    appleh = random(2, 20);
    applev = random(1, 4);
    score++;
    snakelength++;
  }
}

void printsnake() {
  lcd.setCursor(snakeheadH, snakeheadV);

  lcd.print("-");
  for (int i = 0; i < snakelength; i++) {
    lcd.setCursor(snakehor[i], snakever[i]);

    lcd.print("-");


  }
}

void snakemove() {
  snakehor[0] = snakeheadH;
  snakever[0] = snakeheadV;
  for (int i = snakelength; 0 < i; i--) {
    int x = i - 1;
    snakehor[i] = snakehor[x];
    snakever[i] = snakever[x];
  }
}
