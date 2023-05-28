#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Bullet.h"
#include "MyPlane.h"
#include "FixedObject.h"
#include "Enemy.h"
class GameManager
{
public:
    GameManager(){};
    void detactBulletLife(std::list<Bullet> &bullets);
    void detactCollision(MyPlane &myplane, std::list<Bullet> &bullets, std::list<FixedObject> &fixed_objects, std::list<Enemy> &enemies,short &game_situation);

private:
};

#endif // GAMEMANAGER_H

