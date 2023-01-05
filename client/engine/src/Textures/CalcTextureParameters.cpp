#include "CalcTextureParameters.h"

#include <GL/glew.h>

namespace LM {

    int CalcTextureParameters::inputType(Texture2D::MASK mask) {
        if (mask & Texture2D::MASK::NO_SRGB) {
            return GL_RGBA;
        }

        return GL_SRGB_ALPHA;
    }

    int CalcTextureParameters::outputType(Texture2D::MASK mask) {
        if (mask & Texture2D::MASK::NO_ALPHA) {
            return GL_RGB;
        }

        return GL_RGBA;
    }

    int CalcTextureParameters::magFilter(Texture2D::MASK mask) {
        if (mask & Texture2D::MASK::MAG_NEAREST) {
            return GL_NEAREST;
        }

        return GL_LINEAR;
    }

    int CalcTextureParameters::minFilter(Texture2D::MASK mask) {
        if (mask & Texture2D::MASK::MIN_NEAREST) {
            return GL_NEAREST;
        }
        if (mask & Texture2D::MASK::MIN_LINEAR_MIPMAP_LINEAR) {
            return GL_LINEAR_MIPMAP_LINEAR;
        }
        if (mask & Texture2D::MASK::MIN_LINEAR_MIPMAP_NEAREST) {
            return GL_LINEAR_MIPMAP_NEAREST;
        }
        if (mask & Texture2D::MASK::MIN_NEAREST_MIPMAP_LINEAR) {
            return GL_NEAREST_MIPMAP_LINEAR;
        }
        if (mask & Texture2D::MASK::MIN_NEAREST_MIPMAP_NEAREST) {
            return GL_NEAREST_MIPMAP_NEAREST;
        }

        return GL_LINEAR;
    }

    int CalcTextureParameters::wrapS(Texture2D::MASK mask) {
        if (mask & Texture2D::MASK::S_MIRRORED_REPEAT) {
            return GL_MIRRORED_REPEAT;
        }
        if (mask & Texture2D::MASK::S_CLAMP_TO_EDGE) {
            return GL_LINEAR_MIPMAP_LINEAR;
        }
        if (mask & Texture2D::MASK::S_CLAMP_TO_BORDER) {
            return GL_LINEAR_MIPMAP_NEAREST;
        }

        return GL_REPEAT;
    }

    int CalcTextureParameters::wrapT(Texture2D::MASK mask) {
        if (mask & Texture2D::MASK::T_MIRRORED_REPEAT) {
            return GL_MIRRORED_REPEAT;
        }
        if (mask & Texture2D::MASK::T_CLAMP_TO_EDGE) {
            return GL_LINEAR_MIPMAP_LINEAR;
        }
        if (mask & Texture2D::MASK::T_CLAMP_TO_BORDER) {
            return GL_LINEAR_MIPMAP_NEAREST;
        }

        return GL_REPEAT;
    }

    int CalcTextureParameters::wrapR(Texture2D::MASK mask) {
        if (mask & Texture2D::MASK::R_MIRRORED_REPEAT) {
            return GL_MIRRORED_REPEAT;
        }
        if (mask & Texture2D::MASK::R_CLAMP_TO_EDGE) {
            return GL_LINEAR_MIPMAP_LINEAR;
        }
        if (mask & Texture2D::MASK::R_CLAMP_TO_BORDER) {
            return GL_LINEAR_MIPMAP_NEAREST;
        }

        return GL_REPEAT;
    }

    bool CalcTextureParameters::hasMipmap(Texture2D::MASK mask) {
        return mask & Texture2D::MASK::MIN_LINEAR_MIPMAP_LINEAR ||
               mask & Texture2D::MASK::MIN_LINEAR_MIPMAP_NEAREST ||
               mask & Texture2D::MASK::MIN_NEAREST_MIPMAP_LINEAR ||
               mask & Texture2D::MASK::MIN_NEAREST_MIPMAP_NEAREST;
    }

}    // namespace LM
