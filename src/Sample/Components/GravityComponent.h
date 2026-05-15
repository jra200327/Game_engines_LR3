#ifndef GRAVITYCOMPONENT_H
#define GRAVITYCOMPONENT_H

struct GravityComponent {
    float gravity;           
    float currentVelocityY = 0;
    float maxVelocityY = 10;
    bool grounded = false; 
    
    GravityComponent(float g = 1.0f) : gravity(g) 
    {}
};

#endif