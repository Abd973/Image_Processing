// Ibrahim Hassan Mohammed Hassan - 20210002 - ibrahimhassannamr@gmail.com
// Abdulmalik Mahmoud Hussein     - 20220205 - abdelmaleka011@gamil.com
// Islam Mohammed Ahmed Ali       - 20220059 - islmslm999@gmail.com

#include <iostream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
using namespace std;

unsigned char image[SIZE][SIZE][RGB];

//_____________________________________________
void loadImage(){
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name:";
    cin >> imageFileName;
    cout << "___________________________________________________\n";

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}

//_____________________________________________
void saveImage (){
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
}

//_____________________________________________


//_____________________________________________
void RGB_Black_and_White_image(){
    for(int i{0}; i < 256; i++){
        for (int j{0}; j < 256; j++) {
            if (image[i][j][0] > 128 || image[i][j][1] > 128 || image[i][j][2] > 128)
                image[i][j][0] = 255, image[i][j][1] = 255, image[i][j][2] = 255;
            else image[i][j][0] = 0, image[i][j][1] = 0, image[i][j][2] = 0;
        }
    }
}

//_____________________________________________
void InvertRGB() {
    for(int i{0}; i < RGB; i++){
        for (int j{0}; j < SIZE; j++){
            for (int k{0}; k < SIZE; k++){
                image[j][k][i] = 255 - image[j][k][i];
            }
        }
    }
}

//_____________________________________________
void MergeRGB(){
    unsigned char img_to_mergeRGB[SIZE][SIZE][RGB];
    unsigned char merged_pixel;
    char imageFileName[100];

    // Get RGB image file name
    cout << "Please enter name of image file to merge with:\n";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    readRGBBMP(imageFileName, img_to_mergeRGB);

    for(int i{0}; i < 3; i++){
        for (int j{0}; j < SIZE; j++) {
            for (int k{0}; k < SIZE; k++) {
                merged_pixel = (image[j][k][i] + img_to_mergeRGB[j][k][i]) / 2;
                image[j][k][i] = merged_pixel;
            }
        }
    }
}

//_____________________________________________
void RGB_image_Flip()
{
    unsigned char pixel{};
    char choice;

    // get user choice
    cout << "Flip (h)orizontally or (v)ertically\n";
    cin >> choice;

    // applying the horizontal flib
    if(choice == 'h' || choice == 'H'){
        for (int i{0}; i < 3; i++)
            for (int j{0}; j < 256; j++)
                for (int k{0}; k < 128; k++)
                    pixel = image[j][k][i], image[j][k][i] = image[j][255 - k][i], image[j][255 - k][i] = pixel;
    }

    // applying the vertical flib
    else if(choice == 'V' || choice == 'v'){
        for(int i{0}; i < 3; i++)
            for(int j{0}; j < 256; j++)
                for(int k{0}; k < 128; k++)
                    pixel = image[k][j][i], image[k][j][i] = image[255 - k][j][i], image[255 - k][j][i] = pixel;
    }
}

//_____________________________________________
void RotateRGB(){

    unsigned char image2[SIZE][SIZE][RGB]{};
    int degree{};

    // getting the rotate degree
    cout << "Rotate (90), (180) or (270) degrees\n";
    cin >> degree;

    // 90-degree rotation algorithm
    if (degree == 90){
        for(int i{0}; i < RGB; i++){
            for(int j{0}; j < SIZE; j++){
                for(int k{0}; k < SIZE; k++){
                    image2[k][j][i] = image[255 - j][k][i];
                }
            }
        }
    }

        // 180-degree rotation algorithm
    else if (degree == 180){
        for(int i{0}; i < RGB; i++) {
            for (int j{0}; j < SIZE; j++) {
                for (int k{0}; k < SIZE; k++) {
                    image2[j][k][i] = image[SIZE - j - 1][SIZE - k - 1][i];
                }
            }
        }
    }

        // 270-degree rotation algorithm
    else if (degree == 270) {
        for(int i{0}; i < RGB; i++) {
            for (int j{0}; j < SIZE; j++) {
                for (int k{0}; k < SIZE; k++) {
                    image2[k][j][i] = image[j][255 - k][i];
                }
            }
        }
    }

    // applying the changes on the original image
    for(int i{0}; i < RGB; i++){
        for(int j{0}; j < SIZE; j++){
            for(int k{0}; k < SIZE; k++){
            image[j][k][i] = image2[j][k][i];
            }
        }
    }

}

