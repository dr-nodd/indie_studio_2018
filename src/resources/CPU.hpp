/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** description
*/

#ifndef OOP_INDIE_STUDIO_2018_CPU_HPP
#define OOP_INDIE_STUDIO_2018_CPU_HPP

#include "Player.hpp"
#include "Resources.hpp"

namespace indie {
	enum behaviour {
		DEF,
		ATK,
		FARM,
		POWER_UP,
		NONE,
	};
	class CPU : public Player {
		public:
		CPU(bool isCpu, int posX, int posY, int posZ, char id1,
			indie::Resources &resources1, std::string texture);
		void move(float timeMult, std::vector<indie::Bomb *> &);
		void update(float timeMult, std::vector<indie::Bomb *> &);
		bool inDanger();
		bool isSafe(float x, float y, float z);
		bool isWalkable(float x, float y, float z);
		bool isDestructible(float x, float y, float z);
		bool isPowerUp(float x, float y, float z);
		bool isEnemy(float x, float y, float z);
		bool isNextTo(float x, float y);
		bool findWayTo(float x, float y, float z);
		void goSafe();
		bool goFindPowerUp();
		bool goFindEnemies();
		void goFindBlock();
		void setBehaviour(behaviour);
		void findBehaviour();
		private:

		action	_action;
		behaviour _behaviour;
		int _vision;
	};
}
#endif //OOP_INDIE_STUDIO_2018_CPU_HPP
