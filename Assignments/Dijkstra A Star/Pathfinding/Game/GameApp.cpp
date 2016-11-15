#include <allegro5/allegro.h>
#include "Game.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "PathToMessage.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Vector2D.h"
#include "Grid.h"
#include "GridGraph.h"
#include "Connection.h"
#include "Path.h"
#include "DepthFirstPathfinder.h"
#include "Pathfinder.h"
#include "GridPathfinder.h"
#include "GridVisualizer.h"
#include "DebugDisplay.h"
#include "PathfindingDebugContent.h"
#include "Dijkstra.h"
#include "AStar.h"

#include <fstream>
#include <vector>

const IDType BACKGROUND_ID = ENDING_SEQUENTIAL_ID + 1;
const int GRID_SQUARE_SIZE = 32;
const std::string gFileName = "pathgrid.txt";

GameApp::GameApp()
:mpMessageManager(NULL)
,mpGrid(NULL)
,mpGridGraph(NULL)
,mpPathfinder(NULL)
,mpDebugDisplay(NULL)
{
}

GameApp::~GameApp()
{
	cleanup();
}

bool GameApp::init()
{
	bool retVal = Game::init();
	if( retVal == false )
	{

		return false;
	}

	mpMessageManager = new GameMessageManager();

	//create and load the Grid, GridBuffer, and GridRenderer
	mpGrid = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
	mpGridVisualizer = new GridVisualizer( mpGrid );
	std::ifstream theStream( gFileName );
	mpGrid->load( theStream );

	//create the GridGraph for pathfinding
	mpGridGraph = new GridGraph(mpGrid);
	//init the nodes and connections
	mpGridGraph->init();

	mpDijkstra = new Dijkstra(mpGridGraph);
	mpAStar = new AStar(mpGridGraph);

	mpPathfinder = mpDijkstra;
	bool mIsDijkstra = true;

	//load buffers
	mpGraphicsBufferManager->loadBuffer( BACKGROUND_ID, "wallpaper.bmp");

	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( BACKGROUND_ID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, pBackGroundBuffer->getWidth(), pBackGroundBuffer->getHeight() );
	}

	//debug display
	PathfindingDebugContent* pContent = new PathfindingDebugContent( mpPathfinder );
	mpDebugDisplay = new DebugDisplay( Vector2D(0,12), pContent );

	mpMasterTimer->start();
	return true;
}

void GameApp::cleanup()
{
	delete mpMessageManager;
	mpMessageManager = NULL;

	delete mpGrid;
	mpGrid = NULL;

	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	delete mpGridGraph;
	mpGridGraph = NULL;

	delete mpAStar;
	mpAStar = NULL;

	delete mpDijkstra;
	mpDijkstra = NULL;

	delete mpDebugDisplay;
	mpDebugDisplay = NULL;
}

void GameApp::beginLoop()
{
	//should be the first thing done
	Game::beginLoop();
}

void GameApp::processLoop()
{
	//get back buffer
	GraphicsBuffer* pBackBuffer = mpGraphicsSystem->getBackBuffer();
	//copy to back buffer
	mpGridVisualizer->draw( *pBackBuffer );
#ifdef VISUALIZE_PATH
	//show pathfinder visualizer
	mpPathfinder->drawVisualization(mpGrid, pBackBuffer);
#endif

	mpDebugDisplay->draw( pBackBuffer );

	mpMessageManager->processMessagesForThisframe();

	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state( &mouseState );

	ALLEGRO_KEYBOARD_STATE keyboardState;
	al_get_keyboard_state(&keyboardState);

	if( al_mouse_button_down( &mouseState, 1 ) )//left mouse click
	{
		mFirstPos = Vector2D(mouseState.x, mouseState.y);

		GameMessage* pMessage = new PathToMessage(mFirstPos, mSecondPos);
		mpMessageManager->addMessage(pMessage, 0);

	}

	if (al_mouse_button_down(&mouseState, 2))
	{
		mSecondPos = Vector2D(mouseState.x, mouseState.y);

		GameMessage* pMessage = new PathToMessage(mFirstPos, mSecondPos);
		mpMessageManager->addMessage(pMessage, 0);
	}

	if (al_key_down(&keyboardState, ALLEGRO_KEY_A))
	{
		if (mIsDijkstra)
		{
			flipPathfinding();

			GameMessage* pMessage = new PathToMessage(mFirstPos, mSecondPos);
			mpMessageManager->addMessage(pMessage, 0);
		}
	}

	if (al_key_down(&keyboardState, ALLEGRO_KEY_D))
	{
		if (!mIsDijkstra)
		{
			flipPathfinding();

			GameMessage* pMessage = new PathToMessage(mFirstPos, mSecondPos);
			mpMessageManager->addMessage(pMessage, 0);
		}
	}

	//Drawing Text

	Vector2D text1pos = gpGameApp->getGrid()->getULCornerOfSquare(gpGameApp->
		getGrid()->getSquareIndexFromPixelXY((int)mFirstPos.getX(), 
		(int)mFirstPos.getY()));

	Vector2D text2pos = gpGameApp->getGrid()->getULCornerOfSquare(gpGameApp->
		getGrid()->getSquareIndexFromPixelXY((int)mSecondPos.getX(),
		(int)mSecondPos.getY()));

	al_draw_text(mpFont, al_map_rgb(0, 0, 0),
		text1pos.getX(),
		text1pos.getY(),
		ALLEGRO_ALIGN_LEFT, "S");

	al_draw_text(mpFont, al_map_rgb(0, 0, 0),
		text2pos.getX(),
		text2pos.getY(),
		ALLEGRO_ALIGN_LEFT, "G");

	//should be last thing in processLoop
	Game::processLoop();
}

bool GameApp::endLoop()
{
	return Game::endLoop();
}

//Flips the pathfinding algorithm if necessary
void GameApp::flipPathfinding()
{
	if (mIsDijkstra)
	{
		mpPathfinder = mpAStar;
		mIsDijkstra = false;
	}
	else
	{
		mpPathfinder = mpDijkstra;
		mIsDijkstra = true;
	}
}