#include "BreakoutApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Gizmos.h>
#include <glm/ext.hpp>
BreakoutApp::BreakoutApp() {

}

BreakoutApp::~BreakoutApp() {

}

bool BreakoutApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	//increase the 2d line count to maximize the number of items we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);
	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	return true;
}

void BreakoutApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void BreakoutApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();
	//create colors array
	static const glm::vec4 colors[] = { glm::vec4(1,0,0,1), glm::vec4(0,1,0,1), glm::vec4(0.8f,0,0.5,1) };
	//sets size and dimensions for grid
	static const int rows = 5;
	static const int columns = 10;
	static const int hSpace = 1;
	static const int vSpace = 1;
	//Sets extents for each AABB for collision
	static const glm::vec2 scrExtents(100, 50);
	static const glm::vec2 boxExtents(7, 3);
	//sets the start pos for the grid
	static const glm::vec2 startPos(-(columns >> 1)*((boxExtents.x * 2) +vSpace) + boxExtents.x +(vSpace/ 2.0f),scrExtents.y - ((boxExtents.y*2) +hSpace));
	//Add AABB's to list of items to be drawn on for the grid
	glm::vec2 pos;
	for (int y = 0; y < rows; y++)
	{
		pos = glm::vec2(startPos.x, startPos.y - (y * ((boxExtents.y * 2) + hSpace)));
		for (int x = 0; x < columns; x++)
		{
			aie::Gizmos::add2DAABBFilled(pos, boxExtents, colors[y]);
			pos.x += (boxExtents.x * 2) + vSpace;
		}
	}
	//add ball to scene
	aie::Gizmos::add2DCircle(glm::vec2(0, -35), 3, 12, glm::vec4(1, 1, 0, 1));

	//add paddle to scene
	aie::Gizmos::add2DAABBFilled(glm::vec2(0, -40), glm::vec2(12, 2), glm::vec4(1, 0, 1, 1));
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void BreakoutApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}