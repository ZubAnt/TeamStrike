#ifndef MAP_H
#define MAP_H

#include "cocos2d.h"
#include <vector>
#include <string>
#include <stdexcept>
#include "Logging/logger.h"

USING_NS_CC;

enum struct Error;

class MapScene: public cocos2d::Layer
{
public:
    MapScene();
    ~MapScene();
    static cocos2d::Scene* createScene();
    bool init();
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

private:

    TMXTiledMap *_map;
    TMXObjectGroup *_objectGroup;
    cocos2d::Director *_director;
    cocos2d::Size _visibleSize;
    Vec2 _origin;

    float _scale_map_x;
    float _scale_map_y;

    float scale_bg_x;
    float scale_bg_y;

    std::string map_path;
    std::vector<std::string> NameBoxObjects;
    std::vector<std::string> NamePolygonObjects;

    bool enable_draw_polygons;
    bool enable_draw_boxes;
    bool enable_scale_map;
    bool enable_scale_background;

    void setEnableDrawAllSolidFigure(bool enable);
    void setEnableDrawPolygons(bool enable);
    void setEnableDrawBoxes(bool enable);

    void SetEnableScaleMap(bool enable);
    void setEnableScaleBackground(bool enable);


    void setMapScale(Node *node);

    int setupMap();
    int setupObjectGroup();
    int setSolidEdgeBox();
    int setSolidPolygonFigure();
    int setSolidBoxFigure();


};


#endif // MAP_H
