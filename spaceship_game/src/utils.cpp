#include "include/freeglut/include/GL/glut.h"
#include <cstdlib>

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"
#include <iostream>

int randint(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

bool randbool()
{
    return rand() % 2;
}

float randfloat(float min, float max)
{
    return (max - min) * ((float)rand() / RAND_MAX) + min;
}

int randRange(int negmin, int megmax, int posmin, int posmax)
{
    if (randbool())
    {
        return randint(negmin, megmax);
    }
    else
    {
        return randint(posmin, posmax);
    }
}

float min(float a, float b)
{
    return a <= b ? a : b;
}

void generateTexture(GLuint *texture, const char *filename)
{
    // Generate a texture from a file
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data)
    {
        if (nrChannels == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else if (nrChannels == 4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}