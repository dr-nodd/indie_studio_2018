/*
** EPITECH PROJECT, 2022
** OOP_indie_studio_2018
** File description:
** Game Header
*/

#ifndef OOP_INDIE_STUDIO_2018_SAVE_HPP
#define OOP_INDIE_STUDIO_2018_SAVE_HPP

#include "Settings.hpp"

namespace indie {
    typedef struct {
        bool doExist;
        bool isPlayer;
        int x;
        int y;
        char texture[256];
    } characterSave;

    typedef struct {
        char data[MAP_HEIGHT];
    } mapSave;

    typedef struct {
        float cameraPos[3];
        characterSave character[4];
        mapSave map[MAP_WIDTH];
        char shader[256];
    } Save;
}
#endif //OOP_INDIE_STUDIO_2018_SAVE_HPP
