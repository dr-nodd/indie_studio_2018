/*
** EPITECH PROJECT, 2022
** OOP_indie_studio_2018
** File description:
** Game
*/

#include <fstream>
#include <string.h>
#include "Game.hpp"
#include "CPU.hpp"
#include "Map.hpp"
#include "Menu.hpp"
#include "Victory.hpp"

/* New game constructor */
indie::Game::Game(indie::Resources &resources,
	std::vector<std::pair<std::string, std::string>> players,
	const std::string &shader, indie::IScene *deleteIt)
    :   _prevTime(0), _isLeaving(false), _isOptionsClicked(false),
    _resources(resources), _event(ACTIVE), _map(indie::Map(MAP_HEIGHT, MAP_WIDTH)),
    _timer(_resources.getDevice()->getTimer()), _startDeflag(0), _players(std::vector<Player *>()),
    _shader(shader), _bombs(std::vector<Bomb *>()), _idBomb(0)
{
    _resources.getDevice()->getTimer()->setSpeed(1);
    srand((unsigned long)&_isLeaving);
    delete deleteIt;
    memset(&_save, 0, sizeof(indie::Save));
    _resources.playMusic(PATH_GAME_MUSIC, true);
    _resources.addCamera();
    _resources.setCameraPos(0, -55, -65);
    _resources.shaderInject(_shader);
    generate3DMap();
    _resources.addImage(PATH_GAME_OPTIONS, _sizeOptions, std::pair<int, int> (_posOptions[0], _posOptions[1]));
    _options = new indie::OptionsScene(_resources);
    std::vector<std::pair<int, int>> pos = {{-100, 60}, {90, 60}, {-100, -70}, {90, -70}};
    createPlayers(players, pos);
    createClouds();
}

/* Load game constructor */
indie::Game::Game(indie::Resources &resources, indie::IScene *deleteIt)
    :   _prevTime(0), _isLeaving(false), _isOptionsClicked(false),
    _resources(resources), _event(ACTIVE), _map(indie::Map(MAP_HEIGHT, MAP_WIDTH)),
    _timer(_resources.getDevice()->getTimer()), _startDeflag(0), _players(std::vector<Player *>()),
    _bombs(std::vector<Bomb *>()), _idBomb(0)
{
    _resources.getDevice()->getTimer()->setSpeed(1);
    srand((unsigned long)&_isLeaving);
    delete deleteIt;
    memset(&_save, 0, sizeof(indie::Save));
    if (!loadSave())
        throw std::runtime_error("invalid save file");
    _resources.playMusic(PATH_GAME_MUSIC, true);
    _resources.addCamera();
    _resources.setCameraPos(
        int(_save.cameraPos[0]),
        int(_save.cameraPos[1]),
        int(_save.cameraPos[2])
    );
    _shader = std::string(_save.shader);
    _resources.shaderInject(_shader);
    generate3DMap(true);
    _resources.addImage(PATH_GAME_OPTIONS, _sizeOptions, std::pair<int, int> (_posOptions[0], _posOptions[1]));
    _options = new indie::OptionsScene(_resources);
    std::vector<std::pair<std::string, std::string>> players;
    std::vector<std::pair<int, int>> pos;
    for (int i = 0; i < 4; i++) {
        if (_save.character[i].doExist) {
            players.push_back(std::pair<std::string, std::string>(
                _save.character[i].isPlayer ? "Player" : "CPU",
                _save.character[i].texture
            ));
            pos.push_back(std::pair<int, int>(
                _save.character[i].x,
                _save.character[i].y
            ));
        }
    }
    createPlayers(players, pos);
    createClouds();
}

void indie::Game::generate3DMap(bool loadMap)
{
    std::vector<std::string> tmp;

    if (loadMap) {
        for (int i = 0; i < MAP_WIDTH; i++)
            tmp.push_back(std::string(_save.map[i].data, MAP_HEIGHT));
        _map.setMap(tmp);
    } else {
        tmp = _map.getMap();
    }
    for (long unsigned int i = 0; i < tmp.size(); i++) {
        for (long unsigned int j = 0; j < tmp.at(i).size(); j++) {
            if (tmp.at(i).at(j) == 'X') {
                _resources.addCube((-(tmp.size() / 2) + i) * 10, (-(tmp.at(i).size() / 2) + j) * 10, POS_Z - 5, PATH_WALL_TEX, PATH_WALL_MODEL, std::pair<int, int>(i, j));
            }
            else if (tmp.at(i).at(j) == '*') {
                _resources.addCube((-(tmp.size() / 2) + i) * 10, (-(tmp.at(i).size() / 2) + j) * 10, POS_Z - 5, PATH_DESTRUCT_WALL_TEX, PATH_DESTRUCT_WALL_MODEL, std::pair<int, int>(i, j));
            }
            _resources.addCube((-(tmp.size() / 2) + i) * 10, (-(tmp.at(i).size() / 2) + j) * 10, POS_Z + 5, PATH_GROUND_TEX, PATH_GROUND_MODEL, std::pair<int, int>(i, j));
        }
    }
}


