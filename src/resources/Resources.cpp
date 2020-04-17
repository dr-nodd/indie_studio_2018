/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** resources
*/

#include "Bomb.hpp"
#include "Resources.hpp"
#include "ShaderCallBack.hpp"
#include "Player.hpp"

indie::Resources::Resources() :
	_playerKeyCode{{irr::KEY_KEY_Z, irr::KEY_KEY_Q, irr::KEY_KEY_S, irr::KEY_KEY_D, irr::KEY_SPACE},
		{irr::KEY_UP, irr::KEY_LEFT, irr::KEY_DOWN, irr::KEY_RIGHT, irr::KEY_RCONTROL}},
    _playerKeyCodeVector{irr::KEY_KEY_Z, irr::KEY_KEY_Q, irr::KEY_KEY_S, irr::KEY_KEY_D, irr::KEY_SPACE, irr::KEY_UP,
                         irr::KEY_LEFT, irr::KEY_DOWN, irr::KEY_RIGHT, irr::KEY_RCONTROL},
    _font(nullptr), _images(std::vector<image_t *>()),
    _texts(std::vector<text_t *>()), _rectangles(std::vector<rectangle_t *>()),
    _sliders(std::vector<slider_t *>()), _models(std::vector<model_t *>()),
    _bombs(std::vector<bomb_t *>()), _power_ups(std::vector<power_up_t *>()),
    _cubes(std::vector<cube_t *>()), _event(new EventReceiver()), _music(nullptr), _options(new indie::Options(this))
{
    _device = irr::createDevice(irr::video::EDT_OPENGL,
        irr::core::dimension2d<irr::u32>(WINDOW_SIZE_X, WINDOW_SIZE_Y),
        16, _options->getFullscreen(), false, _options->getSynchroVert(), _event);
    if (!_device)
        throw (std::runtime_error("Error : Device creation failed"));
    _driver = _device->getVideoDriver();
    if (!_driver)
        throw (std::runtime_error("Error : Driver could not be loaded"));
    _smgr = _device->getSceneManager();
    if (!_smgr)
        throw (std::runtime_error("Error : Scene Manager could not be loaded"));
    _selector = _smgr->createMetaTriangleSelector();
    _guienv = _device->getGUIEnvironment();
    _device->getCursorControl()->setPosition(float(0.5), float(0.4));
    if (!_guienv)
        throw (std::runtime_error("Error : GUI Environment could not be loaded"));
    _device->setWindowCaption(WINDOW_NAME);
    _driver->getMaterial2D().TextureLayer[0].AnisotropicFilter = 16;
    _driver->getMaterial2D().AntiAliasing = irr::video::EAAM_FULL_BASIC;
    height = _driver->getScreenSize().Height;
    width = _driver->getScreenSize().Width;
}

indie::Resources::~Resources()
{
    stopMusicEngine();
    destroyImages();
    destroyTexts();
    destroyRectangles();
    destroySliders();
    destroyModels();
    destroyMusicEngine();
    destroySoundBufferEngine();
    destroyClouds();
    delete _event;
    delete _options;
    _selector->drop();
    _device->drop();
}

void indie::Resources::destroyMusicEngine()
{
    stopMusicEngine();
    delete _music;
}

void indie::Resources::destroySoundBufferEngine()
{
    delete _sound;
    delete _soundBuffer;
}

void indie::Resources::stopMusicEngine()
{
    _music->stop();
}

void indie::Resources::destroyImages()
{
    for (auto &image: _images)
        delete image;
    _images.erase(_images.begin(), _images.end());
}

void indie::Resources::destroyTexts()
{
    for (auto &text: _texts)
        delete text;
    _texts.erase(_texts.begin(), _texts.end());
}

void indie::Resources::destroyRectangles()
{
    for (auto &rectangle: _rectangles)
        delete rectangle;
    _rectangles.erase(_rectangles.begin(), _rectangles.end());
}

void indie::Resources::destroySliders()
{
    for (auto &slider: _sliders)
        delete slider;
    _sliders.erase(_sliders.begin(), _sliders.end());
}

void indie::Resources::destroyModels()
{
    _selector->removeAllTriangleSelectors();
    _smgr->clear();
    for (auto &model: _models)
        delete model;
    _models.erase(_models.begin(), _models.end());
    for (auto &bomb: _bombs)
        delete bomb;
    _bombs.erase(_bombs.begin(), _bombs.end());
    for (auto &cube: _cubes)
        delete cube;
    _cubes.erase(_cubes.begin(), _cubes.end());
    for (auto &power_up: _power_ups)
        delete power_up;
    _power_ups.erase(_power_ups.begin(), _power_ups.end());
}

void indie::Resources::destroyClouds()
{
    for (auto &cloud : _clouds)
        delete cloud;
    _clouds.erase(_clouds.begin(), _clouds.end());
}

