#include "Map.h"

#include "Menu/AbstractMenuData.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdio>

MapScene::MapScene()
{

    _map = nullptr;
    _objectGroup = nullptr;
    _director = nullptr;
    _visibleSize = Size::ZERO;
    _origin = Vec2::ZERO;

    map_path = "tile_map/map1/ice.tmx";

    NamePolygonObjects = {"Polygon_GND",
                          "Polygon_GNDL1",
                          "Polygon_GNDR1",
                          "Polygon_GNDL2",
                          "Polygon_GNDR2",
                          "Polygon_GNDL3",
                          "Polygon_GNDR3"};

    NameBoxObjects = {"Box_Start_Col_Left",
                      "Box_Start_Col_Right",
                      "Box_GNDL1",
                      "Box_GNDL2",
                      "Box_GNDR1",
                      "Box_GNDR2",
                      "Platform1",
                      "Platform2",
                      "Platform3",
                      "Platform4",
                      "Platform5",
                      "Platform6",
                      "Platform7",
                      "Platform8",
                      "Platform9",
                      "Platform10",
                      "Platform11",
                      "Platform12",
                      "Platform13",
                      "Platform14"
                     };

    enable_scale_map = false;
    enable_scale_background = false;
    enable_draw_polygons = false;
    enable_draw_boxes = false;
}

MapScene::~MapScene()
{}

Scene *MapScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0.f, -98.0f));
    auto layer = MapScene::create();
    scene->addChild(layer);
    return scene;
}

int MapScene::setSolidEdgeBox()
{
    ///@ref Если будем делать слежение камерой за объектом, то здесь не _visibleSize!!!!!!!!!!!!!!!!!!

    PhysicsBody* edgeBox = PhysicsBody::createEdgeBox(_visibleSize);
    Node* edgeNode = Node::create();

    if (edgeBox == nullptr || edgeNode == nullptr)
    {
        print_error(__FILE__, __LINE__, "Can not create edgeBox");
        log_error(__FILE__, __LINE__, "Can not create edgeBox");
        return errAsInt(Error::NULL_PTR);
    }

    edgeNode->setPosition(Point(_visibleSize.width / 2, _visibleSize.height / 2));
    edgeNode->setPhysicsBody(edgeBox);
    this->addChild(edgeNode, 1);
}


int MapScene::setSolidPolygonFigure()
{

    if (_objectGroup == nullptr)
    {
        print_error(__FILE__, __LINE__,
                    "Can not set Polygon Figure(_objectGroup = nullptr), please make setupObjectGroup()");
        log_error(__FILE__, __LINE__,
                  "Can not set Polygon Figure(_objectGroup = nullptr), please make setupObjectGroup()");
        return errAsInt(Error::NULL_PTR);
    }
    for (auto &NameObject: NamePolygonObjects)
    {
        ValueMap object = _objectGroup->getObject(NameObject);

        if (object == ValueMap())
        {
            std::string err = "bad name polygon object: " + NameObject;
            print_error(__FILE__, __LINE__, err.c_str());
            log_error(__FILE__, __LINE__, err.c_str());
            return errAsInt(Error::BAD_NAME_POLYGON_OBJECT);
        }

        try
        {
            ValueVector vec_point= object.at("polylinePoints").asValueVector();
            float pos_x = object.at("x").asFloat(); // start position x
            float pos_y = object.at("y").asFloat(); // start position y

            Vec2 pointsVec2Object[vec_point.size()];

            size_t ind = 0;
            for(auto &point: vec_point)
            {
                ValueMap vm_point = point.asValueMap();

                float x = pos_x + static_cast<float>(vm_point.at("x").asInt());
                float y = pos_y - static_cast<float>(vm_point.at("y").asInt());

                pointsVec2Object[ind] = Vec2(x, y);
                ++ind;
            }

            // create Polygon from point
            auto polygon = PhysicsBody::createPolygon(pointsVec2Object, vec_point.size());
            polygon->setDynamic(false);
            polygon->setGravityEnable(false);

            auto pol_node = Node::create();

            bool isScale = false;
            if (enable_scale_map == true)
            {
                if (_scale_map_x == 0 || _scale_map_y == 0)
                {
                    print_error(__FILE__, __LINE__,
                                "scale_map_x == 0 || scale_map_y == 0 WHEN enable_scale_map == true");
                    log_error(__FILE__, __LINE__,
                              "scale_map_x == 0 || scale_map_y == 0 WHEN enable_scale_map == true");

                    return errAsInt(Error::SCALE_MAP_PARAM_IS_NULL);
                }

                setMapScale(pol_node);
                isScale = true;
            }

            if (enable_draw_polygons == true)
            {
                DrawNode* draw_pol_node = DrawNode::create();

                if (isScale == true)
                {
                    setMapScale(draw_pol_node);
                }

                //creating red polygon with thin black border
                draw_pol_node->drawPolygon(pointsVec2Object, vec_point.size(),
                                           Color4F(1, 0, 0, 1), 2, Color4F(0, 0, 0, 1));
                addChild(draw_pol_node, 100);
            }

            pol_node->setPhysicsBody(polygon);
            this->addChild(pol_node);
        }
        catch (std::out_of_range &err)
        {
            print_exception_error(__FILE__, __LINE__, err);
            log_exception_error(__FILE__, __LINE__, err);
            return errAsInt(Error::CATCHING_AN_EXCEPTION);
        }
    }

    return errAsInt(Error::OK);
}

