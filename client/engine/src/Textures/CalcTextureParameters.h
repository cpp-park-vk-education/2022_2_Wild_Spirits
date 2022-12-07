#pragma once

#include "Texture2D.h"

namespace LM {

    class CalcTextureParameters {
    public:
        static int inputType(Texture2D::MASK mask);
        static int outputType(Texture2D::MASK mask);
        static int magFilter(Texture2D::MASK mask);
        static int minFilter(Texture2D::MASK mask);
        static int wrapS(Texture2D::MASK mask);
        static int wrapT(Texture2D::MASK mask);
        static int wrapR(Texture2D::MASK mask);

        static bool hasMipmap(Texture2D::MASK mask);
    };

}
