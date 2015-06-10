#define OPENGL_MAJOR_VERSION	2
#define OPENGL_MINOR_VERSION	1

#define GLEW_STATIC

//OpenGl
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>

//std
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

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
#include <Math\Constants.hpp>
#include <Math\Quaternion.hpp>

//const value
int WindowWidth = 1024;
int WindowHeight = 768;

using namespace glm;

struct Vertex
{
	Challenge::Vector2 position;
	Challenge::Color color;
	Challenge::Vector2 texCoord;
};

struct ModelAsset
{
	Challenge::ShaderProgram* shaders;
	Challenge::Texture* texture;

	GLuint vbo;
	GLuint ibo;

	GLenum drawType;
	GLint drawCount;
};

struct ModelInstance
{
	ModelAsset* asset;
	Challenge::Matrix4 transform;
};

GLOBAL Challenge::ShaderProgram* g_defaultShader;
GLOBAL ModelAsset g_sprite;
GLOBAL std::vector<ModelInstance> g_instances;
GLOBAL Challenge::Matrix4 g_cameraMatrix;

INTERNAL void
glfwHints()
{
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
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

INTERNAL void
loadShaders()
{
	g_defaultShader = new Challenge::ShaderProgram();
	if (!g_defaultShader->attachShaderfromFile(Challenge::ShaderType::Vertex, "Source\\Shaders\\vert.glsl")) {
		throw std::runtime_error(g_defaultShader->getErrorLog());
	}
	if (!g_defaultShader->attachShaderfromFile(Challenge::ShaderType::Fragment, "Source\\Shaders\\frag.glsl")) {
		throw std::runtime_error(g_defaultShader->getErrorLog());
	}

	g_defaultShader->bindAttributeLocation(0, "a_position");
	g_defaultShader->bindAttributeLocation(1, "a_color");
	g_defaultShader->bindAttributeLocation(2, "a_texCoord");

	if (!g_defaultShader->Link()) {
		throw std::runtime_error(g_defaultShader->getErrorLog());
	}
}

INTERNAL void
loadSpriteAsset()
{
	Vertex vertices[] =
	{
		//  x      y     r     g     b     a       s     t
		{ { -0.5f, -0.5f },{ { 0xFF, 0xFF, 0xFF, 0xFF } },{ 0.0f, 0.0f } }, // Vertex 3
		{ { +0.5f, -0.5f },{ { 0xFF, 0xFF, 0xFF, 0xFF } },{ 1.0f, 0.0f } }, // Vertex 2
		{ { +0.5f, +0.5f },{ { 0xFF, 0xFF, 0xFF, 0xFF } },{ 1.0f, 1.0f } },	// Vertex 0
		{ { -0.5f, +0.5f },{ { 0xFF, 0xFF, 0xFF, 0xFF } },{ 0.0f, 1.0f } }, // Vertex 1
	};

	glGenBuffers(1, &g_sprite.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, g_sprite.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	std::uint32_t indices[] = { 0,1,2,2,3,0 };

	glGenBuffers(1, &g_sprite.ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_sprite.ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	g_sprite.shaders = g_defaultShader;
	g_sprite.texture = new Challenge::Texture();
	g_sprite.texture->loadFromFile("Source\\Textures\\sh.jpg");

	g_sprite.drawType = GL_TRIANGLES;
	g_sprite.drawCount = 6;
}

INTERNAL void
loadInstance()
{

	ModelInstance inst1;
	inst1.asset = &g_sprite;
	inst1.transform = Challenge::translate({ 1,0,0 });
	g_instances.push_back(inst1);

	ModelInstance inst2;
	inst2.asset = &g_sprite;
	inst2.transform = Challenge::translate({ 0,1.2f,1 });
	g_instances.push_back(inst2);

	ModelInstance inst3;
	inst3.asset = &g_sprite;
	inst3.transform = Challenge::translate({ 0,0,2 });
	g_instances.push_back(inst3);

}

INTERNAL void
renderInstance(const ModelInstance& _instance)
{
	_instance.asset->shaders->setUniform("u_camera", g_cameraMatrix);
	_instance.asset->shaders->setUniform("u_model", _instance.transform);
	_instance.asset->shaders->setUniform("u_tex", 0);

	_instance.asset->texture->bind(0);
	glBindBuffer(GL_ARRAY_BUFFER, g_sprite.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_sprite.ibo);

	glEnableVertexAttribArray(0); // vertPosition
	glEnableVertexAttribArray(1); // vertColor
	glEnableVertexAttribArray(2); // vertTexCoord

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(0));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (const GLvoid*)(sizeof(Challenge::Vector2)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(Challenge::Vector2) + sizeof(Challenge::Color)));

	glDrawElements(_instance.asset->drawType, _instance.asset->drawCount, GL_UNSIGNED_INT, nullptr);
	glDisableVertexAttribArray(0); // vertPosition
	glDisableVertexAttribArray(1); // vertColor
	glDisableVertexAttribArray(2); // vertTexCoord
}

INTERNAL void
render()
{
	Challenge::ShaderProgram* currentShaders = nullptr;

	for (const auto& inst : g_instances)
	{
		if (inst.asset->shaders != currentShaders)
		{
			currentShaders = inst.asset->shaders;
			currentShaders->Use();
		}
		renderInstance(inst);
	}

	if (currentShaders) {
		currentShaders->stopUsing();
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

	loadShaders();
	loadSpriteAsset();
	loadInstance();

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
		WindowWidth = width;
		WindowHeight = height;

		{
			using namespace Challenge;
			Matrix4 model = rotate(Degree(glfwGetTime() * 60.0f), { 0,1,0 });
			Matrix4 view = lookAt({ 1.0f,2.0f,4.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,1.0f,0.0f });
			Matrix4 proj = perspective(Degree(50.0f), WindowWidth / WindowHeight, 0.1f, 100.0f);

			g_cameraMatrix = proj * view;
		}

		glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		render();

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
	return(EXIT_SUCCESS);
}

