/*
** EPITECH PROJECT, 2022
** OOP_indie_studio_2018
** File description:
** OptionsScene
*/

#include <string>
#include <iostream>

#include "Menu.hpp"
#include "OptionsScene.hpp"

indie::OptionsScene::OptionsScene(indie::Resources &resources)
    :   _resources(resources), _isActive(false), _isClicked(false),
	_isClickedSynchroVert(false), _isClickedFullscreen(false),
	_isCloseClicked(false), _isVideoClicked(false),
    _isSoundsClicked(false), _isControlsClicked(false), _isAboutClicked(false),
    _isInSounds(false), _isApplyClicked(false),
    _isSynchroVert(_resources.options()->getSynchroVert()),
	_isFullscreen(_resources.options()->getFullscreen()), _isInVideo(true),
	_volumeSlider(0.0), _isInControls(false), _playerNumber(0),
    _isPlayerOneClicked(false), _isPlayerTwoClicked(false),
    _changePlayer(true), _isChanging(false), _controlToChange(L"1")
{
    setControlFromResources(resources.getPlayerControls());
}

indie::OptionsScene::~OptionsScene() = default;

void indie::OptionsScene::initHud()
{
    _resources.addRectangle(_colorsBackground, _posRectBackground);
    _resources.addRectangle(_colorsPauseBackground, _posPauseBackground);
    _resources.addText(L"Options", _posOptions, false, PATH_OPTION_FONT);
    _resources.addText(L"Video", _posVideo, true, PATH_OPTION_FONT);
    _resources.addText(L"Sound", _posSound, true, PATH_OPTION_FONT);
    _resources.addText(L"Controls", _posControls, true, PATH_OPTION_FONT);
    _resources.addText(L"About", _posAbout, true, PATH_OPTION_FONT);
    _resources.addText(L"Close", _posExit, true, PATH_OPTION_FONT);
}

void indie::OptionsScene::initControls()
{
    _resources.addText(L"Up", _posForward, false, PATH_OPTION_FONT);
    _resources.addText(L"Left", _posLeft, false, PATH_OPTION_FONT);
    _resources.addText(L"Down", _posBackward, false, PATH_OPTION_FONT);
    _resources.addText(L"Right", _posRight, false, PATH_OPTION_FONT);
    _resources.addText(L"Drop Bomb", _posDropBomb, false, PATH_OPTION_FONT);
    _resources.addText(L"Player 1", _posPlayerOne, true, PATH_OPTION_FONT);
    _resources.addText(L"Player 2", _posPlayerTwo, true, PATH_OPTION_FONT);
}

void indie::OptionsScene::categories()
{
    if (_resources.isClicked(L"Video"))
        _isVideoClicked = true;
    else if (_isVideoClicked) {
        _resources.getDevice()->getTimer()->setSpeed(0);
        _resources.destroySliders();
        _resources.destroyRectangles();
        _resources.destroyTexts();
        initHud();
        _resources.addText(L"Fullscreen:", _posFullscreen, false, PATH_OPTION_FONT);
        _resources.addText(L"Synchronisation Verticale:", _posSynchroVert, false, PATH_OPTION_FONT);
        _resources.addText(L"Apply", _posApply, true, PATH_OPTION_FONT);
        if (_resources.options()->getFullscreen())
            _resources.addRectangle(_colorsTickWith,
                _posTickFullscreen);
        else
            _resources.addRectangle(_colorsTickWithout,
                _posTickFullscreen);
        if (_resources.options()->getSynchroVert())
            _resources.addRectangle(_colorsTickWith,
                _posTickSynchroVert);
        else
            _resources.addRectangle(_colorsTickWithout,
                _posTickSynchroVert);
        _isInSounds = false;
        _isInControls = false;
        _isInVideo = true;
        _isVideoClicked = false;
    }
    if (_resources.isClicked(L"Sound"))
        _isSoundsClicked = true;
    else if (_isSoundsClicked) {
        _resources.destroySliders();
        _resources.destroyRectangles();
        _resources.destroyTexts();
        initHud();
        _resources.addText(L"Volume:", _posVolume, false, PATH_OPTION_FONT);
        _resources.addSlider(_colorsSlider, _posSliderVolume, _posRectVolume);
        _isInSounds = true;
        _isInControls = false;
        _volumeSlider = 0.0;
        _isSoundsClicked = false;
        _isInVideo = false;
    }
    if (_resources.isClicked(L"Controls"))
        _isControlsClicked = true;
    else if (_isControlsClicked) {
        _resources.destroySliders();
        _resources.destroyRectangles();
        _resources.destroyTexts();
        initHud();
        _isInSounds = false;
        _isInControls = true;
        _isControlsClicked = false;
        _isInVideo = false;
        initControls();
        _playerNumber = 0;
        _changePlayer = true;
    }
    if (_resources.isClicked(L"About"))
        _isAboutClicked = true;
    else if (_isAboutClicked) {
        _resources.destroySliders();
        _resources.destroyRectangles();
        _resources.destroyTexts();
        initHud();
		_resources.addText(L"Indie Studio is a second year Epitech project.", _posText, false, PATH_SMALL_FONT);
		_resources.addText(L"Our team is composed of Arnaud LECLERCQ,", _posText2, false, PATH_SMALL_FONT);
		_resources.addText(L"Aurelien VANDAELE, Benjamin DUPUIS, Nathalie HUGOT-POREZ,", _posText3, false, PATH_SMALL_FONT);
		_resources.addText(L"Philippe SIRVENTE MAROTO-CASTRO and Victor LEBLANC.", _posText4, false, PATH_SMALL_FONT);
		_resources.addText(L"Created with Irrlicht.", _posText5, false, PATH_SMALL_FONT);
		_resources.addText(L"Available on both Windows and Linux.", _posText6, false, PATH_SMALL_FONT);
		_isInSounds = false;
        _isInControls = false;
        _isAboutClicked = false;
        _isInVideo = false;
    }
}

