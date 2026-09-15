#include <ESP8266WiFi.h>

const char* ssid = "hammed";
const char* password = "kudalari";

const int ledPin = 2; 
int waktu = 0; 

void setup() {
  Serial.begin(115200);
  delay(1000); 
  Serial.println();

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); 
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi berhasil terhubung!");
  digitalWrite(ledPin, HIGH); 
  
  // Mencetak tabel untuk Dapeng
  Serial.println("=======================================================================");
  Serial.println("Wkt(s) | Status    | IP Address      | MAC Address       | RSSI | LED");
  Serial.println("=======================================================================");
}

void loop() {
  if (waktu <= 45) {
    Serial.print(waktu);
    if(waktu < 10) Serial.print(" "); 
    Serial.print("     | ");
    
    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("Terhubung | ");
      Serial.print(WiFi.localIP());
      Serial.print(" | ");
      Serial.print(WiFi.macAddress());
      Serial.print(" | ");
      Serial.print(WiFi.RSSI());
      Serial.print("  | HIGH\n");
    } else {
      Serial.print("Terputus  | -               | -                 | -    | LOW\n");
      digitalWrite(ledPin, LOW);
      
      // --- MODIFIKASI AUTO RECONNECT ---
      Serial.println("\n>>> Koneksi terputus! Mencoba menghubungkan ulang...");
      WiFi.disconnect(); 
      WiFi.reconnect(); 
      
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("\n>>> Berhasil terhubung kembali! Melanjutkan pengamatan...\n");
      digitalWrite(ledPin, HIGH);
      // ---------------------------------
    }
    waktu += 5; 
  }
  delay(5000); 
}