//_____________________________________________
void RGB_Darken_and_Lighten(){
    char choice;

    cout << "(L)ighten or (D)arken\n";
    cin >> choice;

    // lighten algorithm
    if(choice == 'L' || choice == 'l'){
        for(int i{0}; i < RGB; i++){
            for(int j{0}; j < SIZE; j++){
                for(int k{0}; k < SIZE; k++){
                    image[j][k][i] = (image[j][k][i] + 255) / 2;
                }
            }
        }
    }

    // darken algorithm
    else if (choice == 'D' || choice == 'd'){
        for(int i{0}; i < RGB; i++){
            for(int j{0}; j < SIZE; j++){
                for(int k{0}; k < SIZE; k++){
                    image[j][k][i] = image[j][k][i] / 2;
                }
            }
        }
    }
}

//_____________________________________________
void Detect_RGB_Image_Edges(){

    unsigned char image2[256][256][3]{};
    bool red_pixel, blue_pixel, green_pixel;
    int interval = 27;

    for (int i{0}; i < 256; i++)
        for (int j{0}; j < 256; j++) {
            if ((j + 1) < 256){
                red_pixel = (image[i][j + 1][0] - image[i][j][0] < interval && image[i][j + 1][0] - image[i][j][0] > -interval);
                green_pixel = (image[i][j + 1][1] - image[i][j][1] < interval && image[i][j + 1][1] - image[i][j][1] > -interval);
                blue_pixel = (image[i][j + 1][2] - image[i][j][2] < interval && image[i][j + 1][2] - image[i][j][2] > -interval);
                if(!red_pixel || !green_pixel || !blue_pixel) {
                    image2[i][j][0] = 0, image2[i][j][1] = 0, image2[i][j][2] = 0;
                    continue;
                }
            }

            if (0 <= (j - 1)){
                red_pixel = image[i][j - 1][0] - image[i][j][0] < interval && image[i][j - 1][0] - image[i][j][0] > -interval;
                green_pixel = image[i][j - 1][1] - image[i][j][1] < interval && image[i][j - 1][1] - image[i][j][1] > -interval;
                blue_pixel = image[i][j - 1][2] - image[i][j][2] < interval && image[i][j - 1][2] - image[i][j][2] > -interval;
                if(!red_pixel || !green_pixel || !blue_pixel) {
                    image2[i][j][0] = 0, image2[i][j][1] = 0, image2[i][j][2] = 0;
                    continue;
                }
            }


            if ((i + 1) < 256){
                red_pixel = image[i + 1][j][0] - image[i][j][0] < interval && image[i + 1][j][0] - image[i][j][0] > -interval;
                green_pixel = image[i + 1][j][1] - image[i][j][1] < interval && image[i + 1][j][1] - image[i][j][1] > -interval;
                blue_pixel = image[i + 1][j][2] - image[i][j][2] < interval && image[i + 1][j][2] - image[i][j][2] > -interval;
                if(!red_pixel || !green_pixel || !blue_pixel) {
                    image2[i][j][0] = 0, image2[i][j][1] = 0, image2[i][j][2] = 0;
                    continue;
                }
            }


            if (0 <= (i - 1)) {
                red_pixel = image[i - 1][j][0] - image[i][j][0] < interval && image[i - 1][j][0] - image[i][j][0] > -interval;
                green_pixel = image[i - 1][j][1] - image[i][j][1] < interval && image[i - 1][j][1] - image[i][j][1] > -interval;
                blue_pixel = image[i - 1][j][2] - image[i][j][2] < interval && image[i - 1][j][2] - image[i][j][2] > -interval;
                if(!red_pixel || !green_pixel || !blue_pixel) {
                    image2[i][j][0] = 0, image2[i][j][1] = 0, image2[i][j][2] = 0;
                    continue;
                }
            }


            if (0 <= (j - 1) && 0 <= (i - 1)){
                red_pixel = image[i - 1][j - 1][0] - image[i][j][0] < interval && image[i - 1][j - 1][0] - image[i][j][0] > -interval;
                green_pixel = image[i - 1][j - 1][1] - image[i][j][1] < interval && image[i - 1][j - 1][1] - image[i][j][1] > -interval;
                blue_pixel = image[i - 1][j - 1][2] - image[i][j][2] < interval && image[i - 1][j - 1][2] - image[i][j][2] > -interval;
                if(!red_pixel || !green_pixel || !blue_pixel) {
                    image2[i][j][0] = 0, image2[i][j][1] = 0, image2[i][j][2] = 0;
                    continue;
                }
            }


            if ((j + 1) < 256 && 0 <= (i - 1)) {
                red_pixel = image[i - 1][j + 1][0] - image[i][j][0] < interval && image[i - 1][j + 1][0] - image[i][j][0] > -interval;
                green_pixel = image[i - 1][j + 1][1] - image[i][j][1] < interval && image[i - 1][j + 1][1] - image[i][j][1] > -interval;
                blue_pixel = image[i - 1][j + 1][2] - image[i][j][2] < interval && image[i - 1][j + 1][2] - image[i][j][2] > -interval;
                if(!red_pixel || !green_pixel || !blue_pixel) {
                    image2[i][j][0] = 0, image2[i][j][1] = 0, image2[i][j][2] = 0;
                    continue;
                }
            }

            if (0 <= (j - 1) && (i + 1) < 256 ){
                red_pixel = image[i + 1][j - 1][0] - image[i][j][0] < interval && image[i + 1][j - 1][0] - image[i][j][0] > -interval;
                green_pixel = image[i + 1][j - 1][1] - image[i][j][1] < interval && image[i + 1][j - 1][1] - image[i][j][1] > -interval;
                blue_pixel = image[i + 1][j - 1][2] - image[i][j][2] < interval && image[i + 1][j - 1][2] - image[i][j][2] > -interval;
                if(!red_pixel || !green_pixel || !blue_pixel) {
                    image2[i][j][0] = 0, image2[i][j][1] = 0, image2[i][j][2] = 0;
                    continue;
                }
            }


            if ((j + 1) < 256 && (i + 1) < 256){
                red_pixel = image[i + 1][j + 1][0] - image[i][j][0] < interval && image[i + 1][j + 1][0] - image[i][j][0] > -interval;
                green_pixel = image[i + 1][j + 1][1] - image[i][j][1] < interval && image[i + 1][j + 1][1] - image[i][j][1] > -interval;
                blue_pixel = image[i + 1][j + 1][2] - image[i][j][2] < interval && image[i + 1][j + 1][2] - image[i][j][2] > -interval;
                if(!red_pixel || !green_pixel || !blue_pixel) {
                    image2[i][j][0] = 0, image2[i][j][1] = 0, image2[i][j][2] = 0;
                    continue;
                }
            }

            image2[i][j][0] = 255, image2[i][j][1] = 255, image2[i][j][2] = 255;

        }

    for(int i{0}; i < RGB; i++)
        for (int j{0}; j < SIZE; j++)
            for(int k{0}; k < SIZE; k++)
                image[j][k][i] = image2[j][k][i];
}

