#pragma once
#include <tmxlite/Map.hpp>
#include <string>

const tmx::Layer *findLayer(const tmx::Map &map, const std::string &name);
