#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200); 
  dht.begin();
  delay(2000);
}

void loop() {
  float suhu = dht.readTemperature();
  float kelembaban = dht.readHumidity();

  if (isnan(suhu) || isnan(kelembaban)) {
    Serial.println("Gagal membaca data dari sensor DHT11!");
  } else {
    Serial.print("Suhu: ");
    Serial.print(suhu);
    Serial.print(" °C | Kelembaban: ");
    Serial.print(kelembaban);
    Serial.println(" %");
  }
  delay(2000);
}