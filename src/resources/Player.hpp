/*
** EPITECH PROJECT, 2022
** OOP_indie_studio_2018
** File description:
** Player Header
*/

#ifndef OOP_INDIE_STUDIO_2018_PLAYER_HPP
#define OOP_INDIE_STUDIO_2018_PLAYER_HPP

#include <vector>
#include "Bomb.hpp"

namespace indie {
    class Player {
    public:
        Player(bool isCPU, int pos_x, int pos_y, int pos_z, char id,
            indie::Resources &resources, std::string texture);
        ~Player();

        bool isPlayer() const;
        bool isAlive() const;
        bool isPlanting() const;
        char getId() const;
        char getNbBomb();
        bool getCanThrow();
        int getRangeBomb();
        std::string getTexture() const;
        irr::core::vector3df getPosition() const;
        irr::core::vector3df getRotation() const;

        void setPosition();
        void setRotation(int);
        void increase_range();
        void increase_bomb();
        void canThrow();
        void increase_speed();
        void die();

		virtual void update(float timeMult, std::vector<indie::Bomb *> &);
    protected:
		virtual void move(float timeMult, std::vector<indie::Bomb *> &);

        bool _isCPU;
        bool _isAlive;
        indie::Resources &_resources;
        char _id;
        int _rangeBomb;
        char _nbBomb;
        bool _canThrow;
        float _speed;
        bool _isPlanting;
        std::string _texture;
        bool _isRunning;
        bool _isIdle;
    };
}

#endif //OOP_INDIE_STUDIO_2018_PLAYER_HPP
