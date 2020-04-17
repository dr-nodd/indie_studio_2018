/*
** EPITECH PROJECT, 2022
** OOP_indie_studio_2018
** File description:
** OptionsScene Header
*/

#ifndef OOP_INDIE_STUDIO_2018_OPTIONSSCENE_HPP
#define OOP_INDIE_STUDIO_2018_OPTIONSSCENE_HPP

#include "IScene.hpp"

namespace indie {
    class OptionsScene {
    public:
        explicit OptionsScene(Resources &);
        ~OptionsScene();

        void display();
        bool isActive();
        bool isQuit();

    private:
        void manageVideo();
        void initHud();
        void initControls();
        void categories();
        void playerControlConverter();
        void chooseControl();
        void setControlFromResources(std::vector<irr::EKEY_CODE>);

        indie::Resources &_resources;
        bool _isActive;
        bool _isClicked;
        bool _isClickedSynchroVert;
        bool _isClickedFullscreen;
        bool _isCloseClicked;
        bool _isVideoClicked;
        bool _isSoundsClicked;
        bool _isControlsClicked;
        bool _isAboutClicked;
        bool _isInSounds;
        bool _isApplyClicked;
        bool _isSynchroVert;
        bool _isFullscreen;
        bool _isInVideo;

        int _colorsBackground[4] = {80, 0, 0, 30};
        int _colorsTickWithout[4] = {255, 120, 0, 0};
        int _colorsTickWith[4] = {255, 0, 120, 0};
        int _colorsSlider[4] = {255, 0, 0, 100};
        int _colorsPauseBackground[4] = {50, 0, 0, 0};

        int _posPauseBackground[4] = {0, 0, 1920, 1080};
        int _posRectBackground[4] = {200, 120, 1720, 960};
        int _posExit[4] = {1400, 800, 1700, 950};
        int _posOptions[4] = {700, 120, 1220, 240};
        int _posVideo[4] = {200, 250, 500, 390};
        int _posSound[4] = {200, 440, 500, 580};
        int _posControls[4] = {200, 630, 500, 770};
        int _posAbout[4] = {200, 820, 500, 960};
        int _posText[4] = {750, 210, 1350, 350};
		int _posText2[4] = {750, 310, 1350, 450};
		int _posText3[4] = {750, 410, 1350, 550};
		int _posText4[4] = {750, 510, 1350, 650};
		int _posText5[4] = {750, 610, 1350, 750};
		int _posText6[4] = {750, 710, 1350, 850};
		int _posFullscreen[4] = {500, 250, 1000, 390};
        int _posTickFullscreen[4] = {1630, _posFullscreen[1] + 50, 1680, _posFullscreen[1] + 100};
        int _posSynchroVert[4] = {_posFullscreen[0], _posFullscreen[1] + 190, _posFullscreen[2] + 500, _posFullscreen[3] + 190};
        int _posTickSynchroVert[4] = {_posTickFullscreen[0], _posTickFullscreen[1] + 190, _posTickFullscreen[2], _posTickFullscreen[3] + 190};
        int _posApply[4] = {_posExit[0] - 350, _posExit[1], _posExit[2] - 350 , _posExit[3]};
        int _posVolume[4] = {570, 250, 800, 390};
        int _posSliderVolume[4] = {_posRectBackground[2] - 300, 320, _posRectBackground[2] - 40, 340};
        int _posVolumeNumber[4] = {_posSliderVolume[0] - 400, _posSliderVolume[1], _posSliderVolume[2], _posSliderVolume[3]};
        int _posRectVolume = _posSliderVolume[2];
        float _volumeSlider;
        float _lastVolumeSlider;
        float _resolutionSlider;
        float _lastResolutionSlider;

        bool _isInControls;
        int _playerNumber;
        bool _isPlayerOneClicked;
        bool _isPlayerTwoClicked;
        bool _changePlayer;
        int _posForward[4] = {700, 250, 900, 350};
        int _posLeft[4] = {700, 380, 900, 480};
        int _posBackward[4] = {700, 510, 900, 610};
        int _posRight[4] = {700, 640, 900, 740};
        int _posDropBomb[4] = {700, 770, 900, 870};
        int _posForwardControl[4] = {1100, 250, 1280, 350};
        int _posLeftControl[4] = {1100, 380, 1280, 480};
        int _posBackwardControl[4] = {1100, 510, 1280, 610};
        int _posRightControl[4] = {1100, 640, 1280, 740};
        int _posDropBombControl[4] = {1100, 770, 1280, 870};
        int _posPlayerOne[4] = {1400, 250, 1700, 380};
        int _posPlayerTwo[4] = {1400, 380, 1700, 510};

        irr::EKEY_CODE _playerKeyCode[2][5];
        std::wstring _playerControls[2][5];
        bool _isChanging;

        std::wstring _controlToChange;
    };
}
#endif //OOP_INDIE_STUDIO_2018_OPTIONSSCENE_HPP
