#include <estia-image.h>

#include "utils.h"

/**
 * @brief Here, you have to define functions of the pixel struct : getPixel and setPixel.
 * 
 */

pixelRGB * get_pixel( unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int n, const unsigned int x, const unsigned int y ){
    /*n = nombre de channel RVB = 3, N&B=1*/
    int res = n*(width+width*height);
    if(x>width || y>height){
        return 0;
    }
    else if(data==0){
        return 0;
    }
    else {
        return (pixelRGB *) &data[n*(width+width*height)];
    }
    


}