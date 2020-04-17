/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** Stage select
*/

#include "CharacterSelect.hpp"
#include "Game.hpp"
#include "StageSelect.hpp"

indie::StageSelect::StageSelect(indie::Resources &resources,
	std::vector<std::pair<std::string, std::string>> players, indie::IScene *deleteIt) :
	_resources(resources), _event(ACTIVE), _isLeaving(false), _players(players)
{
	int pos_background[4] = {0, 0, 1920, 1080};

	delete deleteIt;
	_resources.addImage(PATH_STAGE_SELECT_BACKGROUND, pos_background, std::make_pair(0, 0));
	initTexts();

}

indie::StageSelect::~StageSelect()
{
	destroyScene();
}

void indie::StageSelect::initTexts()
{
	int posExit[4] = {855, 760, 1040, 920};
	int posQuit[4] = {855, 920, 1040, 1080};
	int posRetro[4] = {160, 500, 490, 620};
	int posClassic[4] = {775, 500, 1120, 620};
	int posDark[4] = {1450, 500, 1770, 620};

	_resources.addText(L"RETRO", posRetro, true, PATH_MENU_FONT);
	_resources.addText(L"CLASSIC", posClassic, true, PATH_MENU_FONT);
	_resources.addText(L"DARK", posDark, true, PATH_MENU_FONT);
	_resources.addText(L"BACK", posExit, true, PATH_MENU_FONT);
	_resources.addText(L"QUIT", posQuit, true, PATH_MENU_FONT);
}


indie::event indie::StageSelect::getEvent() const
{
	return _event;
}

void indie::StageSelect::destroyScene()
{
	_resources.destroyImages();
	_resources.destroyTexts();
	_resources.destroyRectangles();
}

indie::IScene *indie::StageSelect::update()
{
	_event = _resources.getEventType();
	if (_event == QUIT) {
		_isLeaving = true;
		_event = ACTIVE;
	} else if (_isLeaving) {
		_isLeaving = false;
		return new indie::CharacterSelect(_resources, this);
	}
	if (_resources.isClicked(L"CLASSIC"))
		return new indie::Game(_resources, _players, PATH_SHADER_REALISTIC, this);
	else if (_resources.isClicked(L"RETRO"))
		return new indie::Game(_resources, _players, PATH_SHADER_RETRO, this);
	else if (_resources.isClicked(L"DARK"))
		return new indie::Game(_resources, _players, PATH_SHADER_DARK, this);
	else if (_resources.isClicked(L"BACK"))
		return new indie::CharacterSelect(_resources, this);
	else if (_resources.isClicked(L"QUIT"))
		_event = QUIT;
	return this;
}

void indie::StageSelect::display()
{
	_resources.display();
}