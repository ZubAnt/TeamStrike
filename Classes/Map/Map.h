#ifndef MAP_H
#define MAP_H

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#define PTM_RATIO 32.0

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

    b2World *_world;
    b2Body *_groundBody;
    b2Fixture *_bottomFixture;
    b2Fixture *_ballFixture;
};


#endif // MAP_H