//_____________________________________________
void Enlarge_RGB_Image() {

    int quarter{};
    cout << "Enter the Quarter NO. you want to enlarge:\n";
    cin >> quarter;
    unsigned char image2[SIZE][SIZE][RGB]{};


    if(quarter == 1) {          //top-left quarter
        for(int i{0}; i < RGB; i++){
            for (int j{0}; j < SIZE; j++){
                for (int k{0}; k < SIZE; k++){
                    image2[j][k][i] = image[j / 2][k / 2][i];
                }
            }
        }
    }


    else if(quarter == 2) {     //top-right quarter
        for(int i{0}; i < RGB; i++){
            for (int j{0}; j < SIZE; j++){
                for (int k{0}; k < SIZE; k++){
                    image2[j][k][i] = image[j / 2][SIZE / 2 + k / 2][i];
                }
            }
        }


    }

    else if(quarter == 3){      //lower-left quarter
        for(int i{0}; i < RGB; i++){
            for (int j{0}; j < SIZE; j++){
                for (int k{0}; k < SIZE; k++){
                    image2[j][k][i] = image[SIZE / 2 + j / 2][k / 2][i];
                }
            }
        }
    }

    else if (quarter == 4) {      //lower-right quarter
        for(int i{0}; i < RGB; i++){
            for (int j{0}; j < SIZE; j++){
                for (int k{0}; k < SIZE; k++){
                    image2[j][k][i] = image[SIZE / 2 + j / 2][SIZE / 2 + k / 2][i];
                }
            }
        }
    }


    // applying the changes on the original image
    for(int i{0}; i < RGB; i++){
        for (int j{0}; j < SIZE; j++){
            for (int k{0}; k < SIZE; k++){
                image[j][k][i] = image2[j][k][i];
            }
        }
    }
}

