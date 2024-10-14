#include <Wire.h>
#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>

// LCD configuration
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Sensor pins
const int trigPin = 9;
const int echoPin = 8;
const int tempPin = A0;  // LM35 connected to A0
const int vibrationPin = 6;
const int ldrPin = A1;
const int accelPinX = A2;  // Accelerometer X-axis
const int accelPinY = A3;  // Accelerometer Y-axis
const int accelPinZ = A4;  // Accelerometer Z-axis

// WiFi configuration (replace with your network credentials)
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

void setup() {
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(vibrationPin, INPUT);
  pinMode(tempPin, INPUT);
  pinMode(ldrPin, INPUT);

  // Initialize Serial for debugging
  Serial.begin(9600);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

// Display welcome message on LCD
  lcd.print("Vehicle Monitor");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Measure distance using Ultrasonic Sensor
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

    // Read temperature from LM35
  int tempReading = analogRead(tempPin);
  float temperature = (tempReading * 5.0 / 1024.0) * 100;

  // Read vibration sensor value
  int vibrationValue = digitalRead(vibrationPin);

  // Read light level using LDR
  int lightLevel = analogRead(ldrPin);

  // Read accelerometer values
  int accelX = analogRead(accelPinX);
  int accelY = analogRead(accelPinY);
  int accelZ = analogRead(accelPinZ);

  // Display data on LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temperature);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Dist:");
  lcd.print(distance);
  lcd.print("cm");

  delay(2000);
  lcd.clear();

  // Check for potential issues
  if (temperature > 100) {
    lcd.print("Overheat Warning!");
    sendToTelegram("Overheat Warning: " + String(temperature) + "C");
  }

  if (vibrationValue == HIGH) {
    lcd.print("Vibration Detected");
    sendToTelegram("Vibration Detected");
  }

  if (distance < 10) {
    lcd.print("Obstacle Near!");
    sendToTelegram("Obstacle Detected: " + String(distance) + "cm");
  }

  delay(1000);
}

// Function to send data to Telegram
void sendToTelegram(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    String url = String("https://api.telegram.org/bot") + botToken + "/sendMessage?chat_id=" + chatId + "&text=" + message;

    client.begin(url);
    client.GET();
    client.stop();
  }
}