void indie::Game::createPlayers(std::vector<std::pair<std::string, std::string>> &players, std::vector<std::pair<int, int>> pos)
{
    int i = 0;

    for (auto &it : players) {
        if (it.first == "Player")
            _players.push_back(new Player(false, pos.at(i).first, pos.at(i).second, POS_Z, i, _resources, it.second.c_str()));
        else if (it.first == "CPU")
            _players.push_back(new CPU(true, pos.at(i).first, pos.at(i).second, POS_Z, i, _resources, it.second.c_str()));
        i++;
    }
}

void indie::Game::createClouds()
{
    std::srand(std::time(nullptr));
    int y_rand = 0;
    int x_rand = 0;

    for (int nb_cloud = 0; nb_cloud < 10; nb_cloud++) {
        y_rand = std::rand() % 260;
        if (y_rand > 180)
            y_rand = (260 - y_rand) * -1;
        x_rand = std::rand() % 400;
        if (x_rand > 200)
            x_rand = (400 - x_rand) * -1;
        _resources.addCloud(x_rand, y_rand, 70, PATH_CLOUD, PATH_CLOUD_TEX);
    }
}

bool indie::Game::loadSave()
{
    std::ifstream saveFile(PATH_SAVE, std::ios::binary);
    if (!saveFile.good())
        return false;
    saveFile.read((char *)&_save, sizeof(indie::Save));
    saveFile.close();
    return true;
}

indie::Game::~Game()
{
    saveGame();
    destroyScene();
    delete _options;
    for (auto &bomb : _bombs)
        delete bomb;
    _bombs.erase(_bombs.begin(), _bombs.end());
    for (auto &player : _players)
        delete player;
    _players.erase(_players.begin(), _players.end());
    _resources.destroyClouds();
}

void indie::Game::destroyScene()
{
    _resources.destroyTexts();
    _resources.destroyImages();
    _resources.destroyRectangles();
    _resources.destroyModels();
    _resources.destroySliders();
}

void indie::Game::saveGame()
{
    /* Save camera */
    irr::core::vector3df cameraPos = _resources.getCamera()->getPosition();
    _save.cameraPos[0] = cameraPos.X;
    _save.cameraPos[1] = cameraPos.Y;
    _save.cameraPos[2] = cameraPos.Z;

    /* Save players */
    for (int i = 0; i < 4; i++) {
        if (static_cast<long unsigned int>(i) < _players.size()) {
            _save.character[i].doExist = _players.at(i)->isAlive();
            _save.character[i].isPlayer = _players.at(i)->isPlayer();
            _save.character[i].x = int(_players.at(i)->getPosition().X);
            _save.character[i].y = int(_players.at(i)->getPosition().Y);
            strcpy(_save.character[i].texture, _players.at(i)->getTexture().c_str());
        } else {
            _save.character[i].doExist = false;
        }
    }

    /* Save map */
    std::vector<std::string> map = _map.getMap();
    for (int i = 0; i < MAP_WIDTH; i++)
        strncpy(_save.map[i].data, map.at(i).c_str(), MAP_HEIGHT);

    /* Save shader */
    strcpy(_save.shader, _shader.c_str());

    /* Write the structure in the file */
    std::ofstream saveFile(PATH_SAVE, std::ios::binary);
    saveFile.write((char *)&_save, sizeof(indie::Save));
    saveFile.close();
}

indie::event indie::Game::getEvent() const
{
    return _event;
}

