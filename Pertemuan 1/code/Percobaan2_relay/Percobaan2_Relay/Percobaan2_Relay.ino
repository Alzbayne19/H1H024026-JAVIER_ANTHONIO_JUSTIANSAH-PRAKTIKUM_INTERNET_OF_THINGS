#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define RELAYPIN 5 

DHT dht(DHTPIN, DHTTYPE);

const float batasAtas = 30.0;
const float batasBawah = 28.0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  // Inisialisasi pin relay sebagai output
  pinMode(RELAYPIN, OUTPUT);
  // Memastikan relay dalam kondisi mati saat awal program berjalan
  digitalWrite(RELAYPIN, LOW);
  
  delay(2000);
}

void loop() {
  float suhu = dht.readTemperature();

  // Validasi apakah pembacaan sensor berhasil
  if (!isnan(suhu)) {
    Serial.print("Suhu Saat Ini: ");
    Serial.print(suhu);
    
    // Logika kendali aktuator
    if (suhu >= batasAtas) {
      digitalWrite(RELAYPIN, HIGH);
      Serial.println(" °C -> Aktuator ON");
    } else if (suhu <= batasBawah) {
      digitalWrite(RELAYPIN, LOW);
      Serial.println(" °C -> Aktuator OFF");
    } else {
      Serial.println(" °C -> Aktuator TETAP (Zona Histerisis)");
    }
  } else {
    Serial.println("Gagal membaca sensor DHT11!");
  }
  
  delay(2000); // Jeda minimal 2 detik untuk sensor DHT
}