#include <stdio.h>      
#include <time.h>       

// Tarih ve saat bilgisini saklamak i�in yap� tan�m�
typedef struct {
    int yil, ay, gun, saat, dakika, saniye;  
} TarihSaat;

typedef union {
    TarihSaat tarih;   // Tarih-saat bilgilerini saklayan yap�
    time_t epoch;      // Epoch zaman de�eri (1970'den itibaren ge�en saniye)
} ZamanBirim;

int main() {  // Program�n ba�lang�� noktas�
    ZamanBirim z1, z2;                      // �ki adet ZamanBirim de�i�keni: z1 ve z2 (�rne�in, birisi check-in, di�eri check-out i�in)
    struct tm zaman1 = {0}, zaman2 = {0};     // �ki adet struct tm de�i�keni; t�m alanlar� s�f�rlanm�� ba�lang�� de�eriyle

    // Kullan�c�dan 1. tarihi alma 
    printf("1. Tarihi giriniz (YYYY MM DD HH MM SS): ");
    scanf("%d %d %d %d %d %d", 
          &z1.tarih.yil, &z1.tarih.ay, &z1.tarih.gun, 
          &z1.tarih.saat, &z1.tarih.dakika, &z1.tarih.saniye);

    // Kullan�c�dan 2. tarihi alma 
    printf("2. Tarihi giriniz (YYYY MM DD HH MM SS): ");
    scanf("%d %d %d %d %d %d", 
          &z2.tarih.yil, &z2.tarih.ay, &z2.tarih.gun, 
          &z2.tarih.saat, &z2.tarih.dakika, &z2.tarih.saniye);

    // 1. tarih i�in struct tm yap�s�n� ayarlama
    zaman1.tm_year = z1.tarih.yil - 1900;  // tm_year: Y�l bilgisi, 1900'den itibaren hesaplan�r
    zaman1.tm_mon  = z1.tarih.ay - 1;        // tm_mon: Ay bilgisi, 0-11 aras� (Ocak=0) olarak tutulur
    zaman1.tm_mday = z1.tarih.gun;           
    zaman1.tm_hour = z1.tarih.saat;          
    zaman1.tm_min  = z1.tarih.dakika;        
    zaman1.tm_sec  = z1.tarih.saniye;        

    // 2. tarih i�in struct tm yap�s�n� ayarlama
    zaman2.tm_year = z2.tarih.yil - 1900;  // 1900'den itibaren y�l bilgisi
    zaman2.tm_mon  = z2.tarih.ay - 1;        // Ay bilgisi, 0-11 aras�
    zaman2.tm_mday = z2.tarih.gun;           
    zaman2.tm_hour = z2.tarih.saat;          
    zaman2.tm_min  = z2.tarih.dakika;        
    zaman2.tm_sec  = z2.tarih.saniye;        

    // mktime fonksiyonu ile struct tm'leri epoch zaman�na �evirme
    z1.epoch = mktime(&zaman1);  // �lk tarihin epoch zaman�n� hesaplar ve z1'e atar
    z2.epoch = mktime(&zaman2);  // �kinci tarihin epoch zaman�n� hesaplar ve z2'ye atar

    // �ki tarih aras�ndaki fark� saniye cinsinden hesapla
    double fark = difftime(z2.epoch, z1.epoch);  // z2 ile z1 aras�ndaki fark� hesaplar
    if (fark < 0) 
        fark = -fark;  // E�er fark negatifse, mutlak de�ere �evir

    // Hesaplanan epoch de�erlerini ve iki tarih aras�ndaki fark� ekrana yazd�r
    printf("\n1. Tarihin epoch de�eri: %ld\n", z1.epoch);  
    printf("2. Tarihin epoch de�eri: %ld\n", z2.epoch);    
    printf("�ki tarih aras�ndaki fark: %.0f saniye\n", fark);  

    return 0; 
}