indie::IScene *indie::Game::update()
{
    _event = _resources.getEventType();
    if (_event == QUIT) {
        _isLeaving = true;
        _event = ACTIVE;
    } else if (_isLeaving) {
        _isLeaving = false;
        return new indie::Menu(_resources, this);
    }
    if (_resources.isClicked(PATH_GAME_OPTIONS, true))
        _isOptionsClicked = true;
    else if (_isOptionsClicked) {
        _options->display();
        _isOptionsClicked = false;
    }
    if (_options->isActive())
        _options->display();
    int currentTime = _timer->getTime();
    auto timeMult = static_cast<float>(float(currentTime - _prevTime) / 20.0 * TIME_MULT);
    _prevTime = currentTime;
    for (auto &player : _players) {
        for (auto &power_up : _resources.getPowerUps())
            if (player->getPosition().X + 5 > power_up->mesh->getPosition().X &&
                player->getPosition().X - 5 < power_up->mesh->getPosition().X &&
                player->getPosition().Y + 5 > power_up->mesh->getPosition().Y &&
                player->getPosition().Y - 5 < power_up->mesh->getPosition().Y &&
                player->getPosition().Z < power_up->mesh->getPosition().Z + 15 &&
                player->getPosition().Z > power_up->mesh->getPosition().Z - 10) {
                if (power_up->path == PATH_BOMB_UP_MODEL)
                    player->increase_bomb();
                else if (power_up->path == PATH_FIRE_MODEL)
                    player->increase_range();
                else if (power_up->path == PATH_KICK_MODEL)
                    player->canThrow();
                else if (power_up->path == PATH_SKATE_MODEL)
                    player->increase_speed();
                power_up->mesh->setPosition(irr::core::vector3df(power_up->mesh->getPosition().X, power_up->mesh->getPosition().Y, 100));
            }
        player->update(timeMult, _bombs);
        if (player->isPlanting())
            plantBomb(player->getId());
    }
    if (checkVictory()) {
    	std::pair<std::string, std::string> winner;
    	for (auto const &it : _players) {
			if (it->isAlive()) {
				if (it->isPlayer()) {
					std::string str = "Player " + std::to_string(static_cast<int>(it->getId() + 1));
					winner = std::make_pair(str, it->getTexture());
				} else {
					std::string str = "CPU" + std::to_string(static_cast<int>(it->getId() + 1));
					winner = std::make_pair(str, it->getTexture());
				}
			}
		}
		return new indie::Victory(_resources, winner, this);
	}
    _resources.setPowerUPsRotation(timeMult);
    for (auto &bomb : _bombs) {
		bomb->update(timeMult, _map);
        if (bomb->isExploding()) {
        	_resources.playSound(PATH_GAME_BOMB_SFX, false);
			explode(bomb);
		}
    }
    if (_startDeflag != 0 && _timer->getRealTime() - _startDeflag > 500) {
        _startDeflag = 0;
        for (auto &deflag : _resources.getPowerUps())
            if (deflag->path == PATH_FIRE_DEFLAG_MODEL)
                deflag->mesh->setPosition(
                    irr::core::vector3df(deflag->mesh->getPosition().X, deflag->mesh->getPosition().Y, -100.0));
    }
    _resources.moveClouds();
    return this;
}

void indie::Game::plantBomb(char id)
{
    char nb_bomb = 0;

    for (auto &bomb : _bombs) {
        if (std::get<0>(bomb->getPos()) == round(_resources.getModel(id)->getPosition().X / 10) * 10 &&
            std::get<1>(bomb->getPos()) == round(_resources.getModel(id)->getPosition().Y / 10) * 10 &&
            std::get<2>(bomb->getPos()) - 10 < _resources.getModel(id)->getPosition().Z &&
            std::get<2>(bomb->getPos()) + 15 > _resources.getModel(id)->getPosition().Z)
            return;
        if (bomb->getIdPlayer() == id)
            nb_bomb++;
    }
    if (nb_bomb >= _players[id]->getNbBomb())
        return;
    _idBomb += 1;
    auto bomb = new Bomb(std::pair<float, float>(
        round(_resources.getModel(id)->getPosition().X / 10) * 10,
        round(_resources.getModel(id)->getPosition().Y / 10) * 10),
        _resources, _idBomb, id, _players[id]->getRangeBomb());
    _bombs.push_back(bomb);
}

bool indie::Game::checkVictory()
{
    int i = 0;

	for (const auto &it : _players) {
		if (it->isAlive())
			i++;
	}
	return i == 1;
}

