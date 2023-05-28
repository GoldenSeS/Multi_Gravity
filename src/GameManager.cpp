#include "GameManager.h"

void GameManager::detactBulletLife(std::list<Bullet> &bullets)
{
    for (auto it = bullets.begin(); it != bullets.end();)
    {
        if (!it->should_exist())
        {
            it = bullets.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void GameManager::detactCollision(MyPlane &myplane, std::list<Bullet> &bullets, std::list<FixedObject> &fixed_objects, std::list<Enemy> &enemies,short &game_situation)
{
    // detect collision between myplane and fixed objects
    for (auto fixed_object : fixed_objects)
    {
        Point temp = myplane.getPosition() - fixed_object.getCenterPoint();
        if (temp.getX() * temp.getX() + 4 * temp.getY() * temp.getY() < 4 * fixed_object.getRadius() * fixed_object.getRadius())
        {
            game_situation = 2;
        }
    }
    // detect collision between myplane and enemies
    for (auto enemy : enemies)
    {
        Point temp = myplane.getPosition() - enemy.getPosition();
        if (temp.getX() * temp.getX() + 4 * temp.getY() * temp.getY() < 4 * enemy.getCollisionRadius() * enemy.getCollisionRadius())
        {
            game_situation = 2;
        }
    }
    // detect collision between bullets and fixed objects
    for (auto fixed_object : fixed_objects)
    {
        for (auto it = bullets.begin(); it != bullets.end();)
        {
            Point temp = it->getPosition() - fixed_object.getCenterPoint();
            if (temp.getX() * temp.getX() + 4 * temp.getY() * temp.getY() < 4 * fixed_object.getRadius() * fixed_object.getRadius())
            {
                it = bullets.erase(it);
            }
            else
            {
                it++;
            }
        }
    }
    // detect collision between bullets and enemies
    // if collision happens, the bullet will be erased and the enemy will be erased too
    auto it1 = bullets.begin();
    while(it1!=bullets.end()){
        auto it2 = enemies.begin();
        while(it2!=enemies.end()){
            Point temp = it1->getPosition() - it2->getPosition();
            if (temp.getX() * temp.getX() + 4 * temp.getY() * temp.getY() < 4 * it2->getCollisionRadius() * it2->getCollisionRadius())
            {
                it1 = bullets.erase(it1);
                it2 = enemies.erase(it2);
            }
            else
            {
                it2++;
            }
        }
        if(it1!=bullets.end()){
            it1++;
        }
    }
}