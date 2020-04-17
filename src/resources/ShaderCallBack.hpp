/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** description
*/

#ifndef OOP_INDIE_STUDIO_2018_SHADERCALLBACK_HPP
#define OOP_INDIE_STUDIO_2018_SHADERCALLBACK_HPP

#include <irrlicht.h>

class ShaderCallBack : public irr::video::IShaderConstantSetCallBack
{
	public:
	virtual void OnSetConstants(irr::video::IMaterialRendererServices *services, irr::s32 userData)
	{
		irr::video::IVideoDriver *driver = services->getVideoDriver();

        irr::core::matrix4 world = driver->getTransform(irr::video::ETS_WORLD);
        world = world.getTransposed();
        services->setVertexShaderConstant("worldMatrix", world.pointer(), 16);

		irr::core::matrix4 invWorld = driver->getTransform(irr::video::ETS_WORLD);
		invWorld.makeInverse();
		services->setVertexShaderConstant("invertedWorldMatrix", invWorld.pointer(), 16);

		irr::core::matrix4 worldViewProj = driver->getTransform(irr::video::ETS_PROJECTION);
		worldViewProj *= driver->getTransform(irr::video::ETS_VIEW);
		worldViewProj *= driver->getTransform(irr::video::ETS_WORLD);
		services->setVertexShaderConstant("worldViewProjectionMatrix", worldViewProj.pointer(), 16);

		irr::core::vector3df pos = _device->getSceneManager()->getActiveCamera()->getAbsolutePosition();
		services->setVertexShaderConstant("lightPos", reinterpret_cast<irr::f32 *>(&pos), 3);

		irr::video::SColorf col(1.0f, 1.0f, 1.0f, 0.1f);
		services->setVertexShaderConstant("lightColor", reinterpret_cast<irr::f32 *>(&col), 4);

		irr::core::vector2df screenDim = {float(driver->getScreenSize().Width), float(driver->getScreenSize().Height)};
		services->setVertexShaderConstant("screenDimensions", reinterpret_cast<irr::f32 *>(&screenDim), 2);

		irr::s32 textureLayerID = 0;
		services->setPixelShaderConstant("colorSampler", &textureLayerID, 1);

        irr::s32 depthLayerID = 1;
        services->setPixelShaderConstant("depthSampler", &depthLayerID, 1);
	}

	void setDevice(irr::IrrlichtDevice *device)
	{
		_device = device;
	}

	private:
	irr::IrrlichtDevice *_device = 0;
};

#endif //OOP_INDIE_STUDIO_2018_SHADERCALLBACK_HPP
