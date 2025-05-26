#include <estia-image.h>
#include <stdio.h>

#include "features.h"
#include "utils.h"

/**
 * @brief Here, you have to code features of the project.
 * Do not forget to commit regurlarly your changes.
 * Your commit messages must contain "#n" with: n = number of the corresponding feature issue.
 * When the feature is totally implemented, your commit message must contain "close #n".
 */

void helloWorld() {
    printf("Hello World !!!");
}
void dimension(char *source_path){
    int width, height, channel_count;
    unsigned char *data;
    int resultat = read_image_data(source_path, &data, &width, &height, &channel_count);
    if (resultat==1){
        printf("dimension: %d,%d", width, height); 
    }
    else {
        printf("Erreur lors de la lecture de l'image");
    }

}

void first_pixel (char *source_path){
    unsigned char *data;
    int width, height, channel_count;
    int resultat = read_image_data(source_path, &data, &width, &height, &channel_count);
    if (resultat==1){
        int r = data[0] , g = data[1], b = data[2];
        printf("first_pixel: %d, %d, %d", r,g,b);
    }
    else {
        printf("Erreur lors de la lecture de l'image");
    }
}

void tenth_pixel (char *source_path){
    unsigned char *data;
    int width, height, channel_count;
    int resultat = read_image_data(source_path, &data, &width, &height, &channel_count);
    if(resultat){
        int r=data[27], g = data[28], b= data[29];
        printf("tenth_pixel: %d,%d,%d",r,g,b);
    }
    else{
        printf("Erreur lors de la lecture de l'image");
    }
}


void second_line(char *source_path){
    unsigned char *data;
    int width, height, channel_count;
    int resultat = read_image_data(source_path, &data, &width, &height, &channel_count);
    if(resultat){
        int r=data[3*width], g = data[3*width+1], b= data[3*width+2];
        printf("second_line: %d, %d, %d",r,g,b);
    }
    else{
        printf("Erreur lors de la lecture de l'image");
    }
}

void print_pixel( char *filename, int x, int y ){
    unsigned char *data;
    int width, height, channel_count;
    //printf("Je suis passe ici\n");
    int resultat = read_image_data(filename, &data, &width, &height, &channel_count);

    if(resultat){
        pixelRGB * pixel = get_pixel(data, width, height, channel_count, x, y );
        printf("print_pixel (%d, %d): %d, %d, %d",x,y, pixel->R, pixel->G, pixel->B );   
    }
    else{
        printf("Erreur lors de la lecture de l'image\n");
    }
}