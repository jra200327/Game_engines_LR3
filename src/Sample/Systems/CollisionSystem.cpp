#include "CollisionSystem.h"

void CollisionSystem::Print(int ent1, int ent2)
{
    std::cout << ent1 << " collided with: " << ent2 << std::endl;
}

void CollisionSystem::OnInit()
{

}

void CollisionSystem::OnUpdate()
{   
    for (const auto ent : _collideables)
    {
        auto& collision = _collisionComponents.Get(ent);
        collision.CollisionEntities.clear();
    }

    for (auto it1 = _collideables.begin(); it1 != _collideables.end(); ++it1)
    {
        auto ent1 = *it1;

        auto& position1 = _positionComponents.Get(ent1);
        auto& collision1 = _collisionComponents.Get(ent1);
        bool hasBox1 = _boxColliderComponents.Has(ent1);
        bool hasCircle1 = _circleColliderComponents.Has(ent1);

        auto it2 = it1;
        ++it2;

        for (; it2 != _collideables.end(); ++it2)
        {
            auto ent2 = *it2;

            auto& position2 = _positionComponents.Get(ent2);
            auto& collision2 = _collisionComponents.Get(ent2);
            bool hasBox2 = _boxColliderComponents.Has(ent2);
            bool hasCircle2 = _circleColliderComponents.Has(ent2);
            bool collided = false;
            
            if (hasBox1 && hasBox2)
            {
                auto& boxCollider1 = _boxColliderComponents.Get(ent1);
                auto& boxCollider2 = _boxColliderComponents.Get(ent2);
                float left1 = position1.X - boxCollider1.Width / 2.0f;
                float top1  = position1.Y - boxCollider1.Height / 2.0f;

                float left2 = position2.X - boxCollider2.Width / 2.0f;
                float top2  = position2.Y - boxCollider2.Height / 2.0f;

                collided = top1 < top2 + boxCollider2.Height && top2 < top1 + boxCollider1.Height && left1 < left2 + boxCollider2.Width &&
                    left2 < left1 + boxCollider1.Width;
                    
            }
            else if (hasCircle1 && hasCircle2)
            {
                auto& circleCollider1 = _circleColliderComponents.Get(ent1);
                auto& circleCollider2 = _circleColliderComponents.Get(ent2);

                float dx = position1.X - position2.X;
                float dy = position1.Y - position2.Y;
                float r = circleCollider1.Radius + circleCollider2.Radius;
                collided = (dx * dx + dy * dy) <= (r * r);
            }
            else if (hasBox1 && hasCircle2)
            {
                auto& box = _boxColliderComponents.Get(ent1);
                auto& circle = _circleColliderComponents.Get(ent2);

                float boxLeft   = position1.X - box.Width / 2.0f;
                float boxTop    = position1.Y - box.Height / 2.0f;
                float boxRight  = boxLeft + box.Width;
                float boxBottom = boxTop + box.Height;

                float closestX = std::max(boxLeft, std::min(position2.X, boxRight));
                float closestY = std::max(boxTop, std::min(position2.Y, boxBottom));

                float dx = position2.X - closestX;
                float dy = position2.Y - closestY;

                collided = (dx * dx + dy * dy) <= (circle.Radius * circle.Radius);
            }

            else if (hasCircle1 && hasBox2)
            {
                auto& box = _boxColliderComponents.Get(ent2);
                auto& circle = _circleColliderComponents.Get(ent1);

                float boxLeft   = position2.X - box.Width / 2.0f;
                float boxTop    = position2.Y - box.Height / 2.0f;
                float boxRight  = boxLeft + box.Width;
                float boxBottom = boxTop + box.Height;

                float closestX = std::max(boxLeft, std::min(position1.X, boxRight));
                float closestY = std::max(boxTop, std::min(position1.Y, boxBottom));

                float dx = position1.X - closestX;
                float dy = position1.Y - closestY;

                collided = (dx * dx + dy * dy) <= (circle.Radius * circle.Radius);
            }

            if (collided)
            {
                collision1.CollisionEntities.push_back(ent2);
                collision2.CollisionEntities.push_back(ent1);
                Print(ent1, ent2);
            }
        }
    }
}