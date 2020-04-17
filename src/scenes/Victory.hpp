/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** Victory screen
*/

#ifndef OOP_INDIE_STUDIO_2018_VICTORY_HPP
#define OOP_INDIE_STUDIO_2018_VICTORY_HPP

#include "IScene.hpp"

namespace indie {
	class Victory : public IScene {
		public:
		Victory(indie::Resources &, std::pair<std::string, std::string>, indie::IScene *deleteIt = nullptr);
		~Victory();

		indie::event getEvent() const;
		IScene *update();
		void display();

		private:
		void destroyScene();
		void initTexts();

		indie::Resources &_resources;
		indie::event _event;
		bool _isLeaving;
		std::pair<std::string, std::string> _winner;
	};
}

#endif //OOP_INDIE_STUDIO_2018_VICTORY_HPP
