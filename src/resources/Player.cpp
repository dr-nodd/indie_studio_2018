/*
** EPITECH PROJECT, 2022
** OOP_indie_studio_2018
** File description:
** Player Class
*/

#include "Bomb.hpp"
#include "Player.hpp"

indie::Player::Player(bool isCPU, int pos_x, int pos_y, int pos_z, char id, indie::Resources &resources, std::string texture)
    :   _isCPU(isCPU), _isAlive(true), _resources(resources), _id(id), _nbBomb(NB_BOMB), _isPlanting(false),
    _canThrow(CAN_THROW), _speed(1), _rangeBomb(RANGE_BOMB), _texture(texture), _isRunning(false), _isIdle(false)
{
	_resources.addCharacter(pos_x, pos_y, pos_z, id, PATH_BOMBER_IDLE, texture.c_str());
}

indie::Player::~Player()
{
}

bool indie::Player::isPlayer() const
{
    return !_isCPU;
}

bool indie::Player::isAlive() const
{
    return _isAlive;
}

bool indie::Player::isPlanting() const
{
    return _isPlanting;
}

char indie::Player::getId() const
{
    return _id;
}

char indie::Player::getNbBomb()
{
    return _nbBomb;
}

bool indie::Player::getCanThrow()
{
    return _canThrow;
}

int indie::Player::getRangeBomb()
{
    return _rangeBomb;
}

std::string indie::Player::getTexture() const
{
    return _texture;
}

irr::core::vector3df indie::Player::getPosition() const
{
    return _resources.getModel(_id)->getPosition();
}

irr::core::vector3df indie::Player::getRotation() const
{
    return _resources.getModel(_id)->getRotation();
}

void indie::Player::setPosition()
{

}

void indie::Player::setRotation(int speed)
{
	auto model = _resources.getModel(_id);

	model->setRotation(irr::core::vector3df(model->getRotation().X,
		model->getRotation().Y + speed,
		model->getRotation().Z));
}

void indie::Player::increase_range()
{
    _rangeBomb++;
}

void indie::Player::increase_bomb()
{
    _nbBomb++;
}

void indie::Player::canThrow()
{
    _canThrow = true;
}

void indie::Player::increase_speed()
{
    _speed += 0.1;
}

void indie::Player::die()
{
    _resources.getModel(_id)->removeAnimators();
    _resources.getModel(_id)->setPosition(irr::core::vector3df(_resources.getModel(_id)->getPosition().X, _resources.getModel(_id)->getPosition().Y, -100.0));
    _isAlive = false;
}

void indie::Player::update(float timeMult, std::vector<indie::Bomb *> &bombVec)
{
    if (_isAlive) {
        move(timeMult, bombVec);
        _isPlanting = _resources.getActionType(_id) == BOMB;
    }
}

void indie::Player::move(float timeMult, std::vector<indie::Bomb *> &bombVec)
{
    static bool is_idle = true;
    static bool temp1 = true;
    auto action = _resources.getActionType(_id);
    auto model = _resources.getModel(_id);

    timeMult *= _speed;
    if (action != IDLE) {
        if (!_isRunning) {
            _isRunning = true;
            _isIdle = false;
            _resources.setBomberToRun(PATH_BOMBER_RUN, _texture.c_str(), _id);
        }
    } else {
        if (!_isIdle) {
            _isIdle = true;
            _isRunning = false;
            _resources.setBomberToIdle(PATH_BOMBER_IDLE, _texture.c_str(), _id);
        }
    }

    irr::core::vector3df newPos(
        model->getPosition().X,
        model->getPosition().Y,
        model->getPosition().Z
    );
    int dirX = 0;
    int dirY = 0;

    if (action == UP) {
        newPos.Y += timeMult;
        dirY = 1;
        model->setRotation(irr::core::vector3df(model->getRotation().X, model->getRotation().Y, 180.f));
    } else if (action == DOWN) {
        newPos.Y -= timeMult;
        dirY = -1;
        model->setRotation(irr::core::vector3df(model->getRotation().X, model->getRotation().Y, 0.f));
    } else if (action == RIGHT) {
        newPos.X += timeMult;
        dirX = 1;
        model->setRotation(irr::core::vector3df(model->getRotation().X, model->getRotation().Y, 90.f));
    } else if (action == LEFT) {
        newPos.X -= timeMult;
        dirX = -1;
        model->setRotation(irr::core::vector3df(model->getRotation().X, model->getRotation().Y, -90.f));
    }
    if (_canThrow) {
        for (auto &bomb : bombVec) {
        irr::core::vector3df bombPos(
            _resources.getModelBomb(bomb->getId())->getPosition());
            if (newPos.X >= bombPos.X - 5.f - timeMult * 2.f &&
                newPos.X <= bombPos.X + 5.f + timeMult * 2.f &&
                newPos.Y >= bombPos.Y - 5.f - timeMult * 2.f &&
                newPos.Y <= bombPos.Y + 5.f + timeMult * 2.f)
                bomb->kick(dirX, dirY);
        }
     }
    model->setPosition(newPos);
}
