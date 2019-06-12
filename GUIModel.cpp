/*
 * GUIModel.cpp
 *
 *  Created on: 7 giu 2019
 *      Author: daniele
 */

#include "GUIModel.h"
#include <sstream>
using namespace std;

GUIModel::GUIModel(IGUIEnvironment *env) {

	this->env = env;

	IGUISkin* skin = env->getSkin();
	IGUIFont* font = env->getFont("media/fontcourier.bmp");
	if (font)
		skin->setFont(font);

	skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);

}

void GUIModel::update(){
	env->clear();
	env->addStaticText(L"Mechanical Energy:", rect<s32>(1920 - 300, 0, 1920, 20), false);
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	float height = 0;


	for(CelestialBody* body : CelestialBody::bodies){
		height += 30;
		std::ostringstream streamObj;
		//Add double to stream
		streamObj << body->getName() << ": " << body->getMechanicalEnergy();
		// Get string from output string stream
		std::string strObj = streamObj.str();
		wstring data = converter.from_bytes(strObj);
		env->addStaticText(data.data() , rect<s32>(1920 - 300, 0 + height, 1920, 20 + height), false);
	}

}

GUIModel::~GUIModel() {
	// TODO Auto-generated destructor stub
}

