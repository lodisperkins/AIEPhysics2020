#include "FixedTimeStepApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Gizmos.h>
#include "PhysicsScene.h"
FixedTimeStepApp::FixedTimeStepApp() {

}

FixedTimeStepApp::~FixedTimeStepApp() {

}

bool FixedTimeStepApp::startup() {
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();
	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	physicsScene = new PhysicsScene();
	physicsScene->setTimeStep(0.01f);
	return true;
}

void FixedTimeStepApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void FixedTimeStepApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	physicsScene->update(deltaTime);
	physicsScene->updateGizmos();
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void FixedTimeStepApp::draw() {

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