void indie::Resources::deleteText(const wchar_t *str)
{
    long unsigned int index = 0;

    if (_texts.empty())
        return;
    for (auto &text: _texts) {
        if (text->msg == str)
            break;
        index++;
    }
    if (_texts.size() == index) //Check error
        return;
    _texts.erase(_texts.begin() + index);
}

void indie::Resources::deleteImage(const std::string& path)
{
    long unsigned int index = 0;

    if (_images.empty())
        return;
    for (auto &image: _images) {
        if (std::string(image->path.substr(image->path.rfind('/') + 1, image->path.size())) == path)
            break;
        index++;
    }
    if (_images.size() == index) //Check error
        return;
    _images.erase(_images.begin() + index);
}

void indie::Resources::deleteRectangle(const int colors[4], const int pos[4])
{
    long unsigned int index = 0;

    if (_rectangles.empty())
        return;
    for (auto &rectangle: _rectangles) {
        if (rectangle->position == irr::core::rect<irr::s32>(pos[0], pos[1], pos[2], pos[3]) &&
            rectangle->colors == irr::video::SColor(colors[0], colors[1], colors[2], colors[3]))
            break;
        index++;
    }
    if (_rectangles.size() == index) //Check error
        return;
    _rectangles.erase(_rectangles.begin() + index);
}

void indie::Resources::deleteSlider(const int *colors, const int *pos)
{
    long unsigned int index = 0;

    if (_sliders.empty())
        return;
    for (auto &rectangle : _rectangles)
        for (auto &slider : _sliders)
            if (slider->colors.getAlpha() == rectangle->colors.getAlpha() &&
                slider->colors.getBlue() + 30 == rectangle->colors.getBlue()) {
                int posRectangle[4] = {
                    slider->position.UpperLeftCorner.X,
                    rectangle->position.UpperLeftCorner.Y,
                    slider->position.LowerRightCorner.X,
                    rectangle->position.LowerRightCorner.Y
                };
                int colorsRectangle[4] = {
                    int(rectangle->colors.getAlpha()),
                    int(rectangle->colors.getRed()),
                    int(rectangle->colors.getGreen()),
                    int(rectangle->colors.getBlue())
                };
                deleteRectangle(colorsRectangle, posRectangle);
            }
    for (auto &slider: _sliders) {
        if (slider->position == irr::core::rect<irr::s32>(pos[0], pos[1], pos[2], pos[3]) &&
            slider->colors == irr::video::SColor(colors[0], colors[1], colors[2], colors[3]))
            break;
        index++;
    }
    if (_sliders.size() == index) //Check error
        return;
    _sliders.erase(_sliders.begin() + index);
}

void indie::Resources::deleteBomb(int id)
{
    int index = 0;

    if (_bombs.empty())
        return;
    for (auto &bomb: _bombs) {
        if (bomb->id == id) {
            //bomb->mesh->remove();
            break;
        }
        index++;
    }
    _bombs.erase(_bombs.begin() + index);
}

void indie::Resources::display()
{
    _driver->beginScene(true, true, irr::video::SColor(0, 0, 191, 255));
    for (auto &image : _images) {
        _driver->draw2DImage(image->texture,
            irr::core::position2d<irr::s32>(image->position.first,
            	image->position.second), image->size, nullptr,
            irr::video::SColor(255, 255, 255, 255), true);
    }
    _smgr->drawAll();
    for (auto &rectangle : _rectangles) {
        for (auto &slider : _sliders)
            if (slider->colors.getAlpha() == rectangle->colors.getAlpha() &&
                slider->colors.getBlue() + 30 == rectangle->colors.getBlue())
                moveSlider(slider, rectangle);
        _driver->draw2DRectangle(rectangle->colors, rectangle->position);
    }
    for (auto &text : _texts) {
        _resultMouseOver = isMouseOver(text->msg);
        if (text->isButton && _resultMouseOver) {
            mouseShadeEffect(text->msg, 30);
            text->isFirstMouseOver++;
            if (text->isFirstMouseOver == 1)
                playSound(PATH_MENU_BTN_SOUND_MOUSE_OVER, false);
        } else if (!_resultMouseOver)
            text->isFirstMouseOver = 0;
        _resultMouseOver = isClicked(text->msg);
        if (text->isButton && _resultMouseOver) {
            mouseShadeEffect(text->msg, 30);
            text->isFirstClick++;
            if (text->isFirstClick == 1)
                playSound(PATH_MENU_BTN_SOUND_CLICK, false);
        } else if (!_resultMouseOver)
            text->isFirstClick = 0;
        _font = _guienv->getFont(text->pathFont.c_str());
        _font->draw(text->msg, text->position,
            irr::video::SColor(255, 255, 255, 255), true, true);
    }
    _guienv->drawAll();
    _driver->endScene();
    height = _driver->getScreenSize().Height;
    width = _driver->getScreenSize().Width;
}

