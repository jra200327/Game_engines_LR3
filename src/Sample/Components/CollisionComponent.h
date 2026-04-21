#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include <SFML/System/Vector2.hpp>
#include <vector>
#include "BoxColliderComponent.h"

struct CollisionComponent
{
    std::vector<int> CollisionEntities;
};

#endif //COLLISIONCOMPONENT_H