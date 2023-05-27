#ifndef _LCOM_GAME_H_
#define _LCOM_GAME_H_

#include <lcom/lcf.h>
#include "state.h"

#include "model/game/map.h"
#include "xpm/loadXpm.h"

#include "model/menu/leaderboard.h"
#include "model/menu/over.h"

#include "controllers/handleInterrupt.h"

#include "devices/keyboard.h"
#include "devices/timer.h"
#include "devices/vbe.h"
#include "devices/graphics.h"
#include "devices/mouse.h"
#include "devices/rtc.h"



int (game_loop)();

#endif

