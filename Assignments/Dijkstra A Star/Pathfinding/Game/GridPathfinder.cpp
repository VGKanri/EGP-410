#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "GridPathfinder.h"
#include "GridGraph.h"
#include "GridVisualizer.h"
#include "Grid.h"
#include "Path.h"
#include "Game.h"
#include "GraphicsBuffer.h"
#include "GameApp.h"

GridPathfinder::GridPathfinder( GridGraph* pGraph )
:Pathfinder(pGraph)
,mTimeElapsed(0.0)
{
#ifdef VISUALIZE_PATH
	mpVisualizer = NULL;
#endif
}

GridPathfinder::~GridPathfinder()
{
#ifdef VISUALIZE_PATH
	delete mpVisualizer;
#endif
}

#ifdef VISUALIZE_PATH
void GridPathfinder::drawVisualization( Grid* pGrid, GraphicsBuffer* pDest )
{
	if (mpVisualizer == NULL)
	{
		mpVisualizer = new GridVisualizer(pGrid);
	}
	else
	{
		mpVisualizer->clear();
	}

	static ALLEGRO_COLOR pathColor = al_map_rgb( 255, 64, 64 );
	static ALLEGRO_COLOR startColor = al_map_rgb(1, 255, 128);
	static ALLEGRO_COLOR stopColor = al_map_rgb(1, 128, 255);

	unsigned int numNodes = mPath.getNumNodes();
	ALLEGRO_COLOR currentPathColor = pathColor;

	if (numNodes > 0)
	{
		for (unsigned int i = 1; i < numNodes-1; i++)
		{
			mpVisualizer->addColor(mPath.peekNode(i)->getId(), currentPathColor);
			float lerpVal = lerp( i, 0, numNodes );
			currentPathColor.r = 1.0f - lerpVal;
		}

		//add beginning and ending color
		mpVisualizer->addColor(mPath.peekNode(0)->getId(), startColor);
		mpVisualizer->addColor(mPath.peekNode(numNodes - 1)->getId(), stopColor);
	}

	mpVisualizer->draw(*pDest);

	centerLines();
}
#endif

//Function to draw center lines between each node
#ifdef VISUALIZE_PATH
void GridPathfinder::centerLines()
{
	float lineOffset = gpGameApp->getGrid()->getSquareSize() / 2; //Gets the offset for the lines

	for (int i = 0; i < mShortPath.getNumNodes() - 1; ++i)
	{
		Vector2D firstPos = gpGameApp->getGrid()->getULCornerOfSquare(mShortPath.peekNode(i)->getId());
		Vector2D secondPos = gpGameApp->getGrid()->getULCornerOfSquare(mShortPath.peekNode(i + 1)->getId());

		al_draw_line(firstPos.getX() + lineOffset, firstPos.getY() + lineOffset, secondPos.getX() + lineOffset, secondPos.getY() + lineOffset, al_map_rgb(255, 255, 255), 5);
	}
}
#endif