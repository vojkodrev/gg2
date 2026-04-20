#pragma once
#include <tmxlite/Map.hpp>
#include <string>

const tmx::Layer *FindLayer(const tmx::Map &map, const std::string &name);
