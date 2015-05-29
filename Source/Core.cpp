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

#include "ShaderProgram.h"
#include "Image.h"
#include "Texture.h"

//const valuse
const int WindowWidth = 1024;
const int WindowHeight = 768;

using namespace glm;


void glfwHints()
{
	glfwWindowHint(GLFW_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_VERSION_MINOR, 1);
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
	shaderProgram.attachShaderfromFile(Challenge::ShaderType::Vertex, "Shaders\\vert.glsl");
	shaderProgram.attachShaderfromFile(Challenge::ShaderType::Fragment, "Shaders\\frag.glsl");
	shaderProgram.bindAttributeLocation(0, "vertPosition");
	shaderProgram.bindAttributeLocation(1, "vertColor");
	shaderProgram.bindAttributeLocation(2, "vertTexCoord");
	shaderProgram.Link();
	shaderProgram.Use();

//rect end

	Challenge::Texture tex;
	tex.loadFromFile("Textures\\test.jpg");
	tex.bind(0);

	shaderProgram.setUniform("uniTex", 0);


	bool running = true;


	while (running)
	{
		//Note(mate): resize window
		{
			int width, height;
			glfwGetWindowSize(window, &width, &height);
			glViewport(0, 0, width, height);
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw Things
		{
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


		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwWindowShouldClose(window) ||
			glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			running = false;
		}
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return EXIT_SUCCESS;
}

