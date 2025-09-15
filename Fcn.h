// Library LCD I2C
#include <LiquidCrystal_I2C.h>
// Set screen LCD to use 16x2 resolution
LiquidCrystal_I2C lcd(0x3f,16,2);


// Set pins LEDs
const int led2 = 5, led1 = 6;
//Setinterval iMax and iMin
float iMax = 532.0, iMin = 542.0;
// intercept with the Y axis (zero analog read)
float n = 537;

/* Convert the analog reading
  (which goes from 0 - 1023)
  to a voltage (0 - 5V): */
float toVolts(float data){
  data = data * 5 / 1023;
  return data;
}

/* Function to show the value volts in the LCD */
void voltage (float sHall){
  /* Convert the data analog to volts */
  float volts = toVolts(sHall);
  
  // Print out the value into lcd:
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Voltage:");
  lcd.setCursor(9,0);
  lcd.print(volts);
  lcd.setCursor(13, 0);
  lcd.print("v");
}

/* Show measure on the screen LCD */
void showMeasure(float field){
  lcd.setCursor(0,1);
  lcd.print("B:");
  lcd.setCursor(2,1);
  if (999 < abs(field)){
    lcd.print((field / 1000));
    lcd.setCursor(7, 1);
    lcd.print("T");
  } else {
    lcd.print(field);
    lcd.setCursor(9, 1);
    lcd.print("mT");
  }
}

/* Show shine from led on serial monitor */
void ledShine (int shine){
  Serial.print("Shine Led: ");
  Serial.println(shine);
}

/* Function to get value from
magnetic field to Tesla */
void teslaMeter(float sHall){
  int shineLed = 0;
  
  // Slope in Volt/Gauss
  float m = 1.4 * 10e-3; //mV/G -> V/G
  // Magnetic field on mT
  float B = ((toVolts(sHall - n))* (1000 / m)) / 1000; //10


  /* 
  Turn on led depending of near magnet.
  Interval when sHall is between iMin and 1023
  */
  if (sHall >= iMin && sHall <= 1023){
    /* Get value from sensor and
    rescale values to the led (0-255) */
    shineLed = map(sHall, iMin, 1023, 1, 255);
    float MagField = map(sHall, iMin, 1023.0, 0.0, 1000.0) / 10; 
    // Print values on serial monitor
    //ledShine(shineLed);
    
    Serial.print(
      "South --> TeslaMeter [mT]: " 
      );
    Serial.println(B);
    //Serial.println((toVolts(sHall) - n) / (m));
    Serial.print("MagField: ");
    Serial.println(MagField);
    //Set shine into led
    analogWrite(led1, shineLed);
    //Show the value in mT on lcd
    showMeasure(B);
  } else {
    digitalWrite(led1, LOW);
  }

  //Interval when sHall is between 0 and iMax
  if (sHall >= 0 && sHall <= iMax){
    shineLed = map(sHall, 0, iMax, 255, 1); 
    // Print values on serial monitor
    //ledShine(shineLed);
    Serial.print(
      "North --> TeslaMeter [mT]: "
      );
    Serial.println(B);
    
    //Set shine into led
    analogWrite(led2, shineLed);
    //Show the value in Teslas or mT on lcd
    showMeasure(B);
  } else {
    digitalWrite(led2, 0);
  }
}
