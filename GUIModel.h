/*
 * GUIModel.h
 *
 *  Created on: 7 giu 2019
 *      Author: daniele
 */

#ifndef GUIMODEL_H_
#define GUIMODEL_H_

#include "irrlicht.h"
#include <string>
#include <locale>
#include <codecvt>
#include <string>

#include "CelestialBody.h"
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class GUIModel {

private:
	IGUIEnvironment *env;

public:
	GUIModel(IGUIEnvironment *env);
	void update();
	virtual ~GUIModel();
};

#endif /* GUIMODEL_H_ */
