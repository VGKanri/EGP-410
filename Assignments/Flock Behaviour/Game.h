#ifndef GAME_H
#define GAME_H

#include "Trackable.h"
#include "PerformanceTracker.h"
#include "Defines.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <string>
#include "UnitManager.h"
#include "InputManager.h"
#include "timer.h"
#include "StateManager.h"

class GraphicsSystem;
class GraphicsBuffer;
class GraphicsBufferManager;
class SpriteManager;
class KinematicUnit;
class GameMessageManager;
class UnitManager;
class Timer;
class InputManager;
class StateManager;

const IDType BACKGROUND_SPRITE_ID = 0;
const IDType PLAYER_ICON_SPRITE_ID = 1;
const IDType AI_ICON_SPRITE_ID = 2;

const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame

class Game :public Trackable
{
public:
	Game();
	~Game();

	bool init();//returns true if no errors, false otherwise
	void cleanup();

	//game loop
	void beginLoop();
	void processLoop();
	bool endLoop();

	inline GraphicsSystem* getGraphicsSystem() const { return mpGraphicsSystem; };
	inline GraphicsBufferManager* getGraphicsBufferManager() const { return mpGraphicsBufferManager; };
	inline SpriteManager* getSpriteManager() const { return mpSpriteManager; };
	inline GameMessageManager* getMessageManager() { return mpMessageManager; };
	inline Timer* getMasterTimer() const { return mpMasterTimer; };
	inline double getCurrentTime() const { return mpMasterTimer->getElapsedTime(); };
	inline ALLEGRO_FONT* getFont() const { return mpFont; };
	inline UnitManager* getUnitManager() const { return mpUnitManager; };
	inline InputManager* getInputManager() const { return mpInputManager; };
	inline bool getShouldEnd() const { return mShouldExit; };
	inline void setShouldEnd(bool end) { mShouldExit = end; };
	inline StateManager* getStateManager()  { return mpStateManager; };
	//static Game* getGame() { return gpGame; };
	
	inline KinematicUnit* getPlayerUnit() { return mpUnitManager->getUnit(0); };//should be someplace else
	
private:
	GraphicsSystem* mpGraphicsSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	SpriteManager* mpSpriteManager;
	GameMessageManager* mpMessageManager;
	UnitManager* mpUnitManager;
	InputManager* mpInputManager;
	Timer* mpLoopTimer;
	Timer* mpMasterTimer;
	StateManager* mpStateManager;
	bool mShouldExit;

	//should be somewhere else
	ALLEGRO_FONT* mpFont;
	ALLEGRO_SAMPLE* mpSample;
	IDType mBackgroundBufferID;
	IDType mPlayerIconBufferID;
	IDType mEnemyIconBufferID;

	//static Game* gpGame;
};

float genRandomBinomial();//range -1:1 from "Artificial Intelligence for Games", Millington and Funge
float genRandomFloat();//range 0:1 from "Artificial Intelligence for Games", Millington and Funge

extern Game* gpGame;
extern PerformanceTracker* gpPerformanceTracker;

#endif