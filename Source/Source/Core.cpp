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
#include <Source\ShaderProgram.h>
#include <Source\Image.h>
#include <Source\Texture.h>
#include <Source\Common.hpp>
#include <Source\Clock.hpp>
#include <Source\TickCounter.hpp>
#include <Math\Vector2.hpp>
#include <Math\Vector3.hpp>
#include <Math\Matrix.hpp>
#include <Source\Color.hpp>

#include <sstream>

//const value
const int WindowWidth = 1024;
const int WindowHeight = 768;

using namespace glm;

struct Vertex
{
	Challenge::Vector2 position;
	Challenge::Color color;
	Challenge::Vector2 texCoord;
};

 INTERNAL void 
glfwHints()
 {
	 	glfwDefaultWindowHints();
	 	glfwWindowHint(GLFW_VERSION_MAJOR, 2);
	 	glfwWindowHint(GLFW_VERSION_MINOR, 1);
	 	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
 }

INTERNAL void
Render()
{
	glEnableVertexAttribArray(0); // vertPosition
	glEnableVertexAttribArray(1); // vertColor
	glEnableVertexAttribArray(2); // vertTexCoord

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(0));
	glVertexAttribPointer(1,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof(Vertex), (const GLvoid*)(sizeof(Challenge::Vector2)));
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(const GLvoid*)(sizeof(Challenge::Vector2) + sizeof(Challenge::Color)));
	
glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(0); // vertPosition
	glDisableVertexAttribArray(1); // vertColor
	glDisableVertexAttribArray(2); // vertTexCoord
}


//TODO(mate): keyboardhandler
INTERNAL void
HandleInput(GLFWwindow* _window, bool* _running)
{
	if (glfwWindowShouldClose(_window) ||
		glfwGetKey(_window, GLFW_KEY_ESCAPE))
	{
		*_running = false;
	}
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

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwHints();

//Note(mate): rect
	Vertex vertices[] =
	{
		//  x      y     r     g     b     a       s     t
		{ { +0.5f, +0.5f },{ { 255, 255, 255, 255 } },{ 1.0f, 0.0f } }, // Vertex 0
		{ { -0.5f, +0.5f },{ { 255, 0, 0, 255 } },{ 0.0f, 0.0f } },     // Vertex 1
		{ { +0.5f, -0.5f },{ { 0, 255, 0, 255 } },{ 1.0f, 1.0f } },     // Vertex 2
		{ { -0.5f, -0.5f },{ { 0, 0, 255, 255 } },{ 0.0f, 1.0f } },     // Vertex 3
	};

//Note(mate): Vertex Buffer Object
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
							 sizeof(vertices),
							 vertices,
							 GL_STATIC_DRAW);

//Note(mate): shader
	Challenge::ShaderProgram shaderProgram;

	if (!shaderProgram.attachShaderfromFile(Challenge::ShaderType::Vertex, "Source\\Shaders\\vert.glsl")) {
		throw std::runtime_error(shaderProgram.getErrorLog());
	}

	if (!shaderProgram.attachShaderfromFile(Challenge::ShaderType::Fragment, "Source\\Shaders\\frag.glsl")) {
		throw std::runtime_error(shaderProgram.getErrorLog());
	}

	shaderProgram.bindAttributeLocation(0, "vertPosition");
	shaderProgram.bindAttributeLocation(1, "vertColor");
	shaderProgram.bindAttributeLocation(2, "vertTexCoord");

	if (!shaderProgram.Link()) {
		throw std::runtime_error(shaderProgram.getErrorLog());}
	shaderProgram.Use();

//Note(mate): texture
	Challenge::Texture tex;
	tex.loadFromFile("Source\\Textures\\test.jpg");
	tex.bind(0);
	shaderProgram.setUniform("uniTex", 0);

//Note(mate):  013,31:19

	bool running = true;

//Note(mate): FPS
	Challenge::TickCounter tc;
	Challenge::Clock frameClock;

	while (running)
	{
		//Note(mate): resize window
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Use();
		{
			float TAU = 6.28318530918f;
			using namespace Challenge;
			Matrix4 model = rotate(Radian(glfwGetTime() / 0.6f), { 0,1,0 });
			Matrix4 view = lookAt({1.0f,2.0f,4.0f }, {0.0f,0.0f,0.0f }, {0.0f,1.0f,0.0f });
			Matrix4 proj = perspective(Degree(50.0f), width/height, 0.1f, 100.0f);

			Matrix4 camera = proj * view;

			shaderProgram.setUniform("uniCamera", camera);
			shaderProgram.setUniform("uniModel", model);
		}

		Render();
		shaderProgram.stopUsing();

		//Note(mate): FPS
		if (tc.update(0.5))
		{
			std::stringstream ss;
			ss << "Challenge  |  " << tc.getTickRate() << " FPS";
			glfwSetWindowTitle(window, ss.str().c_str());
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

		HandleInput(window, &running);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return( EXIT_SUCCESS);
}