//_____________________________________________
void ShrinkRGB(){

    unsigned char image2[SIZE][SIZE][RGB]{};
    unsigned char doubled_pixel{};
    string choice;

    cout << "Shrink to (1/2), (1/3) or (1/4)?\n";
    cin >> choice;


    for(int i{0}; i < RGB; i++){
        for (int j{0}; j < SIZE; j++){
            for (int k{0}; k < SIZE; k++){
                image2[j][k][i] = image[j][k][i], image[j][k][i] = 255;
            }
        }
    }

    if (choice == "1/2"){
        for(int i{0}; i < RGB; i++){
            for (int j{0}, f{0}; j < SIZE / 2; j++, f += 2){
                for (int k{0}, s{0}; k < SIZE / 2; k++, s += 2){
                    doubled_pixel = (image2[f][s][i] + image2[f + 1][s + 1][i]) / 2;
                    image[j][k][i] = doubled_pixel;
                }
            }
        }
    }


    if (choice == "1/3"){
        for(int i{0}; i < RGB; i++){
            for (int j{0}, f{0}; j < SIZE / 3; j++, f += 3){
                for (int k{0}, s{0}; k < SIZE / 3; k++, s += 3){
                    doubled_pixel = (image2[f][s][i] + image2[f + 1][s + 1][i]) / 2;
                    image[j][k][i] = doubled_pixel;
                }
            }
        }
    }


    if (choice == "1/4"){
        for(int i{0}; i < RGB; i++){
            for (int j{0}, f{0}; j < SIZE / 4; j++, f += 4){
                for (int k{0}, s{0}; k < SIZE / 4; k++, s += 4){
                    doubled_pixel = (image2[f][s][i] + image2[f + 1][s + 1][i]) / 2;
                    image[j][k][i] = doubled_pixel;
                }
            }
        }
    }


}

//_____________________________________________
void RGB_Mirror(){

    char choice;

    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side\n";
    cin >> choice;

    if(choice == 'l' || choice == 'L'){

        for(int i{0}; i < RGB; i++)
            for(int j{0}; j < SIZE; j++)
                for(int k{0}; k < SIZE / 2; k++)
                    image[j][(SIZE - 1) - k][i] = image[j][k][i];
    }

    if(choice == 'r' || choice == 'R'){

        for(int i{0}; i < RGB; i++)
            for(int j{0}; j < SIZE; j++)
                for(int k{0}; k < SIZE / 2; k++)
                    image[j][k][i] = image[j][(SIZE - 1) - k][i];
    }

    if(choice == 'u' || choice == 'U'){
        for(int i{0}; i < RGB; i++)
            for(int j{0}; j < SIZE / 2; j++)
                for(int k{0}; k < SIZE; k++)
                    image[(SIZE - 1) - j][k][i] = image[j][k][i];
    }

    if(choice == 'd' || choice == 'D'){
        for(int i{0}; i < RGB; i++)
            for(int j{0}; j < SIZE / 2; j++)
                for(int k{0}; k < SIZE; k++)
                    image[j][k][i] = image[(SIZE - 1) - j][k][i];
    }

}

