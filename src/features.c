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
        const char *dst_path= "image_out.bmp";
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

        const char *dst_path = "image_out.bmp";
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

        const char *dst_path= "image_out.bmp";
        resultat = write_image_data(dst_path, mirror, width, height);
        if(resultat==0){
            printf("Erreur lors de l'ouverture du fichier");
        }
    }
    else{
        printf("Erreur lors de la lecture de l'image");
    }

}

void mirror_total(char *source_path){
    unsigned char *data;
    int width, height, channel_count;
    int resultat = read_image_data(source_path, &data, &width, &height, &channel_count);
    if(resultat){
        unsigned char *mirror = malloc(width*height*channel_count);
        for(int y=0;y<height;y++){
            for(int x=0;x<width;x++){
                pixelRGB *src_pixel = get_pixel(data, width, height, channel_count, x, y ); 
                int new_x = width - x -1;
                int new_y = height - y -1;

                pixelRGB *dst_pixel = get_pixel(mirror, width, height, channel_count, new_x, new_y);

                *dst_pixel = *src_pixel;
            }
        }

        const char *dst_path= "image_out.bmp";
        resultat = write_image_data(dst_path, mirror, width, height);
        if(resultat==0){
            printf("Erreur lors de l'ouverture du fichier");
        }
    }
    else{
        printf("Erreur lors de l'ouverture de l'image");
    }
}


void color_red(char *source_path) {
    unsigned char *data;
    int width, height, channels;
    
    int resultat = read_image_data(source_path, &data, &width, &height, &channels);
    
    if (resultat) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                for (int c = 0; c < channels; c++) {
                    int index = (y * width + x) * channels + c;
                    
                    /*if (c == 0) {
                        data[index] = 255;
                    }
                    else*/ if (c == 1 || c == 2) {
                        data[index] = 0;
                    }
                }
            }
        }
        
        const char *dst_path = "image_out.bmp";
        resultat = write_image_data(dst_path, data, width, height);
        
        if (resultat==0) {
            printf("Erreur lors de l'écriture du fichier\n");}

    }
    else {
        printf("Erreur lors de la lecture de l'image\n");}
}


void color_green(char *source_path) {
    unsigned char *data;
    int width, height, channels;
    
    int resultat = read_image_data(source_path, &data, &width, &height, &channels);
    
    if (resultat) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                for (int c = 0; c < channels; c++) {
                    int index = (y * width + x) * channels + c;
                    
                    /*if (c == 0) {
                        data[index] = 255;
                    }
                    else*/ if (c == 0 || c == 2) {
                        data[index] = 0;
                    }
                }
            }
        }
        
        const char *dst_path = "image_out.bmp";
        resultat = write_image_data(dst_path, data, width, height);
        
        if (resultat==0) {
            printf("Erreur lors de l'écriture du fichier\n");}

    }
    else {
        printf("Erreur lors de la lecture de l'image\n");}
}


void color_blue(char *source_path) {
    unsigned char *data;
    int width, height, channels;
    
    int resultat = read_image_data(source_path, &data, &width, &height, &channels);
    
    if (resultat) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                for (int c = 0; c < channels; c++) {
                    int index = (y * width + x) * channels + c;
                    
                    /*if (c == 0) {
                        data[index] = 255;
                    }
                    else*/ if (c == 0 || c == 1) {
                        data[index] = 0;
                    }
                }
            }
        }
        
        const char *dst_path = "image_out.bmp";
        resultat = write_image_data(dst_path, data, width, height);
        
        if (resultat==0) {
            printf("Erreur lors de l'écriture du fichier\n");}

    }
    else {
        printf("Erreur lors de la lecture de l'image\n");}
}
void color_gray(char *source_path) {
    unsigned char *data;
    int width, height, channels;

    int resultat = read_image_data(source_path, &data, &width, &height, &channels);
    
    if (resultat) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                pixelRGB *pixel = get_pixel(data, width, height, 3, x, y);

                if (pixel != NULL) {
                    unsigned char moyenne = (pixel->R + pixel->G + pixel->B) / 3;

                    pixel->R = moyenne;
                    pixel->G = moyenne;
                    pixel->B = moyenne;
                }
            }
        }
        
        const char *dst_path = "image_out.bmp";
        resultat = write_image_data(dst_path, data, width, height);
        
        if (resultat == 0) {
            printf("Erreur lors de l'écriture du fichier\n");
        }
        
        free(data);
    }
    else {
        printf("Erreur lors de la lecture de l'image\n");
    }
}

