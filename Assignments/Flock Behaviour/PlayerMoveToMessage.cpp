#include "Game.h"

PlayerMoveToMessage::PlayerMoveToMessage( const Vector2D& pos )
:GameMessage(PLAYER_MOVETO_MESSAGE)
,mPos(pos)
{
}

PlayerMoveToMessage::~PlayerMoveToMessage()
{
}

void PlayerMoveToMessage::process()
{
	gpGame->getPlayerUnit()->arrive(mPos);
	//std::cout << mPos.getX() << mPos.getY();
}

