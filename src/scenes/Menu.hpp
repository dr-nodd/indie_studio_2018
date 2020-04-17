/*
** EPITECH PROJECT, 2022
** OOP_indie_studio_2018
** File description:
** Menu Header
*/

#ifndef OOP_INDIE_STUDIO_2018_MENU_HPP
#define OOP_INDIE_STUDIO_2018_MENU_HPP

#include "IScene.hpp"
#include "OptionsScene.hpp"

namespace indie {
    class Menu : public IScene {
    public:
        Menu(indie::Resources &, indie::IScene *deleteIt = nullptr);
        ~Menu();

        indie::event getEvent() const override;
        indie::IScene *update() override;
        void display() override;

    private:
        void destroyScene();
        void initTexts();

        bool _isOptionsClicked;
        indie::Resources &_resources;
        indie::event _event;
        indie::OptionsScene *_options;
    };
}
#endif //OOP_INDIE_STUDIO_2018_MENU_HPP