//_____________________________________________
void ShuffleRGB() {

    unsigned char image2[SIZE][SIZE][RGB]; // we store here the new result
    int seq[4]{}; // array tho save the sequence of new image


    // those variables used to detect the initial index of the quarter which will be copied of the old image
    int old_row_idx{}, old_column_idx{};

    // those variables used to detect the initial index of the quarter which will be filled on the new image
    int new_row_idx{}, new_column_idx{};

    cout << "Enter the New order of Quarters \n";
    for(int i{0}; i < 4; i++)
        cin >> seq[i];

    // applying the filter
    for(int i{0}; i < 4; i++){
        new_row_idx = 0, new_column_idx = 0;
        old_row_idx = 0, old_column_idx = 0;

        // detect the initial index of the quarter which will be copied
        if(seq[i] == 2 || seq[i] == 4) old_column_idx = SIZE / 2;
        if(seq[i] == 3 || seq[i] == 4) old_row_idx = SIZE / 2;

        // detect the initial index of the quarter which will be filled
        if(i == 1 || i == 3) new_column_idx = SIZE / 2;
        if(i == 2 || i == 3) new_row_idx = SIZE / 2;


        // filling the quarters
        for(int s{0}; s < RGB; s++){
            for (int j{0}; j < SIZE / 2; j++){
                for (int k{0}; k < SIZE / 2; k++){
                    image2[new_row_idx + j][new_column_idx + k][s] = image[old_row_idx + j][old_column_idx + k][s];
                }
            }
        }
    }

    // applying the changes on the original image
    for(int i{0}; i < RGB; i++){
        for (int j{0}; j < SIZE; j++){
            for (int k{0}; k < SIZE; k++){
                image[j][k][i] = image2[j][k][i];
            }
        }
    }

}
//_____________________________________________
void BlurRGB(){
    unsigned char doubled_pixel{};
    // Takes average for each pixel with its all adjacent pixels
    for (int i = 0; i < 2; ++i){
        for(int s{0}; s < RGB; s++){
            for (int i{0}; i < SIZE; i++){
                for (int j{0}; j < SIZE; j++){
                    doubled_pixel = (image[i][j][s] + image[i + 1][j + 1][s] + image[i + 1][j][s] + image[i][j + 1][s]
                                    + image[i - 1][j][s] + image[i][j - 1][s] + image[i + 1][j - 1][s] + image[i - 1][j + 1][s] +
                                    image[i - 1][j - 1][s]) / 9;
                                    image[i][j][s] = doubled_pixel;
                }
            }
        }
    }
}

//_____________________________________________
void RGB_Crop(){
    int x, y, l, w;

    cout << "Please enter x y l w\n";
    cin >> x >> y >> l >> w;
    if(y + l - 2 > SIZE || x + w - 2 > SIZE) return;

    for(int i{0}; i < SIZE; i++)
        for(int j{0}; j < SIZE; j++)
            if(!(i >= y - 1 && i <= l + y - 2) || !(j >= x - 1 && j <= x + w - 2))
                image[i][j][0] = 255, image[i][j][1] = 255, image[i][j][2] = 255;
}

//_____________________________________________
void Skew_V(){

    int n;
    cout << "Please enter degree to skew right:\n";
    cin >> n;


    unsigned char img1[SIZE][SIZE][RGB];
    for (int color = 0; color < 3; ++color){
    for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
       img1[i][j][color] = image[i][j][color];
       image[i][j][color] = 255;
    }
    }
    }

    double rad = n * (M_PI/180.0);      //convert from degree to radian
    double scale = 1 / (1 + tan(rad));  //shrink factor to fit the given image into output image
    double dist = 255 - scale * 255;    //distance that will be white 
    for (int color = 0; color < RGB; ++color){
        for (int j = 0; j < SIZE; j++)
        {
            for (int i = 0; i < SIZE; i++)
            {
                double x = i;
                x *= scale;
                x += dist;

                image[int(x)][j][color] = img1[i][j][color];
            }
            dist -= ((256 - scale * 255) / 255);
        }

        dist = 255 - scale * 255;
    }
}

