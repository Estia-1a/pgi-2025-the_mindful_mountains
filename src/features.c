#include <estia-image.h>
#include <stdio.h>
#include <stdlib.h>

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

void max_pixel (char *filename){
    unsigned char *data;
    int width, height, channel_count;
    int resultat = read_image_data(filename, &data, &width, &height, &channel_count);

    int max_sum = -1;
    pixelRGB* max_pixel = NULL;
    unsigned int max_x = 0, max_y = 0;
    int x,y;


    if(resultat){
        for (y=0 ; y < height ; y++){
            for (x=0 ; x < width ; x++){
                pixelRGB * p = get_pixel(data, width, height, channel_count, x, y );
                if (p) {
                int sum = p->R + p->G + p->B;
                if (sum > max_sum) {
                    max_sum = sum;
                    max_pixel = p;
                    max_x = x;
                    max_y = y;
                }
            }
        }
    }

    if (max_pixel) {
        //printf("Max RGB sum pixel at (%u, %u): R=%d G=%d B=%d (Sum=%d)\n",
            //max_x, max_y, max_pixel->R, max_pixel->G, max_pixel->B, max_sum);
        printf("max_pixel (%u, %u): %d, %d, %d\n", max_x, max_y, max_pixel->R, max_pixel->G, max_pixel->B);
    } else {
        printf("No valid pixel found.\n");
    }
            }
    else{
        printf("Erreur lors de la lecture de l'image\n");
    }
}

void rotate_cw(char *source_path){
    unsigned char *data;
    int width, height, channel_count;
    int resultat = read_image_data(source_path, &data, &width, &height, &channel_count);
    if(resultat){
        int new_width = height;
        int new_height = width;
        unsigned char *rotated = malloc(width*height*channel_count);
        for (int y=0;y < height; y++){
            for (int x=0;x<width;x++){
                for(int c=0; c < channel_count; c++){
                    rotated[(x * new_width + (new_width - y - 1)) * channel_count + c] =
                    data[(y * width + x) * channel_count + c];
                }
            }
        }
        const char *dst_path= "image_out.bmp";
        resultat = write_image_data(dst_path, rotated, new_width, new_height);
        if(resultat==0){
            printf("Erreur lors de l'ouverture du fichier");
        }

    }
    else{
        printf("Erreur lors de la lecture de l'image\n");
    }

}

void rotate_acw(char *source_path){
    unsigned char *data;
    int width, height, channel_count;
    int resultat = read_image_data(source_path, &data, &width, &height, &channel_count);
    if(resultat){
        int new_width = height;
        int new_height = width;
        unsigned char *rotated = malloc(width*height*channel_count);
        for (int y=0;y < height; y++){
            for (int x=0;x<width;x++){
                for(int c=0; c < channel_count; c++){
                        rotated[((width - x - 1) * height + y) * channel_count + c] =
                        data[(y * width + x) * channel_count + c];
                }
            }
        }
        const char *dst_path= "image_out_acw.bmp";
        resultat = write_image_data(dst_path, rotated, new_width, new_height);
        if(resultat==0){
            printf("Erreur lors de l'ouverture du fichier");
        }

    }
    else {
        printf("Erreur lors de la lecture de l'image\n");        
    }
}

void mirror_horizontal(char *source_path){
    unsigned char *data;
    int width, height, channel_count;
    int resultat = read_image_data(source_path, &data, &width, &height, &channel_count);
    if(resultat){
        unsigned char *mirror = malloc(width*height*channel_count);
        for(int y=0; y<height;y++){
            for(int x=0; x<width;x++){
                pixelRGB *src_pixel = get_pixel(data, width, height, channel_count, x, y);

                int new_x = width -x -1;
                int new_y = y;
                pixelRGB *dst_pixel = get_pixel(mirror,width, height, channel_count, new_x, new_y);

                if (src_pixel && dst_pixel) {
                    *dst_pixel = *src_pixel; 
                }
            }
        }

        const char *dst_path = "image_mirror_horizontal.bmp";
        resultat = write_image_data(dst_path,mirror, width, height);
        if(resultat==0){
            printf("Erreur lors de l'ouverture du fichier");
        }
    }
    else {
        printf("Erreur lors de la lecture de l'image\n");        
    }

}





void min_pixel (char *filename){
    unsigned char *data;
    int width, height, channel_count;
    int resultat = read_image_data(filename, &data, &width, &height, &channel_count);

    int min_sum = 255+255+255+1;
    pixelRGB* min_pixel = NULL;
    unsigned int min_x = 0, min_y = 0;
    int x,y;


    if(resultat){
        for (y=0 ; y < height ; y++){
            for (x=0 ; x < width ; x++){
                pixelRGB * p = get_pixel(data, width, height, channel_count, x, y );
                if (p) {
                int sum = p->R + p->G + p->B;
                if (sum < min_sum) {
                    min_sum = sum;
                    min_pixel = p;
                    min_x = x;
                    min_y = y;
                }
            }
        }
    }

    if (min_pixel) {
        printf("min_pixel (%u, %u): %d, %d, %d\n", min_x, min_y, min_pixel->R, min_pixel->G, min_pixel->B);
    } else {
        printf("No valid pixel found.\n");
    }
            }
    else{
        printf("Erreur lors de la lecture de l'image\n");
    }
}


void mirror_vertical(char *source_path){
    unsigned char *data;
    int width, height, channel_count ;
    int resultat = read_image_data(source_path, &data, &width, &height, &channel_count);

    if(resultat){
        unsigned char *mirror=malloc(width*height*channel_count);
        for(int y=0;y<height;y++){
            for(int x=0;x<width;x++){
                pixelRGB *src_pixel = get_pixel(data, width, height, channel_count, x, y );

                int new_x = x;
                int new_y = height -y -1;
                pixelRGB *dst_pixel = get_pixel(mirror,width, height, channel_count, new_x, new_y);

                if (src_pixel && dst_pixel) {
                    *dst_pixel = *src_pixel; 
                }
            }
        }

        const char *dst_path= "image_mirror_vertical.bmp";
        resultat = write_image_data(dst_path, mirror, width, height);
        if(resultat==0){
            printf("Erreur lors de l'ouverture du fichier");
        }
    }
    else{
        printf("Erreur lors de la lecture de l'image");
    }

}