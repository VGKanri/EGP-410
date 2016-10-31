#ifndef ADDBOIDMESSAGE_H
#define ADDBOIDMESSAGE_H

#include "GameMessage.h"

class AddBoidMessage : public GameMessage
{
public:
	AddBoidMessage();
	~AddBoidMessage();

	void process();
};


#endif
