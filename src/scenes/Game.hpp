/*
** EPITECH PROJECT, 2022
** OOP_indie_studio_2018
** File description:
** Game Header
*/

#ifndef OOP_INDIE_STUDIO_2018_GAME_HPP
#define OOP_INDIE_STUDIO_2018_GAME_HPP

#include "Map.hpp"
#include "OptionsScene.hpp"
#include "Save.hpp"
#include "Player.hpp"

namespace indie {
    class Game : public IScene {
    public:
        Game(indie::Resources &resources, std::vector<std::pair<std::string, std::string>>, const std::string &path, indie::IScene *deleteIt = nullptr);
        Game(indie::Resources &resources, indie::IScene *deleteIt = nullptr);
        ~Game() override;

        indie::event getEvent() const override;

        indie::IScene *update() override;
        void display() override;

    private:
        void generate3DMap(bool loadMap = false);
        void createPlayers(std::vector<std::pair<std::string, std::string>> &players, std::vector<std::pair<int, int>> pos);
        bool loadSave();
        void destroyScene();
        void saveGame();
        void plantBomb(char id);
        bool checkVictory();
        void explode(Bomb *bomb);
        void createClouds();

        int _sizeOptions[4] = {0, 0, 50, 50};
        int _posOptions[2] = {1850, 20};
        int _prevTime;
        bool _isLeaving;
        bool _isOptionsClicked;
        indie::OptionsScene *_options;
        indie::Resources &_resources;
        indie::event _event;
        indie::Map _map;
        indie::Save _save;
        irr::ITimer *_timer;
        unsigned int _startDeflag;
        std::vector<Player *> _players;
        std::string _shader;
        std::vector<Bomb *> _bombs;
        int _idBomb;
    };
}
#endif //OOP_INDIE_STUDIO_2018_GAME_HPP
