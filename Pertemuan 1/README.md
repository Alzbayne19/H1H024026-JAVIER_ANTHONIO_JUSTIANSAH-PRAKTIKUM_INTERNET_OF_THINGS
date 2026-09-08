# Modul 1 / Pertemuan 1 - Sensor dan Aktuator

## Penjelasan Singkat Mengenai Detail Percobaan
Praktikum ini berfokus pada implementasi sistem akuisisi data dan kendali aktuator cerdas (*closed-loop*). Percobaan meliputi pembacaan besaran suhu dan kelembaban lingkungan secara *real-time* menggunakan sensor **DHT11** yang dihubungkan ke mikrokontroler **ESP8266**. Sistem dikembangkan agar mampu mengambil keputusan otomatis untuk mengendalikan aktuator (Relay) berdasarkan nilai ambang batas (*threshold*) suhu menggunakan metode histerisis.

---

## Library atau Dependencies yang Diperlukan
1. **DHT Sensor Library** (oleh Adafruit) - Untuk antarmuka pembacaan data sensor.
2. **Board Package ESP8266** - Diinstal melalui *Boards Manager* agar IDE mengenali mikrokontroler.
3. **Driver CH340 / CP210x USB-to-Serial** - Untuk memungkinkan komunikasi serial antara PC dan ESP8266.

---

## Penjelasan Code
Kode final praktikum ini merupakan penyesuaian dari modul asli. Modifikasi difokuskan pada sinkronisasi perangkat keras fisis yang digunakan, yaitu mengganti mikrokontroler menjadi ESP8266, sensor menjadi DHT11, pin komunikasi sensor ke GPIO 4, dan pin kontrol relay ke GPIO 5.

---

## Penjelasan Setiap Fungsi

### 1. `setup()`
Fungsi ini dieksekusi hanya satu kali saat mikrokontroler dinyalakan (*booting*).
*   `Serial.begin(115200);`: Membuka jalur komunikasi serial ke PC dengan *baud rate* 115200 bps.
*   `dht.begin();`: Menginisialisasi objek sensor DHT agar siap membaca data lingkungan.
*   `pinMode(RELAYPIN, OUTPUT);`: Menentukan arah aliran sinyal GPIO 5 sebagai jalur keluaran tegangan.
*   `digitalWrite(RELAYPIN, LOW);`: Memastikan relay berada dalam keadaan mati (*OFF*) secara *default* saat sistem baru menyala.

### 2. `loop()`
Fungsi utama yang dieksekusi secara terus-menerus.
*   `float suhu = dht.readTemperature();`: Memerintahkan sensor membaca suhu (°C) dan menyimpannya di variabel desimal.
*   `float kelembaban = dht.readHumidity();`: Memerintahkan sensor membaca kelembaban (%) dan menyimpannya.
*   Fungsi ini kemudian memvalidasi data tersebut, menampilkannya ke Serial Monitor, lalu mengevaluasi nilai suhu untuk menyalakan/mematikan relay, dan diakhiri dengan jeda waktu pembacaan (2 detik).

---

## Penjelasan Percabangan / Conditional

### 1. Validasi Data Sensor (Error Handling)
```cpp
if (isnan(suhu) || isnan(kelembaban)) {
  Serial.println("Gagal membaca data dari sensor DHT11!");
} else {
  // Cetak data ke Serial Monitor
}
```
Menggunakan fungsi `isnan()` *(Is Not a Number)*. Percabangan logika *OR* (`||`) ini berfungsi sebagai proteksi. JIKA sensor gagal membaca suhu ATAU kelembaban (karena terputus/rusak), mikrokontroler akan mencetak pesan "Gagal" alih-alih menampilkan data yang salah. Jika valid, program masuk ke blok `else`.

### 2. Logika Kendali Aktuator (Histerisis)
```cpp
if (suhu >= batasAtas) {
  digitalWrite(RELAYPIN, HIGH);
  Serial.println(" °C -> Aktuator ON");
} else if (suhu <= batasBawah) {
  digitalWrite(RELAYPIN, LOW);
  Serial.println(" °C -> Aktuator OFF");
}
```
Menggunakan dua nilai batas (Atas = 30.0, Bawah = 28.0). 
*   **ON:** Jika suhu menyentuh atau melampaui 30.0 °C, relay diberi sinyal `HIGH`.
*   **OFF:** Relay hanya akan dimatikan (diberi sinyal `LOW`) jika suhu benar-benar turun ke angka 28.0 °C atau lebih rendah.
*   **Zona Histerisis:** Jika suhu berfluktuasi tipis di tengah-tengah (misal 29.0 °C), tidak ada kondisi yang terpenuhi, sehingga status relay tetap ditahan di posisi sebelumnya. Hal ini mencegah kerusakan komponen mekanis *(chattering)*.

---

## Jawaban Pertanyaan Praktikum Berkaitan Code (Assessment 1.4)

1.  **Modifikasi Penyesuaian Perangkat Keras:** Mengubah deklarasi pin (`#define DHTPIN 4` dan `#define RELAYPIN 5`), mengubah tipe sensor (`#define DHTTYPE DHT11`).
2.  **Modifikasi Sistem Histerisis pada Aktuator:** Menggantikan variabel ambang batas tunggal *(single threshold)* dengan variabel batas picu atas (`batasAtas = 30.0`) dan batas picu bawah (`batasBawah = 28.0`) untuk menciptakan sistem kendali bebas osilasi.