sf::Music *indie::Resources::getMusicEngine()
{
    return _music;
}

const char *indie::Resources::getTextureFromId(const char id) const
{
    for (const auto &it : _models) {
        if (id == it->id) {
            return it->texture;
        }
    }
    return nullptr;
}

std::wstring indie::Resources::getTextFromId(std::string &id) const
{
    std::wstring str = L"";

    for (const auto &it : _texts)
        if (id == it->id) {
            if (it->position.UpperLeftCorner.X < 2300) {
                return it->msg.c_str();
            }
        }
    return str;
}

irr::scene::ICameraSceneNode *indie::Resources::getCamera() const
{
    return _camera;
}

irr::scene::IAnimatedMeshSceneNode *indie::Resources::getModel(char id) const
{
	return _models[id]->mesh;
}

irr::scene::IAnimatedMeshSceneNode *indie::Resources::getModelBomb(int id) const
{
    for (auto &bomb: _bombs)
        if (bomb->id == id)
            return bomb->mesh;
    return nullptr;
}

std::vector<indie::cube_t *> indie::Resources::getCubes() const
{
    return _cubes;
}

std::vector<indie::bomb_t *> indie::Resources::getBombs() const
{
    return _bombs;
}

std::vector<indie::model_t *> indie::Resources::getModels() const
{
    return _models;
}

std::vector<indie::power_up_t *> indie::Resources::getPowerUps() const
{
    return _power_ups;
}

std::vector<std::string> indie::Resources::getImageId()
{
    std::vector<std::string> id;

    for (auto &image : _images) {
        id.push_back(image->id);
    }
    return (id);
}

irr::IrrlichtDevice *indie::Resources::getDevice() const
{
    return _device;
}

float indie::Resources::getSliderValue(const int *colors, const int *pos) const
{
    float xLeftBigRectangle = 0;
    float xRightBigRectangle = 0;
    float xLeftLittleRectangle = 0;
    float xRightLittleRectangle = 0;

    for (auto &rectangle: _rectangles)
        if (rectangle->position.UpperLeftCorner.X == pos[0] &&
            rectangle->position.UpperLeftCorner.Y == pos[1] &&
            rectangle->position.LowerRightCorner.X == pos[2] &&
            rectangle->position.LowerRightCorner.Y == pos[3] &&
            rectangle->colors.getAlpha() ==
                static_cast<unsigned int>(colors[0])) {
            xLeftBigRectangle = static_cast<float>(pos[0]);
            xRightBigRectangle = pos[2] - xLeftBigRectangle;
            break;
        }
    for (auto &rectangle : _rectangles)
        for (auto &slider : _sliders)
            if (slider->colors.getAlpha() == rectangle->colors.getAlpha() &&
                slider->colors.getBlue() + 30 == rectangle->colors.getBlue()) {
                xLeftLittleRectangle = rectangle->position.UpperLeftCorner.X - xLeftBigRectangle + 10;
                xRightLittleRectangle = rectangle->position.LowerRightCorner.X - xLeftBigRectangle - 10;
            }
    if (xRightBigRectangle == 0)
        return 0;
    return static_cast<float>(((xRightLittleRectangle - xLeftLittleRectangle) / 2.0 +
        xRightLittleRectangle) / xRightBigRectangle);
}

int indie::Resources::getSliderPos(const int colors[4], const int pos[4]) const
{
    for (auto &rectangle : _rectangles)
        for (auto &slider : _sliders)
            if (slider->colors.getAlpha() == rectangle->colors.getAlpha() &&
                slider->colors.getBlue() + 30 == rectangle->colors.getBlue())
                return rectangle->position.UpperLeftCorner.X + 10;
    return 0;
}

indie::event indie::Resources::getEventType() const
{
    if (!_device->run() || !_driver || !_device->isWindowActive() ||
        _event->isKeyDown(irr::KEY_ESCAPE))
        return QUIT;
    if (_event->isKeyDown(irr::KEY_RETURN))
        return PLAY;
    return ACTIVE;
}

indie::action indie::Resources::getActionType(char id)
{
    if (_event->isKeyDown(_playerKeyCode[id][0]))
        return indie::UP;
    else if (_event->isKeyDown(_playerKeyCode[id][1]))
        return indie::LEFT;
    else if (_event->isKeyDown(_playerKeyCode[id][2]))
        return indie::DOWN;
    else if (_event->isKeyDown(_playerKeyCode[id][3]))
        return indie::RIGHT;
    else if (_event->isKeyDown(_playerKeyCode[id][4]))
        return indie::BOMB;
    return indie::IDLE;
}

void indie::Resources::addCamera()
{
    _camera = _smgr->addCameraSceneNode();
}

