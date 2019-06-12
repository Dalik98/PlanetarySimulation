/*
 * BodyModel.h
 *
 *  Created on: 28 mag 2019
 *      Author: daniele
 */

#ifndef BODYMODELS_H_
#define BODYMODELS_H_

#include <vector>
#include "irrlicht.h"
#include <iostream>
#include "CelestialBody.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace std;

class BodyModels {

private:
	vector<ISceneNode*> nodes;

public:
	BodyModels(ISceneManager *manager);
	vector<CelestialBody*> getBodies();
	void update();
	float scale(float val);
	virtual ~BodyModels();
};

#endif /* BODYMODELS_H_ */
