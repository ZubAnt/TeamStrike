#include "Map.h"

#include "Menu/AbstractMenuData.h"
#include "Player/Player.h"
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

    //    map_path = "tile_map/map1/ice.tmx";
    map_path = "tile_map/map2/map2_64.tmx";
    background_path = "tile_map/map2/BG.png";

    GroundPolygonOblects = {"Polygon_GND",
                            "Polygon_GNDL1",
                            "Polygon_GNDR1",
                            "Polygon_GNDL2",
                            "Polygon_GNDR2",
                            "Polygon_GNDL3",
                            "Polygon_GNDR3"};

    StartColumnBoxOblects = {"Box_Start_Col_Left", "Box_Start_Col_Right"};

    GroundBoxOblects = {"Box_GNDL1", "Box_GNDL2", "Box_GNDR1", "Box_GNDR2"};

    PlatformBoxOblects = {"Platform1",
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
                          "Platform14"};

    enable_scale_map = true;
    enable_scale_background = true;
    enable_draw_polygons = false;
    enable_draw_boxes = false;
}


MapScene::~MapScene()
{}

Scene *MapScene::createScene()
{
    auto scene = Scene::createWithPhysics();
//    scene->getPhysicsWorld()->setAutoStep(false);
//    scene->getPhysicsWorld()->step(1 / 60.0f);
    scene->getPhysicsWorld()->setFixedUpdateRate( 4000 );
//    scene->getPhysicsWorld()->setSubsteps(3);
//    scene->getPhysicsWorld()->setSpeed( 2.0f);
    scene->getPhysicsWorld()->setGravity(Vect(0.f, -4000.0f));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = MapScene::create();
    scene->addChild(layer);
    return scene;
}

int MapScene::setSolidEdgeBox()
{
    ///@ref Если будем делать слежение камерой за объектом, то здесь не _visibleSize!!!!!!!!!!!!!!!!!!

    PhysicsBody* edgeBox = PhysicsBody::createEdgeBox(_map->getContentSize());
    Node* edgeNode = Node::create();

    if (edgeBox == nullptr || edgeNode == nullptr)
    {
        print_error(__FILE__, __LINE__, "Can not create edgeBox");
        log_error(__FILE__, __LINE__, "Can not create edgeBox");
        return errAsInt(Error::NULL_PTR);
    }

    edgeNode->setPosition(_map_centre);
    edgeNode->setPhysicsBody(edgeBox);
    this->addChild(edgeNode, 1);
    return errAsInt(Error::OK);
}


int MapScene::setSolidPolygonFigures(std::vector<std::string> &NamePolygonObjects, int bitmask, const PhysicsMaterial& material)
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
            auto polygon = PhysicsBody::createPolygon(pointsVec2Object, vec_point.size(), material);
            polygon->setDynamic(false);
            polygon->setGravityEnable(false);
            polygon->setContactTestBitmask( true );
            polygon->setCollisionBitmask( bitmask );

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

int MapScene::setSolidBoxFigures(std::vector<std::string> &NameBoxObjects, int bitmask, const PhysicsMaterial& material)
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

            PhysicsBody* polygon = PhysicsBody::createPolygon(rectangle, 4, material);
            polygon->setDynamic(false);
            polygon->setGravityEnable(false);
            polygon->setContactTestBitmask( true );
            polygon->setCollisionBitmask( bitmask );
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

int MapScene::setBackground()
{
    Sprite*  background = Sprite::create(background_path);
    if (background == nullptr)
    {
        std::string err = "Can not create background from " + background_path;
        print_error(__FILE__, __LINE__, err.c_str());
        log_error(__FILE__, __LINE__,err.c_str());
        return errAsInt(Error::NULL_PTR);
    }

    float scale_map_background_X = _map->getContentSize().width / background->getContentSize().width;
    float scale_map_background_Y = _map->getContentSize().height / background->getContentSize().height;

    if (scale_map_background_X > scale_map_background_Y)
    {
        background->setScale(scale_map_background_X);
    }
    else
    {
        background->setScale(scale_map_background_Y);
    }

    background->setPosition(_map_centre);
    addChild(background, -1);

    return errAsInt(Error::OK);
}

int MapScene::setPlayer()
{
    player = Player::create();
    if (player == nullptr)
    {
        std::string err = "Can not create player";
        print_error(__FILE__, __LINE__, err.c_str());
        log_error(__FILE__, __LINE__,err.c_str());
        return errAsInt(Error::NULL_PTR);
    }
    //    player->setPosition(Vec2(_origin.x + _visibleSize.width / 2,
    //                             _origin.y + _visibleSize.height / 2));

    //    player->setScale(0.75f);


    Size size = Director::sharedDirector()->getVisibleSize();  //default screen size (or design resolution size, if you are using design resolution)
    Point center = Point(size.width/2 + _origin.x, size.height/2 + _origin.y);

    player->setPosition(center);
    addChild(player, 5);

    float playfield_width = size.width * 2.0; // make the x-boundry 2 times the screen width
    float playfield_height = size.height * 2.0; // make the y-boundry 2 times the screen height

    ///===============================================================
    /// _leftBoundary = -512; _rightBoundary = 512; _topBoundary = 384; _bottomBoundary = -384
    //        Follow* node = Follow::create(player,
    //                                     Rect(center.x - playfield_width/2,
    //                                          center.y - playfield_height/2 ,
    //                                          playfield_width,
    //                                          playfield_height));
    //        node->printBoundary();
    ///===============================================================
    ///_leftBoundary = 0; _rightBoundary = 0; _topBoundary = 0; _bottomBoundary = 0
    //    Follow* node = Follow::create(player);
    //    node->printBoundary();
    ///===============================================================
    Follow* node = Follow::create(player);

    //    ///@ref MAGIC
    //    node->setBoundary(-3072, 0, 0, -768 * 1.675);
    ////    node->setBoundary(-3072, 0, 0, -1024);
    node->setBoundary(-3 * size.width, 0, -size.height * 67 / 40, 0);
    //    std::cout << size.width << " " << size.height <<  std::endl
    //              << center.x << " " << center.y << std::endl
    //              << _visibleSize.width << " " << _visibleSize.height <<  std::endl
    //              << _map->getContentSize().width << " " << _map->getContentSize().height << std::endl;
    //    node->printBoundary();

    ///===============================================================
    this->runAction(node);


    //    this->runAction(Follow::create(player));
    return errAsInt(Error::OK);
}

