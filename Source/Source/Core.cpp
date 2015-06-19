#define OPENGL_MAJOR_VERSION	2
#define OPENGL_MINOR_VERSION	1

#define GLEW_STATIC


//OpenGl
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW\glfw3.h>

//
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

// Challenge
#include <Source\Common.h>
#include <Source\ShaderProgram.h>
#include <Source\Image.h>
#include <Source\Texture.h>

#include <Source\Clock.h>
#include <Source\TickCounter.h>
#include <Source\Camera.h>
#include <Source\Vertex.h>

#include <Math\Transform.h>
#include <Math\Math.h>

namespace Challenge
{
GLFWwindow* window;

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
	Challenge::Transform transform;
};

GLOBAL int WindowWidth = 1024;
GLOBAL int WindowHeight = 768;
GLOBAL const float TIME_STEP = 1.0f / 60.0f;

GLOBAL Challenge::ShaderProgram* g_defaultShader;
GLOBAL ModelAsset g_sprite;
GLOBAL std::vector<ModelInstance> g_instances;
GLOBAL Challenge::Camera g_camera;

namespace Core
{

INTERNAL void glfwHints()
{
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
}

INTERNAL void resizeCallback(GLFWwindow* _window, int _width, int _height)
{
	WindowWidth = _width;
	WindowHeight = _height;
}

//TODO(mate): Inputhandler class
INTERNAL void HandleInput(GLFWwindow* _window, bool* _running)
{
	if (glfwWindowShouldClose(_window) ||
		 glfwGetKey(_window, GLFW_KEY_ESCAPE))
	{

		*_running = false;
	}
}

INTERNAL void loadShaders()
{
	g_defaultShader = new Challenge::ShaderProgram();
	if (!g_defaultShader->attachShaderfromFile(Challenge::ShaderType::Vertex,
															"Source\\Shaders\\vert.glsl"))
	{
		throw std::runtime_error(g_defaultShader->getErrorLog());
	}
	if (!g_defaultShader->attachShaderfromFile(Challenge::ShaderType::Fragment, 
															"Source\\Shaders\\frag.glsl")) 
	{
		throw std::runtime_error(g_defaultShader->getErrorLog());
	}

	g_defaultShader->bindAttributeLocation(0, "a_position");
	g_defaultShader->bindAttributeLocation(1, "a_color");
	g_defaultShader->bindAttributeLocation(2, "a_texCoord");

	if (!g_defaultShader->Link()) {
		throw std::runtime_error(g_defaultShader->getErrorLog());
	}
}

INTERNAL void loadSpriteAsset()
{
	Challenge::Vertex vertices[] =
	{
		//  x      y		z				r     g     b     a			 s     t
		{ { -0.5f, -0.5f, 0.0f },{ { 0xFF, 0xFF, 0xFF, 0xFF } },{ 0.0f, 0.0f } }, 
		{ { +0.5f, -0.5f, 0.0f },{ { 0xFF, 0xFF, 0xFF, 0xFF } },{ 1.0f, 0.0f } }, 
		{ { +0.5f, +0.5f, 0.0f },{ { 0xFF, 0xFF, 0xFF, 0xFF } },{ 1.0f, 1.0f } },	
		{ { -0.5f, +0.5f, 0.0f },{ { 0xFF, 0xFF, 0xFF, 0xFF } },{ 0.0f, 1.0f } }, 
	};

	glGenBuffers(1, &g_sprite.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, g_sprite.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	std::uint32_t indices[] = { 0,1,2,2,3,0 };

	glGenBuffers(1, &g_sprite.ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_sprite.ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
					 sizeof(indices), 
					 indices, 
					 GL_STATIC_DRAW);

	g_sprite.shaders = g_defaultShader;
	g_sprite.texture = new Challenge::Texture();
	g_sprite.texture->loadFromFile("Source\\Textures\\sh.jpg");

	g_sprite.drawType = GL_TRIANGLES;
	g_sprite.drawCount = 6;
}

INTERNAL void loadInstance()
{

	Challenge::Transform parent;

	ModelInstance a;
	a.asset = &g_sprite;
	a.transform.position = { 0, 0, 0 };
	//a.transform.scale = { 3, 3, 3 };
	a.transform.orientation = Challenge::angleAxis(Challenge::Degree(0), { 0, 0, 1 });
	g_instances.push_back(a);

	ModelInstance b;
	b.asset = &g_sprite;
	b.transform.position = { 0.5f, 0, 0.5f };
	b.transform.orientation = Challenge::angleAxis(Challenge::Degree(90), { 0, 1, 0 });
	b.transform.orientation = Challenge::angleAxis(Challenge::Radian_( Challenge::Constants::PI /2 ), { 0, 1, 0 });
	g_instances.push_back(b);

	ModelInstance c;
	c.asset = &g_sprite;
	c.transform.position = { -0.5f, 0, 0.5f };
	c.transform.orientation = Challenge::angleAxis(Challenge::Degree(90), { 0, 1, 0 });
	g_instances.push_back(c);

	ModelInstance d;
	d.asset = &g_sprite;
	d.transform.position = { 0, 0, 1 };
	d.transform.orientation = Challenge::angleAxis(Challenge::Degree(0), { 0, 1, 0 });
	g_instances.push_back(d);

	ModelInstance e;
	e.asset = &g_sprite;
	e.transform.position = { 0, 0.5f, 0.5f };
	e.transform.orientation = Challenge::angleAxis(Challenge::Degree(90), { 1, 0, 0 });
	g_instances.push_back(e);

	ModelInstance f;
	f.asset = &g_sprite;
	f.transform.position = {0, -0.5f, 0.5f };
	f.transform.orientation = Challenge::angleAxis(Challenge::Degree(90), { 1, 0, 0 });
	g_instances.push_back(f);
}

INTERNAL void update(float _dt)
{
	using namespace Challenge;
/*
	g_instances[0].transform.orientation =
		angleAxis(Degree(120) * _dt, { 0, 1, 0 }) *
		g_instances[0].transform.orientation;
*/

	Vector3& camPos = g_camera.transform.position;

	camPos.x = 5.0f * std::cos(glfwGetTime());
	camPos.y = 5.0f * std::sin(glfwGetTime());
	camPos.z = 5.0f * std::sin(glfwGetTime());

	
	g_camera.lookAt({ 0,0,0 });
	g_camera.projectiontype = ProjectionType::Perspective;
	g_camera.fieldofView = Degree(50.0f);
	g_camera.viewportaspectRatio = (float)WindowWidth / (float)WindowHeight;
}

INTERNAL void renderInstance(const ModelInstance& _instance)
{
	_instance.asset->shaders->setUniform("u_camera", g_camera.getMatrix());
	_instance.asset->shaders->setUniform("u_transform",_instance.transform);
	_instance.asset->shaders->setUniform("u_tex", 0);

	_instance.asset->texture->bind(0);

	glBindBuffer(GL_ARRAY_BUFFER, g_sprite.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_sprite.ibo);

	glEnableVertexAttribArray(0); // vertPosition
	glEnableVertexAttribArray(1); // vertColor
	glEnableVertexAttribArray(2); // vertTexCoord

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 
								 sizeof(Challenge::Vertex), (const GLvoid*)(0));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 
								 sizeof(Challenge::Vector3), 
								 (const GLvoid*)(sizeof(Challenge::Vector3)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Challenge::Vertex), 
								 (const GLvoid*)(sizeof(Challenge::Vector3) + 
								 sizeof(Challenge::Color)));

