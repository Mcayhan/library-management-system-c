/**
 * @file Proje1.h
 * @description Proje 1 icin gerekli yapilarin ve fonksiyon prototiplerinin tanimlandigi baslik dosyasi
 * @assignment Proje 1
 * @date 20.12.2025
 * @author Muhammed Çayhan - 2321021051
 */

#ifndef PROJE1_H
#define PROJE1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *kitapAdi;
    char *yazarAdi;
    unsigned short int kategoriKodu;
    float fiyat;
    int basimYili;
} Kitap;

typedef struct
{
    char *kategoriAdi;
    unsigned short int kategoriKodu;
    Kitap *kategoriKitaplar;
    int kitapSayisi;
    int kapasite;
} Kategori;

Kategori kategoriOlustur(char *ad, unsigned short kod);
Kitap kitapOlustur(char *ad, char *yazar, unsigned short kod, float fiyat, int yil);

void kitapEkle(Kategori *kategoriDizi, int *kategoriSayisi, Kitap yeniKitap);

void kitapBilgileriniYazdir(Kitap *kitap);
void kategoriBilgileriniYazdir(Kategori *kategori);
void tumKategorileriYazdir(Kategori *kategoriDizi, int kategoriSayisi);

float fiyatOrtalamasiHesapla(Kategori *kategori);
void ortalamaUstuKitaplariListele(Kategori *kategori);
void enPahaliKitaplariYazdir(Kategori *kategoriDizi, int kategoriSayisi);
void eskiKitapFiyatGuncelle(Kategori *kategoriDizi, int kategoriSayisi, int yil, float yeniFiyat);

void diziyiDosyayaYaz(Kategori *kategoriDizi, int kategoriSayisi);
void dosyadanDiziyeAktar(Kategori **kategoriDiziPtr, int *kategoriSayisiPtr);

#endif