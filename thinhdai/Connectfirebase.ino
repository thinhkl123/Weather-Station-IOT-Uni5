#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

#define RX_PIN 4   // D2 (GPIO4)
#define TX_PIN 5   // D1 (GPIO5)

FirebaseESP8266 firebase("https://weather-station-iot-ded0e-default-rtdb.asia-southeast1.firebasedatabase.app/");
bool firebaseConnected = false;

SoftwareSerial mySerial(RX_PIN, TX_PIN); // RX, TX

unsigned long lastTime = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin("Akine", "2606104"); //Rename SSID and Password
  while (WiFi.status() != WL_CONNECTED) delay(500);

  firebaseConnected = true;
}

void loop() {

  //Đọc dữ liệu từ arduino
  if (mySerial.available()) {
      String input = mySerial.readStringUntil('\n');
      input.trim();  
      
      int h = -1, c = -1, m = -1;
      String r = "N";
      String f = "N";

      int hIndex = input.indexOf("H:");
      int cIndex = input.indexOf("C:");
      int rIndex = input.indexOf("R:");
      int mIndex = input.indexOf("M:");
      int fIndex = input.indexOf("F:");

      if (hIndex >= 0) h = input.substring(hIndex + 2, input.indexOf(",", hIndex)).toInt();
      if (cIndex >= 0) c = input.substring(cIndex + 2, input.indexOf(",", cIndex)).toInt();
      if (rIndex >= 0) r = input.substring(rIndex + 2, input.indexOf(",", rIndex) == -1 ? input.length() : input.indexOf(",", rIndex));
      if (mIndex >= 0) m = input.substring(mIndex + 2).toInt();
      if (fIndex >= 0) f = input.substring(fIndex + 2, input.indexOf(",", fIndex) == -1 ? input.length() : input.indexOf(",", fIndex));

      Serial.println("Đã tách:");
      Serial.println("Humi: " + String(h));
      Serial.println("Temp: " + String(c));
      Serial.println("Rain: " + r);
      Serial.println("Moist: " + String(m));
      Serial.println("Firebase: " + String(f));

      firebase.setInt("iot/temperature", c);
      firebase.setInt("iot/humidity", h);
      firebase.setString("iot/rain", r);
      firebase.setInt("iot/moisture", m);
      if (f == "Y") {
        firebase.setString("iot/atof", "yes");
      } else {
        firebase.setString("iot/atof", "no");
      }
  }

  // if (millis() - lastTime >= 2000) {
  //   String pumpOn = firebase.getString("iot/ftoa");

  //   // Gửi lệnh điều khiển về Arduino
  //   if (pumpOn == "yes") {
  //     mySerial.println("FtoA:1");
  //     Serial.println("FtoA:1");
  //   } else {
  //     mySerial.println("FtoA:0");
  //     Serial.println("FtoA:0");
  //   }

  //   lastTime = millis();
  // }

}