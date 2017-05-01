#ifndef MAP_H
#define MAP_H

#include "cocos2d.h"
#include <vector>
#include <string>
#include <stdexcept>
#include "Logging/logger.h"
#include "Player/Player.h"
#include "BitMask.h"
#include "Bullet/Bullet.h"


#define MAP_DENSITY 1000.0f
#define MAP_RESTITUTION 0.0000001f
#define MAP_FRICTION 5.0f

USING_NS_CC;

enum struct Error;

class MapScene: public cocos2d::Layer
{
public:
    MapScene();
    ~MapScene();
    static cocos2d::Scene* createScene();
    bool init();
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
    double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);
    bool onContactBegin( cocos2d::PhysicsContact &contact );
    bool onContactPreSolve( cocos2d::PhysicsContact &contact );
    bool onContactSeparate( cocos2d::PhysicsContact &contact );
    bool onContactPostSolve( cocos2d::PhysicsContact &contact );
    CREATE_FUNC(MapScene)

    enum struct Error
    {
        OK = 0,
        NULL_PTR = 1,
        CATCHING_AN_EXCEPTION = 2,
        BAD_NAME_POLYGON_OBJECT = 3,
        BAD_NAME_BOX_OBJECT = 4,
        SCALE_MAP_PARAM_IS_NULL = 5
    };
    const char* const err_string[6] = {"OK",
                                       "NULL_PTR",
                                       "CATCHING_AN_EXCEPTION"
                                       "BAD_NAME_POLYGON_OBJECT",
                                       "BAD_NAME_BOX_OBJECT",
                                       "SCALE_MAP_PARAM_IS_NULL"
                                      };
    int errAsInt(Error err);

    void update(float dt);
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void onMouseDown(Event *event);
    void onMouseUp(Event *event);
//print_error
private:

    TMXTiledMap *_map;
    Point _map_centre;
    TMXObjectGroup *_objectGroup;
    cocos2d::Director *_director;
    cocos2d::Size _visibleSize;
    Vec2 _origin;

    Player * player;
    std::vector<Bullet*> bullets;

    float _scale_map_x;
    float _scale_map_y;

    float scale_bg_x;
    float scale_bg_y;

    std::string map_path;
    std::string background_path;

    std::vector<std::string> StartColumnBoxOblects;
    std::vector<std::string> PlatformBoxOblects;
    std::vector<std::string> GroundBoxOblects;
    std::vector<std::string> GroundPolygonOblects;

    bool enable_draw_polygons;
    bool enable_draw_boxes;
    bool enable_scale_map;
    bool enable_scale_background;
    bool isJump;

    void setEnableDrawAllSolidFigure(bool enable);
    void setEnableDrawPolygons(bool enable);
    void setEnableDrawBoxes(bool enable);

    void SetEnableScaleMap(bool enable);
    void setEnableScaleBackground(bool enable);

    void setMapScale(Node *node);

    int setupMap();
    int setupObjectGroup();
    int setSolidEdgeBox();
    int setSolidPolygonFigures(std::vector<std::string> &NamePolygonObjects, int bitmask, const PhysicsMaterial &material);
    int setSolidBoxFigures(std::vector<std::string> &NameBoxObjects, int bitmask, const PhysicsMaterial& material);
    int setBackground();
    int setPlayer();
    int setupEventListener();
};


#endif // MAP_H
