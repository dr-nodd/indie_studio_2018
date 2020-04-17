/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** Character Selection
*/

#include <unordered_map>
#include "CharacterSelect.hpp"
#include "StageSelect.hpp"
#include "Menu.hpp"

indie::CharacterSelect::CharacterSelect(indie::Resources &resources,
	indie::IScene *deleteIt) :
	_isLeaving(false), _resources(resources), _event(ACTIVE), _timer(_resources.getDevice()->getTimer()->getRealTime())
{
	int pos_background[4] = {0, 0, 1920, 1080};
	int pos_arrow[4] = {0, 0, 90, 68};

	delete deleteIt;
	//_resources.shaderInject();
	_resources.addImage(PATH_CHARACTER_SELECT_BACKGROUND, pos_background);
	for (int i = 0; i < 4; i++) {
		_resources.addImage(PATH_CHARACTER_SELECT_ARROW, pos_arrow,
		std::make_pair(370 + 482 * i, 835), "arrow" + std::to_string(i));
		_resources.addImage(PATH_CHARACTER_SELECT_LEFT_ARROW, pos_arrow,
		std::make_pair(20 + 482 * i, 835), "arrow" + std::to_string(i));
		_resources.addImage(PATH_CHARACTER_SELECT_ARROW, pos_arrow,
			std::make_pair(370 + 482 * i, 165), "color" + std::to_string(i));
		_resources.addImage(PATH_CHARACTER_SELECT_LEFT_ARROW, pos_arrow,
			std::make_pair(20 + 482 * i, 165), "color" + std::to_string(i));
	}
	_resources.addCamera();
	_resources.setCameraPos(0, 0, 0);
	_resources.createMenuCharacter(-20, -5, 22, PATH_BOMBER_FLOSS, PATH_BOMBER_TEX, 0);
	_resources.createMenuCharacter(-7, -5, 22, PATH_BOMBER_FLOSS, PATH_BOMBER_TEX_PINK, 1);
	_resources.createMenuCharacter(7, -5, 22, PATH_BOMBER_FLOSS, PATH_BOMBER_TEX_BLUE, 2);
	_resources.createMenuCharacter(20, -5, 22, PATH_BOMBER_FLOSS, PATH_BOMBER_TEX_YELLOW, 3);
	initTexts();
}

indie::CharacterSelect::~CharacterSelect()
{
	destroyScene();
}

void indie::CharacterSelect::initTexts()
{
	int posStart[4] = {605, 940, 825, 1080};
	int posExit[4] = {1080, 940, 1300, 1080};
	int posOut[4] = {2300, 2300, 2500, 2500};

	_resources.addText(L"Play", posStart, true, PATH_MENU_FONT);
	_resources.addText(L"Back", posExit, true, PATH_MENU_FONT);
	for (int i = 0; i < 4; i++) {
		int val = 482 * i;
		int posColor[4] = {190 + val, 150, 290 + val, 250};
		int posPlayer[4] = {190 + val, 820, 290 + val, 920};
		if (i < 2) {
			_resources.addText(L"Player", posPlayer, false, PATH_MENU_FONT,
				"Player" + std::to_string(i));
			_resources.addText(L"CPU", posOut, false, PATH_MENU_FONT,
				"CPU" + std::to_string(i));
		}
		if (i >= 2) {
			_resources.addText(L"CPU", posPlayer, false, PATH_MENU_FONT,
				"CPU" + std::to_string(i));
			_resources.addText(L"NONE", posOut, false, PATH_MENU_FONT,
				"NONE" + std::to_string(i));
		}
		_resources.addText(L"Color", posColor, false, PATH_MENU_FONT, "Color"
		+ std::to_string(i));
	}
}

void indie::CharacterSelect::destroyScene()
{
	_resources.destroyImages();
	_resources.destroyModels();
	_resources.destroyTexts();
}

indie::event indie::CharacterSelect::getEvent() const
{
	return _event;
}

void indie::CharacterSelect::moveText(const std::string &posid, std::vector<std::pair<const wchar_t *, std::string>> select)
{
	static int i = 0;
	int val = std::stoi(posid) * 482;
	int posOut[4] = {2300, 2300, 2500, 2500};
	int posIn[4] = {190 + val, 820, 290 + val, 920};

	if (i == 1) {
		_resources.setTextPosition(select[i - 1].first, posIn,
			select[i - 1].second + posid);
		_resources.setTextPosition(select[i].first, posOut,
			select[i].second + posid);
		i = 0;
	} else {
		_resources.setTextPosition(select[i + 1].first, posIn,
			select[i + 1].second + posid);
		_resources.setTextPosition(select[i].first, posOut,
			select[i].second + posid);
		i++;
	}
}