void indie::Resources::addCube(int pos_x, int pos_y, int pos_z, const char *tex_path, const char *model_path, std::pair<int, int> rawPos)
{
    irr::scene::IAnimatedMeshSceneNode *cube = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh(model_path));
    if (!cube)
        throw (std::runtime_error("Couldn't load mesh"));
    cube->setScale(irr::core::vector3df(5, 5, 5));
    cube->setTriangleSelector(_selector);
    cube->setPosition(irr::core::vector3df(static_cast<irr::f32>(pos_x), static_cast<irr::f32>(pos_y), static_cast<irr::f32>(pos_z)));
    cube->setMaterialTexture(0, _driver->getTexture(tex_path));
    cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    cube->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
    cube->setMaterialType((irr::video::E_MATERIAL_TYPE)_mtlShader);
    irr::scene::ITriangleSelector *selector = _smgr->createTriangleSelectorFromBoundingBox(cube);
    _selector->addTriangleSelector(selector);
    selector->drop();
    auto newCube = new cube_t;
    newCube->path = model_path;
    newCube->mesh = cube;
    newCube->rawPos = rawPos;
    _cubes.push_back(newCube);
}

void indie::Resources::addCharacter(int pos_x, int pos_y, int pos_z, char id, const char *path, const char *texture)
{
	auto model = new model_t;
	model->mesh = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh(path));
	if (!model->mesh)
		throw (std::runtime_error("Couldn't load mesh"));
	model->id = id;
	model->mesh->setMaterialTexture(0, _driver->getTexture(texture));
	model->mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	model->mesh->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
    model->mesh->setMaterialType((irr::video::E_MATERIAL_TYPE)_mtlShader);
    model->mesh->setFrameLoop(0, 30);
    model->mesh->setAnimationSpeed(10);
    model->mesh->setRotation(irr::core::vector3df(180, 0, 0));
    model->mesh->setPosition(irr::core::vector3df(pos_x, pos_y, pos_z));
    model->mesh->setScale(irr::core::vector3df(5, 5, 5));
    irr::scene::ITriangleSelector *selector = _smgr->createTriangleSelectorFromBoundingBox(model->mesh);
    _selector->addTriangleSelector(selector);
    irr::scene::ISceneNodeAnimator *animator = _smgr->createCollisionResponseAnimator(_selector, model->mesh,
        irr::core::vector3df(2.1, 2.1, 2.1), irr::core::vector3df(0, 0, 0));
    model->mesh->addAnimator(animator);
    selector->drop();
    animator->drop();
    _models.push_back(model);
}

void indie::Resources::addBomb(int pos_x, int pos_y, int pos_z, int id)
{
    for (auto &bomb : _bombs)
        if (bomb->mesh->getPosition().X == pos_x &&
            bomb->mesh->getPosition().Y == pos_y &&
            bomb->mesh->getPosition().Z == pos_z)
            return;
    auto bomb = new bomb_t;

    bomb->mesh = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh(PATH_BOMB));
    bomb->mesh->setMaterialTexture(0, _driver->getTexture(PATH_BOMB_TEX));
    bomb->mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    bomb->mesh->setMaterialType((irr::video::E_MATERIAL_TYPE)_mtlShader);
    if (!bomb->mesh)
    	throw (std::runtime_error("Couldn't load mesh"));
    bomb->id = id;
    bomb->mesh->setPosition(irr::core::vector3df(pos_x, pos_y, pos_z));
    irr::scene::ITriangleSelector *selector = _smgr->createTriangleSelectorFromBoundingBox(bomb->mesh);
    _selector->addTriangleSelector(selector);
    selector->drop();
    bomb->mesh->setScale(irr::core::vector3df(5, 5, 5));
    _bombs.push_back(bomb);
}

void indie::Resources::addPowerUp(int pos_x, int pos_y, int pos_z, std::string path, std::string tex_path)
{
    for (auto &power_up : _power_ups)
        if (power_up->mesh->getPosition().X == pos_x &&
            power_up->mesh->getPosition().Y == pos_y &&
            power_up->mesh->getPosition().Z == pos_z)
            return;
    auto power_up = new power_up_t;
    power_up->mesh = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh(path.c_str()));
    power_up->mesh->setMaterialTexture(0, _driver->getTexture(tex_path.c_str()));
    power_up->mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    power_up->mesh->setMaterialType((irr::video::E_MATERIAL_TYPE)_mtlShader);
    if (!power_up->mesh)
        throw (std::runtime_error("Couldn't load mesh"));
    power_up->mesh->setPosition(irr::core::vector3df(round(pos_x / 10) * 10,
        pos_y, pos_z));
    power_up->path = path;
    power_up->mesh->setScale(irr::core::vector3df(5, 5, 5));
    _power_ups.push_back(power_up);
}

