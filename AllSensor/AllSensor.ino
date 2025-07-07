#include <dht11.h>

#define DHT11PIN 8
#define RAIN_SENSOR_ANALOG A0
#define SOIL_SENSOR_PIN A1

Adafruit_BMP085 bmp;

//Lopp để gửi dữ liệu do được từ sensor
unsigned long lastTime = 0;
  
void setup() {
  Serial.begin(9600);

  lastTime = millis() - 3000;
}
  
void loop() {

    if (Serial.available()) {
      String line = Serial.readStringUntil('\n');
      line.trim();

      if (line.startsWith("FtoA:")) {
        if (line.endsWith("1")) {
          digitalWrite(relayPin, HIGH);
          isPumping = true;
        } else if (line.endsWith("0")) {
          digitalWrite(relayPin, LOW);
          isPumping = false;
        }
      }
    }

    if (millis() - lastTime >= 3000) {
        //DHT11 do nhiet do va do am
        int chk = DHT11.read(DHT11PIN);

        Serial.print("H:");
        Serial.println(DHT11.humidity);

        Serial.print("C:");
        Serial.println(DHT11.temperature);

        //Xac dinh co mua hay khong
        int rainValue = analogRead(RAIN_SENSOR_ANALOG);
        //Serial.print("Giá trị cảm biến mưa (AO): ");
        //Serial.println(rainValue);

        // if (rainValue < 400) {
        //   Serial.println("🌧️  Mưa lớn!");
        // } else if (rainValue < 800) {
        //   Serial.println("🌧  Mưa nhẹ");
        // } else {
        //   Serial.println("☀️  Không mưa");
        // }
        if (rainValue < 800) {
          Serial.println("R:Y");
        } else {
          Serial.println("R:N");
        }

        //Do do am dat
        int soilValue = analogRead(SOIL_SENSOR_PIN);

        Serial.print("M:");
        Serial.println(soilValue);

        // if (soilValue < 300) {
        //   Serial.println(" → Đất rất ướt");
        // } else if (soilValue < 700) {
        //   Serial.println(" → Đất đủ ẩm");
        // } else {
        //   Serial.println(" → Đất khô, cần tưới nước!");
        // }

        lastTime = millis();
    }
}