	glDrawElements(_instance.asset->drawType, 
						_instance.asset->drawCount, 
						GL_UNSIGNED_INT, 
						nullptr);
	glDisableVertexAttribArray(0); // vertPosition
	glDisableVertexAttribArray(1); // vertColor
	glDisableVertexAttribArray(2); // vertTexCoord
}

INTERNAL void render(GLFWwindow* _window)
{
	glViewport(0, 0, WindowWidth, WindowHeight);

	glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Challenge::ShaderProgram* currentShaders = nullptr;

	for (const auto& inst : g_instances){
		if (inst.asset->shaders != currentShaders){
			currentShaders = inst.asset->shaders;
			currentShaders->Use();
		}
		renderInstance(inst);
	}
	if (currentShaders) {
		currentShaders->stopUsing();
	}
	glfwSwapBuffers(_window);
	glfwPollEvents();
}

void init()
{
	// Initialize GLFW
	assert(glfwInit() && "Failed to init GLFW\n");

	window = glfwCreateWindow(WindowWidth, WindowHeight,
									  "Challenge",
									  NULL, NULL);

	assert(window != NULL && "Failed to open GLFW window");
	glfwSetWindowSizeCallback(window, resizeCallback);
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	assert(!glewInit() && "Failed to init GLEW");

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwHints();

	loadShaders();
	loadSpriteAsset();
	loadInstance();
}


void run()
{
	bool running = true;
	//Note(mate): FPS
	Challenge::TickCounter tc;
	Challenge::Clock frameClock;

	double accumulator = 0;
	double prevTime = glfwGetTime();

	std::stringstream titleStream;

	while (running)
	{
		double currentTime = glfwGetTime();
		double dt = currentTime - prevTime;
		prevTime = currentTime;
		accumulator += dt;

		HandleInput(window, &running);

		while (accumulator >= TIME_STEP)
		{
			accumulator -= TIME_STEP;
			update(TIME_STEP);
		}

		//Note(mate): FPS
		if (tc.update(0.5))
		{
			titleStream.str("");
			titleStream.clear();
			titleStream << "Challenge - " << 1000.0 / tc.getTickRate() << " ms";
			glfwSetWindowTitle(window, titleStream.str().c_str());
		}

		render(window);

		// Frame Limiter
		while (frameClock.getElapsedTime() < 1.0 / 240.0)
		{
		}
		frameClock.restart();
	}
}

void exit()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow* getWindow() { return window; }


} // !namespace Core
} // !namespace Challenge
