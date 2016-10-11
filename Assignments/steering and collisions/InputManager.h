//Input Manager also taken from final project in EGP - 310
//Made in conjunction with Matthew Makuch and used with permission
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "UnitManager.h"
#include "GameMessage.h"
#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "ExitGameMessage.h"
#include "AddUnitMessageArrive.h"
#include "AddUnitMessageSeek.h"
#include "RemoveUnitMessage.h"
#include "SpriteManager.h"
#include "Game.h"
#include "AddUnitMessageWanderAndSeek.h"
#include "AddUnitMessageWanderAndFlee.h"

class Game;

//Class for the InputManager
class InputManager : public Trackable
{
private:
	static InputManager* mpsInstance;

	static ALLEGRO_EVENT_QUEUE* mpEventQueue;

	Game* mpsGame;
	GraphicsSystem* mpGraphicSystem;
	ALLEGRO_FONT* mpFont;
	GameMessageManager* mpGameMessageManager;
	SpriteManager* mpSpriteManager;

	//Input buffer to prevent tons of inputs at the same time
	int inputBuffer;

public:
	InputManager();
	~InputManager();

	static InputManager* getInstance() { return mpsInstance; };
	static void init();
	void update();
	void cleanUp();
};

#endif
