#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>

FirebaseESP8266 firebase("https://weather-station-iot-ded0e-default-rtdb.asia-southeast1.firebasedatabase.app/");
bool firebaseConnected = false;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin("TANG 3", "71duong12D"); //Rename SSID and Password
  while (WiFi.status() != WL_CONNECTED) delay(500);

  firebaseConnected = true;

  // delay(5000);
  firebase.setInt("weather/humidity", 90);
  firebase.setInt("weather/pressure", 2000);
  firebase.setInt("weather/rain", 5);
  firebase.setInt("weather/temperature", 100);

  // int data1 = firebase.getInt("weather/humidity");
  // Serial.print("Received humidity:\t");
  // Serial.println(data1);

  // int data2 = firebase.getInt("weather/pressure");
  // Serial.print("Received pressure:\t\t");
  // Serial.println(data2);

  // int data3 = firebase.getInt("weather/rain");
  // Serial.print("Received rain:\t\t");
  // Serial.println(data3);

  // int data4 = firebase.getInt("weather/temperature");
  // Serial.print("Received temperature:\t\t");
  // Serial.println(data4);
}

void loop() {
}