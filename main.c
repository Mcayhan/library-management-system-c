/**
 * @file main.c
 * @description Ana program dosyasi
 * @assignment Proje 1
 * @date 20.12.2025
 * @author Muhammed Çayhan - 2321021051
 */

#include "Proje1.h"

int main()
{

    printf("\n==== Kitapevi Yonetim Sistemi ====\n");

    Kategori *kategoriDizisi = NULL;
    int kategoriSayisi = 0;

    dosyadanDiziyeAktar(&kategoriDizisi, &kategoriSayisi);

    if (kategoriSayisi == 0)
    {

        printf("\nVeriler olusturuluyor...\n");

        kategoriSayisi = 3;
        kategoriDizisi = (Kategori *)malloc(kategoriSayisi * sizeof(Kategori));

        kategoriDizisi[0] = kategoriOlustur("Distopik", 101);
        kategoriDizisi[1] = kategoriOlustur("Tarih", 102);
        kategoriDizisi[2] = kategoriOlustur("Otobiyografi", 103);

        Kitap k1 = kitapOlustur("1984", "George Orwell", 101, 100.0, 1949);
        Kitap k2 = kitapOlustur("Fahreneit", "Ray Bradbury", 101, 200.0, 1953);
        Kitap k3 = kitapOlustur("Fatih Sultan Mehmed: Doğu’nun ve Batı’nın Efendisi", "Ilber Ortayli", 102, 189, 2008);
        Kitap k4 = kitapOlustur("Kısa Osmanlı Tarihi", "Halil İnalcık", 102, 150.0, 1974);
        Kitap k5 = kitapOlustur("Steve Jobs", "Walter Isaacson", 103, 300.0, 2011);
        Kitap k6 = kitapOlustur("Kavgam", "Adolf Hitler", 103, 120.0, 1925);
        Kitap k7 = kitapOlustur("Brave New World", "Aldous Huxley", 101, 180.0, 1932);

        kitapEkle(kategoriDizisi, &kategoriSayisi, k1);
        kitapEkle(kategoriDizisi, &kategoriSayisi, k2);
        kitapEkle(kategoriDizisi, &kategoriSayisi, k3);
        kitapEkle(kategoriDizisi, &kategoriSayisi, k4);
        kitapEkle(kategoriDizisi, &kategoriSayisi, k5);
        kitapEkle(kategoriDizisi, &kategoriSayisi, k6);
        kitapEkle(kategoriDizisi, &kategoriSayisi, k7);
    }

    printf("\n--- Kategori ve Kitap Bilgileri ---\n");

    // Fonksiyon Testleri
    tumKategorileriYazdir(kategoriDizisi, kategoriSayisi);
    ortalamaUstuKitaplariListele(&kategoriDizisi[0]);
    ortalamaUstuKitaplariListele(&kategoriDizisi[1]);
    ortalamaUstuKitaplariListele(&kategoriDizisi[2]);
    enPahaliKitaplariYazdir(kategoriDizisi, kategoriSayisi);
    eskiKitapFiyatGuncelle(kategoriDizisi, kategoriSayisi, 1950, 250.0);

    printf("\n--- Guncel Liste ---\n");
    tumKategorileriYazdir(kategoriDizisi, kategoriSayisi);

    // Veri Yazma
    diziyiDosyayaYaz(kategoriDizisi, kategoriSayisi);

    // Bellek Temizliği
    printf("\nBellek temizleniyor...\n");
    if (kategoriDizisi != NULL)
    {
        for (int i = 0; i < kategoriSayisi; i++)
        {

            for (int j = 0; j < kategoriDizisi[i].kitapSayisi; j++)
            {
                free(kategoriDizisi[i].kategoriKitaplar[j].kitapAdi);
                free(kategoriDizisi[i].kategoriKitaplar[j].yazarAdi);
            }

            free(kategoriDizisi[i].kategoriKitaplar);

            free(kategoriDizisi[i].kategoriAdi);
        }

        free(kategoriDizisi);
    }
    printf("Bellek temizlendi.\nProgram kapatiliyor.\n");
}
