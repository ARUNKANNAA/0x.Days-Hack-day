#include <esp_now.h>
#include <WiFi.h>

#define ledPin 4

int a;

void OnDataRecv(const esp_now_recv_info *info, const uint8_t *incomingData, int len) {
  memcpy(&a, incomingData, sizeof(a));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("a: ");
  Serial.println(a);

  if (a == LOW) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Nothing to do here
}
