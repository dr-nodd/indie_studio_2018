CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(OOP_indie_studio_2018)
SET(EXECUTABLE_NAME bomberman)
SET(CMAKE_CXX_STANDARD 14)

INCLUDE_DIRECTORIES(
		include
        src/resources
        src/scenes
)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

FIND_PACKAGE(SFML 2 REQUIRED audio)

IF(WIN32)
	FIND_PACKAGE(IRRLICHT)
ENDIF(WIN32)

IF(UNIX)
	INCLUDE_DIRECTORIES(/usr/include/irrlicht
						/usr/include/SFML)
	LINK_DIRECTORIES(/lib/irrlicht-1.8.4/lib/linux)
	LINK_LIBRARIES(Irrlicht GL GLU X11 Xxf86vm sfml-audio)
ENDIF(UNIX)

IF(NOT SFML_FOUND)
	MESSAGE(FATAL_ERROR "SFML not found")
ENDIF()

INCLUDE_DIRECTORIES(${Irrlicht_INCLUDE_DIRS} ${SFML_INCLUDE_DIR})

ADD_EXECUTABLE(${EXECUTABLE_NAME}
        include/Settings.hpp
        src/Main.cpp
        src/resources/Resources.cpp
        src/resources/Resources.hpp
        src/resources/Options.cpp
        src/resources/Options.hpp
        src/resources/EventReceiver.cpp
        src/resources/EventReceiver.hpp
		src/resources/ShaderCallBack.hpp
		src/resources/Bomb.hpp
		src/resources/Bomb.cpp
		src/resources/Player.hpp
		src/resources/Player.cpp
		src/resources/CPU.cpp
		src/resources/CPU.hpp
        src/resources/Save.hpp
        src/scenes/CharacterSelect.cpp
		src/scenes/CharacterSelect.hpp
        src/scenes/Map.cpp
        src/scenes/Map.hpp
        src/scenes/IScene.hpp
        src/scenes/Menu.cpp
        src/scenes/Menu.hpp
        src/scenes/Game.cpp
        src/scenes/Game.hpp
        src/scenes/OptionsScene.cpp
        src/scenes/OptionsScene.hpp
		src/scenes/Victory.cpp
		src/scenes/Victory.hpp
		src/scenes/StageSelect.cpp
		src/scenes/StageSelect.hpp)

TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${Irrlicht_LIBRARIES})