#pragma once

#include "Layer.h"

namespace LM {

    class LayerSettings: public Layer {
    public:
        LayerSettings();
        ~LayerSettings();

        virtual void onEvent(Ref<Event> _Event) override;
        virtual void onUpdate(Tick tick) override;
    protected:
    };

}    // namespace LM
