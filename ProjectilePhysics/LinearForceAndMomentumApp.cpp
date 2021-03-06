#include "LinearForceAndMomentumApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Gizmos.h>
#include "PhysicsScene.h"
#include "Sphere.h"
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
	physicsScene = new PhysicsScene();
	physicsScene->setGravity(glm::vec2(0,-10));
	physicsScene->setTimeStep(0.5f);
	setupContinuousDemo({ -40,0 }, { 20, 25 }, 10);
	Sphere* ball1 = new Sphere(glm::vec2(-40, 0), glm::vec2(20, 25), 1.0f, 1, glm::vec4(1, 0, 0, 1));
	//Sphere* ball2 = new Sphere(glm::vec2(10, 0), glm::vec2(-5, 0), 4.0f, 4, glm::vec4(0, 1, 0, 1));
	physicsScene->addActor(ball1);
	//physicsScene->addActor(ball2);*/
	return true;
}

void LinearForceAndMomentumApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void LinearForceAndMomentumApp::setupContinuousDemo(glm::vec2 startPos, glm::vec2 velocity, float gravity)
{
	float t = 0;
	float tStep = 0.5f;
	float radius = 1.0f;
	int segments = 12;
	glm::vec4 color = glm::vec4(1, 1, 0, 1);
	int x;
	int y;
	while (t <= 5)
	{
		x = startPos.x + velocity.x*t;
		y = startPos.y + velocity.y *t + .5f * -gravity * t*t;
		aie::Gizmos::add2DCircle(glm::vec2(x, y), radius, segments, color);
		t += tStep;
	}
}

void LinearForceAndMomentumApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	//aie::Gizmos::clear();

	physicsScene->update(deltaTime);
	physicsScene->updateGizmos();
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