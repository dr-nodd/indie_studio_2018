/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** description
*/

#include <utility>
#include "CPU.hpp"

indie::CPU::CPU(bool isCpu, int posX, int posY, int posZ, char id1,
	indie::Resources &resources1, std::string texture)
	: Player(isCpu, posX, posY, posZ, id1, resources1, texture), _action(IDLE), _behaviour(NONE), _vision(5)
{
}

bool indie::CPU::inDanger()
{
	auto pos = _resources.getModel(_id)->getPosition();
	std::vector<irr::core::vector3df> bombPos;

	for (auto &it : _resources.getBombs()) {
		bombPos.push_back(it->mesh->getPosition());
	}
	for (auto &it : bombPos) {
		if ((pos.X > it.X - 5 && pos.X < it.X + 5 && pos.Y > it.Y - 45 && pos.Y < it.Y + 45 && it.Z == POS_Z) ||
			(pos.Y > it.Y - 5 && pos.Y < it.Y + 5 && pos.X > it.X - 45 && pos.X < it.X + 45 && it.Z == POS_Z)) {
			return true;
		}
	}
	return false;
}

bool indie::CPU::findWayTo(float x, float y, float z)
{
	auto player = _resources.getModel(_id)->getPosition();
	irr::core::vector3df dest(x, y, z);

	if (isSafe(player.X, player.Y, player.Z)) {
		if (player.X > dest.X && isWalkable(player.X - 10, player.Y, player.Z) && isSafe(player.X - 10, player.Y, player.Z))
			_action = LEFT;
		else if (player.Y > dest.Y && isWalkable(player.X, player.Y - 10, player.Z) && isSafe(player.X, player.Y - 10, player.Z))
			_action = DOWN;
		else if (player.X < dest.X && isWalkable(player.X + 10, player.Y, player.Z) && isSafe(player.X + 10, player.Y, player.Z))
			_action = RIGHT;
		else if (player.Y < dest.Y && isWalkable(player.X, player.Y + 10, player.Z) && isSafe(player.X, player.Y + 10, player.Z))
			_action = UP;
	} else {
		if (player.X > dest.X && isWalkable(player.X - 10, player.Y, player.Z))
			_action = LEFT;
		else if (player.Y > dest.Y && isWalkable(player.X, player.Y - 10, player.Z))
			_action = DOWN;
		else if (player.X < dest.X && isWalkable(player.X + 10, player.Y, player.Z))
			_action = RIGHT;
		else if (player.Y < dest.Y && isWalkable(player.X, player.Y + 10, player.Z))
			_action = UP;

	}
	return true;
}

void indie::CPU::goSafe()
{
	std::vector<irr::core::vector3df> pos;
	std::vector<irr::core::vector3df> visiblePos;
	int maxX = 1;
	int maxY = 1;
	int sign = -1;
	int x = 0;
	int y = 0;

	pos.push_back(_resources.getModel(_id)->getPosition());
	while (maxY != _vision + 20) {
		while (maxX != x) {
			pos.emplace_back(pos.at(pos.size() - 1).X + sign * 10, pos.at(pos.size() - 1).Y, POS_Z);
			x++;
		}
		sign *= -1;
		x = 0;
		maxX += 1;
		if (maxX == _vision + 20)
			break;
		while (maxY != y) {
			pos.emplace_back(pos.at(pos.size() - 1).X, pos.at(pos.size() - 1).Y + sign * 10, POS_Z);
			y++;
		}
		y = 0;
		maxY += 1;
	}
	visiblePos.push_back(pos.at(0));
	pos.erase(pos.begin());
	for (int i = 7; i >= 0; i--) {
		if (i % 2 == 0) {
			visiblePos.push_back(pos.at(i));
			if (i == 0)
				pos.erase(pos.begin());
			else
				pos.erase(pos.begin() + i - 1);
		}
	}
	for (int i = 3; i >= 0; i--) {
		visiblePos.push_back(pos.at(i));
		if (i == 0)
			pos.erase(pos.begin());
		else
			pos.erase(pos.begin() + i - 1);
	}
	for (auto &it : pos) {
		visiblePos.push_back(it);
	}
	for (auto &it : visiblePos)
		if (isSafe(it.X, it.Y, POS_Z) && isWalkable(it.X, it.Y, POS_Z)) {
			findWayTo(it.X, it.Y, POS_Z);
			return;
		}
}

