#include <ESP8266WiFi.h>

const char* ap_ssid = "ESP punya yogi"; 
const char* ap_password = "12345678"; 

const char* sta_ssid = "hammed";
const char* sta_password = "kudalari"; 

int waktu = 0; 

void setup() {
  Serial.begin(115200);
  delay(1000); 
  Serial.println();
  
  // --- MODIFIKASI MODE GANDA (AP+STA) ---
  WiFi.mode(WIFI_AP_STA);
  
  // 1. Konfigurasi Mode AP (Hotspot Mandiri)
  WiFi.softAP(ap_ssid, ap_password);
  
  // 2. Konfigurasi Mode STA (Klien ke Router)
  WiFi.begin(sta_ssid, sta_password);
  Serial.print("Menghubungkan ke WiFi Router");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Router (STA) Terhubung!");
  // --------------------------------------
  
  Serial.println("\nAccess Point aktif!");
  Serial.print("SSID AP    : "); Serial.println(ap_ssid);
  Serial.print("IP AP      : "); Serial.println(WiFi.softAPIP());
  Serial.print("IP STA     : "); Serial.println(WiFi.localIP());
  
  // Mencetak header tabel Dapeng untuk memantau AP
  Serial.println("\n=========================================================================");
  Serial.println("Wkt(s) | Jml Client | Perangkat Terhubung | Keterangan");
  Serial.println("=========================================================================");
}

void loop() {
  if (waktu <= 45) {
    Serial.print(waktu);
    if(waktu < 10) Serial.print(" "); 
    Serial.print("     | ");
    
    int jumlahClient = WiFi.softAPgetStationNum();
    
    Serial.print(jumlahClient);
    Serial.print("          | ");
    
    if (jumlahClient > 0) {
      Serial.print("Smartphone/Laptop   | Perangkat berhasil terkoneksi\n");
    } else {
      Serial.print("-                   | Menunggu perangkat terhubung...\n");
    }
    
    waktu += 5; 
  }
  delay(5000); 
}