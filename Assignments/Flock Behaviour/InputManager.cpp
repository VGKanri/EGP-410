//Input Manager also taken from final project in EGP - 310
//Made in conjunction with Matthew Makuch and used with permission
#include "InputManager.h"
#include <sstream>

InputManager* InputManager::mpsInstance = NULL;

ALLEGRO_EVENT_QUEUE* InputManager::mpEventQueue = NULL;

InputManager::InputManager()
{
	mpsGame = gpGame;
	mpGraphicSystem = mpsGame->getGraphicsSystem();
	mpGameMessageManager = mpsGame->getMessageManager();
	mpSpriteManager = mpsGame->getSpriteManager();
	inputBuffer = 10;
}

InputManager::~InputManager()
{
	cleanUp();
}

void InputManager::init()
{
	if (mpsInstance == NULL)
	{
		mpsInstance = new InputManager;
	}

	//return true;
}

void InputManager::update()
{
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);

	inputBuffer--;

	if (al_mouse_button_down(&mouseState, 1))//left mouse click
	{
		Vector2D pos(mouseState.x, mouseState.y);
		GameMessage* pMessage = new PlayerMoveToMessage(pos);
		//MESSAGE_MANAGER->addMessage(pMessage, 0);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	//create mouse text
	std::stringstream mousePos;
	mousePos << mouseState.x << ":" << mouseState.y;

	mpFont = mpsGame->getFont();

	//write text at mouse position
	al_draw_text(mpFont, al_map_rgb(255, 255, 255), mouseState.x, mouseState.y, ALLEGRO_ALIGN_CENTRE, mousePos.str().c_str());

	mpGraphicSystem->swap();

	//get current keyboard state
	ALLEGRO_KEYBOARD_STATE keyState;
	al_get_keyboard_state(&keyState);

	//if escape key was down then exit the loop
	if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
	{
		GameMessage* pMessage = new ExitGameMessage();
		MESSAGE_MANAGER->addMessage(pMessage, 0);
		inputBuffer = 100;
	}

	//all this should be moved to InputManager!!!
	if (inputBuffer < 0)
	{

		if (al_key_down(&keyState, ALLEGRO_KEY_I))
		{
			GameMessage* pMessage = new AddBoidMessage();
			MESSAGE_MANAGER->addMessage(pMessage, 0);
			inputBuffer = 10;
		}

		if (al_key_down(&keyState, ALLEGRO_KEY_A))
		{
			gpGame->getStateManager()->setSelectedProperty(ALIGNMENT_WEIGHT);
			inputBuffer = 10;
		}

		if (al_key_down(&keyState, ALLEGRO_KEY_C))
		{
			gpGame->getStateManager()->setSelectedProperty(COHESION_WEIGHT);
			inputBuffer = 10;
		}

		if (al_key_down(&keyState, ALLEGRO_KEY_S))
		{
			gpGame->getStateManager()->setSelectedProperty(SEPARATION_WEIGHT);
			inputBuffer = 10;
		}

		if (al_key_down(&keyState, ALLEGRO_KEY_D) && gpGame->getUnitManager()->getListLength() <= 6)
		{
			GameMessage* pMessage = new ExitGameMessage();
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}

		if (al_key_down(&keyState, ALLEGRO_KEY_D) && gpGame->getUnitManager()->getListLength() > 6)
		{
			GameMessage* pMessage = new RemoveUnitMessage(0);
			MESSAGE_MANAGER->addMessage(pMessage, 0);
			inputBuffer = 10;
		}

		if (al_key_down(&keyState, ALLEGRO_KEY_R))
		{
			gpGame->getStateManager()->setSelectedProperty(REACTION_RADIUS);
			inputBuffer = 10;
		}

		if (al_key_down(&keyState, ALLEGRO_KEY_E))
		{
			gpGame->getStateManager()->setSelectedProperty(ROT_VELOCITY);
			inputBuffer = 10;
		}

		if (al_key_down(&keyState, ALLEGRO_KEY_V))
		{
			gpGame->getStateManager()->setSelectedProperty(MAX_VELOCITY);
			inputBuffer = 10;
		}

		if (al_key_down(&keyState, ALLEGRO_KEY_EQUALS))
		{
			gpGame->getStateManager()->addStat();
			inputBuffer = 10;
		}

		if (al_key_down(&keyState, ALLEGRO_KEY_MINUS))
		{
			gpGame->getStateManager()->subStat();
			inputBuffer = 10;
		}

		if (al_key_down(&keyState, ALLEGRO_KEY_LCTRL) && al_key_down(&keyState, ALLEGRO_KEY_S))
		{
			gpGame->getStateManager()->saveData();
			inputBuffer = 10;
		}
	}
}

void InputManager::cleanUp()
{
	delete mpsInstance;
}
