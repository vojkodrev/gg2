#include "FindLayer.h"

const tmx::Layer *findLayer(const tmx::Map &map, const std::string &name)
{
    for (auto &layer : map.getLayers())
        if (layer->getName() == name)
            return layer.get();
    return nullptr;
}
