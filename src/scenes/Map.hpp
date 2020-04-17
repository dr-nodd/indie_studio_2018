/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** description
*/

#ifndef OOP_INDIE_STUDIO_2018_MAP_HPP
#define OOP_INDIE_STUDIO_2018_MAP_HPP

#include <vector>
#include <string>

namespace indie {
	class Map {
		public:
			Map(const int x, const int y);
			~Map() = default;
			void setSize(int, int);
			void GenerateMap();
			void printMap();
			std::vector<std::string> getMap() const;
			void setMap(std::vector<std::string> map);
			void create3DModel();
		private:
			std::pair<int, int> _size;
			std::vector<std::string> _map;
	};
}

#endif //OOP_INDIE_STUDIO_2018_MAP_HPP