void indie::Resources::addCloud(int pos_x, int pos_y, int pos_z, std::string path, std::string tex_path)
{
    for (auto &cloud : _clouds)
        if (cloud->mesh->getPosition().X == pos_x &&
            cloud->mesh->getPosition().Y == pos_y &&
            cloud->mesh->getPosition().Z == pos_z)
            return;
    auto cloud = new cloud_t;

    cloud->mesh = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh(path.c_str()));
    if (!cloud->mesh)
        throw (std::runtime_error("Couldn't load mesh"));
    cloud->mesh->setMaterialTexture(0, _driver->getTexture(tex_path.c_str()));
    cloud->mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	cloud->mesh->setMaterialType((irr::video::E_MATERIAL_TYPE)_mtlShader);
	cloud->mesh->setPosition(irr::core::vector3df(pos_x, pos_y, pos_z));
    cloud->mesh->setScale(irr::core::vector3df(7, 7, 7));
    _clouds.push_back(cloud);
}

void indie::Resources::addText(const wchar_t *str, const int pos[4], bool isButton, const std::string &pathFont, const std::string &id)
{
    for (auto &text : _texts)
        if (text->msg == str && id.empty())
            return;
    auto *text = new text_t;

    text->id = id;
    text->msg = str;
    text->position = irr::core::rect<irr::s32>(pos[0], pos[1], pos[2], pos[3]);
    text->isButton = isButton;
    text->isFirstMouseOver = 0;
    text->isFirstClick = 0;
    text->pathFont = pathFont;
    _texts.push_back(text);
    _guienv = _device->getGUIEnvironment();
    _font = _guienv->getFont(pathFont.c_str());
    if (!_font)
    	throw (std::runtime_error("Couldn't load font"));
}


void indie::Resources::addImage(const std::string &path, const int i[4], std::pair<int, int> pos, const std::string &id)
{
    for (auto &image: _images)
        if (std::string(image->path.substr(image->path.rfind('/') + 1,
            image->path.size())) == path && id.empty())
            return;
    auto *tmp = new image_t;

    tmp->id = id;
    tmp->path = path;
    tmp->texture = _driver->getTexture(path.c_str());
    if (!tmp->texture)
    	throw (std::runtime_error("Couldn't load image"));
    tmp->size = irr::core::rect<irr::s32>(i[0], i[1], i[2], i[3]);
    tmp->position = pos;
    if (path.find("background") != path.npos)
        _images.insert(_images.begin(), tmp);
    else
        _images.push_back(tmp);
}

void indie::Resources::addRectangle(const int colors[4], const int pos[4])
{
    for (auto &rectangle : _rectangles)
        if (rectangle->colors.getAlpha() == static_cast<unsigned int>(colors[0])
        	&& rectangle->position.UpperLeftCorner.X == pos[0] &&
            rectangle->position.UpperLeftCorner.Y == pos[1] &&
            rectangle->position.LowerRightCorner.X == pos[2] &&
            rectangle->position.LowerRightCorner.Y == pos[3])
            return;
    auto *rectangle = new rectangle_t;

    rectangle->colors = irr::video::SColor(colors[0], colors[1], colors[2], colors[3]),
    rectangle->position = irr::core::rect<irr::s32>(pos[0], pos[1], pos[2], pos[3]);
    _rectangles.push_back(rectangle);
}

void indie::Resources::addSlider(const int colors[4], const int pos[4], const int posRectVolume)
{
    for (auto &slider : _sliders)
        if (slider->position.UpperLeftCorner.X == pos[0] &&
            slider->position.UpperLeftCorner.Y == pos[1])
            return;
    auto *slider = new slider_t;
    int posBackRectangle[4] = {
        pos[0],
        pos[1],
        pos[2],
        pos[3]
    };
    int posSlider[4] = {
        posRectVolume - 10,
        pos[1] - 10,
        posRectVolume + 10,
        pos[3] + 10
    };
    int colorsSlider[4] = {
        colors[0],
        colors[1] + 30,
        colors[2] + 30,
        colors[3] + 30
    };

    slider->position = irr::core::rect<irr::s32>(pos[0], pos[1], pos[2], pos[3]);
    slider->colors = irr::video::SColor(colors[0], colors[1], colors[2], colors[3]),
    addRectangle(colors, posBackRectangle);
    addRectangle(colorsSlider, posSlider);
    _sliders.push_back(slider);
}

void indie::Resources::setMusicEngine()
{
    _music = new sf::Music;
}

void indie::Resources::setSoundEngine()
{
    _soundBuffer = new sf::SoundBuffer;
    _sound = new sf::Sound;
}

void indie::Resources::setModelsRotation(int speed)
{
	for (auto &model : _models) {
		model->mesh->setRotation(
			irr::core::vector3df(model->mesh->getRotation().X,
				model->mesh->getRotation().Y + speed,
				model->mesh->getRotation().Z));
	}
}

