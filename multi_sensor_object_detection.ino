#include <WiFi.h>

// Your hotspot credentials
const char* ssid = "hi";
const char* password = "9437265232";

// IR sensor pins
const int ir1 = 2;
const int ir2 = 4;
const int ir3 = 5;

// Ultrasonic sensor pins
const int trigPin = 19;
const int echoPin = 21;

// Buzzer pin
const int buzzer = 18;

// Distance threshold
const int threshold = 20;

// Previous state
bool objectDetected = false;

void setup() {
  Serial.begin(115200);
  delay(1000);  // Give time for Serial to start

  Serial.println("System Started");

  // WiFi connection with timeout
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  int timeout = 0;
  while (WiFi.status() != WL_CONNECTED && timeout < 20) {
    delay(500);
    Serial.print(".");
    timeout++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi Failed! Continuing without WiFi...");
  }

  // Sensor setup
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);

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

  bool ir1Detected = (irVal1 == LOW);
  bool ir2Detected = (irVal2 == LOW);
  bool ir3Detected = (irVal3 == LOW);
  bool ultraDetected = (distance < threshold);

  bool currentState = ir1Detected || ir2Detected || ir3Detected || ultraDetected;

  if (currentState && !objectDetected) {

    Serial.print("Object detected by: ");

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

  delay(100);
}