void Skew_H(){

    int n;
    cout << "Please enter degree to skew right:\n";
    cin >> n;


    unsigned char img1[SIZE][SIZE][RGB];
    for (int color = 0; color < 3; ++color){
    for (int i = 0; i < SIZE; ++i){
    for (int j = 0; j < SIZE; ++j){
       img1[i][j][color] = image[i][j][color];
       image[i][j][color] = 255;
    }
    }
    }

    double rad = n * (M_PI/180.0);      //convert from degree to radian
    double scale = 1 / (1 + tan(rad));  //shrink factor to fit the given image into output image
    double dist = 255 - scale * 255;    //distance that will be white 
    for (int color = 0; color < RGB; ++color){
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                double x = j;
                x *= scale;
                x += dist;

                image[i][int(x)][color] = img1[i][j][color];
            }
            dist -= ((256 - scale * 255) / 255);
        }

        dist = 255 - scale * 255;
    }

    
}

void Skew() {
    cout << "Skew (H)orizontally or (V)ertically\n";
    char choice; cin >> choice;
    if (choice == 'h' || 'H')
        Skew_H();
    else if (choice == 'v' || choice == 'V')
        Skew_V();
    else cout << "Not Defined Function!\n";
}
//_____________________________________________
//_____________________________________________

void menu(){

    string FilterNo{};

    while(true){
        cout << "1) Black & White Filter\n"
             << "2) Invert Filter\n"
             << "3) Merge Images\n"
             << "4) Flip Image\n"
             << "5) Rotate Images\n"
             << "6) Darken and Lighten Image\n"
             << "7) Detect Image Edges\n"
             << "8) Enlarge Image\n"
             << "9) Shrink Image\n"
             << "10) Mirror Image\n"
             << "11) Shuffle Image\n"
             << "12) Blur Image\n"
             << "13) Crop Image\n"
             << "14) Skew Image\n"
             << "S- Save Image\n"
             << "0) Exit\n"
             << "___________________________________________________\n";
        cin >> FilterNo;
        cout << "___________________________________________________\n";

        if(FilterNo == "1")
            RGB_Black_and_White_image();

        else if(FilterNo == "2")
            InvertRGB();

        else if(FilterNo == "3")
            MergeRGB();

        else if(FilterNo == "4")
            RGB_image_Flip();

        else if(FilterNo == "5")
            RotateRGB();

        else if(FilterNo == "6")
            RGB_Darken_and_Lighten();

        else if(FilterNo == "7")
            Detect_RGB_Image_Edges();

        else if(FilterNo == "8")
            Enlarge_RGB_Image();

        else if(FilterNo == "9")
            ShrinkRGB();

        else if(FilterNo == "10")
            RGB_Mirror();

        else if(FilterNo == "11")
            ShuffleRGB();

        else if(FilterNo == "12")
            BlurRGB();

        else if(FilterNo == "13")
            RGB_Crop();

        else if(FilterNo == "14")
            Skew();

        else if(FilterNo == "S"  || FilterNo == "s"){
            saveImage();
            cout << "Image saved\n"
                 << "___________________________________________________\n";
            continue;
        }

        else if(FilterNo == "0"){
            cout << "Terminated\n"
                 << "___________________________________________________\n";
            break;
        }
        else {
            cout << "Not Defined Filter\n"
            << "___________________________________________________\n";
            continue;
        }
        cout << "Filter Applied\n"
             << "___________________________________________________\n";
    }

}

//_____________________________________________


int main() {
    loadImage();
    menu();
    return 0;
}