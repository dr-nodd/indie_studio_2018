/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** Stage Select
*/

#ifndef OOP_INDIE_STUDIO_2018_STAGESELECT_HPP
#define OOP_INDIE_STUDIO_2018_STAGESELECT_HPP

#include "IScene.hpp"

namespace indie {
	class StageSelect : public IScene {
		public:
		StageSelect(indie::Resources &, std::vector<std::pair<std::string, std::string>>, indie::IScene *deleteIt = nullptr);
		~StageSelect();

		indie::event getEvent() const;
		IScene *update();
		void display();

		private:
		void destroyScene();
		void initTexts();

		indie::Resources &_resources;
		indie::event _event;
		bool _isLeaving;
		std::vector<std::pair<std::string, std::string>> _players;
		std::string _stage;
	};
}

#endif //OOP_INDIE_STUDIO_2018_STAGESELECT_HPP
