#include <stdio.h>      
#include <time.h>       

// Tarih ve saat bilgisini saklamak için yapý tanýmý
typedef struct {
    int yil, ay, gun, saat, dakika, saniye;  
} TarihSaat;

typedef union {
    TarihSaat tarih;   // Tarih-saat bilgilerini saklayan yapý
    time_t epoch;      // Epoch zaman deðeri (1970'den itibaren geçen saniye)
} ZamanBirim;

int main() {  // Programýn baþlangýç noktasý
    ZamanBirim z1, z2;                      // Ýki adet ZamanBirim deðiþkeni: z1 ve z2 (örneðin, birisi check-in, diðeri check-out için)
    struct tm zaman1 = {0}, zaman2 = {0};     // Ýki adet struct tm deðiþkeni; tüm alanlarý sýfýrlanmýþ baþlangýç deðeriyle

    // Kullanýcýdan 1. tarihi alma 
    printf("1. Tarihi giriniz (YYYY MM DD HH MM SS): ");
    scanf("%d %d %d %d %d %d", 
          &z1.tarih.yil, &z1.tarih.ay, &z1.tarih.gun, 
          &z1.tarih.saat, &z1.tarih.dakika, &z1.tarih.saniye);

    // Kullanýcýdan 2. tarihi alma 
    printf("2. Tarihi giriniz (YYYY MM DD HH MM SS): ");
    scanf("%d %d %d %d %d %d", 
          &z2.tarih.yil, &z2.tarih.ay, &z2.tarih.gun, 
          &z2.tarih.saat, &z2.tarih.dakika, &z2.tarih.saniye);

    // 1. tarih için struct tm yapýsýný ayarlama
    zaman1.tm_year = z1.tarih.yil - 1900;  // tm_year: Yýl bilgisi, 1900'den itibaren hesaplanýr
    zaman1.tm_mon  = z1.tarih.ay - 1;        // tm_mon: Ay bilgisi, 0-11 arasý (Ocak=0) olarak tutulur
    zaman1.tm_mday = z1.tarih.gun;           
    zaman1.tm_hour = z1.tarih.saat;          
    zaman1.tm_min  = z1.tarih.dakika;        
    zaman1.tm_sec  = z1.tarih.saniye;        

    // 2. tarih için struct tm yapýsýný ayarlama
    zaman2.tm_year = z2.tarih.yil - 1900;  // 1900'den itibaren yýl bilgisi
    zaman2.tm_mon  = z2.tarih.ay - 1;        // Ay bilgisi, 0-11 arasý
    zaman2.tm_mday = z2.tarih.gun;           
    zaman2.tm_hour = z2.tarih.saat;          
    zaman2.tm_min  = z2.tarih.dakika;        
    zaman2.tm_sec  = z2.tarih.saniye;        

    // mktime fonksiyonu ile struct tm'leri epoch zamanýna çevirme
    z1.epoch = mktime(&zaman1);  // Ýlk tarihin epoch zamanýný hesaplar ve z1'e atar
    z2.epoch = mktime(&zaman2);  // Ýkinci tarihin epoch zamanýný hesaplar ve z2'ye atar

    // Ýki tarih arasýndaki farký saniye cinsinden hesapla
    double fark = difftime(z2.epoch, z1.epoch);  // z2 ile z1 arasýndaki farký hesaplar
    if (fark < 0) 
        fark = -fark;  // Eðer fark negatifse, mutlak deðere çevir

    // Hesaplanan epoch deðerlerini ve iki tarih arasýndaki farký ekrana yazdýr
    printf("\n1. Tarihin epoch deðeri: %ld\n", z1.epoch);  
    printf("2. Tarihin epoch deðeri: %ld\n", z2.epoch);    
    printf("Ýki tarih arasýndaki fark: %.0f saniye\n", fark);  

    return 0; 
}
