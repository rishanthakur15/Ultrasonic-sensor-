// Includes the Servo and OLED libraries
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Display settings
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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
  myServo.attach(12); // Defines on which pin is the servo motor attached

  // Initialize the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C is the standard I2C address for 128x64 OLEDs
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  // rotates the servo motor from 15 to 165 degrees
  for(int i=15; i<=165; i++){  
    myServo.write(i);
    delay(30);
    distance = calculateDistance(); 
    
    Serial.print(i); 
    Serial.print(","); 
    Serial.print(distance); 
    Serial.print("."); 
    
    updateDisplay(i, distance); // Update the OLED screen
  }
  
  // Repeats the previous lines from 165 to 15 degrees
  for(int i=165; i>15; i--){  
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
    
    updateDisplay(i, distance); // Update the OLED screen
  }
}

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2;
  return distance;
}

// Function to display values on the OLED screen
void updateDisplay(int currentAngle, int currentDistance) {
  display.clearDisplay();
  
  display.setTextSize(2);             // Set text size
  display.setTextColor(SSD1306_WHITE); // Set text color
  
  // Print Angle
  display.setCursor(0, 10);           
  display.print("Angle: ");
  display.print(currentAngle);
  
  // Print Distance
  display.setCursor(0, 40);           
  display.print("Dist:  ");
  display.print(currentDistance);
  display.print("cm");

  display.display();           // Push the data to the screen
}
