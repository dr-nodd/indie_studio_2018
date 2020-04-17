/*
** EPITECH PROJECT, 2022
** OOP_indie_studio_2018
** File description:
** Menu
*/

#include "CharacterSelect.hpp"
#include "Game.hpp"
#include "Menu.hpp"

indie::Menu::Menu(indie::Resources &resources, indie::IScene *deleteIt)
    :   _isOptionsClicked(false), _resources(resources),
    _event(ACTIVE)
{
    int pos_background[4] = {0, 0, 1920, 1080};
    int pos_title[4] = {0, 0, 721, 583};

    delete deleteIt;
    if (_resources.getMusicEngine()) {
        _resources.stopMusicEngine();
    } else {
        _resources.setMusicEngine();
        _resources.setSoundEngine();
    }
    _resources.playMusic(PATH_MENU_MUSIC, true);
    _resources.addImage(PATH_MENU_BACKGROUND, pos_background);
    _resources.addImage(PATH_MENU_TITLE, pos_title);
    initTexts();
    _options = new indie::OptionsScene(_resources);
}

void indie::Menu::initTexts()
{
    int posNew[4] = {220, 320, 540, 480};
    int posLoad[4] = {220, 500, 540, 660};
    int posOptions[4] = {220, 680, 540, 840};
    int posExit[4] = {220, 860, 540, 1020};

    _resources.addText(L"New", posNew, true, PATH_MENU_FONT);
    _resources.addText(L"Load", posLoad, true, PATH_MENU_FONT);
    _resources.addText(L"Options", posOptions, true, PATH_MENU_FONT);
    _resources.addText(L"Exit", posExit, true, PATH_MENU_FONT);
}

indie::Menu::~Menu()
{
    destroyScene();
}

void indie::Menu::destroyScene()
{
    _resources.destroyImages();
    _resources.destroySliders();
    _resources.destroyRectangles();
    _resources.destroyTexts();
    delete _options;
}

indie::event indie::Menu::getEvent() const
{
    return _event;
}

indie::IScene *indie::Menu::update()
{
    if (_resources.isClicked(L"Options"))
        _isOptionsClicked = true;
    else if (_isOptionsClicked) {
        _options->display();
        _isOptionsClicked = false;
        return this;
    }
    if (_options->isActive()) {
        _options->display();
        return this;
    }
    if (_options->isQuit())
        initTexts();
    if (_resources.isClicked(L"New"))
        return new indie::CharacterSelect(_resources, this);
    if (_resources.isClicked(L"Load"))
        return new indie::Game(_resources, this);
    _event = _resources.getEventType();
    if (_resources.isClicked(L"Exit"))
        _event = QUIT;
    return this;
}

void indie::Menu::display()
{
    _resources.display();
}