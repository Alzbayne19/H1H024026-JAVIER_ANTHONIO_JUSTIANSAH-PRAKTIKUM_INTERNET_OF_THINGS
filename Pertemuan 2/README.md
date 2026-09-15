# Library atau dependencies yang diperlukan
- Arduino IDE
- Library ESP8266 wifi 
- NodeMCU ESP8266
- Relay atau LED
- kanel jumper 
- resistor
- breadboard

# Penjelasan kode
## kode percobaan 1A
Program ini mengatur ESP32 sebagai klien WiFi menggunakan WiFi.mode(WIFI_STA).
Proses koneksi ke router diinisialisasi melalui WiFi.begin(ssid, password) dan ditunggu
menggunakan perulangan while hingga statusnya WL_CONNECTED. Setelah berhasil
terhubung, program mengambil dan menampilkan data jaringan seperti alamat IP, MAC
Address, dan RSSI (kekuatan sinyal).

## kode percobaan 2A
Program ini menjadikan ESP32 sebagai pemancar WiFi (hotspot) dengan perintah
WiFi.mode(WIFI_AP). Jaringan SSID dan password mandiri dibuat menggunakan
WiFi.softAP(ap_ssid, ap_password). Alamat IP jaringan lokal ditampilkan dengan
WiFi.softAPIP() (default 192.168.4.1). Pada perulangan utama, program secara aktif
menghitung dan menampilkan jumlah perangkat (klien) yang terhubung ke ESP32
tersebut.

# Penjelasan setiap fungsi
- `WiFi.mode()`: Menetapkan mode operasi jaringan pada ESP32, seperti mode Station (STA), Access Point (AP), atau gabungan keduanya (AP+STA).  
- `WiFi.begin(ssid, password)`: Memulai proses koneksi ESP32 ke jaringan Wi-Fi eksternal pada mode Station.  
- `WiFi.status()`: Mengembalikan nilai status koneksi saat ini, seperti WL_CONNECTED jika koneksi sukses.  
- `WiFi.localIP()`: Menampilkan alamat IP yang diterima oleh ESP32 dari router pada mode Station.  
- `WiFi.macAddress()`: Menampilkan alamat MAC dari perangkat ESP32.  
- `WiFi.RSSI()`: Menunjukkan kekuatan sinyal jaringan Wi-Fi dalam satuan dBm.  
- `WiFi.softAP(ssid, password)`: Mengaktifkan mode Access Point mandiri pada ESP32 dengan SSID dan kata sandi yang telah ditentukan.  
- `WiFi.softAPIP()`: Menampilkan alamat IP default dari Access Point yang dipancarkan oleh ESP32.  
- `WiFi.softAPgetStationNum()`: Menghitung dan mengembalikan jumlah perangkat klien yang sedang terhubung ke Access Point ESP32.

# Penjelasan percabangan/conditional
perulangan:
`while (WiFi.status() != WL_CONNECTED)`: Loop ini berfungsi untuk menahan eksekusi program. Selama ESP32 belum terhubung ke WiFi, program akan terus mencetak titik (.) di Serial Monitor sambil menunggu koneksi stabil.  

percabagan
`if (WiFi.status() == WL_CONNECTED) ... else ...`: Blok percabangan ini digunakan di dalam fungsi `loop()` untuk memantau status jaringan setiap 5 detik. Jika ESP32 masih tersambung, program akan mencetak "Status: Terhubung". Jika koneksi putus, program akan masuk ke blok else untuk mencetak "Status: Terputus" dan mematikan LED.  


# Penjelasan singkat mengenai detail percobaan
### Percobaan 2A (Mode Station)
Mengonfigurasi ESP32 untuk bertindak sebagai klien (seperti laptop/smartphone) yang menyambung ke jaringan WiFi yang sudah ada. Tujuannya agar ESP32 mendapat akses jaringan lokal atau internet untuk membaca IP Address, MAC, dan kekuatan sinyal.  
### Percobaan 2B (Mode Access Point)
Mengonfigurasi ESP32 menjadi penyedia jaringan (hotspot) mandiri. Perangkat ini membuat jaringan baru agar smartphone atau laptop lain dapat langsung terhubung kepadanya tanpa memerlukan router tambahan.

# Jawaban pertanyaan praktikum yang berkaitan dengan code
## A. A. Pertanyaan 2.5.4 No 4
```cpp
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

- `WiFi.disconnect();` : Memastikan koneksi yang bermasalah diputus sepenuhnya sebelum mencoba koneksi baru.
- `WiFi.reconnect();` : Memerintahkan ESP32 untuk secara otomatis mencoba menyambung kembali ke jaringan WiFi menggunakan SSID dan password yang sebelumnya sudah dimasukkan pada `WiFi.begin()`.

## Pertanyaan 2.6.4 No 4
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
  

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ap_ssid, ap_password);
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
- `WiFi.mode(WIFI_AP_STA);` : Mengubah mode WiFi menjadi mode gabungan, sehingga fungsi Access Point dan Station dapat berjalan bersamaan.
- `WiFi.begin(ssid, password);` : Memulai koneksi ESP32 ke jaringan WiFi eksternal (router/hotspot) sebagai Station.
- `WiFi.softAP(ap_ssid, ap_password);` : Mengaktifkan ESP32 sebagai Access Point dengan SSID dan password khusus agar perangkat lain dapat terhubung ke ESP.


