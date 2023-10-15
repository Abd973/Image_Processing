#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

unsigned char imgRGB[SIZE][SIZE][RGB];

void loadimage          ();
void saveimage          ();
void ShrinkRGB          ();
void BlurRGB            ();
void MergeRGB           ();
void Lighten_DarkenRGB  ();

int main(){

    loadimage ();

    Lighten_DarkenRGB();
    saveimage ();

}

//________________________________________________________Primary

void loadimage(){

    char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   
   readRGBBMP(imageFileName, imgRGB);

}

void saveimage(){

    char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeRGBBMP(imageFileName, imgRGB);
}

//_______________________________________________________Shrink

void Shrink50RGB(){
    unsigned char imgshrink[SIZE][SIZE][RGB];
    int r = 1, b = 2, g = 3;
    for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
       imgshrink[i][j][r] = imgRGB[i][j][r];
       imgRGB[i][j][r] = 255;
    }
    }
    for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
       imgshrink[i][j][b] = imgRGB[i][j][b];
       imgRGB[i][j][b] = 255;
    }
    }
    for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
       imgshrink[i][j][g] = imgRGB[i][j][g];
       imgRGB[i][j][g] = 255;
    }
    }

    for (int i = 0, f = 0; i < SIZE / 2; ++i, f += 2){
    for (int j = 0, k = 0; j < SIZE / 2; ++j, k += 2){
        unsigned char doubled_pixel = (imgshrink[f][k][r] + imgshrink[f + 1][k + 1][r]) / 2;
        imgRGB[i][j][r] = doubled_pixel;
    }
    }
    for (int i = 0, f = 0; i < SIZE / 2; ++i, f += 2){
    for (int j = 0, k = 0; j < SIZE / 2; ++j, k += 2){
        unsigned char doubled_pixel = (imgshrink[f][k][b] + imgshrink[f + 1][k + 1][b]) / 2;
        imgRGB[i][j][b] = doubled_pixel;
    }
    }
    for (int i = 0, f = 0; i < SIZE / 2; ++i, f += 2){
    for (int j = 0, k = 0; j < SIZE / 2; ++j, k += 2){
        unsigned char doubled_pixel = (imgshrink[f][k][g] + imgshrink[f + 1][k + 1][g]) / 2;
        imgRGB[i][j][g] = doubled_pixel;
    }
    }

}

void Shrink25RGB(){
    unsigned char imgshrink[SIZE][SIZE][RGB];
    int r = 1, b = 2, g = 3;
    for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
       imgshrink[i][j][r] = imgRGB[i][j][r];
       imgRGB[i][j][r] = 255;
    }
    }
    for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
       imgshrink[i][j][b] = imgRGB[i][j][b];
       imgRGB[i][j][b] = 255;
    }
    }
    for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
       imgshrink[i][j][g] = imgRGB[i][j][g];
       imgRGB[i][j][g] = 255;
    }
    }

    for (int i = 0, f = 0; i < SIZE / 4; ++i, f += 4){
    for (int j = 0, k = 0; j < SIZE / 4; ++j, k += 4){
        unsigned char doubled_pixel = (imgshrink[f][k][r] + imgshrink[f + 1][k + 1][r]) / 2;
        imgRGB[i][j][r] = doubled_pixel;
    }
    }
    for (int i = 0, f = 0; i < SIZE / 4; ++i, f += 4){
    for (int j = 0, k = 0; j < SIZE / 4; ++j, k += 4){
        unsigned char doubled_pixel = (imgshrink[f][k][b] + imgshrink[f + 1][k + 1][b]) / 2;
        imgRGB[i][j][b] = doubled_pixel;
    }
    }
    for (int i = 0, f = 0; i < SIZE / 4; ++i, f += 4){
    for (int j = 0, k = 0; j < SIZE / 4; ++j, k += 4){
        unsigned char doubled_pixel = (imgshrink[f][k][g] + imgshrink[f + 1][k + 1][g]) / 2;
        imgRGB[i][j][g] = doubled_pixel;
    }
    }

}

void Shrink33RGB(){
unsigned char imgshrink[SIZE][SIZE][RGB];
    int r = 1, b = 2, g = 3;
    for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
       imgshrink[i][j][r] = imgRGB[i][j][r];
       imgRGB[i][j][r] = 255;
    }
    }
    for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
       imgshrink[i][j][b] = imgRGB[i][j][b];
       imgRGB[i][j][b] = 255;
    }
    }
    for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
       imgshrink[i][j][g] = imgRGB[i][j][g];
       imgRGB[i][j][g] = 255;
    }
    }

    for (int i = 0, f = 0; i < SIZE / 3; ++i, f += 3){
    for (int j = 0, k = 0; j < SIZE / 3; ++j, k += 3){
        unsigned char doubled_pixel = (imgshrink[f][k][r] + imgshrink[f + 1][k + 1][r]) / 2;
        imgRGB[i][j][r] = doubled_pixel;
    }
    }
    for (int i = 0, f = 0; i < SIZE / 3; ++i, f += 3){
    for (int j = 0, k = 0; j < SIZE / 3; ++j, k += 3){
        unsigned char doubled_pixel = (imgshrink[f][k][b] + imgshrink[f + 1][k + 1][b]) / 2;
        imgRGB[i][j][b] = doubled_pixel;
    }
    }
    for (int i = 0, f = 0; i < SIZE / 3; ++i, f += 3){
    for (int j = 0, k = 0; j < SIZE / 3; ++j, k += 3){
        unsigned char doubled_pixel = (imgshrink[f][k][g] + imgshrink[f + 1][k + 1][g]) / 2;
        imgRGB[i][j][g] = doubled_pixel;
    }
    }

}