int MapScene::setSolidBoxFigure()
{
    if (_objectGroup == nullptr)
    {
        print_error(__FILE__, __LINE__,
                    "Can not set Polygon Figure(_objectGroup = nullptr), please make setupObjectGroup()");
        log_error(__FILE__, __LINE__,
                  "Can not set Polygon Figure(_objectGroup = nullptr), please make setupObjectGroup()");
        return errAsInt(Error::NULL_PTR);
    }

    for (auto &NameObject: NameBoxObjects)
    {
        ValueMap object = _objectGroup->getObject(NameObject);

        if (object == ValueMap())
        {
            std::string err = "bad name box object: " + NameObject;
            print_error(__FILE__, __LINE__, err.c_str());
            log_error(__FILE__, __LINE__, err.c_str());
            return errAsInt(Error::BAD_NAME_POLYGON_OBJECT);
        }

        try
        {
            float x = 0.0f;
            float y = 0.0f;
            float height = 0.0f;
            float width = 0.0f;
            x = object.at("x").asFloat();
            y = object.at("y").asFloat();
            height = object.at("height").asFloat();
            width = object.at("width").asFloat();

            Vec2 rectangle[4];
            rectangle[0] = Vec2(x, y);
            rectangle[1] = Vec2(x, y + height);
            rectangle[2] = Vec2(x + width, y + height);
            rectangle[3] = Vec2(x + width, y);

            PhysicsBody* polygon = PhysicsBody::createPolygon(rectangle, 4);
            polygon->setDynamic(false);
            polygon->setGravityEnable(false);
            auto pol_node = Node::create();

            bool isScale = false;
            if (enable_scale_map == true)
            {
                if (_scale_map_x == 0 || _scale_map_y == 0)
                {
                    print_error(__FILE__, __LINE__,
                                "scale_map_x == 0 || scale_map_y == 0 WHEN enable_scale_map == true");
                    log_error(__FILE__, __LINE__,
                              "scale_map_x == 0 || scale_map_y == 0 WHEN enable_scale_map == true");

                    return errAsInt(Error::SCALE_MAP_PARAM_IS_NULL);
                }

                setMapScale(pol_node);
                isScale = true;
            }

            if (enable_draw_polygons == true)
            {
                DrawNode* rectNode = DrawNode::create();

                if (isScale == true)
                {
                    setMapScale(rectNode);
                }

                rectNode->drawPolygon(rectangle, 4, Color4F (1, 0, 0, 1), 1, Color4F (0, 0, 0, 1));
                addChild(rectNode, 100);
            }

            pol_node->setPhysicsBody(polygon);
            addChild(pol_node, 1);
        }
        catch (std::out_of_range &err)
        {
            print_exception_error(__FILE__, __LINE__, err);
            log_exception_error(__FILE__, __LINE__, err);
            return errAsInt(Error::CATCHING_AN_EXCEPTION);
        }
    }

    return errAsInt(Error::OK);
}

void MapScene::setEnableDrawAllSolidFigure(bool enable)
{
    setEnableDrawPolygons(true);
    setEnableDrawBoxes(true);
}

void MapScene::setEnableDrawPolygons(bool enable)
{
    enable_draw_polygons = enable;
}

void MapScene::setEnableDrawBoxes(bool enable)
{
    enable_draw_boxes = enable;
}

void MapScene::SetEnableScaleMap(bool enable)
{
    enable_scale_map = enable;
}

void MapScene::setEnableScaleBackground(bool enable)
{
    enable_scale_background = enable;
}

void MapScene::setMapScale(Node *node)
{
    node->setScaleX(_scale_map_x);
    node->setScaleY(_scale_map_y);
}

int MapScene::setupMap()
{
    _map = TMXTiledMap::create(map_path);
    if (_map == nullptr)
    {
        std::string err = "Can not create map from " + map_path;
        print_error(__FILE__, __LINE__, err.c_str());
        log_error(__FILE__, __LINE__,err.c_str());
        return errAsInt(Error::NULL_PTR);
    }

    if (enable_scale_map == true)
    {
        _scale_map_x = _visibleSize.width / _map->getContentSize().width;
        _scale_map_y = _visibleSize.height / _map->getContentSize().height;

        setMapScale(_map);
    }

    addChild(_map, 0);

    return errAsInt(Error::OK);
}

