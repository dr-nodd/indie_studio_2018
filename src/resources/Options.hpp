/*
** EPITECH PROJECT, 2022
** OOP_indie_studio_2018
** File description:
** Options
*/

#ifndef OOP_INDIE_STUDIO_2018_OPTIONS_HPP
#define OOP_INDIE_STUDIO_2018_OPTIONS_HPP

#include "Resources.hpp"

namespace indie {
    class Resources;

    class Options {
    public:
        Options(indie::Resources *);
        ~Options();

        void setSoundVolume(float soundVolume);
        void changeSynchroVert();
        void changeFullscreen();
        bool getSynchroVert() const;
        bool getFullscreen() const;
        unsigned char getSoundVolume() const;
        void apply();

    private:
        indie::Resources *_resources;

        bool _synchroVert;
        bool _fullscreen;
        unsigned char _soundVolume;
    };
}

#endif //OOP_INDIE_STUDIO_2018_OPTIONS_HPP
