// CellExtraction.c 
// (Relies upon a color-segmented DIC image in .PPM format)
// 
// Wu Lab, Johns Hopkins University
//
// Author: Sun Jay Yoo
// Date: June 15, 2017

#include <stdio.h>

#include <string.h>
#include <stdlib.h>

typedef struct { 
    unsigned char red; 
    unsigned char green; 
    unsigned char blue; 
} pixels;

typedef struct {
     int x;
     int y;
     pixels *pixelData;
} image;

int redInput;
int greenInput;
int blueInput;

image* readFile(char *filename){
    char header[16];
    image *img;
    int comments, colors;
    FILE *finput = fopen(filename, "r");
    if (finput == NULL) {
        puts("Error Code 1: file does not exist or file is NULL.\n");
        exit(1);
    }
    if (fgets(header, sizeof(header), finput) == NULL) {
        puts("Error Code 2: improper .PPM header.\n");
        exit(1);
    }
    if (!(header[0] == 'P' && header[1] == '6')) {
         puts("Error Code 3: not a P6 file.\n");
         exit(1);
    }
    img = (image *) malloc(sizeof(image));
    comments = getc(finput);
    while (comments == '#') {
        while (getc(finput) != '\n') ;
        comments = getc(finput);
    }
    ungetc(comments, finput);
    //read image size information
    if (fscanf(finput, "%d %d", &img->x, &img->y) != 2) {
         puts("Error Code 4: improper image size (not 2x2).\n");
         exit(1);
    }

    //read rgb component
    if (fscanf(finput, "%d", &colors) != 1) {
         puts("Error Code 5: improper color encoding.\n");
         exit(1);
    }


    while (fgetc(finput) != '\n') ;
    //memory allocation for pixel pixelData
    img->pixelData = (pixels*) malloc(img->x * img->y * sizeof(pixels));

    //read pixel pixelData from file
    if (fread(img->pixelData, 3 * img->x, img->y, finput) != (unsigned long)img->y) {
         puts("Error Code 6: error opening file and reading pixel data.\n");
         exit(1);
    }

    fclose(finput);
    return img;
}

void writeFile(char *filename, image *img){
    FILE *finput = fopen(filename, "w");

    //write the header file
    //image format
    fprintf(finput, "P6\n");
    //image size
    fprintf(finput, "%d %d\n",img->x,img->y);
    // rgb component depth
    fprintf(finput, "%d\n",255);
    // pixel pixelData
    fwrite(img->pixelData, 3 * img->x, img->y, finput);
    fclose(finput);
}

void extract(image *img){
    int i;
    if(img){
         for(i=0;i<img->x*img->y;i++){
            if (img->pixelData[i].red == redInput && img->pixelData[i].green == greenInput && img->pixelData[i].blue == blueInput){
                img->pixelData[i].red = 255;
                img->pixelData[i].green = 255;
                img->pixelData[i].blue = 255;
            }
            else {
                img->pixelData[i].red = 0;
                img->pixelData[i].green = 0;
                img->pixelData[i].blue = 0;
            }

         }
    }
}

int main(){

    char *fileread = (char*) malloc(50*sizeof(char));
    char *filewrite = (char*) malloc(50*sizeof(char));

    puts("Type the ppm file name to read in current directory:");
    scanf("%s", fileread);
    image *newImage = readFile(fileread);

    int bool = 1;

    puts("Menu:\n"
        "'x' - extract color individually\n"
        "'a' - extract all colors automatically\n"
        "'q' - quit program:");
    while (bool){
        char i = getchar();
        if (i == 'x'){
            puts("Integer RED value:");
            scanf("%d", &redInput);
            puts("Integer GREEN value:");
            scanf("%d", &greenInput);
            puts("Integer BLUE value:");
            scanf("%d", &blueInput);
            puts("Output mask filename (ending in '.ppm'):");
            scanf("%s", filewrite);
            newImage = readFile(fileread);
            extract(newImage);
            writeFile(filewrite, newImage);
            puts("Menu:\n"
                "Type 'x' to extract colors individually.\n"
                "Type 'a' to extract all colors automatically.\n"
                "Type 'q' to quit program.");
        } else if (i == 'q'){
            bool = 0;
        }

    }
    return 0;
}
