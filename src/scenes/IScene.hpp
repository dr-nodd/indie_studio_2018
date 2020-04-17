/*
** EPITECH PROJECT, 2022
** OOP_indie_studio_2018
** File description:
** Interface for scenes
*/

#ifndef OOP_INDIE_STUDIO_2018_ISCENE_HPP
#define OOP_INDIE_STUDIO_2018_ISCENE_HPP

#include "Resources.hpp"
#include "Settings.hpp"

namespace indie {
    class IScene {
    public:
        virtual ~IScene() = default;

        virtual indie::event getEvent() const = 0;
        virtual IScene *update() = 0;
        virtual void display() = 0;
    };
}

#endif //OOP_INDIE_STUDIO_2018_ISCENE_HPP
