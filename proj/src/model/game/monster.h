#pragma once

#include <lcom/lcf.h>
#include "../drawableObject.h"
#include "../direction.h"

enum MonsterType {
  OSVALDO,
  IVAN,
  MIRO
};

typedef struct Monster {
  drawableObject_t* drawableObject;
  int points;
  bool isAlive;
  enum Direction direction;
  int speedX;
  int speedY;
} Monster_t;

Monster_t* createMonster(enum MonsterType monsterType, int x, int y, int speedX, int speedY);
void destroyMonster(Monster_t* monster);
int getMonsterImageIndex(enum MonsterType monsterType);
void changeMonsterDirection(Monster_t* monster);


