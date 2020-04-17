/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** description
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <ISceneManager.h>
#include "Map.hpp"

indie::Map::Map(const int x, const int y) : _size(std::make_pair(x - 2, y - 2))
{
	std::srand(static_cast<unsigned int>(std::time(0)));
	GenerateMap();
}

void indie::Map::setSize(int x, int y)
{
	_size = std::make_pair(x, y);
}

void indie::Map::GenerateMap()
{
//	generate first quarter
	std::string walls;
	walls += 'X';
	for (int i = 0; i < _size.first / 2; i++)
		walls += 'X';
	_map.emplace_back(walls);
	std::string str;
	str += 'X';
	for (int i = 0; i < _size.first / 2; i++)
		str += '*';
	for (int i = 0; i < _size.second / 2; i++)
		_map.emplace_back(str);
//	add random walls
	for (auto &i : _map) {
		for (auto &j : i) {
			if (j == '*' && std::rand() % 7 == 0) {
				j = 'X';
			} else if (j == '*' && std::rand() % 2 == 0) {
				j = '0';
			}
		}
	}
//	check validity
	_map.at(1).at(1) = '0';
	_map.at(1).at(2) = '0';
	_map.at(2).at(1) = '0';
//	vertical dup
	std::vector<std::string> tmp(_map);
	std::reverse(tmp.begin(), tmp.end());
	for (long unsigned int i = 0; i < tmp.size(); i++)
		_map.emplace_back(tmp.at(i));
//	hzontal dup
	std::vector<std::string> res(_map);
	for (long unsigned int i = 0; i < _map.size(); i++)
		std::reverse(res.at(i).begin(), res.at(i).end());
//	concat vectors
	for (long unsigned int i = 0; i < _map.size(); i++)
		_map.at(i) = _map.at(i) + res.at(i);
}

std::vector<std::string> indie::Map::getMap() const
{
	return _map;
}

void indie::Map::setMap(std::vector<std::string> map)
{
    _map = map;
}

void indie::Map::printMap()
{
	for (long unsigned int i = 0; i < _map.size(); i++)
		std::cout << _map.at(i) << std::endl;
}