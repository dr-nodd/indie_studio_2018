/*
** EPITECH PROJECT, 2022
** OOP_indie_studio_2018
** File description:
** EventReceiver
*/

#include <iostream>
#include "EventReceiver.hpp"

EventReceiver::EventReceiver()
    :   _keyIsDown()
{
    _mouseState.leftButtonDown = false;
    for (bool & i : _keyIsDown)
        i = false;
}

bool EventReceiver::OnEvent(const irr::SEvent &event)
{
    switch (event.EventType) {
    case irr::EET_MOUSE_INPUT_EVENT:
        switch(event.MouseInput.Event) {
        case irr::EMIE_LMOUSE_PRESSED_DOWN:
            _mouseState.leftButtonDown = true;
            break;
        case irr::EMIE_LMOUSE_LEFT_UP:
            _mouseState.leftButtonDown = false;
            break;
        case irr::EMIE_MOUSE_MOVED:
            _mouseState.position.X = event.MouseInput.X;
            _mouseState.position.Y = event.MouseInput.Y;
            break;
        default:
            break;
        }
        break;
    case irr::EET_KEY_INPUT_EVENT:
        _keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        break;
    default:
        break;
    }
    return false;
}

bool EventReceiver::isKeyDown(irr::EKEY_CODE keyCode) const
{
    return _keyIsDown[keyCode];
}

const EventReceiver::mouseState_t &EventReceiver::getMouseState() const
{
    return _mouseState;
}