void max_component (char *filename, char component){
    unsigned char *data;
    int width, height, channel_count;
    int resultat = read_image_data(filename, &data, &width, &height, &channel_count);

    pixelRGB* max_pixel = NULL;
    int max_val = -1;
    int max_x = 0, max_y = 0;

    if (resultat){

    int comp_id;
    if (component == 'R') comp_id = 0;
    else if (component == 'G') comp_id = 1;
    else if (component == 'B') comp_id = 2;
    else {
        printf("Composant invalide : utilisez 'R', 'G' ou 'B'.\n");
        return;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            pixelRGB* p = get_pixel(data, width, height, channel_count, x, y);
            if (p) {
                unsigned char val;
                if (comp_id == 0) val = p->R;
                else if (comp_id == 1) val = p->G;
                else val = p->B;

                if (val > max_val) {
                    max_val = val;
                    max_pixel = p;
                    max_x = x;
                    max_y = y;
                }
            }
        }
    }

    if (max_pixel) {
        if (component == 'R'){
            printf("max_component R (%u, %u): %u", max_x, max_y, max_pixel->R);
        }
        else if (component == 'G'){
            printf("max_component G (%u, %u): %u", max_x, max_y, max_pixel->G);
        }
        else {
            printf("max_component B (%u, %u): %u", max_x, max_y, max_pixel->B);
        }
        
    } else {
        printf("Aucun pixel valide trouvé.\n");
    }
}
}

void min_component (char *filename, char component){
    unsigned char *data;
    int width, height, channel_count;
    int resultat = read_image_data(filename, &data, &width, &height, &channel_count);

    pixelRGB* min_pixel = NULL;
    int min_val = 255+255+256;
    int min_x = 0, min_y = 0;

    if (resultat){

    int comp_id;
    if (component == 'R') comp_id = 0;
    else if (component == 'G') comp_id = 1;
    else if (component == 'B') comp_id = 2;
    else {
        printf("Composant invalide : utilisez 'R', 'G' ou 'B'.\n");
        return;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            pixelRGB* p = get_pixel(data, width, height, channel_count, x, y);
            if (p) {
                unsigned char val;
                if (comp_id == 0) val = p->R;
                else if (comp_id == 1) val = p->G;
                else val = p->B;

                if (val < min_val) {
                    min_val = val;
                    min_pixel = p;
                    min_x = x;
                    min_y = y;
                }
            }
        }
    }

    if (min_pixel) {
        if (component == 'R'){
            printf("min_component R (%u, %u): %u", min_x, min_y, min_pixel->R);
        }
        else if (component == 'G'){
            printf("min_component G (%u, %u): %u", min_x, min_y, min_pixel->G);
        }
        else {
            printf("min_component B (%u, %u): %u", min_x, min_y, min_pixel->B);
        }
        
    } else {
        printf("Aucun pixel valide trouvé.\n");
    }
}
}


void color_invert(char *source_path){
    unsigned char *data;
    int width, height, channels;

    int resultat = read_image_data(source_path, &data, &width, &height, &channels);
    
    if (resultat) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                pixelRGB *pixel = get_pixel(data, width, height, 3, x, y);

                if (pixel != NULL) {

                    unsigned char new_R = (255 - pixel->R);
                    unsigned char new_G = (255 - pixel->G);
                    unsigned char new_B = (255 - pixel->B);

                    pixel->R = new_R;
                    pixel->G = new_G;
                    pixel->B = new_B;
                }
            }
        }
        
        const char *dst_path = "image_out.bmp";
        resultat = write_image_data(dst_path, data, width, height);
        
        if (resultat == 0) {
            printf("Erreur lors de l'écriture du fichier\n");
        }
        
        free(data);
    }
    else {
        printf("Erreur lors de la lecture de l'image\n");
    }
}
/*
void stat_report(char *filename, char *report_filename) {
    FILE *output = fopen(report_filename, "w");
    if (!output) {
        perror("Erreur lors de l'ouverture du fichier de rapport");
        return;
    }

    fprintf(output, "Statistical Report for image: %s\n", char *filename);
    fprintf(output, "======================================\n");

    max_pixel (char *filename, output);
    fprintf(output, "\n");
    min_pixel (char *filename, output);
    fprintf(output, "\n");
    max_component(char *filename, 'R', output);
    fprintf(output, "\n");
    max_component(char *filename, 'G', output);
    fprintf(output, "\n");
    max_component(char *filename, 'B', output);
    fprintf(output, "\n");
    min_component(char *filename, 'R', output);
    fprintf(output, "\n");
    min_component(char *filename, 'G', output);
    fprintf(output, "\n");
    min_component(char *filename, 'B', output);

    fclose(output);
}*/



