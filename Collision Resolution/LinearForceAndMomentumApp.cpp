#include "LinearForceAndMomentumApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Gizmos.h>
#include "PhysicsScene.h"
#include "Sphere.h"
#include "Plane.h"
LinearForceAndMomentumApp::LinearForceAndMomentumApp() {

}

LinearForceAndMomentumApp::~LinearForceAndMomentumApp() {

}


bool LinearForceAndMomentumApp::startup() {
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();
	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0,-10));
	m_physicsScene->setTimeStep(0.01f);

	// create a balls to print on the screen
	Sphere* movingBall = new Sphere({ 10,20 }, { 18,15 }, 1.0f, 4.0f, glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
	m_physicsScene->addActor(movingBall);

	//Redish
	Sphere* topBall = new Sphere(glm::vec2(60.0f, 30.0f), glm::vec2(0.0f, 0.0f), 1.0f, 4.0f, glm::vec4(1.0f, 0.3f, 0.0f, 1.0f));
	m_physicsScene->addActor(topBall);

	//Orange
	Sphere* secondBall = new Sphere(glm::vec2(60.0f, 20.0f), glm::vec2(0.0f, 0.0f), 1.0f, 4.0f, glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));
	m_physicsScene->addActor(secondBall);

	//White
	Sphere* thirdBall = new Sphere(glm::vec2(60.0f, 10.0f), glm::vec2(0.0f, 0.0f), 1.0f, 4.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	m_physicsScene->addActor(thirdBall);

	//Pink
	Sphere* forthBall = new Sphere(glm::vec2(60.0f, 0.0f), glm::vec2(0.0f, 0.0f), 1.0f, 4.0f, glm::vec4(1.0f, 0.0f, 0.5f, 1.0f));
	m_physicsScene->addActor(forthBall);

	//Purplish
	Sphere* fifthBall = new Sphere(glm::vec2(60.0f, -10.0f), glm::vec2(0.0f, 0.0f), 1.0f, 4.0f, glm::vec4(0.7f, 0.0f, 0.5f, 1.0f));
	m_physicsScene->addActor(fifthBall);

	//box
	Plane* floor = new Plane(glm::normalize(glm::vec2(0.0f, -20.0f)), 40.0f);
	m_physicsScene->addActor(floor);

	Plane* rightWall = new Plane(glm::normalize(glm::vec2(80.0f, 0.0f)), 80.0f);
	m_physicsScene->addActor(rightWall);

	Plane* leftWall = new Plane(glm::normalize(glm::vec2(-80.0f, 0.0f)), 80.0f);
	m_physicsScene->addActor(leftWall);

	Plane* roof = new Plane(glm::normalize(glm::vec2(0.0f, 20.0f)), 40.0f);
	m_physicsScene->addActor(roof);
	return true;
}

void LinearForceAndMomentumApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void LinearForceAndMomentumApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void LinearForceAndMomentumApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100, -1.0f, 1.0f));
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}