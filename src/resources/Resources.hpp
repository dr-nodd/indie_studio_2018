/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** resources Header
*/

#ifndef OOP_INDIE_STUDIO_2018_RESOURCES_HPP
#define OOP_INDIE_STUDIO_2018_RESOURCES_HPP

#include <irrlicht.h>
#include <irrlicht/IrrlichtDevice.h>
#include <driverChoice.h>
#include <vector>
#include <SFML/Audio.hpp>

#include "Settings.hpp"
#include "EventReceiver.hpp"
#include "Options.hpp"

namespace indie {
    class Bomb;
    class Options;
    enum event {
        ACTIVE,
        QUIT,
        PLAY
    };

    enum action {
        UP,
        LEFT,
        DOWN,
        RIGHT,
        BOMB,
        IDLE
    };

    typedef struct image_s {
        std::string path;
        irr::video::ITexture *texture;
        irr::core::rect<irr::s32> size;
        std::pair<int, int> position;
        std::string id;
    } image_t;

    typedef struct text_s {
    	std::string id;
        bool isButton;
        unsigned int isFirstMouseOver;
        unsigned int isFirstClick;
        irr::core::stringw msg;
        irr::core::rect<irr::s32> position;
        std::string pathFont;
    } text_t;

    typedef struct rectangle_s {
        irr::video::SColor colors;
        irr::core::rect<irr::s32> position;
    } rectangle_t;

    typedef struct slider_s {
        irr::video::SColor colors;
        irr::core::rect<irr::s32> position;
    } slider_t;

    typedef struct model_s {
        irr::scene::IAnimatedMeshSceneNode *mesh;
        const char *texture;
        char id;
    } model_t;

    typedef struct cube_s {
        std::string path;
        irr::scene::IAnimatedMeshSceneNode *mesh;
        std::pair<int, int> rawPos;
    } cube_t;

    typedef struct bomb_s {
        irr::scene::IAnimatedMeshSceneNode *mesh;
        int id;
    } bomb_t;

    typedef struct power_up_s {
        irr::scene::IAnimatedMeshSceneNode *mesh;
        std::string path;
    } power_up_t;

    typedef struct cloud_s {
        irr::scene::IAnimatedMeshSceneNode *mesh;
    } cloud_t;

    class Resources {
    public:
        Resources();
        ~Resources();

        void destroyMusicEngine();
        void destroySoundBufferEngine();
        void stopMusicEngine();
        void destroyImages();
        void destroyTexts();
        void destroyRectangles();
        void destroySliders();
        void destroyModels();
        void destroyClouds();
        void deleteText(const wchar_t *);
        void deleteImage(const std::string& path);
        void deleteRectangle(const int colors[4], const int position[4]);
        void deleteSlider(const int colors[4], const int position[4]);
        void deleteBomb(int id);

        void display();

        sf::Music *getMusicEngine();
        const char *getTextureFromId(const char) const;
        std::wstring getTextFromId(std::string &) const;
        irr::scene::ICameraSceneNode *getCamera() const;
        irr::scene::IAnimatedMeshSceneNode *getModel(char id) const;
        irr::scene::IAnimatedMeshSceneNode *getModelBomb(int id) const;
        std::vector<cube_t *> getCubes() const;
        std::vector<bomb_t *> getBombs() const;
        std::vector<model_t *> getModels() const;
        std::vector<power_up_t *> getPowerUps() const;
        std::vector<std::string> getImageId();
        irr::IrrlichtDevice *getDevice() const;
        float getSliderValue(const int colors[4], const int pos[4]) const;
        int getSliderPos(const int colors[4], const int pos[4]) const;
        indie::event getEventType() const;
        indie::action getActionType(char);

        void addCamera();
        void addCube(int pos_x, int pos_y, int pos_z, const char *path, const char *, std::pair<int, int> rawPos = std::pair<int, int>(-1, -1));
        void addCharacter(int, int, int, char, const char *, const char *);
        void addBomb(int pos_x, int pos_y, int pos_z, int id);
        void addPowerUp(int pos_x, int pos_y, int pos_z, std::string path, std::string);
        void addCloud(int pos_x, int pos_y, int pos_z, std::string, std::string);
        void addText(const wchar_t *, const int [4], bool, const std::string &, const std::string & = "");
        void addImage(const std::string& path, const int [4], std::pair<int, int> = {0, 0}, const std::string & = "");
        void addRectangle(const int colors[4], const int position[4]);
        void addSlider(const int colors[4], const int pos[4], const int posRectVolume);

        void setMusicEngine();
        void setSoundEngine();
		void setModelsRotation(int speed);
		void setPowerUPsRotation(float speed);
        void setCameraTarget(int, int, int);
        void setCameraPos(int, int, int);
        void setTextPosition(const wchar_t *, const int [4], const std::string & = "");
        void setPlayerKeyCode(irr::EKEY_CODE keyCode[2][5]);
        void setBomberToIdle(const char *, const char *, char);
        void setBomberToRun(const char *, const char *, char);
        void playMusic(const char *, bool);
        void playSound(const char *, bool);

        void createMenuCharacter(int, int, int, const char *, const char *, const char);
        void changeMenuCharacter(const char *, const char, bool);
        void moveSlider(slider_t *slider, rectangle_t *rectangle);
        void moveClouds();
        void changeColorRectangle(const int colors[4], const int position[4]);

        bool isClicked(const irr::core::stringw &textMsg);
        bool isClicked(const int color[4], const int pos[4]);
        bool isClicked(const std::string &, bool, const std::string & = "");
        bool isMouseOver(const irr::core::stringw& text);
        indie::Options *options() const;
        void restartDevice(bool fullscreen = false, bool synchroVert = false);
        void shaderInject(const std::string &);

        std::vector<irr::EKEY_CODE> getPlayerControls();
        irr::EKEY_CODE isDown();
    private:
        void mouseShadeEffect(const irr::core::stringw &, int percentageShade);
        bool _resultMouseOver;

        unsigned int height;
        unsigned int width;
        irr::IrrlichtDevice *_device;
        irr::gui::IGUIFont *_font;
        irr::video::IVideoDriver *_driver;
        irr::scene::ISceneManager *_smgr;
        irr::gui::IGUIEnvironment *_guienv;
        irr::scene::ISceneNode *_cube;
        irr::scene::ICameraSceneNode *_camera;
        std::vector<image_t *> _images;
        std::vector<text_t *> _texts;
        std::vector<rectangle_t *> _rectangles;
        std::vector<slider_t *> _sliders;
        std::vector<model_t *> _models;
        std::vector<bomb_t *> _bombs;
        std::vector<power_up_t *> _power_ups;
        std::vector<cloud_t *> _clouds;
        std::vector<cube_t *> _cubes;
        EventReceiver *_event;
        sf::Music *_music;
        sf::SoundBuffer *_soundBuffer;
        sf::Sound *_sound;
        indie::Options *_options;
        irr::scene::IMetaTriangleSelector *_selector;
        irr::s32 _mtlShader = 0;

        irr::EKEY_CODE _playerKeyCode[2][5];
        std::vector<irr::EKEY_CODE> _playerKeyCodeVector;
    };
}
#endif //OOP_INDIE_STUDIO_2018_RESOURCES_HPP