bool indie::CPU::isWalkable(float x, float y, float z)
{
	for (auto &it : _resources.getCubes())
		if (it->mesh->getPosition().X - 5 <= x &&
            it->mesh->getPosition().X + 5 >= x &&
            it->mesh->getPosition().Y - 5 <= y &&
            it->mesh->getPosition().Y + 5 >= y &&
            it->mesh->getPosition().Z + 5 == z)
			return false;
	return true;
}

bool indie::CPU::isDestructible(float x, float y, float z)
{
	for (auto &it : _resources.getCubes())
		if (it->mesh->getPosition().X - 5 <= x &&
            it->mesh->getPosition().X + 5 >= x &&
            it->mesh->getPosition().Y - 5 <= y &&
            it->mesh->getPosition().Y + 5 >= y &&
            it->mesh->getPosition().Z + 5 == z &&
            it->path == PATH_DESTRUCT_WALL_MODEL)
			return true;
	return false;
}

bool indie::CPU::isPowerUp(float x, float y, float z)
{
	for (auto &it : _resources.getPowerUps())
		if (it->mesh->getPosition().X - 5 <= x &&
			it->mesh->getPosition().X + 5 >= x &&
			it->mesh->getPosition().Y - 5 <= y &&
			it->mesh->getPosition().Y + 5 >= y &&
			it->mesh->getPosition().Z == z)
			return true;
	return false;
}

bool indie::CPU::isEnemy(float x, float y, float z)
{
	for (auto &it : _resources.getModels()) {
		if (it->mesh->getPosition().X ==
			_resources.getModel(_id)->getPosition().X &&
			it->mesh->getPosition().Y ==
				_resources.getModel(_id)->getPosition().Y &&
			it->mesh->getPosition().Z ==
				_resources.getModel(_id)->getPosition().Z)
			return false;
		if (it->mesh->getPosition().X - 5 <= x &&
			it->mesh->getPosition().X + 5 >= x &&
			it->mesh->getPosition().Y - 5 <= y &&
			it->mesh->getPosition().Y + 5 >= y &&
			it->mesh->getPosition().Z == z)
			return true;
	}
	return false;
}

bool indie::CPU::isNextTo(float x, float y)
{
	auto pos = _resources.getModel(_id)->getPosition();

	if ((pos.X >= x - 5 && pos.X <= x + 5 && pos.Y >= y - 15 && pos.Y <= y + 15) ||
		(pos.Y >= y - 5 && pos.Y <= y + 5 && pos.X >= x - 15 && pos.X <= x + 15)) {
		return true;
	}
	return false;
}

