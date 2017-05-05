#ifndef REDPLAYER_H
#define REDPLAYER_H

#include "../Player.h"

class RedPlayer: public Player
{
public:
    RedPlayer();
    static Player* create();
    void initPlayer();
};

#endif // REDPLAYER_H
