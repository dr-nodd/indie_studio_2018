/*
** EPITECH PROJECT, 2022
** OOP_indie_studio_2018
** File description:
** Bomb Header
*/

#ifndef OOP_INDIE_STUDIO_2018_BOMB_HPP
#define OOP_INDIE_STUDIO_2018_BOMB_HPP

#include <tuple>
#include <vector>
#include "Map.hpp"
#include "Resources.hpp"

namespace indie {
    class Bomb {
    public:
        Bomb(std::pair<float, float> pos, indie::Resources &resources, int id, char idPlayer, char range);
        ~Bomb();

        std::tuple<float, float, float> getPos(void) const;
        char getRange() const;
        int getId() const;
        char getIdPlayer() const;
        bool isExploding() const;

        void setPos(float, float, float);
        void kick(int, int);
        void update(float timeMult, indie::Map &map);
        void explode();

    private:
        unsigned int _timePlant;
        std::tuple<float, float, float> _pos;
        indie::Resources &_resources;
        int _id;
        char _idPlayer;
        char _range;
        bool _exploding;
        std::pair<int, int> _kick;
    };
}

#endif //OOP_INDIE_STUDIO_2018_BOMB_HPP
