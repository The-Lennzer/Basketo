#pragma once

#include <cstdint>
#include <bitset>
#include "Entity.h"

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;
