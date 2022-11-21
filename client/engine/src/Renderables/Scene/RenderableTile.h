#pragma once

#include "RenderableSceneTexture.h"

namespace LM {

    class RenderableTile : public RenderableSceneTexture {
    public:
        RenderableTile();
        virtual ~RenderableTile() = default;

        virtual void onEvent(Ref<Event> event) override;
    };

}
