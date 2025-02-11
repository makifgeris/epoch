#include <stdio.h>
#include <time.h>

// Tarih ve saat bilgisini saklamak i�in yap� tan�m�
typedef struct {
    int yil;
    int ay;
    int gun;
    int saat;
    int dakika;
    int saniye;
} TarihSaat;

// Ayn� bellek alan�n� hem TarihSaat hem de epoch zaman (time_t) olarak kullanabilmek i�in union tan�m�
typedef union {
    TarihSaat tarih;
    time_t epoch;
} ZamanBilesimi;

int main() {
    // Check-in ve check-out tarihlerini saklamak i�in iki union de�i�keni
    ZamanBilesimi checkIn, checkOut;
    struct tm tmCheckIn = {0}, tmCheckOut = {0};

    // Kullan�c�dan check-in tarih bilgisini al
    printf("Check-in tarihini giriniz (YYYY MM DD HH MM SS): ");
    if (scanf("%d %d %d %d %d %d", 
              &checkIn.tarih.yil, &checkIn.tarih.ay, &checkIn.tarih.gun,
              &checkIn.tarih.saat, &checkIn.tarih.dakika, &checkIn.tarih.saniye) != 6) {
        printf("Girdi format� hatal�!\n");
        return 1;
    }

    // Kullan�c�dan check-out tarih bilgisini al
    printf("Check-out tarihini giriniz (YYYY MM DD HH MM SS): ");
    if (scanf("%d %d %d %d %d %d", 
              &checkOut.tarih.yil, &checkOut.tarih.ay, &checkOut.tarih.gun,
              &checkOut.tarih.saat, &checkOut.tarih.dakika, &checkOut.tarih.saniye) != 6) {
        printf("Girdi format� hatal�!\n");
        return 1;
    }

    // Check-in tarihi i�in struct tm yap�s�n� ayarla
    tmCheckIn.tm_year = checkIn.tarih.yil - 1900;  // tm_year: 1900'den itibaren ge�en y�l say�s�d�r
    tmCheckIn.tm_mon  = checkIn.tarih.ay - 1;        // tm_mon: 0-11 aras� (0 = Ocak)
    tmCheckIn.tm_mday = checkIn.tarih.gun;
    tmCheckIn.tm_hour = checkIn.tarih.saat;
    tmCheckIn.tm_min  = checkIn.tarih.dakika;
    tmCheckIn.tm_sec  = checkIn.tarih.saniye;
    tmCheckIn.tm_isdst = -1;  // Yaz saati uygulamas�n� otomatik alg�lamas� i�in

    // Check-out tarihi i�in struct tm yap�s�n� ayarla
    tmCheckOut.tm_year = checkOut.tarih.yil - 1900;
    tmCheckOut.tm_mon  = checkOut.tarih.ay - 1;
    tmCheckOut.tm_mday = checkOut.tarih.gun;
    tmCheckOut.tm_hour = checkOut.tarih.saat;
    tmCheckOut.tm_min  = checkOut.tarih.dakika;
    tmCheckOut.tm_sec  = checkOut.tarih.saniye;
    tmCheckOut.tm_isdst = -1;

    // mktime fonksiyonu ile struct tm bilgilerini epoch zaman�na �evir
    checkIn.epoch = mktime(&tmCheckIn);
    checkOut.epoch = mktime(&tmCheckOut);

    // �ki tarih aras�ndaki fark� saniye cinsinden hesapla
    double farkSaniye = difftime(checkOut.epoch, checkIn.epoch);
    if (farkSaniye < 0) {
        farkSaniye = -farkSaniye;
    }

    // Fark� g�n cinsine �evir (1 g�n = 86400 saniye)
    double farkGun = farkSaniye / 86400.0;

    // Sonu�lar� ekrana yazd�r
    printf("\nCheck-in epoch de�eri: %ld\n", checkIn.epoch);
    printf("Check-out epoch de�eri: %ld\n", checkOut.epoch);
    printf("Konaklama s�resi: %.0f saniye (yakla��k %.2f g�n)\n", farkSaniye, farkGun);

    return 0;
}