int MapScene::setupEventListener()
{

    auto listener = EventListenerKeyboard::create();
    auto contactListener = EventListenerPhysicsContact::create();
    auto mouseListener = EventListenerMouse::create();

    if (listener == nullptr || contactListener == nullptr || mouseListener == nullptr)
    {
        std::string err = "Can not setup Listener";
        print_error(__FILE__, __LINE__, err.c_str());
        log_error(__FILE__, __LINE__,err.c_str());

        return errAsInt(Error::NULL_PTR);
    }


    listener->onKeyPressed = CC_CALLBACK_2(MapScene::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(MapScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    contactListener->onContactBegin = CC_CALLBACK_1(MapScene::onContactBegin, this);
    contactListener->onContactPreSolve = CC_CALLBACK_1(MapScene::onContactPreSolve, this);
    contactListener->onContactPostSolve = CC_CALLBACK_1(MapScene::onContactPostSolve, this);
    contactListener->onContactSeparate = CC_CALLBACK_1(MapScene::onContactSeparate, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    mouseListener->onMouseUp = CC_CALLBACK_1(MapScene::onMouseUp, this);
    mouseListener->onMouseDown = CC_CALLBACK_1(MapScene::onMouseDown, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);



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

    _map_centre = Point(_map->getContentSize().width / 2, _map->getContentSize().height / 2);

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
    setEnableDrawPolygons(false);

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
        print_error(__FILE__, __LINE__, "bad work setSolidEdgeBox()");
        log_error(__FILE__, __LINE__, "bad work setSolidEdgeBox()");
        return false;
    }

    /// Set Ground Polygon objects
    err_ind = setSolidPolygonFigures(GroundPolygonOblects, BitMask::GROUND, PhysicsMaterial(MAP_DENSITY, MAP_RESTITUTION, MAP_FRICTION));
    if (err_ind != 0)
    {
        print_error(__FILE__, __LINE__, "bad work setSolidPolygonFigure()");
        log_error(__FILE__, __LINE__, "bad work setSolidPolygonFigure()");
        return false;
    }
    /// Set Ground Box objects
    err_ind = setSolidBoxFigures(GroundBoxOblects, BitMask::GROUND, PhysicsMaterial(MAP_DENSITY, MAP_RESTITUTION, MAP_FRICTION));
    if (err_ind != 0)
    {
        print_error(__FILE__, __LINE__, "bad work setSolidBoxFigures()");
        log_error(__FILE__, __LINE__, "bad work setSolidBoxFigures()");
        return false;
    }
    /// Set Start Column Box objects
    err_ind = setSolidBoxFigures(StartColumnBoxOblects, BitMask::StartCOLUMN, PhysicsMaterial(MAP_DENSITY, MAP_RESTITUTION, MAP_FRICTION));
    if (err_ind != 0)
    {
        print_error(__FILE__, __LINE__, "bad work setSolidBoxFigures()");
        log_error(__FILE__, __LINE__, "bad work setSolidBoxFigures()");
        return false;
    }
    err_ind = setSolidBoxFigures(PlatformBoxOblects, BitMask::PLATFORMS, PhysicsMaterial(MAP_DENSITY, MAP_RESTITUTION, MAP_FRICTION));
    if (err_ind != 0)
    {
        print_error(__FILE__, __LINE__, "bad work setSolidBoxFigures()");
        log_error(__FILE__, __LINE__, "bad work setSolidBoxFigures()");
        return false;
    }

    /// Set Background
    err_ind = setBackground();
    if (err_ind != 0)
    {
        print_error(__FILE__, __LINE__, "bad work setBackground()");
        log_error(__FILE__, __LINE__, "bad work setBackground()");
        return false;
    }

    /// Set Player
    err_ind = setPlayer();
    if (err_ind != 0)
    {
        print_error(__FILE__, __LINE__, "bad work setPlayer()");
        log_error(__FILE__, __LINE__, "bad work setPlayer()");
        return false;
    }

    /// Setup Listener
    err_ind = setupEventListener();
    if (err_ind != 0)
    {
        print_error(__FILE__, __LINE__, "bad work setupEventListener()");
        log_error(__FILE__, __LINE__, "bad work setupEventListener()");
        return false;
    }
    player->is_onGround = false;
    this->scheduleUpdate();

    return true;
}

int MapScene::errAsInt(MapScene::Error err)
{
    return static_cast<int>(err);
}

