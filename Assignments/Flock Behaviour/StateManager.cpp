#include "StateManager.h"
#include "Game.h"

#include <fstream>
#include <string>

StateManager::StateManager()
{
	mDebugState = ON;
	mSelectedProperty = ALIGNMENT_WEIGHT;

	mAlignWeight = 20;
	mCohWeight = 50;
	mSepWeight = 20;

	mMaxVelocity = 50.0f;
	mRotVelocity = 0.0f;
	mReactRadius = 100.0f;

	loadData();

	//Drawing Text to the screen with the values
}

StateManager::~StateManager()
{
}

void StateManager::loadData()
{
	std::string input;
	std::ifstream fin("properties.txt");

	if (fin.is_open())
	{
		std::getline(fin, input);
		mAlignWeight = std::stof(input);

		std::getline(fin, input);
		mCohWeight = std::stof(input);

		std::getline(fin, input);
		mSepWeight = std::stof(input);

		fin.close();
	}
}

void StateManager::saveData() const
{
	std::ofstream fout;

	fout.open("properties.txt");

	fout << mAlignWeight << std::endl
		<< mCohWeight << std::endl
		<< mSepWeight;

	fout.close();
}

void StateManager::update()
{
	std::string text = AL_WEIGHT + to_string(mAlignWeight);
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), 10, 10, ALLEGRO_ALIGN_LEFT, text.c_str());
	text = COH_WEIGHT + to_string(mCohWeight);
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), 10, 30, ALLEGRO_ALIGN_LEFT, text.c_str());
	text = SEP_WEIGHT + to_string(mSepWeight);
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), 10, 50, ALLEGRO_ALIGN_LEFT, text.c_str());
	text = M_VELOCITY + to_string(mMaxVelocity);
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), 10, 70, ALLEGRO_ALIGN_LEFT, text.c_str());
	text = ROT_VEL + to_string(mRotVelocity);
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), 10, 90, ALLEGRO_ALIGN_LEFT, text.c_str());
	text = REACTION_RAD + to_string(mReactRadius);
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), 10, 110, ALLEGRO_ALIGN_LEFT, text.c_str());

	//Drawing active property in red
	switch(mSelectedProperty)
	{
	case ALIGNMENT_WEIGHT:
		text = AL_WEIGHT + to_string(mAlignWeight);
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 0, 0), 10, 10, ALLEGRO_ALIGN_LEFT, text.c_str());
		break;
	case COHESION_WEIGHT:
		text = COH_WEIGHT + to_string(mCohWeight);
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 0, 0), 10, 30, ALLEGRO_ALIGN_LEFT, text.c_str());
		break;
	case SEPARATION_WEIGHT:
		text = SEP_WEIGHT + to_string(mSepWeight);
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 0, 0), 10, 50, ALLEGRO_ALIGN_LEFT, text.c_str());
		break;
	case MAX_VELOCITY:
		text = M_VELOCITY + to_string(mMaxVelocity);
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 0, 0), 10, 70, ALLEGRO_ALIGN_LEFT, text.c_str());
		break;
	case ROT_VELOCITY:
		text = ROT_VEL + to_string(mRotVelocity);
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 0, 0), 10, 90, ALLEGRO_ALIGN_LEFT, text.c_str());
		break;
	case REACTION_RADIUS:
		text = REACTION_RAD + to_string(mReactRadius);
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 0, 0), 10, 110, ALLEGRO_ALIGN_LEFT, text.c_str());
		break;
	}
}

void StateManager::addStat()
{
	std::string text;
	switch (mSelectedProperty)
	{
	case ALIGNMENT_WEIGHT:
		mAlignWeight += 5.0f;
		text = AL_WEIGHT + to_string(mAlignWeight);
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 0, 0), 10, 10, ALLEGRO_ALIGN_LEFT, text.c_str());
		break;
	case COHESION_WEIGHT:
		mCohWeight += 5.0f;
		text = COH_WEIGHT + to_string(mCohWeight);
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 0, 0), 10, 30, ALLEGRO_ALIGN_LEFT, text.c_str());
		break;
	case SEPARATION_WEIGHT:
		mSepWeight += 5.0f;
		text = SEP_WEIGHT + to_string(mSepWeight);
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 0, 0), 10, 50, ALLEGRO_ALIGN_LEFT, text.c_str());
		break;
	case MAX_VELOCITY:
		mMaxVelocity += 5.0f;
		gpGame->getUnitManager()->setMaxVelocities(mMaxVelocity);
		text = M_VELOCITY + to_string(mMaxVelocity);
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 0, 0), 10, 70, ALLEGRO_ALIGN_LEFT, text.c_str());
		break;
	case ROT_VELOCITY:
		mRotVelocity += 5.0f;
		gpGame->getUnitManager()->setRotationalVelocity(mRotVelocity);
		text = ROT_VEL + to_string(mRotVelocity);
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 0, 0), 10, 90, ALLEGRO_ALIGN_LEFT, text.c_str());
		break;
	case REACTION_RADIUS:
		mReactRadius += 5.0f;
		gpGame->getUnitManager()->setReactionRadius(mReactRadius);
		text = REACTION_RAD + to_string(mReactRadius);
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 0, 0), 10, 110, ALLEGRO_ALIGN_LEFT, text.c_str());
		break;
	}
}

void StateManager::subStat()
{
	std::string text;
	switch (mSelectedProperty)
	{
	case ALIGNMENT_WEIGHT:
		mAlignWeight -= 5.0f;
		text = AL_WEIGHT + to_string(mAlignWeight);
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 0, 0), 10, 10, ALLEGRO_ALIGN_LEFT, text.c_str());
		break;
	case COHESION_WEIGHT:
		mCohWeight -= 5.0f;
		text = COH_WEIGHT + to_string(mCohWeight);
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 0, 0), 10, 30, ALLEGRO_ALIGN_LEFT, text.c_str());
		break;
	case SEPARATION_WEIGHT:
		mSepWeight -= 5.0f;
		text = SEP_WEIGHT + to_string(mSepWeight);
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 0, 0), 10, 50, ALLEGRO_ALIGN_LEFT, text.c_str());
		break;
	case MAX_VELOCITY:
		mMaxVelocity -= 5.0f;
		gpGame->getUnitManager()->setMaxVelocities(mMaxVelocity);
		text = M_VELOCITY + to_string(mMaxVelocity);
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 0, 0), 10, 70, ALLEGRO_ALIGN_LEFT, text.c_str());
		break;
	case ROT_VELOCITY:
		mRotVelocity -= 5.0f;
		gpGame->getUnitManager()->setRotationalVelocity(mRotVelocity);
		text = ROT_VEL + to_string(mRotVelocity);
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 0, 0), 10, 90, ALLEGRO_ALIGN_LEFT, text.c_str());
		break;
	case REACTION_RADIUS:
		mReactRadius -= 5.0f;
		gpGame->getUnitManager()->setReactionRadius(mReactRadius);
		text = REACTION_RAD + to_string(mReactRadius);
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 0, 0), 10, 110, ALLEGRO_ALIGN_LEFT, text.c_str());
		break;
	}
}