void ShrinkRGB(){
    cout << "Shrink to (1/2), (1/3) or (1/4)?\n";
    string shrinkawy; cin >> shrinkawy;
    if (shrinkawy == "1/2") Shrink50RGB();
    if (shrinkawy == "1/3") Shrink33RGB();
    if (shrinkawy == "1/4") Shrink25RGB();
}

//________________________________________________________Blur

void BlurRGB(){

for (int i = 0; i < 2; ++i){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; j++){
            int r = 1;
            unsigned char blurred_R = (imgRGB[i][j][r] + imgRGB[i + 1][j + 1][r] + imgRGB[i + 1][j][r] + imgRGB[i][j + 1][r]
            + imgRGB[i - 1][j][r] + imgRGB[i][j - 1][r] + imgRGB[i + 1][j - 1][r] + imgRGB[i - 1][j + 1][r] + imgRGB[i - 1][j - 1][r]) / 9;
            imgRGB[i][j][r] = blurred_R;
        }
        
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; j++){
            int b = 2;
            unsigned char blurred_R = (imgRGB[i][j][b] + imgRGB[i + 1][j + 1][b] + imgRGB[i + 1][j][b] + imgRGB[i][j + 1][b]
            + imgRGB[i - 1][j][b] + imgRGB[i][j - 1][b] + imgRGB[i + 1][j - 1][b] + imgRGB[i - 1][j + 1][b] + imgRGB[i - 1][j - 1][b]) / 9;
            imgRGB[i][j][b] = blurred_R;
        }
        
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; j++){
            int g = 3;
            unsigned char blurred_R = (imgRGB[i][j][g] + imgRGB[i + 1][j + 1][g] + imgRGB[i + 1][j][g] + imgRGB[i][j + 1][g]
            + imgRGB[i - 1][j][g] + imgRGB[i][j - 1][g] + imgRGB[i + 1][j - 1][g] + imgRGB[i - 1][j + 1][g] + imgRGB[i - 1][j - 1][g]) / 9;
            imgRGB[i][j][g] = blurred_R;
        }
        
    }
    }


}

//________________________________________________________Merge


void MergeRGB(){
    unsigned char img_to_mergeRGB[SIZE][SIZE][RGB];
    cout << "Load the Image you wanna merge withn\n";
    char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   
   readRGBBMP(imageFileName, img_to_mergeRGB);

    int r = 1, b = 2, g = 3;
   for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
        unsigned char merged_pixel = (imgRGB[i][j][r] + img_to_mergeRGB[i][j][r]) / 2;
        imgRGB[i][j][r] = merged_pixel;
    }
   }
   for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
        unsigned char merged_pixel = (imgRGB[i][j][g] + img_to_mergeRGB[i][j][g]) / 2;
        imgRGB[i][j][g] = merged_pixel;
    }
   }
   for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
        unsigned char merged_pixel = (imgRGB[i][j][b] + img_to_mergeRGB[i][j][b]) / 2;
        imgRGB[i][j][b] = merged_pixel;
    }
   }
}

//________________________________________________________Lighten & Darken

void Lighten(){
    int r = 1, b = 2, g = 3;
    for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
        imgRGB[i][j][r] = (imgRGB[i][j][r] + 255) / 2;
    }
   }

   for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
        imgRGB[i][j][b] = (imgRGB[i][j][b] + 255) / 2;
    }
   }

   for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
        imgRGB[i][j][g] = (imgRGB[i][j][g] + 255) / 2;
    }
   }
}

void Darken(){
    int r = 1, b = 2, g = 3;
    for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
        imgRGB[i][j][r] = (imgRGB[i][j][r]) / 2;
    }
   }

   for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
        imgRGB[i][j][b] = (imgRGB[i][j][b]) / 2;
    }
   }

   for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
        imgRGB[i][j][g] = (imgRGB[i][j][g]) / 2;
    }
   }

}

void Lighten_DarkenRGB(){
    cout << "(L)ighten or (D)arken\n";
    char choice; cin >> choice;
    if (choice == 'L' || choice == 'l')
        Lighten();
    else if (choice == 'D' || choice == 'd')
        Darken();
}