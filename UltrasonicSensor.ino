// Includes the Servo and OLED libraries
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h> // NEW: Added for Bluetooth

// OLED Display settings
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SoftwareSerial btSerial(2, 3); // RX, TX (connect to TX, RX of HC-05)

// Defines Trig and Echo pins of the Ultrasonic Sensor
const int trigPin = 10;
const int echoPin = 11;

// Variables for the duration and the distance
long duration;
int distance;
Servo myServo; // Creates a servo object for controlling the servo motor

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  btSerial.begin(9600); // Initialize Bluetooth serial communication
  myServo.attach(12); // Defines on which pin is the servo motor attached

  // Initialize the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  // Rotates the servo motor from 15 to 165 degrees
  for(int i = 15; i <= 165; i++){  
    myServo.write(i);
    delay(30);
    distance = calculateDistance(); 
    
    updateDisplay(i, distance); 
    sendBluetoothData(i, distance); // Handles both Serial and Bluetooth printing
  }
  
  // Rotates the servo motor from 165 to 15 degrees
  for(int i = 165; i > 15; i--){  
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    
    updateDisplay(i, distance); 
    sendBluetoothData(i, distance); // Handles both Serial and Bluetooth printing
  }
}

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH); 
  distance = duration * 0.034 / 2;
  return distance;
}

// Function to display values on the OLED screen
void updateDisplay(int currentAngle, int currentDistance) {
  display.clearDisplay();
  display.setTextSize(2);             
  display.setTextColor(SSD1306_WHITE); 
  
  // Print Angle
  display.setCursor(0, 10);           
  display.print("Angle: ");
  display.print(currentAngle);
  
  // Print Distance
  display.setCursor(0, 40);           
  display.print("Dist:  ");
  display.print(currentDistance);
  display.print("cm");

  display.display();           
}

// Function to send data over the HC-05 Bluetooth module & Serial Monitor
void sendBluetoothData(int currentAngle, int currentDistance) {
  Serial.print(currentAngle); 
  Serial.print(","); 
  Serial.print(currentDistance); 
  Serial.print("."); 
  
  btSerial.print(currentAngle); 
  btSerial.print(","); 
  btSerial.print(currentDistance); 
  btSerial.print("."); 
}
