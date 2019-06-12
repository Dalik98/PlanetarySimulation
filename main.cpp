/*
 * main.cpp
 *
 *  Created on: 28 mag 2019
 *      Author: daniele
 */
#include <vector>
#include <iostream>

#include "Application.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "CelestialBody.h"

using namespace std;

void setupLog();
bool compareInterval(CelestialBody *body1, CelestialBody *body2);

int main(){

	setupLog();

	CelestialBody::bodies = CelestialBody::readJson("SolarSystem.json");
	sort(CelestialBody::bodies.begin(), CelestialBody::bodies.end(), compareInterval);

	Application app;
	app.run();

}

bool compareInterval(CelestialBody *body1, CelestialBody *body2)
{
    return (body1->getPos()->getLength() < body2->getPos()->getLength());
}

void setupLog(){

	spdlog::stdout_color_mt("physics");
	spdlog::stdout_color_mt("internalPhysics");
	spdlog::stdout_color_mt("camera");
	spdlog::get("physics")->set_level(spdlog::level::off);
	spdlog::get("internalPhysics")->set_level(spdlog::level::off);
	spdlog::get("camera")->set_level(spdlog::level::off);

}

