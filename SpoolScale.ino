#include "HX711.h" //https://github.com/bogde/HX711
#include "LiquidCrystal.h"

// Configuration
int inPin = 7; // Button pin
float Onemm_weight = 3.0; // Average weight per 1.75 mm filament meter
float Threemm_weight = 8.0; // Average weight per 3mm filament meter
float spoolWeight = 225; // Average weight of spool

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int backLight = 9;    // LCD pin 13 will control the backlight

// HX711.DOUT	- pin #A2
// HX711.PD_SCK	- pin #A3

HX711 scale(A2, A3);		// parameter "gain" is ommited; the default value 128 is used by the library
int val = 0; // variable for reading the pin
int incoming = 0;
float weight = 0.0;
int showWeight = 0;
int fMeters = 0;
float weight_div = Onemm_weight;

void setup() {
  Serial.begin(38400);
  pinMode(inPin, INPUT); // declare pushbutton
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH); // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
  Serial.println("Spool Scale");
  // set up the LCD's number of columns and rows: 
  lcd.begin(20,4);
  
  // Print a message to the LCD.
  lcd.setCursor(4,0);
  lcd.print("Spool Scale");
  lcd.setCursor(9,1);
  lcd.print("By");
  lcd.setCursor(4,2);
  lcd.print("Robert Haddad");
  delay(3000);
  lcd.clear();
  scale.set_scale(432); // Set this to empty scale.set_scale() for calibration
  scale.tare();
  checkFil();
}  

void checkFil(){
  lcd.setCursor(0,0);
  lcd.print("Are you using 3mm");
  lcd.setCursor(0,1);
  lcd.print("Filament? Hold Tare");
  lcd.setCursor(0,2);
  lcd.print("for YES");
  lcd.setCursor(0,3);
  boolean tarePressed = false;
  int countdown = 10;
  while (!tarePressed && countdown >= 0){
    val = digitalRead(inPin);
    if(val == HIGH){
      lcd.clear();
      lcd.setCursor(0,2);
      lcd.print("Filament set to 3mm");
      delay(1000);
      tarePressed = true;
      weight_div = Threemm_weight;
      lcd.clear();
    }
    lcd.setCursor(0,3);
    lcd.print("Countdown:   ");
    lcd.setCursor(0,3);
    lcd.print("Countdown: ");
    lcd.print(countdown);
    countdown--;
    if(countdown <0){
      lcd.clear();
      lcd.setCursor(0,0);
    }
    if(tarePressed){
      lcd.clear();
      lcd.setCursor(0,0);
    }
    delay(1000);
  }
}
    
void loop() {
  val = digitalRead(inPin); // read input value
  if(val == HIGH) {
    lcd.setCursor(7,2);
    lcd.print("Taring");
    delay(500);
    scale.tare();
    lcd.clear();
  }
  lcd.setCursor(0,0);
  weight = scale.get_units(20);
  Serial.println(weight);
  showWeight = weight;
  lcd.print("                   ");
  lcd.setCursor(0,0);
  lcd.print("Weight~ ");
  lcd.print(showWeight);
  lcd.print(" g");
  lcd.setCursor(0,1);
  lcd.print("                   ");
  lcd.setCursor(0,1);
  lcd.print("Fil. Left~ ");
  fMeters = ((showWeight-spoolWeight)/weight_div);
  lcd.print(fMeters);
  lcd.print(" m");
  if(fMeters <= 2){
    lcd.setCursor(1,3);
    lcd.print("* Change Filament!");
  } else {
    lcd.setCursor(1,3);
    lcd.print("                   ");
  }
}
