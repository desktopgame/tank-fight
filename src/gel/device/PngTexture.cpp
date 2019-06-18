#include "PngTexture.hpp"
#if __APPLE__
#include <libpng16/png.h>
#else
#include <png.h>
#endif
#include <assert.h>
#include <stdlib.h>
namespace gel {
PngTexture::PngTexture() : textureId(0), width(0), height(0), data(NULL) {}

void PngTexture::load(const std::string& path) {
        FILE* fp = fopen(path.c_str(), "rb");
        // check file exists
        if (!fp) {
                perror("LoadPng");
                return;
        }
        png_structp pPng =
            png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        png_infop pInfo = png_create_info_struct(pPng);
        png_init_io(pPng, fp);
        png_read_info(pPng, pInfo);
        png_get_IHDR(pPng, pInfo, &(this->width), &(this->height),
                     &(this->depth), &(this->colorType), &(this->interlaceType),
                     NULL, NULL);
        // check bounds
        if (this->width == 0 || this->height == 0) {
                fprintf(stderr, "LoadPng: Invalid Bounds ");
                return;
        }
        // check color type
        if (this->colorType != PNG_COLOR_TYPE_RGB &&
            this->colorType != PNG_COLOR_TYPE_RGBA) {
                fprintf(stderr,
                        "LoadPng: Supported color type are RGB and RGBA.");
                return;
        }
        // check interlace type
        if (this->interlaceType != PNG_INTERLACE_NONE) {
                fprintf(stderr, "LoadPng: Interlace image is not supported.");
                return;
        }
        int rowSize = png_get_rowbytes(pPng, pInfo);
        // int imgSize = rowSize * this->height;
        int imgSize = rowSize * this->height;
        this->data = (unsigned char*)::malloc(imgSize);
        assert(this->data != NULL);
        // read pixels
        for (int i = 0; i < this->height; i++) {
                png_read_row(pPng, &(this->data[i * rowSize]), NULL);
        }
        png_read_end(pPng, pInfo);
        // generate texture
        glGenTextures(1, &(this->textureId));
        glBindTexture(GL_TEXTURE_2D, this->textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glEnable(GL_TEXTURE_2D);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, this->data);
        glDisable(GL_TEXTURE_2D);
        png_destroy_info_struct(pPng, &pInfo);
        png_destroy_read_struct(&pPng, NULL, NULL);
        fclose(fp);
}

void PngTexture::unload(const std::string& path) {
        ::free(this->data);
        glDeleteTextures(1, &textureId);
}

GLuint PngTexture::getID() const { return textureId; }

unsigned char* PngTexture::getData() const { return data; }

int PngTexture::getWidth() const { return width; }

int PngTexture::getHeight() const { return height; }

Vector2 PngTexture::getSize() const { return Vector2(width, height); }

}  // namespace gel