
Bu projede, kullanıcı tarafından girilen iki tarih arasındaki farkı hesaplayan iki farklı C programı bulunmaktadır. Programlar, tarih ve saat bilgilerini hem yapı (`TarihSaat`) hem de epoch zaman (`time_t`) olarak saklamak amacıyla `union` yapısını kullanmaktadır.

Her iki programda da kullanıcıdan `YYYY MM DD HH MM SS` formatında tarih ve saat bilgisi alınmakta; bu bilgiler, bir `struct tm` yapısına aktarılmakta ve `mktime()` fonksiyonu kullanılarak epoch zaman değerine dönüştürülmektedir. Sonrasında, iki epoch değeri arasındaki fark hesaplanarak ekrana yazdırılmaktadır.

### Epoch.c 
- **Amaç:** İki tarih arasında saniye cinsinden fark hesaplamak.
- **Kullanılan Yapılar:**
  - `TarihSaat`: Yıl, ay, gün, saat, dakika, saniye bilgilerini saklar.
  - `ZamanBirim` (union): Hem `TarihSaat` hem de `time_t` (epoch) değerini aynı bellek alanında tutar.
- **İşleyiş:** 
  1. Kullanıcıdan iki tarih alınır.
  2. Her tarih için `struct tm` yapılandırılır (yıl, ay, gün, saat, dakika, saniye ayarlamaları yapılır).
  3. `mktime()` ile epoch zamanı elde edilir.
  4. `difftime()` ile iki tarih arasındaki fark saniye cinsinden hesaplanır ve ekrana yazdırılır.

### EpochOrnek.c
- **Amaç:** Check-in ve check-out tarihleri arasında saniye ve gün cinsinden fark hesaplamak.
- **Kullanılan Yapılar:**
  - `TarihSaat`: Yıl, ay, gün, saat, dakika, saniye bilgilerini saklar.
  - `ZamanBilesimi` (union): Hem `TarihSaat` hem de `time_t` (epoch) değerini aynı bellek alanında tutar.
- **İşleyiş:**
  1. Kullanıcıdan check-in ve check-out tarihleri alınır.
  2. Her iki tarih için `struct tm` yapılandırılır. (Yaz saati uygulaması için `tm_isdst = -1` ayarlanır.)
  3. `mktime()` ile epoch zamanı elde edilir.
  4. `difftime()` kullanılarak iki tarih arasındaki fark saniye cinsinden hesaplanır.
  5. Saniye cinsinden fark, gün cinsine çevrilir (1 gün = 86400 saniye).
  6. Ekrana yazdırılır.


