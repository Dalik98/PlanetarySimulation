#include <iostream>
using namespace std;
#include "CelestialBody.h"

nlohmann::json CelestialBody::jsonBodies;
vector<CelestialBody*> CelestialBody::bodies;

CelestialBody::CelestialBody(std::string name){
    this->name = name;
    mass = 0;
    polarRay = 0;
    equatorialRay = 0;
    inclination = 0;
    this->pos = new vector3df();
    this->vel = new vector3df();
}

CelestialBody::CelestialBody(std::string name, float mass, float polarRay, float equatorialRay, float inclination){
    this->name = name;
    this->mass = mass;
    this->polarRay = polarRay;
    this->equatorialRay = equatorialRay;
    this->inclination = inclination;
    this->pos = new vector3df();
    this->vel = new vector3df();
}

CelestialBody::CelestialBody(std::string name, float mass, float ray){
    this->name = name;
    this->mass = mass;
    this->polarRay = ray;
    this->equatorialRay = ray;
    this->inclination = 0;
    this->pos = new vector3df();
    this->vel = new vector3df();
}

vector3df* CelestialBody::getVel() const
{
    return vel;
}

void CelestialBody::setVel(vector3df* value)
{
    vel = value;
}

float CelestialBody::getMass() const
{
    return mass;
}

void CelestialBody::setMass(float value)
{
    mass = value;
}

float CelestialBody::getPolarRay() const
{
    return polarRay;
}

void CelestialBody::setPolarRay(float value)
{
    polarRay = value;
}

std::string CelestialBody::getName() const
{
    return name;
}

void CelestialBody::setName(std::string value)
{
    name = value;
}

float CelestialBody::getEquatorialRay() const
{
    return equatorialRay;
}

void CelestialBody::setEquatorialRay(float value)
{
    equatorialRay = value;
}

float CelestialBody::getInclination() const
{
    return inclination;
}

void CelestialBody::setInclination(float value)
{
    inclination = value;
}

vector3df* CelestialBody::getPos() const
{
    return pos;
}

void CelestialBody::setPos(vector3df *value)
{
    pos = value;
}

float CelestialBody::getMechanicalEnergy(){

	float kinetic = 1./2 * getMass() * pow(getVel()->getLength(), 2);

	float potential = 0;
	for(CelestialBody *othersBody : CelestialBody::bodies){
		if(othersBody == this ) continue;

		float distance = getPos()->getDistanceFrom(*othersBody->getPos());

		float potRel = 6.67408E-11 * othersBody->getMass() * getMass() / distance;
		potential += potRel;
	}

	return kinetic - potential;
}

void CelestialBody::action(float elapsed_secs){

	spdlog::get("physics")->info("Name: {0}", getName());

	vector3df acc(0, 0, 0);
	for(CelestialBody *othersBody : CelestialBody::bodies){
		if(othersBody == this) continue;

		spdlog::get("internalPhysics")->info("SottoPianeta: {0}", othersBody->getName());

		float distance = getPos()->getDistanceFrom(*othersBody->getPos());

		vector3df joint = (*getPos() - *othersBody->getPos()).normalize() * -1;

		vector3df accRel = 6.67408E-11 * othersBody->getMass() / pow(distance,2) * joint;

		acc += accRel;
	}
	*getVel() = acc * elapsed_secs + *getVel();
	*getPos() = *getVel() * elapsed_secs  + *getPos();

}

//statics methods
void CelestialBody::writeJson(vector<CelestialBody*> bodies, std::string fileName)
{

    for(CelestialBody* body : bodies){

        CelestialBody::jsonBodies[body->getName()]["name"] = body->getName();
        CelestialBody::jsonBodies[body->getName()]["mass"] = body->getMass();
        CelestialBody::jsonBodies[body->getName()]["inclination"] = body->getInclination();
        CelestialBody::jsonBodies[body->getName()]["equatorialRay"] = body->getEquatorialRay();
        CelestialBody::jsonBodies[body->getName()]["polarRay"] = body->getPolarRay();
        CelestialBody::jsonBodies[body->getName()]["xpos"] = body->getPos()->X;
        CelestialBody::jsonBodies[body->getName()]["ypos"] = body->getPos()->Y;
        CelestialBody::jsonBodies[body->getName()]["zpos"] = body->getPos()->Z;

        CelestialBody::jsonBodies[body->getName()]["xvel"] = body->getVel()->X;
        CelestialBody::jsonBodies[body->getName()]["yvel"] = body->getVel()->Y;
        CelestialBody::jsonBodies[body->getName()]["zvel"] = body->getVel()->Z;

    }

    std::string jsonText = CelestialBody::jsonBodies.dump(4);

    ofstream myfile;
    myfile.open(fileName);
    myfile << jsonText;
    myfile.close();
}



vector<CelestialBody *> CelestialBody::readJson(std::string fileName)
{

    std::string jsonText, temp;

    ifstream inFile;
    inFile.open(fileName);

    if(inFile.is_open())
        while(inFile >> temp){

            jsonText += temp;
        }
    else{
        return vector<CelestialBody*>();
    }

    CelestialBody::jsonBodies = nlohmann::json::parse(jsonText);

    vector<CelestialBody*> bodies;
    for(nlohmann::json test : CelestialBody::jsonBodies){
        CelestialBody *body = new CelestialBody("empty");
        body->setName(test["name"]);
        cout << body->getName() << endl;
        body->setMass(test["mass"]);
        body->setInclination(test["inclination"]);
        body->setEquatorialRay(test["equatorialRay"]);
        body->setPolarRay(test["polarRay"]);
        vector3df* pos = new vector3df(test["posx"], test["posy"], test["posz"]);
        body->setPos(pos);
        vector3df* vel = new vector3df(test["velx"], test["vely"], test["velz"]);
        body->setVel(vel);
        bodies.push_back(body);
    }

    return bodies;
}
