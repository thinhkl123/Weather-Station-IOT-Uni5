#define SOIL_SENSOR_PIN A1   // Cảm biến gắn vào chân analog A1

void setup() {
  Serial.begin(9600);
  Serial.println("🚜 Bắt đầu đọc cảm biến độ ẩm đất...");
}

void loop() {
  int soilValue = analogRead(SOIL_SENSOR_PIN);

  Serial.print("🌱 Giá trị độ ẩm đất: ");
  Serial.print(soilValue);

  // Tùy chỉnh theo cảm biến thực tế của bạn
  if (soilValue < 300) {
    Serial.println(" → Đất rất ướt");
  } else if (soilValue < 700) {
    Serial.println(" → Đất đủ ẩm");
  } else {
    Serial.println(" → Đất khô, cần tưới nước!");
  }

  delay(1000);  // Đọc mỗi giây
}
