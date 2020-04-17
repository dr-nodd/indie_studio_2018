/*
** EPITECH PROJECT, 2022
** OOP_indie_studio_2018
** File description:
** Bomb Class
*/

#include "Bomb.hpp"
#include "Resources.hpp"

indie::Bomb::Bomb(std::pair<float, float> pos, indie::Resources &resources, int id, char idPlayer, char range)
    :   _pos(std::tuple<float, float, float>(pos.first, pos.second, POS_Z)), _resources(resources),
    _id(id), _idPlayer(idPlayer), _range(range), _exploding(false), _kick(std::pair<int, int>(0, 0))
{
    _timePlant = _resources.getDevice()->getTimer()->getRealTime();
    _resources.addBomb(int(pos.first), int(pos.second), POS_Z, id);
}

indie::Bomb::~Bomb()
{
    //_resources.deleteBomb(_id);TODO
}

std::tuple<float, float, float> indie::Bomb::getPos() const
{
    return _pos;
}

char indie::Bomb::getRange() const
{
    return _range;
}

int indie::Bomb::getId() const
{
    return _id;
}

char indie::Bomb::getIdPlayer() const
{
    return _idPlayer;
}

bool indie::Bomb::isExploding() const
{
    return _exploding;
}

void indie::Bomb::setPos(float x, float y, float z)
{
    std::get<0>(_pos) = x;
    std::get<1>(_pos) = y;
    std::get<2>(_pos) = z;
}

void indie::Bomb::kick(int dirX, int dirY)
{
    if (_resources.getDevice()->getTimer()->getRealTime() > _timePlant + 500)
        _kick = std::pair<int, int>(dirX, dirY);
}

void indie::Bomb::update(float timeMult, indie::Map &map)
{
    if (_exploding || _resources.getDevice()->getTimer()->getRealTime() > _timePlant + 3000) {
        _exploding = true;
    } else {
        std::pair<float, float> bombPos(std::get<0>(_pos), std::get<1>(_pos));
        std::pair<int, int> collision(
            int(bombPos.first / 10 + MAP_WIDTH / 2) + _kick.first,
            int(bombPos.second / 10 + MAP_HEIGHT / 2) + _kick.second);

        if (collision.first >= 0 && collision.second >= 0 &&
            collision.first < map.getMap().size() &&
            collision.second < map.getMap().at(0).size() &&
            map.getMap().at(collision.first).at(collision.second) == '0') {
            auto model = _resources.getModelBomb(_id);

            if (model) {
                model->setPosition(
                    irr::core::vector3df(bombPos.first + _kick.first * timeMult,
                        bombPos.second + _kick.second * timeMult, POS_Z));
                this->setPos(int(model->getPosition().X),
                    int(model->getPosition().Y), 45);
            } else {
                _kick = std::pair<int, int>(0, 0);
            }
        } else {
            _kick = std::pair<int, int>(0, 0);
        }
    }
}

void indie::Bomb::explode()
{
    _exploding = true;
}
