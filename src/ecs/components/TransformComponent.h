#pragma once
#include "../../vendor/nlohmann/json.hpp"

struct TransformComponent {
    float x = 0.0f;
    float y = 0.0f;
    float width = 32.0f;
    float height = 32.0f;
    float rotation = 0.0f; 
    int z_index = 0;

    TransformComponent() = default;
    TransformComponent(float x_val, float y_val, float w_val, float h_val, float rot_val, int z_val)
        : x(x_val), y(y_val), width(w_val), height(h_val), rotation(rot_val), z_index(z_val) {}

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(TransformComponent, x, y, width, height, rotation, z_index);
};

inline void to_json(nlohmann::json& j, const TransformComponent& c) {
    j = nlohmann::json{
        {"x", c.x},
        {"y", c.y},
        {"width", c.width},
        {"height", c.height},
        {"rotation", c.rotation},
        {"z_index", c.z_index}
    };
}

inline void from_json(const nlohmann::json& j, TransformComponent& c) {
    c.x = j.value("x", 0.0f);
    c.y = j.value("y", 0.0f);
    c.width = j.value("width", 32.0f);
    c.height = j.value("height", 32.0f);
    c.rotation = j.value("rotation", 0.0f); 
    c.z_index = j.value("z_index", 0);
}
