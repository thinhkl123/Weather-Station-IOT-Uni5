#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>

FirebaseESP8266 firebase("https://weather-station-iot-ded0e-default-rtdb.asia-southeast1.firebasedatabase.app/");
bool firebaseConnected = false;

unsigned long lastTime = 0;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin("AKINE", "26061304"); //Rename SSID and Password
  while (WiFi.status() != WL_CONNECTED) delay(500);

  firebaseConnected = true;
}

void loop() {

  //Đọc dữ liệu từ arduino
  if (Serial.available()) {
      String line = Serial.readStringUntil('\n');
      line.trim();  

      if (line.startsWith("M:")) {
        int moisture = line.substring(2).toInt();
        firebase.setInt("iot/moisture", moisture);
      } else if (line.startsWith("H:")) {
        int humidity = line.substring(2).toInt();
        firebase.setInt("iot/humidity", humidity);
      } else if (line.startsWith("T:")) {
        int temp = line.substring(2).toInt();
        Firebase.setInt("iot/temperature", temp);
      } else if (line.startsWith("R:")) {
        char r = line.charAt(2);
        if (r == 'Y' || r == 'y') {
          Firebase.setString("iot/rain", "yes");
        } else {
          Firebase.setString("iot/rain", "no");
        }
      }
  }

  if (millis() - lastUpdate >= 100) {
    bool pumpOn = firebase.getBool("iot/ftoa");

    // Gửi lệnh điều khiển về Arduino
    if (pumpOn) {
      Serial.println("FtoA:1");
    } else {
      Serial.println("FtoA:0");
    }

    lastTime = millis();
  }

}







