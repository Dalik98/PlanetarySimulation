/*
 * Application.cpp
 *
 *  Created on: 28 mag 2019
 *      Author: daniele
 */

#include "Application.h"

bool Application::activePhysics = false;

void printVector(vector3df vec, std::string name, std::string logname = "physics"){

	spdlog::get(logname)->info("{3} =  X: {0}, Y: {1}, Z: {2}", vec.X, vec.Y, vec.Z, name);

}

Application::Application() {

	device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(WIDTH, HEIGHT), true);
	device->maximizeWindow();
	device->setWindowCaption(L"My test");
	device->setResizable(true);
	device->getCursorControl()->setVisible(false);
	device->setEventReceiver(this);
	ISceneManager *manager = device->getSceneManager();
	IGUIEnvironment *env = device->getGUIEnvironment();
	gui = new GUIModel(env);
	models = new BodyModels(manager);

	/*Set the camera move with WASD*/
	SKeyMap keyMap[8];
	keyMap[0].Action = EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = KEY_KEY_W;

	keyMap[1].Action = EKA_MOVE_BACKWARD;
	keyMap[1].KeyCode = KEY_KEY_S;

	keyMap[2].Action = EKA_STRAFE_LEFT;
	keyMap[2].KeyCode = KEY_KEY_A;

	keyMap[3].Action = EKA_STRAFE_RIGHT;
	keyMap[3].KeyCode = KEY_KEY_D;

	for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
	            KeyIsDown[i] = false;

	cam = manager->addCameraSceneNodeFPS(0, 100, 1500, -1, keyMap, 4);
	cam->setFarValue(4E6);

	cam->setPosition(vector3df(0, 1575, 12400));
	cam->bindTargetAndRotation(false);

	begin = clock();
}

void Application::run(){

	IVideoDriver *driver = device->getVideoDriver();
	ISceneManager *scene = device->getSceneManager();
	IGUIEnvironment *guiEnv = device->getGUIEnvironment();
	ISceneManager *manager = device->getSceneManager();

	auto fut = async(physicsCycle);

	begin = clock();

	while(device->run() && device){

		if (device->isWindowActive()){
			//INPUT
			if(IsKeyDown(irr::KEY_KEY_I)){
				activePhysics = true;
				begin = clock();
			}else if(IsKeyDown(irr::KEY_KEY_O)){
				activePhysics = false;
			}else if(IsKeyDown(irr::KEY_KEY_1)){
					manager->setActiveCamera(cam);
					device->getCursorControl()->setVisible(false);
			}else if(IsKeyDown(irr::KEY_KEY_2)){
					ICameraSceneNode* cam2 = manager->addCameraSceneNode(0,cam->getPosition(), cam->getTarget());
					cam2->setFarValue(cam->getFarValue());
					device->getCursorControl()->setVisible(true);
			}

			//UPDATE
			driver->beginScene(true, true, SColor(0,255,255,255));
			gui->update();
			models->update();

			//DRAW
			scene->drawAll();
			guiEnv->drawAll();
			driver->endScene();
			printVector(cam->getPosition(), "Position Camera", "camera");
		}
	}
	device->drop();

}

void Application::physicsCycle(){

	while(!Application::activePhysics){}
	auto begin = clock();
	while(1){
		clock_t end = clock();
		f32 elapsed_secs = f32(end - begin) / CLOCKS_PER_SEC;

		elapsed_secs *= 1E8;

		for(CelestialBody *body : CelestialBody::bodies){

			body->action(elapsed_secs);
		}
		while(!Application::activePhysics){}
		begin = clock();

	}


}

// This is the one method that we have to implement
bool Application::OnEvent(const SEvent& event){
	// Remember whether each key is down or up
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	return false;
}

// This is used to check whether a key is being held down
bool Application::IsKeyDown(EKEY_CODE keyCode) const{
	return KeyIsDown[keyCode];
}

Application::~Application() {

}

