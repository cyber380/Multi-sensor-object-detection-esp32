#include <WiFi.h>
#include <HTTPClient.h>

//  WiFi credentials
const char* ssid = "Anushka's A36";
const char* password = "@nushka123";

//  Flask server
const char* serverName = "http://10.137.185.37:5000/data";

// IR sensor pins
const int ir1 = 2;
const int ir2 = 4;
const int ir3 = 5;

// Ultrasonic pins
const int trigPin = 19;
const int echoPin = 21;

// Buzzer
const int buzzer = 18;

// Distance threshold
const int threshold = 20;

bool objectDetected = false;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("System Started");

  // WiFi connect
  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.println(WiFi.localIP());

  // 🔥 FIX: Use INPUT_PULLUP for stable readings
  pinMode(ir1, INPUT_PULLUP);
  pinMode(ir2, INPUT_PULLUP);
  pinMode(ir3, INPUT_PULLUP);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(buzzer, OUTPUT);
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) return 999;

  return duration * 0.034 / 2;
}

void loop() {

  int irVal1 = digitalRead(ir1);
  int irVal2 = digitalRead(ir2);
  int irVal3 = digitalRead(ir3);

  long distance = getDistance();

  // Debug (VERY IMPORTANT)
  Serial.print("IR1: "); Serial.print(irVal1);
  Serial.print(" IR2: "); Serial.print(irVal2);
  Serial.print(" IR3: "); Serial.print(irVal3);
  Serial.print(" Distance: "); Serial.println(distance);

  // Correct logic (LOW = detected)
  bool ir1Detected = (irVal1 == LOW);
  bool ir2Detected = (irVal2 == LOW);
  bool ir3Detected = (irVal3 == LOW);
  bool ultraDetected = (distance < threshold);

  bool currentState = ir1Detected || ir2Detected || ir3Detected || ultraDetected;

  //  Buzzer logic
  if (currentState && !objectDetected) {
    Serial.print("Detected by: ");
    if (ir1Detected) Serial.print("IR1 ");
    if (ir2Detected) Serial.print("IR2 ");
    if (ir3Detected) Serial.print("IR3 ");
    if (ultraDetected) Serial.print("Ultrasonic ");
    Serial.println();

    digitalWrite(buzzer, HIGH);
    objectDetected = true;
  }

  else if (!currentState && objectDetected) {
    Serial.println("No object");
    digitalWrite(buzzer, LOW);
    objectDetected = false;
  }

  //  Send data to server
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    String json = "{";
    json += "\"ir1\":" + String(irVal1) + ",";
    json += "\"ir2\":" + String(irVal2) + ",";
    json += "\"ir3\":" + String(irVal3) + ",";
    json += "\"distance\":" + String(distance);
    json += "}";

    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    int response = http.POST(json);

    Serial.print("Server Response: ");
    Serial.println(response);

    http.end();
  }

  delay(2000);
}