bool indie::CPU::goFindPowerUp()
{
	std::vector<irr::core::vector3df> pos;
	std::vector<irr::core::vector3df> visiblePos;
	int maxX = 1;
	int maxY = 1;
	int sign = -1;
	int x = 0;
	int y = 0;

	pos.push_back(_resources.getModel(_id)->getPosition());
	while (maxY != _vision + 2) {
		while (maxX != x) {
			pos.emplace_back(pos.at(pos.size() - 1).X + sign * 10, pos.at(pos.size() - 1).Y, POS_Z);
			x++;
		}
		sign *= -1;
		x = 0;
		maxX += 1;
		if (maxX == _vision + 2)
			break;
		while (maxY != y) {
			pos.emplace_back(pos.at(pos.size() - 1).X, pos.at(pos.size() - 1).Y + sign * 10, POS_Z);
			y++;
		}
		y = 0;
		maxY += 1;
	}
	visiblePos.push_back(pos.at(0));
	pos.erase(pos.begin());
	for (int i = 7; i >= 0; i--) {
		if (i % 2 == 0) {
			visiblePos.push_back(pos.at(i));
			if (i == 0)
				pos.erase(pos.begin());
			else
				pos.erase(pos.begin() + i - 1);
		}
	}
	for (int i = 3; i >= 0; i--) {
		visiblePos.push_back(pos.at(i));
		if (i == 0)
			pos.erase(pos.begin());
		else
			pos.erase(pos.begin() + i - 1);
	}
	for (auto &it : pos) {
		visiblePos.push_back(it);
	}
	for (auto &it : visiblePos) {
		if (isPowerUp(it.X, it.Y, POS_Z)) {
			if (isSafe(it.X, it.Y, POS_Z))
				findWayTo(it.X, it.Y, POS_Z);
			return true;
			}
		}
	return false;
}

bool indie::CPU::goFindEnemies()
{
	std::vector<irr::core::vector3df> pos;
	std::vector<irr::core::vector3df> visiblePos;
	int maxX = 1;
	int maxY = 1;
	int sign = -1;
	int x = 0;
	int y = 0;

	pos.push_back(_resources.getModel(_id)->getPosition());
	while (maxY != _vision + 4) {
		while (maxX != x) {
			pos.emplace_back(pos.at(pos.size() - 1).X + sign * 10, pos.at(pos.size() - 1).Y, POS_Z);
			x++;
		}
		sign *= -1;
		x = 0;
		maxX += 1;
		if (maxX == _vision + 4)
			break;
		while (maxY != y) {
			pos.emplace_back(pos.at(pos.size() - 1).X, pos.at(pos.size() - 1).Y + sign * 10, POS_Z);
			y++;
		}
		y = 0;
		maxY += 1;
	}
	visiblePos.push_back(pos.at(0));
	pos.erase(pos.begin());
	for (int i = 7; i >= 0; i--) {
		if (i % 2 == 0) {
			visiblePos.push_back(pos.at(i));
			if (i == 0)
				pos.erase(pos.begin());
			else
				pos.erase(pos.begin() + i - 1);
		}
	}
	for (int i = 3; i >= 0; i--) {
		visiblePos.push_back(pos.at(i));
		if (i == 0)
			pos.erase(pos.begin());
		else
			pos.erase(pos.begin() + i - 1);
	}
	for (auto &it : pos) {
		visiblePos.push_back(it);
	}
	for (auto &it : visiblePos) {
		if (isEnemy(it.X, it.Y, POS_Z)) {
			if (isNextTo(it.X, it.Y)) {
				_isPlanting = true;
				return true;
			}
		findWayTo(it.X, it.Y, POS_Z);
		return true;
		}
	}
	return false;
}

void indie::CPU::goFindBlock()
{
	std::vector<irr::core::vector3df> pos;
	std::vector<irr::core::vector3df> visiblePos;
	int maxX = 1;
	int maxY = 1;
	int sign = -1;
	int x = 0;
	int y = 0;

	pos.push_back(_resources.getModel(_id)->getPosition());
	while (maxY != _vision + 40) {
		while (maxX != x) {
			pos.emplace_back(pos.at(pos.size() - 1).X + sign * 10, pos.at(pos.size() - 1).Y, POS_Z);
			x++;
		}
		sign *= -1;
		x = 0;
		maxX += 1;
		if (maxX == _vision + 40)
			break;
		while (maxY != y) {
			pos.emplace_back(pos.at(pos.size() - 1).X, pos.at(pos.size() - 1).Y + sign * 10, POS_Z);
			y++;
		}
		y = 0;
		maxY += 1;
	}
	visiblePos.push_back(pos.at(0));
	pos.erase(pos.begin());
	for (int i = 7; i >= 0; i--) {
		if (i % 2 == 0) {
			visiblePos.push_back(pos.at(i));
			if (i == 0)
				pos.erase(pos.begin());
			else
				pos.erase(pos.begin() + i - 1);
		}
	}
	for (int i = 3; i >= 0; i--) {
		visiblePos.push_back(pos.at(i));
		if (i == 0)
			pos.erase(pos.begin());
		else
			pos.erase(pos.begin() + i - 1);
	}
	for (auto &it : pos) {
		visiblePos.push_back(it);
	}
	for (auto &it : visiblePos) {
		if (isDestructible(it.X, it.Y, POS_Z)) {
			if (isNextTo(it.X, it.Y)) {
				_isPlanting = true;
				return;
			}
			findWayTo(it.X, it.Y, POS_Z);
			return;
		}
	}
}

