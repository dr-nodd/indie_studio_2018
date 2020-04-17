/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** Victory screen
*/

#include "Menu.hpp"
#include "Victory.hpp"


indie::Victory::Victory(indie::Resources &resources, std::pair<std::string,
	std::string> winner, indie::IScene *deleteIt) : _resources(resources),
	_event(ACTIVE), _isLeaving(false), _winner(winner)
{
	int pos_victory[4] = {0, 0, 1920, 1080};

	delete deleteIt;
	_resources.addImage(PATH_GAME_VICTORY, pos_victory, std::make_pair(0, 0));
	_resources.playMusic(PATH_GAME_VICTORY_MUSIC, false);
	initTexts();
	_resources.addCamera();
	_resources.setCameraPos(0, 0, 0);
	_resources.createMenuCharacter(0, -5, 20, PATH_BOMBER_DAB, _winner.second.c_str(), '1');

//	it->setRotation(1);
}

indie::Victory::~Victory()
{
	destroyScene();
}

void indie::Victory::initTexts()
{
	int posExit[4] = {800, 760, 1120, 920};
	int posQuit[4] = {800, 920, 1120, 1080};
	int posPlayer[4] = {1400, 500, 1600, 600};

	std::string txt = _winner.first + " WINS!";
	std::wstring str = std::wstring(txt.begin(), txt.end());
	const wchar_t *winner = str.c_str();
	_resources.addText(L"TO MENU", posExit, true, PATH_MENU_FONT);
	_resources.addText(L"QUIT", posQuit, true, PATH_MENU_FONT);
	_resources.addText(winner, posPlayer, false, PATH_MENU_FONT);
}


indie::event indie::Victory::getEvent() const
{
	return _event;
}

void indie::Victory::destroyScene()
{
	_resources.destroyImages();
	_resources.destroyTexts();
	_resources.destroyRectangles();
	_resources.destroyModels();
}

indie::IScene *indie::Victory::update()
{
	_event = _resources.getEventType();
	if (_event == QUIT) {
		_isLeaving = true;
		_event = ACTIVE;
	} else if (_isLeaving) {
		_isLeaving = false;
		return new indie::Menu(_resources, this);
	}
	if (_resources.isClicked(L"TO MENU"))
		return new indie::Menu(_resources, this);
	else if (_resources.isClicked(L"QUIT"))
		_event = QUIT;
	return this;
}

void indie::Victory::display()
{
	_resources.display();
}