int MapScene::setupObjectGroup()
{
    if(_map == nullptr)
    {
        print_error(__FILE__, __LINE__, "Can not setup objects group(map = nullptr), please make setupMap()");
        log_error(__FILE__, __LINE__, "Can not setup objects group(map = nullptr), please make setupMap()");
        return errAsInt(Error::NULL_PTR);
    }

    std::string nameGroupObject = "Objects";
    _objectGroup =  _map->getObjectGroup(nameGroupObject);

    if (_objectGroup == nullptr)
    {
        std::string err = "Can not setup objects group from object's group name: " + nameGroupObject;
        print_error(__FILE__, __LINE__, err.c_str());
        log_error(__FILE__, __LINE__, err.c_str());
        return errAsInt(Error::NULL_PTR);
    }

    return errAsInt(Error::OK);
}

bool MapScene::init()
{
    if (!Layer::init()) { return false; }

    _director = Director::getInstance();
    _visibleSize = _director->getVisibleSize();
    _origin = _director->getVisibleOrigin();

    Vec2 vec_center(_visibleSize.width / 2, _visibleSize.height/2);

    SetEnableScaleMap(false);
    setEnableDrawPolygons(true);

    /// setup and set map
    int err_ind = setupMap();
    if (err_ind != 0)
    {
        print_error(__FILE__, __LINE__, "bad work setMap()");
        log_error(__FILE__, __LINE__, "bad work setMap()");
        return false;
    }

    /// get ptr to objectGroup
    err_ind = setupObjectGroup();
    if (err_ind != 0)
    {
        print_error(__FILE__, __LINE__, "bad work setupObjectGroup()");
        log_error(__FILE__, __LINE__, "bad work setupObjectGroup()");
        return false;
    }

    /// Set borders around the screen or map
    ///@ref Watch size EdgeBox
    err_ind = setSolidEdgeBox();
    if (err_ind != 0)
    {
        print_error(__FILE__, __LINE__, "bad work setupObjectGroup()");
        log_error(__FILE__, __LINE__, "bad work setupObjectGroup()");
        return false;
    }

    /// Set Polygon objects
    err_ind = setSolidPolygonFigure();
    if (err_ind != 0)
    {
        print_error(__FILE__, __LINE__, "bad work setSolidPolygonFigure()");
        log_error(__FILE__, __LINE__, "bad work setSolidPolygonFigure()");
        return false;
    }
    err_ind = setSolidBoxFigure();
    if (err_ind != 0)
    {
        print_error(__FILE__, __LINE__, "bad work setSolidBoxFigure()");
        log_error(__FILE__, __LINE__, "bad work setSolidBoxFigure()");
        return false;
    }

    ///==============================================================================

    auto background = Sprite::create("tile_map/map1/Snow_Background_NSMBW.png");


    float scaleY = _visibleSize.height / background->getContentSize().height;
    float scaleX = _visibleSize.width / background->getContentSize().width;

    float scale_map_background_X = _map->getContentSize().width / background->getContentSize().width;
    float scale_map_background_Y = _map->getContentSize().height / background->getContentSize().height;

    //    if (scaleX > scaleY) { background->setScale(scaleX); }
    //    else { background->setScale(scaleY); }

    background->setScale(scale_map_background_Y);
    //    background->setScaleX(scale_map_background_X);
    //    background->setScaleY(scale_map_background_Y);

    background->setPosition(Point(_origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height / 2));
    addChild(background, -1);



    float radius = 16;
    PhysicsBody* physicsBody = PhysicsBody::createCircle(radius);
    physicsBody->setDynamic(true);
    physicsBody->setGravityEnable(true);



    //create a sprite
    auto sprite = Sprite::create("ball_32.png");
//    float scale_ball = 2 * radius / sprite->getContentSize().width;
//    sprite->setScale(scale_ball);
    sprite->setPosition(Point(_origin.x + _visibleSize.width / 2 + 130, _origin.y + _visibleSize.height / 2));
    sprite->setPhysicsBody(physicsBody);

    addChild(sprite);

    //apply physicsBody to the sprite

//    add five dynamic body
        for (int i = 0; i < 300; ++i)
        {
            physicsBody = PhysicsBody::createCircle(radius);

            //set the body isn't affected by the physics world's gravitational force
            physicsBody->setDynamic(true);
            physicsBody->setGravityEnable(true);

            //set initial velocity of physicsBody
            physicsBody->setVelocity(Vec2(cocos2d::random(-500,500),
                                          cocos2d::random(-500,500)));
            physicsBody->setTag(1);

            sprite = Sprite::create("ball_32.png");
            sprite->setPosition(Vec2(vec_center.x + cocos2d::random(-300,300),
                                     vec_center.y + cocos2d::random(-300,300)));
            sprite->setPhysicsBody(physicsBody);

            addChild(sprite);
        }


    return true;
}

int MapScene::errAsInt(MapScene::Error err)
{
    return static_cast<int>(err);
}


