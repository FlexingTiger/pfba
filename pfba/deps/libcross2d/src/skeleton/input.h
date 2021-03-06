//
// Created by cpasjuste on 11/01/17.
//

#ifndef _INPUT_H
#define _INPUT_H

#include <cstring>
#include <vector>

#define PLAYER_COUNT 4
#define KEY_COUNT 14

#define EV_RESIZE 0x4000
#define EV_QUIT 0x8000
#define EV_REFRESH 0x10000

class Input {

public:

    enum Key {
        KEY_UP = 0x0001,
        KEY_DOWN = 0x0002,
        KEY_LEFT = 0x0004,
        KEY_RIGHT = 0x0008,
        KEY_COIN = 0x0010,
        KEY_START = 0x0020,
        KEY_FIRE1 = 0x0040,
        KEY_FIRE2 = 0x0080,
        KEY_FIRE3 = 0x0100,
        KEY_FIRE4 = 0x0200,
        KEY_FIRE5 = 0x0400,
        KEY_FIRE6 = 0x0800,
        KEY_MENU1 = 0x1000,
        KEY_MENU2 = 0x2000,
    };

    struct Axis {
        int id;
        short value;
    };

    struct Player {
        int mapping[KEY_COUNT];
        Axis lx {0, 0};
        Axis ly {1, 0};
        Axis rx {2, 0};
        Axis ry {3, 0};
        unsigned int state;
        int dead_zone = 8000;
        bool enabled = false;
        void *data = NULL;
        int id = 0;
    };

    // map keyboard to player 0
    struct Keyboard {
        int mapping[KEY_COUNT];
    };

    Input() {};

    virtual ~Input() {};

    virtual Player *Update(int rotate = 0) { return players; }; // to implement
    virtual int GetButton(int player) { return -1; }; // to implement

    virtual int Clear(int player);
    virtual void SetJoystickMapping(int player, int *mapping, int deadzone = 8000);
    virtual void SetKeyboardMapping(int *mapping);

    Player players[PLAYER_COUNT];
    Keyboard keyboard;
};

#ifdef __PSP2__
#include "sdl2/sdl2_input.h"
#elif __3DS__
#include "3ds/ctr_input.h"
#elif __SDL2__
#include "sdl2/sdl2_input.h"
#elif __SFML__
#include "sfml/sfml_input.h"
#endif

#endif //_INPUT_H
