/*================================================================
*   Copyright (C) 2020 * Ltd. All rights reserved.
*
*   Editor      : VIM
*   File name   : image.cpp
*   Author      : YunYang1994
*   Created date: 2020-04-11 18:15:20
*   Description :
*
*===============================================================*/

#include <stdio.h>
#include <string>

#include "image.hpp"
#include "stb_image.h"


Image::Image(int h, int w, int c){                          // 构造函数
    rows = h;
    cols = w;
    channels = c;
    size = h * w * c;

    data = (float *)calloc(size, sizeof(float));
    std::cout << "调用构造函数 " << data << std::endl;
}

Image::~Image(){                                           // 析构函数
    std::cout << "调用析构函数 " << data << std::endl;
    free(data);                                            // 释放空间
    data = NULL;
}

Image::Image(const Image &im){                             // 拷贝构造函数
    this->rows = im.rows;
    this->cols = im.cols;
    this->size = im.size;
    this->channels = im.channels;

    this->data = (float *)calloc(im.size, sizeof(float));
    memcpy(this->data, im.data, im.size * sizeof(float));
    std::cout << "调用拷贝构造函数 " << im.data << " -> " << data << std::endl;
}

float &Image::at(int y, int x, int z) const{              // 加 const 是为了不改变成员, & 则是引用，可以改变像素值
    assert(x < cols && y < rows && z < channels);
    return data[x + y*cols + z*rows*cols];
}


Image Image::copy(){
    Image im(rows, cols, channels);
    memcpy(im.data, data, im.size * sizeof(float));
    return im;
}



#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Image imread(std::string filename, int channels){
    int w, h, c;
    char *p = (char *)filename.c_str();

    unsigned char *data = stbi_load(p, &w, &h, &c, channels);
    if(!data){
        fprintf(stderr, "Cannot load image \"%s\"\nSTB Reason: %s\n", p, stbi_failure_reason());
        exit(0);
    }

    int i, j, k;
    Image im(h, w, c);

    for(k = 0; k < c; ++k){
        for(j = 0; j < h; ++j){
            for(i = 0; i < w; ++i){
                int dst_index = i + w*j + w*h*k;
                int src_index = k + c*i + c*w*j;
                im.data[dst_index] = (float)data[src_index];
            }
        }
    }

    free(data);
    data = NULL;

    return im;
}

void imwrite(std::string filename, Image im){


}

