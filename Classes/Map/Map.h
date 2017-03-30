#ifndef MAP_H
#define MAP_H

#include "cocos2d.h"

USING_NS_CC;

class MapScene: public cocos2d::Layer
{
public:
    MapScene();
    static cocos2d::Scene* createScene();
    bool init();
    CREATE_FUNC(MapScene)

    void set_edgeBox();

private:

    cocos2d::Director *_director;
    cocos2d::Size _visibleSize;
    Vec2 _origin;
};


#endif // MAP_H
