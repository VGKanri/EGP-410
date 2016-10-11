#pragma once

#include "Trackable.h"

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	PLAYER_MOVETO_MESSAGE = 0,
	EXIT_GAME_MESSAGE = 1,
	ADD_UNIT_MESSAGE_ARRIVE = 2,
	ADD_UNIT_MESSAGE_SEEK = 3,
	REMOVE_UNIT_MESSAGE = 4,
	ADD_UNIT_MESSAGE_WANDER_AND_SEEK = 5,
	ADD_UNIT_MESSAGE_WANDER_AND_FLEE = 6
};

class GameMessage: public Trackable
{
public:
	friend class GameMessageManager;

	GameMessage( MessageType type  );
	~GameMessage();

	double getSubmittedTime() const { return mSubmittedTime; };
	double getScheduledTime() const { return mScheduledTime; };

protected:
	MessageType mType;
	double mSubmittedTime;
	double mScheduledTime;

private:
	virtual void process() = 0; 
};

