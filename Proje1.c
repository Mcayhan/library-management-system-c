/**
 * @file Proje1.c
 * @description Fonksiyonlarin gerceklestrildigi kaynak dosyasi
 * @assignment Proje 1
 * @date 20.12.2025
 * @author Muhammed Çayhan - 2321021051
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Proje1.h"

Kategori kategoriOlustur(char *ad, unsigned short kod)
{
    Kategori yeniKategori;
    
    yeniKategori.kategoriAdi = (char *)malloc(sizeof(char) * (strlen(ad) + 1));
    strcpy(yeniKategori.kategoriAdi, ad);

    yeniKategori.kategoriKodu = kod;
    yeniKategori.kapasite = 2;
    yeniKategori.kitapSayisi = 0;
    yeniKategori.kategoriKitaplar = (Kitap *)malloc(sizeof(Kitap) * yeniKategori.kapasite);

    return yeniKategori;
}

Kitap kitapOlustur(char *ad, char *yazar, unsigned short kod, float fiyat, int yil)
{
    Kitap yeniKitap;

    yeniKitap.kitapAdi = (char *)malloc(sizeof(char) * (strlen(ad) + 1));
    strcpy(yeniKitap.kitapAdi, ad);

    yeniKitap.yazarAdi = (char *)malloc(sizeof(char) * (strlen(yazar) + 1));
    strcpy(yeniKitap.yazarAdi, yazar);

    yeniKitap.kategoriKodu = kod;
    yeniKitap.fiyat = fiyat;
    yeniKitap.basimYili = yil;

    return yeniKitap;
}

void kitapEkle(Kategori *kategoriDizi, int *kategoriSayisi, Kitap yeniKitap)
{
    for (int i = 0; i < *kategoriSayisi; i++)
    {
        if (kategoriDizi[i].kategoriKodu == yeniKitap.kategoriKodu)
        {
            Kategori *ktg = &kategoriDizi[i];

            if (ktg->kitapSayisi == ktg->kapasite)
            {
                ktg->kapasite *= 2;
                ktg->kategoriKitaplar = (Kitap *)realloc(ktg->kategoriKitaplar, ktg->kapasite * sizeof(Kitap));
            }

            ktg->kategoriKitaplar[ktg->kitapSayisi] = yeniKitap;
            ktg->kitapSayisi++;
            return;
        }
    }

    free(yeniKitap.kitapAdi);
    free(yeniKitap.yazarAdi);
}

void kitapBilgileriniYazdir(Kitap *kitap)
{
    printf("Kitap Adi: %s\n", kitap->kitapAdi);
    printf("Yazar Adi: %s\n", kitap->yazarAdi);
    printf("Kategori Kodu: %hu\n", kitap->kategoriKodu);
    printf("Fiyat: %.2f\n", kitap->fiyat);
    printf("Basim Yili: %d\n", kitap->basimYili);
    printf("-------------------------\n");
}

void kategoriBilgileriniYazdir(Kategori *kategori)
{
    printf("Kategori Adi: %s\n", kategori->kategoriAdi);
    printf("Kategori Kodu: %hu\n", kategori->kategoriKodu);
    printf("Kitap Sayisi: %d\n", kategori->kitapSayisi);
    printf("Kapasite: %d\n", kategori->kapasite);
    printf("Bu kategorinin kitapları:\n");
    printf("\n");
}

void tumKategorileriYazdir(Kategori *kategoriDizi, int kategoriSayisi)
{
    for (int i = 0; i < kategoriSayisi; i++)
    {
        kategoriBilgileriniYazdir(&kategoriDizi[i]);
        for (int j = 0; j < kategoriDizi[i].kitapSayisi; j++)
        {
            kitapBilgileriniYazdir(&kategoriDizi[i].kategoriKitaplar[j]);
        }
        printf("\n");
    }
}

float fiyatOrtalamasiHesapla(Kategori *kategori)
{
 float toplamFiyat = 0.0;
    for (int i = 0; i < kategori->kitapSayisi; i++)
    {
        toplamFiyat += kategori->kategoriKitaplar[i].fiyat;
    }
    return toplamFiyat / kategori->kitapSayisi;
}

void ortalamaUstuKitaplariListele(Kategori *kategori)
{
    printf("\nFiyat Ortalamasi: %.2f\n", fiyatOrtalamasiHesapla(kategori));
    float ortalamaFiyat = fiyatOrtalamasiHesapla(kategori);
    printf("Ortalama Fiyatin Ustundeki Kitaplar:\n");

    for (int i = 0; i < kategori->kitapSayisi; i++)
    {
        if (kategori->kategoriKitaplar[i].fiyat > ortalamaFiyat)
        {
            kitapBilgileriniYazdir(&kategori->kategoriKitaplar[i]);
        }
    }
}

void enPahaliKitaplariYazdir(Kategori *kategoriDizi, int kategoriSayisi)
{
    float maxFiyat = 0.0;

    for (int i = 0; i < kategoriSayisi; i++)
    {
        for (int j = 0; j < kategoriDizi[i].kitapSayisi; j++)
        {
            if (kategoriDizi[i].kategoriKitaplar[j].fiyat > maxFiyat)
            {
                maxFiyat = kategoriDizi[i].kategoriKitaplar[j].fiyat;
            }
        }
    }

    printf("En Pahali Kitaplar:\n");
    for (int i = 0; i < kategoriSayisi; i++)
    {
        for (int j = 0; j < kategoriDizi[i].kitapSayisi; j++)
        {
            if (kategoriDizi[i].kategoriKitaplar[j].fiyat == maxFiyat)
            {
                kitapBilgileriniYazdir(&kategoriDizi[i].kategoriKitaplar[j]);
            }
        }
    }
}

void eskiKitapFiyatGuncelle(Kategori *kategoriDizi, int kategoriSayisi, int yil, float yeniFiyat)
{
    for (int i = 0; i < kategoriSayisi; i++)
    {
        for (int j = 0; j < kategoriDizi[i].kitapSayisi; j++)
        {
            if (kategoriDizi[i].kategoriKitaplar[j].basimYili < yil)
            {
                kategoriDizi[i].kategoriKitaplar[j].fiyat = yeniFiyat;
            }
        }
    }
    printf("\nEski kitaplarin fiyatlari guncellendi.\n");
}

void diziyiDosyayaYaz(Kategori *kategoriDizi, int kategoriSayisi)
{
    // Kategorileri yaz
    FILE *kategoriDosya = fopen("kategoriler.txt", "w");
    if (kategoriDosya == NULL)
    {
        printf("Dosya acilamadi!\n");
        return;
    }

    for (int i = 0; i < kategoriSayisi; i++)
    {
        fprintf(kategoriDosya, "%hu\t%s\n", kategoriDizi[i].kategoriKodu, kategoriDizi[i].kategoriAdi);
    }
    fclose(kategoriDosya);

    // Kitaplari yaz
    FILE *kitapDosya = fopen("kitaplar.txt", "w");
    if (kitapDosya == NULL)
    {
        printf("Dosya acilamadi!\n");
        return;
    }

    for (int i = 0; i < kategoriSayisi; i++)
    {
        for (int j = 0; j < kategoriDizi[i].kitapSayisi; j++)
        {
            Kitap *k = &kategoriDizi[i].kategoriKitaplar[j];
            fprintf(kitapDosya, "%s\t%s\t%hu\t%.2f\t%d\n", k->kitapAdi, k->yazarAdi, k->kategoriKodu, k->fiyat, k->basimYili);
        }
    }
    fclose(kitapDosya);

    printf("Tum veriler dosyalara basariyla kaydedildi.\n");
}

void dosyadanDiziyeAktar(Kategori **kategoriDiziPtr, int *kategoriSayisiPtr)
{
    FILE *kategoriDosya = fopen("kategoriler.txt", "r");
    FILE *kitapDosya = fopen("kitaplar.txt", "r");

    *kategoriDiziPtr = NULL;
    *kategoriSayisiPtr = 0;

    if (kategoriDosya == NULL) return;

    unsigned short kod;
    char ad[50];

    while (fscanf(kategoriDosya, "%hu\t%[^\n]\n", &kod, ad) != EOF)
    {
        (*kategoriSayisiPtr)++;
        *kategoriDiziPtr = realloc(*kategoriDiziPtr, (*kategoriSayisiPtr) * sizeof(Kategori));

        (*kategoriDiziPtr)[(*kategoriSayisiPtr) - 1] = kategoriOlustur(ad, kod);
    }
    fclose(kategoriDosya);

    if (kitapDosya == NULL) return;

    // kitaplari oku ve ekle
    char satir[256];
    while (fgets(satir, sizeof(satir), kitapDosya))
    {

        char *kitapAdi = strtok(satir, "\t");
        char *yazarAdi = strtok(NULL, "\t");
        char *kodStr = strtok(NULL, "\t");
        char *fiyatStr = strtok(NULL, "\t");
        char *yilStr = strtok(NULL, "\t");

        if (kitapAdi && yazarAdi && kodStr && fiyatStr && yilStr)
        {
            Kitap yeniK = kitapOlustur(kitapAdi, yazarAdi, (unsigned short)atoi(kodStr), atof(fiyatStr), atoi(yilStr));
            kitapEkle(*kategoriDiziPtr, kategoriSayisiPtr, yeniK);
        }
    }
    fclose(kitapDosya);
    printf("\nVeriler dosyadan yuklendi.\n");
}