void indie::Resources::setPowerUPsRotation(float speed)
{
	std::cout <<speed << std::endl;
	for (auto &model : _power_ups) {
		model->mesh->setRotation(
			irr::core::vector3df(model->mesh->getRotation().X,
				model->mesh->getRotation().Y,
				model->mesh->getRotation().Z + speed));
	}
}

void indie::Resources::setCameraTarget(int x, int y, int z)
{
    _camera->setTarget(irr::core::vector3df(static_cast<irr::f32>(x),
        static_cast<irr::f32>(y), static_cast<irr::f32>(z)));
}

void indie::Resources::setCameraPos(int x, int y, int z)
{
    _camera->setPosition(irr::core::vector3df(static_cast<irr::f32>(x),
        static_cast<irr::f32>(y), static_cast<irr::f32>(z)));
}

void indie::Resources::setTextPosition(const wchar_t *str, const int pos[4], const std::string &id)
{
    for (const auto &text : _texts)
        if (text->msg == str && text->id == id) {
            text->position = irr::core::rect<irr::s32>(pos[0], pos[1], pos[2],
                pos[3]);
        }
}

void indie::Resources::setPlayerKeyCode(irr::EKEY_CODE keyCode[2][5])
{
    for (int player = 0; player < 2; player++) {
        for (int code = 0; code < 5; code++) {
            _playerKeyCode[player][code] = keyCode[player][code];
        }
    }
}

void indie::Resources::setBomberToIdle(const char *path, const char *texture, char id)
{
    _models[id]->mesh->setMesh(_smgr->getMesh(path));
    _models[id]->mesh->setMaterialTexture(0, _driver->getTexture(texture));
    _models[id]->mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _models[id]->mesh->setFrameLoop(0, 30);
    _models[id]->mesh->setAnimationSpeed(10);
}

void indie::Resources::setBomberToRun(const char *path, const char *texture, char id)
{
    _models[id]->mesh->setMesh(_smgr->getMesh(path));
    _models[id]->mesh->setMaterialTexture(0, _driver->getTexture(texture));
    _models[id]->mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _models[id]->mesh->setFrameLoop(0, 40);
    _models[id]->mesh->setAnimationSpeed(70);
}

void indie::Resources::playMusic(const char *path, bool loop)
{
    if (!_music->openFromFile(path))
        throw (std::runtime_error("Couldn't load music"));
    _music->play();
    _music->setLoop(loop);
}

void indie::Resources::playSound(const char *path, bool loop)
{
    if (!_soundBuffer->loadFromFile(path))
        throw (std::runtime_error("Couldn't load sound effects"));
    _sound->setBuffer(*_soundBuffer);
    _sound->play();
    _sound->setLoop(loop);
}

void indie::Resources::createMenuCharacter(int pos_x, int pos_y, int pos_z, const char *path, const char *texture, const char id)
{
    auto model = new model_t;
    model->id = id;
    model->texture = texture;
    model->mesh = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh(path));
    if (!model->mesh)
        throw (std::runtime_error("Couldn't load mesh"));
    model->mesh->setMaterialTexture(0, _driver->getTexture(texture));
    model->mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    model->mesh->setFrameLoop(0, 60);
    model->mesh->setAnimationSpeed(30);
    model->mesh->setRotation(irr::core::vector3df(270, 0, 0));
    model->mesh->setPosition(irr::core::vector3df(pos_x, pos_y, pos_z));
    model->mesh->setScale(irr::core::vector3df(5, 5, 5));
    _models.push_back(model);
}

void indie::Resources::changeMenuCharacter(const char *texture, const char id, bool right)
{
    std::vector<std::string> textures = {PATH_BOMBER_TEX, PATH_BOMBER_TEX_PINK,
        PATH_BOMBER_TEX_BLUE, PATH_BOMBER_TEX_YELLOW, PATH_BOMBER_TEX_BLACK};

    int i = 0;
    for (const auto &it : textures) {
        if (it == texture) {
            break;
        }
        i++;
    }
    if (right) {
        if (i >= 4)
            i = -1;
        for (auto &it : _models)
            if (id == it->id && texture == it->texture) {
                auto tmp = new std::string(textures.at(i + 1));
                it->texture = tmp->c_str();
                it->mesh->setMaterialTexture(0,
                    _driver->getTexture(it->texture));
                break;
            }
    } else {
        if (i <= 0)
            i = 5;
        for (auto &it : _models)
            if (id == it->id && texture == it->texture) {
                auto tmp = new std::string(textures.at(i - 1));
                it->texture = tmp->c_str();
                it->mesh->setMaterialTexture(0,
                    _driver->getTexture(it->texture));
                break;
            }
    }
}