void indie::Game::explode(Bomb *bomb)
{
    for (auto &bomb_recursive : _bombs)
        if (bomb != bomb_recursive && ((std::get<0>(bomb->getPos()) - 5 - 10 * bomb->getRange() < std::get<0>(bomb_recursive->getPos()) &&
            std::get<0>(bomb->getPos()) + 5 + 10 * bomb->getRange() > std::get<0>(bomb_recursive->getPos()) &&
            std::get<1>(bomb->getPos()) == std::get<1>(bomb_recursive->getPos())) ||
            (std::get<1>(bomb->getPos()) - 5 - 10 * bomb->getRange() < std::get<1>(bomb_recursive->getPos()) &&
                std::get<1>(bomb->getPos()) + 5 + 10 * bomb->getRange() > std::get<1>(bomb_recursive->getPos()) &&
                std::get<0>(bomb->getPos()) == std::get<0>(bomb_recursive->getPos())))) {
            bomb_recursive->explode();
            break;
        }
    for (auto &player : _players)
        if (!(EZ_GAME && _players[0] == player) &&
            (((std::get<0>(bomb->getPos()) - 5 - 10 * bomb->getRange() < player->getPosition().X &&
                std::get<0>(bomb->getPos()) + 5 + 10 * bomb->getRange() > player->getPosition().X &&
                std::get<1>(bomb->getPos()) - 5 <= player->getPosition().Y &&
                std::get<1>(bomb->getPos()) + 5 >= player->getPosition().Y) ||
                (std::get<1>(bomb->getPos()) - 5 - 10 * bomb->getRange() < player->getPosition().Y &&
                    std::get<1>(bomb->getPos()) + 5 + 10 * bomb->getRange() > player->getPosition().Y &&
                    std::get<0>(bomb->getPos()) - 5 <= player->getPosition().X &&
                    std::get<0>(bomb->getPos()) + 5 >= player->getPosition().X)) && POS_Z - 10 < player->getPosition().Z &&
                POS_Z + 50 > player->getPosition().Z)) {
            _resources.playSound(PATH_GAME_DEATH_SFX, false);
            player->die();
        }
	std::vector<std::string> map = _map.getMap();
    for (auto &power_up : _resources.getPowerUps())
        if ((std::get<0>(bomb->getPos()) - 5 - 10 * bomb->getRange() < power_up->mesh->getPosition().X &&
            std::get<0>(bomb->getPos()) + 5 + 10 * bomb->getRange() > power_up->mesh->getPosition().X &&
            std::get<1>(bomb->getPos()) == power_up->mesh->getPosition().Y) ||
            (std::get<1>(bomb->getPos()) - 5 - 10 * bomb->getRange() < power_up->mesh->getPosition().Y &&
                std::get<1>(bomb->getPos()) + 5 + 10 * bomb->getRange() > power_up->mesh->getPosition().Y &&
                std::get<0>(bomb->getPos()) == power_up->mesh->getPosition().X))
            power_up->mesh->setPosition(irr::core::vector3df(power_up->mesh->getPosition().X, power_up->mesh->getPosition().Y, 100));
    for (auto &cube : _resources.getCubes()) {
        irr::core::vector3df cubePos = cube->mesh->getPosition();
        if (cube->path == PATH_DESTRUCT_WALL_MODEL &&
            ((std::get<0>(bomb->getPos()) - 5 - 10 * bomb->getRange() < cubePos.X &&
            std::get<0>(bomb->getPos()) + 5 + 10 * bomb->getRange() > cubePos.X &&
            std::get<1>(bomb->getPos()) == cubePos.Y) ||
            (std::get<1>(bomb->getPos()) - 5 - 10 * bomb->getRange() < cubePos.Y &&
            std::get<1>(bomb->getPos()) + 5 + 10 * bomb->getRange() > cubePos.Y &&
            std::get<0>(bomb->getPos()) == cubePos.X))) {
            if ((rand() % CHANCE_POWER_UPS - 1) == 0) {
                int luck = rand() % 4;
                switch (luck) {
                case 0:
                    _resources.addPowerUp(cubePos.X, cubePos.Y, cubePos.Z + 5, std::string(PATH_BOMB_UP_MODEL), PATH_BOMB_UP_TEX);
                    break;
                case 1:
                    _resources.addPowerUp(cubePos.X, cubePos.Y, cubePos.Z + 5, std::string(PATH_FIRE_MODEL), PATH_FIRE_TEX);
                    break;
                case 2:
                    _resources.addPowerUp(cubePos.X, cubePos.Y, cubePos.Z + 5, std::string(PATH_KICK_MODEL), PATH_KICK_TEX);
                    break;
                case 3:
                    _resources.addPowerUp(cubePos.X, cubePos.Y, cubePos.Z + 5, std::string(PATH_SKATE_MODEL), PATH_SKATE_TEX);
                    break;
                default:
                    break;
                }
            }
            cubePos.Z = -100.f;
            cube->mesh->setPosition(cubePos);
            std::pair<int, int> cubeRawPos = cube->rawPos;
            if (cubeRawPos.first != -1 && cubeRawPos.second != -1)
                map.at(cubeRawPos.first).at(cubeRawPos.second) = '0';
        }
    }
    _map.setMap(map);
	_resources.addPowerUp(std::get<0>(bomb->getPos()), std::get<1>(bomb->getPos()), std::get<2>(bomb->getPos()), PATH_FIRE_DEFLAG_MODEL, PATH_FIRE_DEFLAG_TEX);
    bool stop = false;

    for (unsigned int i = 1; i < bomb->getRange() + 1; i++) {
        for (auto &cube : _resources.getCubes()) {
            if ((cube->path == PATH_WALL_MODEL &&
                std::get<0>(bomb->getPos()) + 10 * i == cube->mesh->getPosition().X &&
                std::get<1>(bomb->getPos()) == cube->mesh->getPosition().Y &&
                std::get<2>(bomb->getPos()) - 5 == cube->mesh->getPosition().Z) || std::get<0>(bomb->getPos()) >= 50) {
                stop = true;
            }
        }
        if (!stop)
            _resources.addPowerUp(std::get<0>(bomb->getPos()) + 10 * i, std::get<1>(bomb->getPos()),
            std::get<2>(bomb->getPos()), PATH_FIRE_DEFLAG_MODEL, PATH_FIRE_DEFLAG_TEX);
        stop = false;
        for (auto &cube : _resources.getCubes()) {
            if ((cube->path == PATH_WALL_MODEL &&
                std::get<0>(bomb->getPos()) - 10 * i == cube->mesh->getPosition().X &&
                std::get<1>(bomb->getPos()) == cube->mesh->getPosition().Y &&
                std::get<2>(bomb->getPos()) - 5 == cube->mesh->getPosition().Z) || std::get<0>(bomb->getPos()) <= -50) {
                stop = true;
            }
        }
        if (!stop)
            _resources.addPowerUp(std::get<0>(bomb->getPos()) - 10 * i, std::get<1>(bomb->getPos()),
                std::get<2>(bomb->getPos()), PATH_FIRE_DEFLAG_MODEL, PATH_FIRE_DEFLAG_TEX);
        stop = false;
        for (auto &cube : _resources.getCubes()) {
            if ((cube->path == PATH_WALL_MODEL &&
                std::get<0>(bomb->getPos()) == cube->mesh->getPosition().X &&
                std::get<1>(bomb->getPos()) - 10 * i == cube->mesh->getPosition().Y &&
                std::get<2>(bomb->getPos()) - 5 == cube->mesh->getPosition().Z) || std::get<1>(bomb->getPos()) <= -50) {
                stop = true;
            }
        }
        if (!stop)
            _resources.addPowerUp(std::get<0>(bomb->getPos()), std::get<1>(bomb->getPos()) - 10 * i,
                std::get<2>(bomb->getPos()), PATH_FIRE_DEFLAG_MODEL, PATH_FIRE_DEFLAG_TEX);
        stop = false;
        for (auto &cube : _resources.getCubes()) {
            if ((cube->path == PATH_WALL_MODEL &&
                std::get<0>(bomb->getPos()) == cube->mesh->getPosition().X &&
                std::get<1>(bomb->getPos()) + 10 * i == cube->mesh->getPosition().Y &&
                std::get<2>(bomb->getPos()) - 5 == cube->mesh->getPosition().Z) || std::get<1>(bomb->getPos()) >= 50) {
                stop = true;
            }
        }
        if (!stop)
            _resources.addPowerUp(std::get<0>(bomb->getPos()), std::get<1>(bomb->getPos()) + 10 * i,
                std::get<2>(bomb->getPos()), PATH_FIRE_DEFLAG_MODEL, PATH_FIRE_DEFLAG_TEX);
        stop = false;
    }
	_startDeflag = _resources.getDevice()->getTimer()->getRealTime();
	if (_resources.getModelBomb(bomb->getId()) != nullptr) {
        _resources.getModelBomb(bomb->getId())->setPosition(
            irr::core::vector3df(std::get<0>(bomb->getPos()), std::get<1>(bomb->getPos()), -100));
        bomb->setPos(std::get<0>(bomb->getPos()), std::get<1>(bomb->getPos()), -100);
        int index = 0;
        for (auto &bombDel : _bombs) {
            if (std::get<0>(bomb->getPos()) == std::get<0>(bombDel->getPos()) &&
                std::get<1>(bomb->getPos()) == std::get<1>(bombDel->getPos()))
                break;
            index++;
        }
        delete bomb;
        _bombs.erase(_bombs.begin() + index);
    }
}

void indie::Game::display()
{
    _resources.display();
}
