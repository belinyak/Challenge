#define OPENGL_MAJOR_VERSION	2
#define OPENGL_MINOR_VERSION	1

// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW\glfw3.h>

// Include GLM
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <iostream>

// Challenge
#include "ShaderProgram.h"
#include "Image.h"
#include "Texture.h"
#include "Common.hpp"

#include <sstream>

//const valuse
const int WindowWidth = 1024;
const int WindowHeight = 768;

using namespace glm;

class Clock
{
public:
	Clock()
	{
	}

	double getElapsedTime() const
	{
		return (glfwGetTime() - m_startTime);
	}

	double restart() 
	{
		double now = glfwGetTime();
		double elapsed = now - m_startTime;
		m_startTime = now;

		return elapsed;
	}

private:
		double m_startTime = glfwGetTime();
};

class TickCounter
{
public:
	bool update(double _frequency)
	{
		bool reset = false;
		if (m_clock.getElapsedTime() >= _frequency)
		{
			m_tickRate = m_tick / _frequency;
			m_tick = 0;
			reset = true;
			m_clock.restart();
		}
		m_tick++;

		return reset;
	}
	inline std::size_t getTickRate() const {
		return m_tickRate;
	}

private:
	std::size_t m_tick;
	std::size_t m_tickRate;
	Clock m_clock;
};


INTERNAL void
HandleInput(GLFWwindow* _window, bool* _running)
{
	if (glfwWindowShouldClose(_window) ||
		glfwGetKey(_window, GLFW_KEY_ESCAPE))
	{
		*_running = false;
	}
}

INTERNAL void
Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(0); // vertPosition
	glEnableVertexAttribArray(1); // vertColor
	glEnableVertexAttribArray(2); // vertTexCoord

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const GLvoid*)(2 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const GLvoid*)(5 * sizeof(float)));

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(0); // vertPosition
	glDisableVertexAttribArray(1); // vertColor
	glDisableVertexAttribArray(2); // vertTexCoord
}

INTERNAL void
glfwHint()
{
	glfwWindowHint(GLFW_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_VERSION_MINOR, 1);
	glfwSwapInterval(1);
}

int
main(void)
{
	GLFWwindow* window;

	// Initialize GLFW
	assert(glfwInit() && "Failed to init GLFW\n");

	window = glfwCreateWindow(WindowWidth, WindowHeight,
							  "Challenge",
							  NULL, NULL);

	assert(window != NULL && "Failed to open GLFW window");

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	assert(!glewInit() && "Failed to init GLEW");

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwHint();

	//rect
	float vertices[] =
	{
		//      x      y     r     g     b     s     t
			+0.5f, +0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // Vertex 0
			-0.5f, +0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Vertex 1
			+0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Vertex 2
			-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // Vertex 3
	};

	//Vertex Buffer Object
	GLuint vbo; // Vertex Buffer Object
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
				 sizeof(vertices),
				 vertices,
				 GL_STATIC_DRAW);

	//Note(mate): shader
	Challenge::ShaderProgram shaderProgram;

	if (!shaderProgram.attachShaderfromFile(Challenge::ShaderType::Vertex, "Shaders\\vert.glsl")) {
		throw std::runtime_error(shaderProgram.getErrorLog());
	}

	if (!shaderProgram.attachShaderfromFile(Challenge::ShaderType::Fragment, "Shaders\\frag.glsl")) {
		throw std::runtime_error(shaderProgram.getErrorLog());
	}

	shaderProgram.bindAttributeLocation(0, "vertPosition");
	shaderProgram.bindAttributeLocation(1, "vertColor");
	shaderProgram.bindAttributeLocation(2, "vertTexCoord");

	if (!shaderProgram.Link()) {
		throw std::runtime_error(shaderProgram.getErrorLog());
	}
	shaderProgram.Use();

	//rect end

	Challenge::Texture tex;
	tex.loadFromFile("Textures\\test.jpg");
	tex.bind(0);

	shaderProgram.setUniform("uniTex", 0);

	bool running = true;

	//Note(mate): FPS
	TickCounter tc;

	while (running)
	{
		//Note(mate): resize window
		{
			int width, height;
			glfwGetWindowSize(window, &width, &height);
			glViewport(0, 0, width, height);
		}

		//Note(mate): FPS
		if (tc.update(0.5))
		{
			std::stringstream ss;
			ss << "Challenge  |  " << tc.getTickRate() << " FPS";
			glfwSetWindowTitle(window, ss.str().c_str());
		}

		Render();

		glfwSwapBuffers(window);
		glfwPollEvents();

		HandleInput(window, &running);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return EXIT_SUCCESS;
}

