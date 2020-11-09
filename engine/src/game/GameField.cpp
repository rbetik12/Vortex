#include <cstddef>
#include <platform/opengl/OpenGLErrorLog.h>
#include <Log.h>
#include <random>
#include "GameField.h"

#define GAMEFIELD_SIZE 1280*720

namespace Vortex {
    //Width and height are hardcoded
    GameField::GameField():width(1280), height(720), frameBuffer(PixelFrameBuffer(1280, 720)) {
        glCall(glGenTextures(1, &rendererId))
        glCall(glBindTexture(GL_TEXTURE_2D, rendererId));

        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        Update();
        unBind();
    }

    GameField::~GameField() {
        glCall(glDeleteTextures(1, &rendererId));
    }

    void GameField::bind(unsigned int slot) const {
        glCall(glActiveTexture(GL_TEXTURE0 + slot));
        glCall(glBindTexture(GL_TEXTURE_2D, rendererId));
    }

    void GameField::unBind() const {
        glCall(glBindTexture(GL_TEXTURE_2D, 0));
    }

    void GameField::Update() {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<float> randGen(0.0, 1.0);
        for (size_t i = 0; i < GAMEFIELD_SIZE; i++) {
            Pixel pixel;
            pixel.GetColor().r = mt();
            pixel.GetColor().b = mt();
            pixel.GetColor().g = mt();
            frameBuffer[i] = pixel;
        }

        uint8_t * rawPixelArray = frameBuffer.GetUInt8Array();
        glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rawPixelArray));
        delete [] rawPixelArray;
    }
}