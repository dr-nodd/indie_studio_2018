/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** Character Select Screen
*/

#ifndef OOP_INDIE_STUDIO_2018_CHARACTERSELECT_HPP
#define OOP_INDIE_STUDIO_2018_CHARACTERSELECT_HPP

#include "IScene.hpp"

namespace indie {
	class CharacterSelect : public IScene {
		public:
		CharacterSelect(indie::Resources &, indie::IScene *deleteIt = nullptr);
		~CharacterSelect();

		indie::event getEvent() const override;
		indie::IScene *update() override;
		void display() override;


		private:
		void destroyScene();
		void initTexts();
		void moveText(const std::string &, std::vector<std::pair<const wchar_t *, std::string>>);
		void managePlayer(const std::vector<std::string> &);
		void manageTexture(const std::vector<std::string> &);

		bool _isLeaving;
		indie::Resources &_resources;
		indie::event _event;
		unsigned int _timer;
	};
}

#endif //OOP_INDIE_STUDIO_2018_CHARACTERSELECT_HPP
