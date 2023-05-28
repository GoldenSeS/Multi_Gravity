#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <conio.h>
#include "MyPlane.h"
#include "Bullet.h"
#include <chrono>
class Keyboard
{
public:
    Keyboard(){};
   
    void planeControl(MyPlane &plane,std::list<Bullet> &bullets,short &predict_mode);
    void exitOpeningCG(bool &should_exit);
    void introductionControl(short &intro_index);

private:
};

#endif