void indie::Resources::moveSlider(indie::slider_t *slider, indie::rectangle_t *rectangle)
{
    int posRectangle[4] = {slider->position.UpperLeftCorner.X, slider->position.UpperLeftCorner.Y,
        slider->position.LowerRightCorner.X, slider->position.LowerRightCorner.Y};
    int colorsRectangle[4] = {
        int(rectangle->colors.getAlpha()),
        int(rectangle->colors.getRed()),
        int(rectangle->colors.getGreen()),
        int(rectangle->colors.getBlue())
    };

    if (isClicked(colorsRectangle, posRectangle)) {
        posRectangle[0] = _device->getCursorControl()->getPosition().X - 10;
        posRectangle[1] -= 10;
        posRectangle[2] = _device->getCursorControl()->getPosition().X + 10;
        posRectangle[3] += 10;
        if ((posRectangle[0] + 10 > slider->position.UpperLeftCorner.X) &&
            (posRectangle[2] - 10 < slider->position.LowerRightCorner.X))
            rectangle->position = irr::core::rect<irr::s32>(posRectangle[0],
                posRectangle[1], posRectangle[2], posRectangle[3]);
    }
}

void indie::Resources::moveClouds()
{
    irr::core::vector3df pos;

    for (auto &cloud : _clouds) {
        pos = cloud->mesh->getPosition();
        pos.X -= 1;
        if (pos.X < -270) {
            pos.X = 280;
            pos.Y = std::rand() % 260;
            if (pos.Y > 170)
                pos.Y = (260 - pos.Y) * -1;
        }
        cloud->mesh->setPosition(pos);
    }
}

void indie::Resources::changeColorRectangle(const int *colors, const int *pos)
{
    for (auto &rectangle: _rectangles)
        if (rectangle->position == irr::core::rect<irr::s32>(pos[0], pos[1], pos[2], pos[3]))
            rectangle->colors = irr::video::SColor(colors[0], colors[1], colors[2], colors[3]);
}


bool indie::Resources::isClicked(const irr::core::stringw &textMsg)
{
    for (auto &text : _texts)
        if (text->msg == textMsg)
            if ((text->position.UpperLeftCorner.X <=
                _event->getMouseState().position.X &&
                text->position.LowerRightCorner.X >=
                    _event->getMouseState().position.X) &&
                (text->position.UpperLeftCorner.Y <=
                    _event->getMouseState().position.Y &&
                    text->position.LowerRightCorner.Y >=
                        _event->getMouseState().position.Y) &&
                _event->getMouseState().leftButtonDown)
                return true;
    return false;
}

bool indie::Resources::isClicked(const int color[4], const int pos[4])
{
    for (auto &rectangle : _rectangles)
        if (rectangle->colors.getAlpha() == static_cast<unsigned int>(color[0])
        	&& rectangle->position.UpperLeftCorner.X == pos[0] &&
            rectangle->position.LowerRightCorner.X == pos[2] &&
            rectangle->position.UpperLeftCorner.Y == pos[1] &&
            rectangle->position.LowerRightCorner.Y == pos[3])
            if ((rectangle->position.UpperLeftCorner.X <=
                _event->getMouseState().position.X &&
                rectangle->position.LowerRightCorner.X >=
                    _event->getMouseState().position.X) &&
                (rectangle->position.UpperLeftCorner.Y <=
                    _event->getMouseState().position.Y &&
                    rectangle->position.LowerRightCorner.Y >=
                        _event->getMouseState().position.Y) &&
                _event->getMouseState().leftButtonDown)
                return true;
    return false;
}

bool indie::Resources::isClicked(const std::string &path, bool isImage, const std::string &id)
{
	if (isImage) {
		for (const auto &image : _images)
			if (image->path == path && image->id == id)
				if ((image->position.first <=
					_event->getMouseState().position.X &&
					(image->position.first + image->size.LowerRightCorner.X) >=
						_event->getMouseState().position.X) &&
					(image->position.second <=
						_event->getMouseState().position.Y &&
						(image->position.second + image->size.LowerRightCorner.Y) >=
							_event->getMouseState().position.Y) &&
					_event->getMouseState().leftButtonDown) {
					return true;
				}
	}
	return false;
}

bool indie::Resources::isMouseOver(const irr::core::stringw &textMsg)
{
    for (auto &text : _texts)
        if (text->msg == textMsg) {
            if ((text->position.UpperLeftCorner.X <=
                _event->getMouseState().position.X &&
                text->position.LowerRightCorner.X >=
                    _event->getMouseState().position.X) &&
                (text->position.UpperLeftCorner.Y <=
                    _event->getMouseState().position.Y &&
                    text->position.LowerRightCorner.Y >=
                        _event->getMouseState().position.Y))
                return true;
        }
    return false;
}

void indie::Resources::mouseShadeEffect(const irr::core::stringw &textMsg,
    int percentageShade)
{
    for (auto &text : _texts)
        if (text->msg == textMsg)
            _driver->draw2DRectangle(
                irr::video::SColor(255 * percentageShade / 100, 0, 0, 0),
                text->position);
}

indie::Options *indie::Resources::options() const
{
    return _options;
}