void indie::OptionsScene::chooseControl()
{
    int hex = 0;

    if ((hex = _resources.isDown()) != (irr::EKEY_CODE)0xFF) {
        if (hex == (irr::EKEY_CODE)0xFE) {
            _isChanging = false;
            return;
        }
        for (int player = 0; _playerKeyCode[player]; player++) {
            for (int code = 0; _playerKeyCode[player][code]; code++) {
                if (_playerControls[player][code] == _controlToChange) {
                    _playerKeyCode[player][code] = (irr::EKEY_CODE)hex;
                    _isChanging = false;
                    playerControlConverter();
                    _resources.setPlayerKeyCode(_playerKeyCode);
                    return;
                }
            }
        }
    }
}

void indie::OptionsScene::display()
{
    if (!_isActive) {
        _resources.destroyTexts();
        initHud();
        _isVideoClicked = true;
        _isCloseClicked = false;
    }
    categories();
    _isActive = true;
    if (_isInSounds) {
        _lastVolumeSlider = static_cast<float>((_resources.getSliderValue(_colorsSlider, _posSliderVolume) * 100) +
                .5);
        if (_volumeSlider != _lastVolumeSlider) {
            _resources.deleteText(std::to_wstring(int(_volumeSlider)).c_str());
            _volumeSlider = _lastVolumeSlider;
            _posRectVolume = _resources.getSliderPos(_colorsSlider,
                _posSliderVolume);
            _resources.addText(std::to_wstring(int(_volumeSlider)).c_str(),
                _posVolumeNumber, false, PATH_OPTION_FONT);
            _resources.options()->setSoundVolume(float(_volumeSlider / 100));
        }
    }
    if (_isInControls) {
        for (int i = 0; i <= 4; i++) {
            if (_resources.isClicked(_playerControls[_playerNumber][i].c_str())) {
                _isChanging = true;
                _controlToChange = _playerControls[_playerNumber][i];
            }
        }
        if (_isChanging)
            chooseControl();
        if (_resources.isClicked(L"Player 1") && _playerNumber != 0) {
            _isPlayerOneClicked = true;
        } else if (_isPlayerOneClicked) {
            _isPlayerOneClicked = false;
            _playerNumber = 0;
            _changePlayer = true;
        }
        if (_resources.isClicked(L"Player 2") && _playerNumber != 1) {
            _isPlayerTwoClicked = true;
        } else if (_isPlayerTwoClicked) {
            _isPlayerTwoClicked = false;
            _playerNumber = 1;
            _changePlayer = true;
        }
        if (_changePlayer) {
            _changePlayer = false;
            _resources.destroyTexts();
            _resources.destroyRectangles();
            initHud();
            initControls();
            _resources.addText(_playerControls[_playerNumber][0].c_str(), _posForwardControl, true, PATH_OPTION_FONT);
            _resources.addText(_playerControls[_playerNumber][1].c_str(), _posLeftControl, true, PATH_OPTION_FONT);
            _resources.addText(_playerControls[_playerNumber][2].c_str(), _posBackwardControl, true, PATH_OPTION_FONT);
            _resources.addText(_playerControls[_playerNumber][3].c_str(), _posRightControl, true, PATH_OPTION_FONT);
            _resources.addText(_playerControls[_playerNumber][4].c_str(), _posDropBombControl, true, PATH_OPTION_FONT);

        }
    }
    manageVideo();
    if (_resources.getEventType() == QUIT ||
        _resources.isClicked(L"Close"))
        _isClicked = true;
    else if (_isClicked) {
        _resources.getDevice()->getTimer()->setSpeed(1);
        _resources.destroySliders();
        _resources.destroyRectangles();
        _resources.destroyTexts();
        _isCloseClicked = true;
        _isClicked = false;
        _isActive = false;
        _isInSounds = false;
        _volumeSlider = -1.0;
    }
}

