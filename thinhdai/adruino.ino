#include <SoftwareSerial.h>
#include <dht11.h>

#define RX_PIN 10
#define TX_PIN 11

#define DHT11PIN 8
#define RAIN_SENSOR_ANALOG A0
#define SOIL_SENSOR_PIN A1

#define RELAY_PIN 7
#define BUTTON 6

SoftwareSerial espSerial(RX_PIN, TX_PIN); 
dht11 DHT11;

//Lopp để gửi dữ liệu do được từ sensor
unsigned long lastTime = 0;

bool isPumping = false;
bool isCancel = false;

bool lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
  
void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);        // Giao tiếp ESP

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON, INPUT);

  digitalWrite(RELAY_PIN, HIGH); //Ban dau tat may bom

  lastTime = millis() - 3000;
}
  
void loop() {

    // if (espSerial.available()) {
    //   String line = espSerial.readStringUntil('\n');
    //   //Serial.println(line);
    //   if (line.startsWith("FtoA:")) {
    //     if (line.endsWith("1")) {
    //       digitalWrite(RELAY_PIN, LOW); //Bat may bom
    //       Serial.println("Turn On");
    //       isPumping = true;
    //     } else if (line.endsWith("0")) {
    //       digitalWrite(RELAY_PIN, HIGH); //Tat may bom
    //       Serial.println("Turn Off");
    //       isPumping = false;
    //     }
    //   }
    // }

    // int reading = digitalRead(BUTTON);

    // Serial.println(reading);

    // if (reading != lastButtonState) {
    //     lastDebounceTime = millis();
    // }

    // if ((millis() - lastDebounceTime) > debounceDelay) {
    //     if (reading == LOW && lastButtonState == HIGH) {
    //         // Đã nhấn nút
    //         Serial.println("Press button");
    //         isPumping = !isPumping;
    //         //digitalWrite(RELAY_PIN, isPumping ? LOW : HIGH);
    //     }
    // }

    // lastButtonState = reading;

    if (digitalRead(BUTTON) == HIGH) {
      delay(150);
      if (digitalRead(BUTTON) == HIGH) {
        Serial.println("Press button");
        isPumping = !isPumping;
        if (isPumping) {
            digitalWrite(RELAY_PIN, LOW); //Bat may bom
            Serial.println("Turn On");
            isCancel = false;
        } else {
           digitalWrite(RELAY_PIN, HIGH); //Tat may bom
            Serial.println("Turn Off");
            isCancel = true;
        }
      }
    }

    if (millis() - lastTime >= 3000) {
        //DHT11 do nhiet do va do am
        int chk = DHT11.read(DHT11PIN);

        //Serial.print("H:");
        //Serial.println(DHT11.humidity);

        //Serial.print("C:");
        //Serial.println(DHT11.temperature);

        int temp = DHT11.temperature;
        int humi = DHT11.humidity;


        //Xac dinh co mua hay khong
        int rainValue = analogRead(RAIN_SENSOR_ANALOG);
        String isRaining = "Y";

        //Serial.println(rainValue);
        if (rainValue < 800) {
          //Serial.println("RainY: " + rainValue);
          isRaining = "Y";
        } else {
          //Serial.println("RainN: " + rainValue);
          isRaining = "N";
        }

        //Do do am dat
        int soilValue = analogRead(SOIL_SENSOR_PIN);

        //Serial.print("M:");
        //Serial.println(soilValue);

        String isPump = "N";

        if (soilValue > 300 && !isCancel) {
          digitalWrite(RELAY_PIN, LOW); //Bat may bom
          Serial.println("Turn On");
          isPumping = true;
          isPump = "Y";
        } else if (soilValue <= 300) {
          digitalWrite(RELAY_PIN, HIGH); //Tat may bom
          Serial.println("Turn Off");
          isPumping = false;
          isPump = "N";
        }

        // Tạo chuỗi theo định dạng yêu cầu
        String payload = "H:" + String(humi) +
                     ",C:" + String(temp) +
                     ",R:" + isRaining +
                     ",M:" + String(soilValue) +
                     ",F:" + isPump;

        Serial.println(payload);

        espSerial.println(payload);

        lastTime = millis();
    }
}