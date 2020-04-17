/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Main
*/

#include <iostream>
#include <exception>
#include <functional>

#include "Menu.hpp"
#include "Game.hpp"
#include "Settings.hpp"

int main(void)
{
    indie::Resources resources;
    indie::IScene *current_scene;

    try {
		current_scene = new indie::Menu(resources);
		while (current_scene->getEvent() != indie::QUIT && resources.getDevice()->run()) {
			current_scene = current_scene->update();
			current_scene->display();
		}
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
		return 84;
	}
    delete current_scene;
    return 0;
}