#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <irrlicht.h>
#include "spdlog/spdlog.h"

using namespace irr;
using namespace core;

class CelestialBody{

private:

    std::string name;
    float mass;
    float polarRay;
    float equatorialRay;
    float inclination;

    vector3df* pos;
    vector3df* vel;

    static nlohmann::json jsonBodies;

public:
    CelestialBody(std::string name);
    CelestialBody(std::string name, float mass, float polarRay, float equatorialRay, float inclination);
    CelestialBody(std::string name, float mass, float ray);

    std::string getName() const;
    void setName(std::string value);

    float getMass() const;
    void setMass(float value);

    float getPolarRay() const;
    void setPolarRay(float value);

    float getEquatorialRay() const;
    void setEquatorialRay(float value);

    float getInclination() const;
    void setInclination(float value);

    vector3df* getPos() const;
    void setPos(vector3df *value);

    vector3df* getVel() const;
    void setVel(vector3df *value);

    float getMechanicalEnergy();
    void action(float elapsed_sec);

    static void writeJson(std::vector<CelestialBody*> bodies, std::string fileName);
    static std::vector<CelestialBody*> readJson(std::string fileName);

    static std::vector<CelestialBody*> bodies;
};

#endif
