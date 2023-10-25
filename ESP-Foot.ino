#include <esp_now.h>
#include <WiFi.h>
String data;
typedef struct arm {
  float pitch;
  float roll;
} arm;
arm data1;
#define BTN1 4
#define BTN2 33
#define BTN3 21
#define BTN4 32
#define BTN5 34

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  data = "";
  memcpy(&data1, incomingData, sizeof(data1));
  data += data1.pitch;
  data += ";";
  data += data1.roll;
  data += ';';
  data += digitalRead(BTN1);
  data += ';';
  data += digitalRead(BTN2);
  data += ';';
  data += digitalRead(BTN3);
  data += ';';
  data += digitalRead(BTN4);
  data += ';';
  data += digitalRead(BTN5);
  data += ';';
  Serial.println(data);
}
 
void setup() {
  Serial.begin(115200);
  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);
  pinMode(BTN3, INPUT);
  pinMode(BTN4, INPUT);
  pinMode(BTN5, INPUT);
  
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {

}
