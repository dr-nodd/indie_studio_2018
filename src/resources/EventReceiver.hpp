/*
** EPITECH PROJECT, 2022
** OOP_indie_studio_2018
** File description:
** EventReceiver Header
*/

#ifndef OOP_INDIE_STUDIO_2018_EVENTRECEIVER_HPP
#define OOP_INDIE_STUDIO_2018_EVENTRECEIVER_HPP

#include <irrlicht.h>

class EventReceiver : public irr::IEventReceiver {
public:
    typedef struct SMouseState_s {
        irr::core::position2di position;
        bool leftButtonDown;
    } mouseState_t;

    EventReceiver();
    virtual bool OnEvent(const irr::SEvent &event);
    virtual bool isKeyDown(irr::EKEY_CODE keyCode) const;
    const mouseState_t &getMouseState() const;

private:
    bool _keyIsDown[irr::KEY_KEY_CODES_COUNT];
    mouseState_t _mouseState;
};

#endif //OOP_INDIE_STUDIO_2018_EVENTRECEIVER_HPP
