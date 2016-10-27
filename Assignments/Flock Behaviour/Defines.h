#ifndef DEFINES_H
#define DEFINES_H

#include <string>

typedef int IDType;
typedef std::string IDDescriptor;

const float AVOIDANCE_RADIUS = 128.0f;
const float FLEE_RADIUS = 32.0f;

const IDType INVALID_ID = -1;

const IDType HIGHEST_ID = 9999;

const float MAX_WANDER_ROTATION = 1.0f;

#define MESSAGE_MANAGER gpGame->getMessageManager()
#define GRAPHICS_SYSTEM gpGame->getGraphicsSystem()

#endif