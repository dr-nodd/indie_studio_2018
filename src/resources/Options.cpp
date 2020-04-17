/*
** EPITECH PROJECT, 2022
** OOP_indie_studio_2018
** File description:
** Options Header
*/

#include "Resources.hpp"
#include "Options.hpp"

indie::Options::Options(Resources *resources)
    :   _resources(resources), _synchroVert(SYNCHROVERT),
    _fullscreen(FULLSCREEN), _soundVolume(100)
{
}

indie::Options::~Options()
{
}

void indie::Options::setSoundVolume(float soundVolume)
{
    if (soundVolume == _soundVolume)
        return;
    _resources->getMusicEngine()->setVolume(soundVolume * 100);
}

void indie::Options::changeSynchroVert(void)
{
    _synchroVert = !_synchroVert;
}

void indie::Options::changeFullscreen(void)
{
    _fullscreen = !_fullscreen;
}

bool indie::Options::getSynchroVert(void) const
{
    return _synchroVert;
}

bool indie::Options::getFullscreen(void) const
{
    return _fullscreen;
}

unsigned char indie::Options::getSoundVolume(void) const
{
    return _soundVolume;
}

void indie::Options::apply()
{
    _resources->restartDevice(_fullscreen, _synchroVert);
}
