#define RAIN_SENSOR_ANALOG A0

void setup() {
  Serial.begin(9600);
}

void loop() {
  int rainValue = analogRead(RAIN_SENSOR_ANALOG);
  Serial.print("Giá trị cảm biến mưa (AO): ");
  Serial.println(rainValue);

  if (rainValue < 400) {
    Serial.println("🌧️  Mưa lớn!");
  } else if (rainValue < 800) {
    Serial.println("🌧  Mưa nhẹ");
  } else {
    Serial.println("☀️  Không mưa");
  }

  delay(1000);
}