#include "Item.h"

Item::Item() 
{ 
    ;
}
Item::Item(const Point pos, const int kinds, const int tick){
    this -> pos = pos;
    this -> kinds = kinds;
    this -> created_tick = tick;
}
int Item::getKinds(){ //아이템의 종류반환
    return kinds;
}
int Item::getCreatedTick(){//아이템 생성 시기 반환
    return created_tick;
} 
void Item::setPos(const Point pos){//아이템의 위치 설정
    this -> pos = pos;
} 
void Item::setKinds(const int kinds){//아이템의 종류 설정
    this -> kinds = kinds;
} 
void Item::setCreatedTick(const int tick){//아이템 생성 시기 설정
    created_tick = tick;
} 
Point Item::getPos() { //아이템의 위치 반환
    return pos;
}