void indie::Resources::restartDevice(bool fullscreen, bool synchroVert)
{
    irr::core::vector2d<irr::s32> cursorPos = _device->getCursorControl()->getPosition();
    _device->closeDevice();
    _device->drop();
    _device = irr::createDevice(irr::video::EDT_OPENGL,
        irr::core::dimension2d<irr::u32>(WINDOW_SIZE_X, WINDOW_SIZE_Y),
        16, fullscreen, false, synchroVert, _event);
    _device->getCursorControl()->setPosition(cursorPos);
    if (!_device)
        throw (std::runtime_error("Error : Device creation failed"));
    _driver = _device->getVideoDriver();
    if (!_driver)
        throw (std::runtime_error("Error : Driver could not be loaded"));
    _smgr = _device->getSceneManager();
    if (!_smgr)
        throw (std::runtime_error("Error : Scene Manager could not be loaded"));
    _guienv = _device->getGUIEnvironment();
    if (!_guienv)
        throw (std::runtime_error("Error : GUI Environment could not be loaded"));
    _device->setWindowCaption(WINDOW_NAME);
    _driver->getMaterial2D().TextureLayer[0].AnisotropicFilter = 16;
    _driver->getMaterial2D().AntiAliasing = irr::video::EAAM_FULL_BASIC;
    height = _driver->getScreenSize().Height;
    width = _driver->getScreenSize().Width;
    for (auto &rectangle : _rectangles) {
        int colors[4] = {
            int(rectangle->colors.getAlpha()),
            int(rectangle->colors.getRed()),
            int(rectangle->colors.getGreen()),
            int(rectangle->colors.getBlue())
        };
        int pos[4] = {
            rectangle->position.UpperLeftCorner.X,
            rectangle->position.UpperLeftCorner.Y,
            rectangle->position.LowerRightCorner.X,
            rectangle->position.LowerRightCorner.Y
        };
        deleteRectangle(colors, pos);
        addRectangle(colors, pos);
    }
    for (auto &text : _texts) {
        int pos[4] = {text->position.UpperLeftCorner.X, text->position.UpperLeftCorner.Y,
            text->position.LowerRightCorner.X, text->position.LowerRightCorner.Y};
        bool isButton = text->isButton;
        const wchar_t *tmp = text->msg.c_str();
        deleteText(text->msg.c_str());
        addText(tmp, pos, isButton, text->pathFont);
    }
    for (auto &slider : _sliders) {
        int colors[4] = {
            int(slider->colors.getAlpha()),
            int(slider->colors.getRed()),
            int(slider->colors.getGreen()),
            int(slider->colors.getBlue())
        };
        int pos[4] = {
            slider->position.UpperLeftCorner.X,
            slider->position.UpperLeftCorner.Y,
            slider->position.LowerRightCorner.X,
            slider->position.LowerRightCorner.Y
        };
        destroySliders();
        addSlider(colors, pos, pos[2]);
    }
    for (auto &image : _images) {
        int pos[4] = {
            image->size.UpperLeftCorner.X,
            image->size.UpperLeftCorner.Y,
            image->size.LowerRightCorner.X,
            image->size.LowerRightCorner.Y
        };
        std::string path = image->path;
        deleteImage(std::string(image->path.substr(path.rfind('/') + 1, path.size())));
        addImage(path, pos);
    }
}

irr::EKEY_CODE indie::Resources::isDown()
{
    for (int hex = 0x0D; hex <= (irr::EKEY_CODE)0xA4; hex++) {
        if (_event->isKeyDown((irr::EKEY_CODE)hex)) {
            for (int player = 0; player < 2; player++) {
                for (int code = 0; code < 5; code++) {
                    if (_playerKeyCode[player][code] == (irr::EKEY_CODE)hex)
                        return (irr::EKEY_CODE)0xFE;
                }
            }
            return ((irr::EKEY_CODE)hex);
        }
    }
    return (irr::EKEY_CODE)0xFF;
}

std::vector<irr::EKEY_CODE> indie::Resources::getPlayerControls()
{
    return (_playerKeyCodeVector);
}

void indie::Resources::shaderInject(const std::string &path)
{
	irr::video::IGPUProgrammingServices *gpu = _driver->getGPUProgrammingServices();
	_mtlShader = irr::video::EMT_SOLID;

	ShaderCallBack* callback = new ShaderCallBack;
	callback->setDevice(_device);

	_mtlShader = gpu->addHighLevelShaderMaterialFromFiles(
		"./resources/shaders/shaders.vert", "main", irr::video::EVST_VS_1_1,
		path.c_str(), "main", irr::video::EPST_PS_1_1,
		callback, irr::video::EMT_SOLID , 0, irr::video::EGSL_DEFAULT);

	if (_mtlShader == -1)
		_mtlShader = 0;
	callback->drop();
}