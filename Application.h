/*
 * Application.h
 *
 *  Created on: 28 mag 2019
 *      Author: daniele
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <vector>
#include <iostream>
#include "irrlicht.h"

#include "GUIModel.h"
#include "BodyModels.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <future>
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace std;

#define WIDTH 1920
#define HEIGHT 1080

class Application : public IEventReceiver{

private:
	GUIModel *gui;
	IrrlichtDevice *device;
	ICameraSceneNode *cam;
	BodyModels *models;
	clock_t begin;
	static bool activePhysics;
	bool KeyIsDown[KEY_KEY_CODES_COUNT];

	static void physicsCycle();
public:
	Application();
	void setupUI(IGUIEnvironment *env);
	virtual bool OnEvent(const SEvent& event);
	virtual bool IsKeyDown(EKEY_CODE keyCode) const;
	void run();
	virtual ~Application();
};

#endif /* APPLICATION_H_ */
