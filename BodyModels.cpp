/*
 * BodyModel.cpp
 *
 *  Created on: 28 mag 2019
 *      Author: daniele
 */

#include "BodyModels.h"

BodyModels::BodyModels(ISceneManager *manager) {

	for(CelestialBody* body : CelestialBody::bodies){
		float scaleEquRay = scale(body->getEquatorialRay());
		ISceneNode* sphere =  manager->addSphereSceneNode(scaleEquRay, 64);
		sphere->setPosition(vector3df(0, 0, 0));
		nodes.push_back(sphere);

	}

	update();
}


void BodyModels::update(){

	for(int i = 0; i < int(CelestialBody::bodies.size()); i++){
		//originally 1.43225436838E-7
		vector3df vec;
		if(CelestialBody::bodies[i]->getPos()->getLength() > 0.001)
			vec = *CelestialBody::bodies[i]->getPos() * pow(4.6E11 / CelestialBody::bodies[i]->getPos()->getLength(), 1./2) * 0.3E-5;
		else
			vec = *CelestialBody::bodies[i]->getPos() * 0.3E-5;
		nodes[i]->setPosition(vector3df(vec.X, vec.Y, vec.Z));
	}
}

float BodyModels::scale(float val){

	float temp = abs(val);
	temp = pow(temp, 1/1.5) / 5;

	return temp;
}

BodyModels::~BodyModels() {

}
