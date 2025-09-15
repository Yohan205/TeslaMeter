#include "Fcn.h"

void setup() {
  /* Initialize connection to
  serial monitor with 9600 baud */
  Serial.begin(9600);
  // Set pin led as output
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  // Led turn off
  digitalWrite(led1, LOW); 
  digitalWrite(led2, LOW);
  Serial.println("Systems are ready!");
  // Initialize the LCD
  lcd.init();
  // Turn on background light of LCD
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("South -> Green");
  lcd.setCursor(0,1);
  lcd.print("North -> Blue");
  delay(1500);
  // Clean screen
  lcd.clear();
}


void loop() {
  // Get voltage from sensor
  float sensorHall = analogRead(A0);
  Serial.print("Sensor Hall: ");
  Serial.println(sensorHall);

  /* Call to voltage function
  and show the voltage */
  voltage(sensorHall);
  teslaMeter(sensorHall);

  // Waiting half second to repeat the loop
  delay(500);
}
