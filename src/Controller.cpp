#include <Arduino.h>
#include <Controller.h>


Controller::Controller(){
    this->x = 50;
    this->y = 40;
    this->pinX = 1;
    this->pinY = 2;
}

void Controller::connect(){
    this->x = 2;
}

void Controller::myloop(){
    
}
