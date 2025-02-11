#include <stdio.h>
#include <time.h>

// Tarih ve saat bilgisini saklamak için yapý tanýmý
typedef struct {
    int yil;
    int ay;
    int gun;
    int saat;
    int dakika;
    int saniye;
} TarihSaat;

// Ayný bellek alanýný hem TarihSaat hem de epoch zaman (time_t) olarak kullanabilmek için union tanýmý
typedef union {
    TarihSaat tarih;
    time_t epoch;
} ZamanBilesimi;

int main() {
    // Check-in ve check-out tarihlerini saklamak için iki union deðiþkeni
    ZamanBilesimi checkIn, checkOut;
    struct tm tmCheckIn = {0}, tmCheckOut = {0};

    // Kullanýcýdan check-in tarih bilgisini al
    printf("Check-in tarihini giriniz (YYYY MM DD HH MM SS): ");
    if (scanf("%d %d %d %d %d %d", 
              &checkIn.tarih.yil, &checkIn.tarih.ay, &checkIn.tarih.gun,
              &checkIn.tarih.saat, &checkIn.tarih.dakika, &checkIn.tarih.saniye) != 6) {
        printf("Girdi formatý hatalý!\n");
        return 1;
    }

    // Kullanýcýdan check-out tarih bilgisini al
    printf("Check-out tarihini giriniz (YYYY MM DD HH MM SS): ");
    if (scanf("%d %d %d %d %d %d", 
              &checkOut.tarih.yil, &checkOut.tarih.ay, &checkOut.tarih.gun,
              &checkOut.tarih.saat, &checkOut.tarih.dakika, &checkOut.tarih.saniye) != 6) {
        printf("Girdi formatý hatalý!\n");
        return 1;
    }

    // Check-in tarihi için struct tm yapýsýný ayarla
    tmCheckIn.tm_year = checkIn.tarih.yil - 1900;  // tm_year: 1900'den itibaren geçen yýl sayýsýdýr
    tmCheckIn.tm_mon  = checkIn.tarih.ay - 1;        // tm_mon: 0-11 arasý (0 = Ocak)
    tmCheckIn.tm_mday = checkIn.tarih.gun;
    tmCheckIn.tm_hour = checkIn.tarih.saat;
    tmCheckIn.tm_min  = checkIn.tarih.dakika;
    tmCheckIn.tm_sec  = checkIn.tarih.saniye;
    tmCheckIn.tm_isdst = -1;  // Yaz saati uygulamasýný otomatik algýlamasý için

    // Check-out tarihi için struct tm yapýsýný ayarla
    tmCheckOut.tm_year = checkOut.tarih.yil - 1900;
    tmCheckOut.tm_mon  = checkOut.tarih.ay - 1;
    tmCheckOut.tm_mday = checkOut.tarih.gun;
    tmCheckOut.tm_hour = checkOut.tarih.saat;
    tmCheckOut.tm_min  = checkOut.tarih.dakika;
    tmCheckOut.tm_sec  = checkOut.tarih.saniye;
    tmCheckOut.tm_isdst = -1;

    // mktime fonksiyonu ile struct tm bilgilerini epoch zamanýna çevir
    checkIn.epoch = mktime(&tmCheckIn);
    checkOut.epoch = mktime(&tmCheckOut);

    // Ýki tarih arasýndaki farký saniye cinsinden hesapla
    double farkSaniye = difftime(checkOut.epoch, checkIn.epoch);
    if (farkSaniye < 0) {
        farkSaniye = -farkSaniye;
    }

    // Farký gün cinsine çevir (1 gün = 86400 saniye)
    double farkGun = farkSaniye / 86400.0;

    // Sonuçlarý ekrana yazdýr
    printf("\nCheck-in epoch deðeri: %ld\n", checkIn.epoch);
    printf("Check-out epoch deðeri: %ld\n", checkOut.epoch);
    printf("Konaklama süresi: %.0f saniye (yaklaþýk %.2f gün)\n", farkSaniye, farkGun);

    return 0;
}
