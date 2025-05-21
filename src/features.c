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
    printf("Hello World !");
}

void dimension (char *source_path){
    int width, height, channel_count;
    unsigned char *data;
    int resultat = read_image_data(source_path, &data, &width, &height, &channel_count);
    if (resultat){
        printf("dimension : %d,%d",width,height);
    }
    else{
        printf("Erreur lors de la lecture du fichier");
    }
}

void first_pixel (char *source_path){
    int r,g,b;
    int width, height, channel_count;
    unsigned char *data;
    int resultat = read_image_data(source_path, &data, &width, &height, &channel_count);
    r = data[0];
    g = data[1];
    b = data[2];
    if (resultat){
        printf("first_pixel: %d, %d, %d",r,g,b);
    }
    else{
        printf("Erreur lors de la lecture du fichier");
    }
}

void tenth_pixel (char *source_path){
    int r,g,b;
    int width, height, channel_count;
    unsigned char *data;
    int resultat = read_image_data(source_path, &data, &width, &height, &channel_count);
    r = data[27];
    g = data[28];
    b = data[29];
    if (resultat){
        printf("tenth_pixel: %d, %d, %d",r,g,b);
    }
    else{
        printf("Erreur lors de la lecture du fichier");
    }
}

void second_line(char *source_path){
    int r,g,b;
    int width, height, channel_count;
    unsigned char *data;
    int resultat = read_image_data(source_path, &data, &width, &height, &channel_count);
    r = data[3*width];
    g = data[3*width+1];
    b = data[3*width+2];
    if (resultat){
        printf("second_line: %d, %d, %d",r,g,b);
    }
    else{
        printf("Erreur lors de la lecture du fichier");
    }
}