void scale_nearest(char *source_path,float X){
    unsigned char *data;
    int width, height, channel_count;
    int resultat = read_image_data(source_path, &data, &width, &height, &channel_count);

    if(resultat){
        int new_width = width*X;
        int new_height = height*X;
        unsigned char *scale = malloc(new_height*new_width*channel_count);
        for(int y=0;y<new_height;y++){
            for(int x=0;x<new_width;x++){
                int src_x = (int)(x / X);
                if (src_x >= width) src_x = width - 1;

                int src_y = (int)(y / X);
                if (src_y >= height) src_y = height - 1;
                pixelRGB *src_pixel = get_pixel(data, width, height, channel_count, src_x,src_y);

                pixelRGB *dst_pixel = get_pixel(scale, new_width, new_height, channel_count, x, y);

                *dst_pixel=*src_pixel;
            }
        }

        const char *dst_path = "image_out.bmp";
        resultat = write_image_data(dst_path, scale, new_width, new_height);    
        if(resultat==0){
            printf("Erreur lors de l'ouverture du fichier image_out");
        }
        
    }
    else {
        printf("Erreur lors de l'ouverture de l'image");
    }
}

void color_gray_luminance(char *source_path) {
    unsigned char *data;
    int width, height, channels;

    int resultat = read_image_data(source_path, &data, &width, &height, &channels);
    
    if (resultat) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                pixelRGB *pixel = get_pixel(data, width, height, 3, x, y);

                if (pixel != NULL) {

                    pixel->R = pixel->R * 0.21;
                    pixel->G = pixel->G * 0.72;
                    pixel->B = pixel->B * 0.07;
                }
            }
        }
        
        const char *dst_path = "image_out.bmp";
        resultat = write_image_data(dst_path, data, width, height);
        
        if (resultat == 0) {
            printf("Erreur lors de l'écriture du fichier\n");
        }
        
        free(data);
    }
    else {
        printf("Erreur lors de la lecture de l'image\n");
    }
}




void scale_crop (char *source_path, int center_x, int center_y, int crop_width, int crop_height){
    unsigned char *data;
    int width, height, channels, n_channels;

    int resultat = read_image_data(source_path, &data, &width, &height, &channels);

    if (resultat){
        // Allouer la mémoire pour la nouvelle image
        unsigned char* cropped_data = (unsigned char*) malloc(crop_width * crop_height * n_channels);
        if (!cropped_data) {
            printf("Erreur d'allocation mémoire.\n");
            return NULL;
        }

        // Ajuster les coordonnées du centre si elles dépassent les limites de l'image
        if (center_x + crop_width/2 > width){
            center_x = width - crop_width/2;
        } 
        if (center_y + crop_height/2 > height){
            center_y = height - crop_height/2;
        }
        if (center_x < crop_width/2){
            center_x = crop_width/2;
        } 
        if (center_y < crop_height/2){
            center_y = crop_height/2;
        } 

        //Trouver le coin superieur gauche de la nouvelle image
        int start_x = center_x - crop_width / 2;
        int start_y = center_y - crop_height / 2;

        //Parcours de l'image
        for (int y = 0; y < crop_height; y++) {
            for (int x = 0; x < crop_width; x++) {
                int src_x = center_x - width/2 + x;
                int src_y = center_y - height/2 + y;
                pixelRGB* src_pixel = get_pixel(data, width, height, channels, src_x, src_y);
                if (src_pixel) {
                    int dest_idx = channels * (x + y * crop_width);
                    cropped_data[dest_idx] = src_pixel->R;
                    cropped_data[dest_idx + 1] = src_pixel->G;
                    cropped_data[dest_idx + 2] = src_pixel->B;
                }
            }
        }
    const char *dst_path = "image_crop.bmp";
    int res = write_image_data(dst_path, data, width, height);

    if (res == 0) {
            printf("Erreur lors de l'écriture du fichier\n");
        }

    free(data);
    free(cropped_data);
    return NULL;
    }

    else {
        printf("Erreur lors de la lecture de l'image\n");
    }
}