bool indie::OptionsScene::isActive()
{
    return _isActive;
}

bool indie::OptionsScene::isQuit()
{
    return _isCloseClicked;
}

void indie::OptionsScene::manageVideo()
{
    if (_resources.isClicked(_colorsTickWithout, _posTickFullscreen))
        _isClickedFullscreen = true;
    else if (_isClickedFullscreen) {
        _isFullscreen = !_isFullscreen;
        if (!_isFullscreen)
            _resources.changeColorRectangle(_colorsTickWithout,
                _posTickFullscreen);
        else
            _resources.changeColorRectangle(_colorsTickWith,
                _posTickFullscreen);
        _isClickedFullscreen = false;
    }
    if (_resources.isClicked(_colorsTickWithout, _posTickSynchroVert))
        _isClickedSynchroVert = true;
    else if (_isClickedSynchroVert) {
        _isSynchroVert = !_isSynchroVert;
        if (!_isSynchroVert)
            _resources.changeColorRectangle(_colorsTickWithout,
                _posTickSynchroVert);
        else
            _resources.changeColorRectangle(_colorsTickWith,
                _posTickSynchroVert);
        _isClickedSynchroVert = false;
    }
    if (_resources.isClicked(L"Apply"))
        _isApplyClicked = true;
    else if (_isApplyClicked) {
        if (_resources.options()->getSynchroVert() != _isSynchroVert) {
            _resources.options()->changeSynchroVert();
            _resources.options()->apply();
        } else if (_resources.options()->getFullscreen() != _isFullscreen) {
            _resources.options()->changeFullscreen();
            _resources.options()->apply();

        }
        _isApplyClicked = false;
    }
}

void indie::OptionsScene::playerControlConverter()
{
    for (int player = 0; player < 2; player++) {
        for (int code = 0; code < 5; code++) {
            if (_playerKeyCode[player][code] == (irr::EKEY_CODE)0x20) {
                _playerControls[player][code] = L"Space";
            } else if (_playerKeyCode[player][code] == (irr::EKEY_CODE)0x0D) {
                _playerControls[player][code] = L"Enter";
            } else if (_playerKeyCode[player][code] == (irr::EKEY_CODE)0xA3) {
                _playerControls[player][code] = L"RCtrl";
            } else if (_playerKeyCode[player][code] == (irr::EKEY_CODE)0xA1) {
                _playerControls[player][code] = L"RShift";
            } else if (_playerKeyCode[player][code] == (irr::EKEY_CODE)0x25) {
                _playerControls[player][code] = L"Left Arrow";
            } else if (_playerKeyCode[player][code] == (irr::EKEY_CODE)0x26) {
                _playerControls[player][code] = L"Up Arrow";
            } else if (_playerKeyCode[player][code] == (irr::EKEY_CODE)0x27) {
                _playerControls[player][code] = L"Right Arrow";
            } else if (_playerKeyCode[player][code] == (irr::EKEY_CODE)0x28) {
                _playerControls[player][code] = L"Down Arrow";
            } else if ((irr::EKEY_CODE)0x41 <= _playerKeyCode[player][code] &&
                       _playerKeyCode[player][code] <= (irr::EKEY_CODE)0x5A) {
                _playerControls[player][code] = (wchar_t)_playerKeyCode[player][code];
            }
        }
    }
    _changePlayer = true;
}

void indie::OptionsScene::setControlFromResources(std::vector<irr::EKEY_CODE> playerKeyCodeVector)
{
    int player = 0;
    int code = 0;

    for (auto it = playerKeyCodeVector.begin(); it != playerKeyCodeVector.end(); it++) {
        _playerKeyCode[player][code] = *it;
        if (code < 4)
            code++;
        else {
            code = 0;
            player++;
        }
    }
    playerControlConverter();
}