void indie::CharacterSelect::managePlayer(const std::vector<std::string> &id)
{
	std::vector<std::pair<const wchar_t *, std::string>> select = {{L"Player", "Player"}, {L"CPU", "CPU"}};
	std::vector<std::pair<const wchar_t *, std::string>> select_all = {{L"CPU", "CPU"}, {L"NONE", "NONE"}};
	for (const auto &it : id) {
		if (it.compare(0, 5, "arrow", 0, 5) == 0 && _resources.isClicked(PATH_CHARACTER_SELECT_ARROW, true, it) && _resources.getDevice()->getTimer()->getRealTime() > _timer + 300) {
			const std::string posid = it.substr(5);
			if (std::stoi(posid) < 2) {
				moveText(posid, select);
				_timer = _resources.getDevice()->getTimer()->getRealTime();
				break;
			} else {
				moveText(posid, select_all);
				_timer = _resources.getDevice()->getTimer()->getRealTime();
				break;
			}
		} else if (it.compare(0, 5, "arrow", 0, 5) == 0 && _resources.isClicked(PATH_CHARACTER_SELECT_LEFT_ARROW, true, it) && _resources.getDevice()->getTimer()->getRealTime() > _timer + 300) {
			const std::string posid = it.substr(5);
			if (std::stoi(posid) < 2) {
				moveText(posid, select);
				_timer = _resources.getDevice()->getTimer()->getRealTime();
				break;
			} else {
				moveText(posid, select_all);
				_timer = _resources.getDevice()->getTimer()->getRealTime();
				break;
			}
		}
	}
}

void indie::CharacterSelect::manageTexture(const std::vector<std::string> &id)
{
	for (const auto &it : id) {
		if (it.compare(0, 5, "color", 0, 5) == 0 &&
			_resources.isClicked(PATH_CHARACTER_SELECT_ARROW, true, it) &&
			_resources.getDevice()->getTimer()->getRealTime() > _timer + 300) {
			int posid = std::stoi(it.substr(5));
			_resources.changeMenuCharacter(
				_resources.getTextureFromId(posid), posid, true);
			_timer = _resources.getDevice()->getTimer()->getRealTime();
		} else if (it.compare(0, 5, "color", 0, 5) == 0 &&
			_resources.isClicked(PATH_CHARACTER_SELECT_LEFT_ARROW, true, it) &&
			_resources.getDevice()->getTimer()->getRealTime() > _timer + 300) {
			int posid = std::stoi(it.substr(5));
			_resources.changeMenuCharacter(
				_resources.getTextureFromId(posid), posid, false);
			_timer = _resources.getDevice()->getTimer()->getRealTime();
		}
	}
}

indie::IScene *indie::CharacterSelect::update()
{
	_resources.setModelsRotation(-1);
	if (_resources.isClicked(L"Play")) {
		std::vector<std::pair<std::string, std::string>> players;
		std::vector<std::vector<std::string>> ids = {{"Player0", "CPU0"}, {"Player1", "CPU1"}, {"CPU2", "NONE2"}, {"CPU3", "NONE3"}};
			for (int i = 0; i < 4; i++) {
				std::string str;
				for (auto &it : ids.at(i)) {
					if (!_resources.getTextFromId(it).empty()) {
						for (auto c : _resources.getTextFromId(it)) {
							if (c)
								str += c;
						}
					}
				}
				players.emplace_back(std::make_pair(str,
					_resources.getTextureFromId(i)));
			}
		return new indie::StageSelect(_resources, players, this);
	}
	_event = _resources.getEventType();
	if (_resources.isClicked(L"Back"))
		return new indie::Menu(_resources, this);
	managePlayer(_resources.getImageId());
	manageTexture(_resources.getImageId());
	if (_event == QUIT) {
		_isLeaving = true;
		_event = ACTIVE;
	} else if (_isLeaving) {
		_isLeaving = false;
		return new indie::Menu(_resources, this);
	}
	return this;
}

void indie::CharacterSelect::display()
{
	_resources.display();
}