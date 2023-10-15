#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];

void loadImage ();
void saveImage ();
void Black_and_White ();
void merge ();
void Darken_and_Lighten ();
void Shrink ();
void Blur ();
void menu ();

int main() {

    loadImage();
    menu();
    saveImage();

    return 0;
}

//_________________________________________
void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   
   readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image);
}

//_________________________________________
void Black_and_White() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j< SIZE; j++) {
        if (image[i][j] > 127)
            image[i][j] = 255;
        else
            image[i][j] = 0;

    }
  }
}

//_________________________________________
void menu(){    

    cout << "Enter which filter do you want to apply: " << endl;

    string filters[] = {
        "1  - Black and White Image",
        "2  - Invert Image",
        "3  - Merge Images",
        "4  - Flip Image",
        "5  - Rotate Image",
        "6  - Darken and Lighten Image",
        "7  - Detect Image Edges",
        "8  - Enlarge Image",
        "9  - Shrink Image",
        "10 - Mirror Image",
        "11 - Shuffle Image",
        "12 - Blur Image",
        "0  - Exit"
    };

    for (int i = 0; i < 12; ++i){
        cout << filters[i] << endl;
    }

    int FilterNO; cin >> FilterNO;

    switch(FilterNO){
        case(0):
            cout << "Terminated\n";
            return;

        case(1):
            Black_and_White();
            break;

        case(2):
            
            break;

        case(3):
            merge();
            break;

        case(4):
            
            break;

        case(5):
            
            break;

        case(6):
            Darken_and_Lighten();
            break;

        case(7):
            
            break;

        case(8):
            
            break;

        case(9):
            Shrink();
            break;

        case(10):
            
            break;

        case(11):
            
            break;
        case(12):
            Blur();
            break;
    }

}

void Lighten(){
    for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
        image[i][j] = (image[i][j] + 255) / 2;
    }
   }


}

void Darken(){
    for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
        image[i][j] = (image[i][j]) / 2;
    }
   }
}

void Darken_and_Lighten(){
    cout << "(L)ighten or (D)arken\n";
    char choice; cin >> choice;
    if (choice == 'L' || choice == 'l')
        Lighten();
    else if (choice == 'D' || choice == 'd')
        Darken();
}

void Shrink50(){

    unsigned char imgshrink[SIZE][SIZE];
    
    for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
       imgshrink[i][j] = image[i][j];
       image[i][j] = 255;
    }
   }

    for (int i = 0, f = 0; i < SIZE / 2; ++i, f += 2){
    for (int j = 0, k = 0; j < SIZE / 2; ++j, k += 2){
        unsigned char doubled_pixel = (imgshrink[f][k] + imgshrink[f + 1][k + 1]) / 2;
        image[i][j] = doubled_pixel;
    }
   }
}

void Shrink25(){
    unsigned char imgshrink[SIZE][SIZE];
    
    for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
       imgshrink[i][j] = image[i][j];
       image[i][j] = 255;
    }
   }

   for (int i = 0, f = 0; i < SIZE / 4; ++i, f += 4){
    for (int j = 0, k = 0; j < SIZE / 4; ++j, k += 4){
        unsigned char doubled_pixel = (imgshrink[f][k] + imgshrink[f + 1][k + 1]) / 2;
        image[i][j] = doubled_pixel;
    }
   }
}

void Shrink33(){
    unsigned char imgshrink[SIZE][SIZE];
    
    for (int i = 0, f = 0; i < SIZE; ++i){
    for (int j = 0, k = 0; j < SIZE; ++j){
       imgshrink[i][j] = image[i][j];
       image[i][j] = 255;
    }
   }

   for (int i = 0, f = 0; i < SIZE / 3; ++i, f += 3){
    for (int j = 0, k = 0; j < SIZE / 3; ++j, k += 3){
        unsigned char doubled_pixel = (imgshrink[f][k] + imgshrink[f + 1][k + 1]) / 2;
        image[i][j] = doubled_pixel;
    }
   }
}

void Shrink(){
    cout << "Shrink to (1/2), (1/3) or (1/4)?\n";
    string shrinkawy; cin >> shrinkawy;
    if (shrinkawy == "1/2") Shrink50();
    if (shrinkawy == "1/3") Shrink33();
    if (shrinkawy == "1/4") Shrink25();
}

void Blur(){
    for (int i = 0; i < SIZE; ++i){
     for (int j = 0; j < SIZE ; ++j){
            unsigned char doubled_pixel = (image[i][j] + image[i + 1][j + 1] + image[i + 1][j] + image[i][j + 1]
            + image[i - 1][j] + image[i][j - 1] + image[i + 1][j - 1] + image[i - 1][j + 1] + image[i - 1][j - 1]) / 9;
            image[i][j] = doubled_pixel;
     }
    }
    for (int i = 0; i < SIZE; ++i){
     for (int j = 0; j < SIZE; ++j){
            unsigned char doubled_pixel = (image[i][j] + image[i + 1][j + 1] + image[i + 1][j] + image[i][j + 1]
            + image[i - 1][j] + image[i][j - 1] + image[i + 1][j - 1] + image[i - 1][j + 1] + image[i - 1][j - 1]) / 9;
            image[i][j] = doubled_pixel;
     }
    }
}

void merge(){
    unsigned char img_to_merge[SIZE][SIZE];
    cout << "Load the Image you wanna merge withn\n";
    char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   
   readGSBMP(imageFileName, img_to_merge);

   for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
        unsigned char merged_pixel = (image[i][j] + img_to_merge[i][j]) / 2;
        image[i][j] = merged_pixel;
    }
   }

}