bool indie::CPU::isSafe(float x, float y, float z)
{
	auto pos = irr::core::vector3df(x, y, z);
	std::vector<irr::core::vector3df> bombPos;

	for (auto &it : _resources.getBombs()) {
		bombPos.push_back(it->mesh->getPosition());
	}
	for (auto &it : bombPos) {
		if ((pos.X > it.X - 5 && pos.X < it.X + 5 && pos.Y > it.Y - 55 && pos.Y < it.Y + 55 && it.Z == POS_Z) ||
			(pos.Y > it.Y - 5 && pos.Y < it.Y + 5 && pos.X > it.X - 55 && pos.X < it.X + 55 && it.Z == POS_Z)) {
			return false;
		}
	}
	return true;
}

void indie::CPU::findBehaviour()
{
	if (inDanger()) {
		setBehaviour(DEF);
	} else if (goFindPowerUp()) {
		setBehaviour(POWER_UP);
	} else if (goFindEnemies()) {
		setBehaviour(ATK);
	} else {
		setBehaviour(FARM);
	}
}

void indie::CPU::setBehaviour(behaviour val)
{
	_behaviour = val;
}

void indie::CPU::move(float timeMult, std::vector<indie::Bomb *> &bombVec)
{
	auto model = _resources.getModel(_id);
	irr::core::vector3df newPos(model->getPosition().X, model->getPosition().Y, model->getPosition().Z);
    int dirX = 0;
    int dirY = 0;

	if (_action != IDLE) {
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
	switch (_action) {
	case UP:
		newPos.Y += 1;
		dirY = 1;
		model->setRotation(irr::core::vector3df(model->getRotation().X, model->getRotation().Y, 180.f));
		break;
	case DOWN:
		newPos.Y -= 1;
		dirY = -1;
		model->setRotation(irr::core::vector3df(model->getRotation().X, model->getRotation().Y, 0.f));
		break;
	case LEFT:
		newPos.X -= 1;
		dirX = 1;
		model->setRotation(irr::core::vector3df(model->getRotation().X, model->getRotation().Y, -90.f));
		break;
	case RIGHT:
		newPos.X += 1;
		dirX = -1;
		model->setRotation(irr::core::vector3df(model->getRotation().X, model->getRotation().Y, 90.f));
		break;
	default:
		break;
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

void indie::CPU::update(float timeMult, std::vector<indie::Bomb *> &bombVec)
{
	auto player = _resources.getModel(_id)->getPosition();

	if (_isAlive) {
        _isPlanting = false;
        if (static_cast<int>(player.X) % 10 == 0 && static_cast<int>(player.Y) % 10 == 0) {
			_action = IDLE;
			findBehaviour();
			if (_behaviour == DEF) {
				goSafe();
			} else if (_behaviour == POWER_UP) {
				goFindPowerUp();
			} else if (_behaviour == ATK) {
				goFindEnemies();
			} else {
				goFindBlock();
			}
		}
        move(timeMult, bombVec);
    }
}