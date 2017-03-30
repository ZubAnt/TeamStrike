#include "Map.h"

#include "Menu/AbstractMenuData.h"

MapScene::MapScene()
{}

Scene *MapScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0.f, -98.0f));
    auto layer = MapScene::create();
    scene->addChild(layer);
    return scene;
}

void MapScene::set_edgeBox()
{
    auto edgeBody = PhysicsBody::createEdgeBox(_visibleSize, PHYSICSSHAPE_MATERIAL_DEFAULT, 3);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(_visibleSize.width / 2, _visibleSize.height / 2));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);
}

bool MapScene::init()
{
    if (!Layer::init()) { return false; }

    _director = Director::getInstance();
    _visibleSize = _director->getVisibleSize();
    _origin = _director->getVisibleOrigin();

    Vec2 vec_center(_visibleSize.width / 2, _visibleSize.height/2);

//    auto _tileMap = new CCTMXTiledMap();
//    _tileMap->initWithTMXFile("map.tmx");

    auto map = TMXTiledMap::create("map.tmx");
//    map->setContentSize(Size(_visibleSize));
//    map->setPosition(vec_center);
    addChild(map, 0);


    // all tiles are aliased by default, let's set them anti-aliased
    for (const auto& child : map->getChildren())
    {
        static_cast<SpriteBatchNode*>(child)->getTexture()->setAntiAliasTexParameters();
    }
//    set_edgeBox();

//    auto physicsBody = PhysicsBody::createBox(Size(100, 100), PhysicsMaterial(0.1f, 1.0f, 0.0f));
//    physicsBody->setDynamic(true);
//    physicsBody->setGravityEnable(true);
//    //create a sprite
//    auto sprite = Sprite::create("ball.png");
//    sprite->setPosition(vec_center);
//    addChild(sprite);
//    sprite->setPhysicsBody(physicsBody);


    return true;
}


