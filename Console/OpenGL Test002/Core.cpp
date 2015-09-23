#include <iostream>
#include <map>
#include <string>
#include <vector>

#define GLEW_STATIC
#include <GLEW/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Shader.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include <STB/stb_truetype.h>

const GLuint WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
const float LINE_WIDTH = WINDOW_WIDTH/2;
const float LINE_HEIGTH = 20;

GLuint VAO, VBO;

struct Message;
float RenderText(Shader *shader,Message test, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
void RenderText2(Shader *shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

void Hints()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

/// Holds all state information relevant to a character as loaded using FreeType
struct Character 
{
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;    // Horizontal offset to advance to next glyph
};

struct Font
{
	const unsigned int FontWidth;
	const unsigned int FontHeight;

	FT_Library ft;
	FT_Face face;
	std::map<GLchar, Character> Characters;

	void Debug(Character _Character)
	{
		std::cout << "TextureID " << _Character.TextureID << '\t';
		std::cout << "Size: " << _Character.Size.x << ";" << _Character.Size.y << '\t';
		std::cout << "Bearing: " << _Character.Bearing.x << ";" << _Character.Bearing.y << '\t';
		std::cout << "Advance: " << _Character.Advance;
	}

	Font(const char* _FontPath, const unsigned int _FontWidth, const unsigned int _FontHeight)
		: FontWidth(_FontWidth)
		, FontHeight(_FontHeight)
	{
		if (FT_Init_FreeType(&ft))
		{
			//TODO(mate): error handling    
		}
		if (FT_New_Face(ft, _FontPath, 0, &face))
		{
			//TODO(mate): error handling
		}
		
		SetSize(FontWidth,FontHeight);
	}

	void StoreCharacter(GLubyte _Character)
	{
		if (FT_Load_Char(face, _Character, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			return;
		}

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
			);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, Character>(_Character, character));


		//Debug(character);
	}

	void SetSize(unsigned int _Width, unsigned int _Height)
	{
		FT_Set_Pixel_Sizes(face, _Width, _Height);
	}

	void LoadCharacters(unsigned int _Count)
	{
		for (GLubyte i = 0; i < _Count; i++)
		{
			StoreCharacter(i);
		}
	}

	~Font()
	{
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}
};

Font* g_TestFont;
Shader* shader;
std::string g_Command;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if ( (action == GLFW_PRESS) &&
		( key <= 90 && key >= 65 ) )
	{
		g_Command += (char)(key + 32);
	}
	if (key == GLFW_KEY_ENTER)
	{
		g_Command.clear();
	}
}

std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> value;
	std::stringstream ss(s);
	std::string word;
	while (std::getline(ss, word, delim))
	{
		value.push_back(word);
	}
	return(value);
}

struct Message
{
	std::vector<std::string> lines;
	
	Message(std::string message, float scale, float x)
	{
		float width = 0;
		Character ch;
		std::string line;
		std::vector<std::string> words = split(message, ' ');
		for (int i = 0; i < words.size(); i++)
		{
			words[i].append(" ");

			for (int j = 0; j < words[i].length(); j++)
			{
				ch = g_TestFont->Characters[words[i][j]];
				width += (ch.Advance >> 6) * scale - (ch.Bearing.x) * scale;
			}
			if (x + width >= LINE_WIDTH)
			{
				lines.push_back(line);
				line.clear();
				width = 0;
			}
			line.append(words[i]);

			if (i == words.size() - 1)
			{
				lines.push_back(line);
			}
			x += (ch.Advance >> 6) * scale;
		}
	}
};

int main()
{
#pragma region MyRegion
	if (glfwInit() == GL_FALSE)
	{
		std::cout << "failed to init GLFW\n";
	}
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "ConsoleTest", nullptr, nullptr); // Windowed
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
	

	Hints();

	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	GLenum err = glewInit();
	if (err != GLEW_OK) 
	{
		std::cout << "Failed to init GLEW\n" << glewGetErrorString(err); 
	}

	// Define the viewport dimensions
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	// Set OpenGL options
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetKeyCallback(window,key_callback);

	// Compile and setup the shader
	shader = new Shader("Shaders\\TextFT.vs", "Shaders\\TextFT.frag");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WINDOW_WIDTH), 0.0f, static_cast<GLfloat>(WINDOW_HEIGHT));
		//glm::vec3 centerVec = glm::vec3(0.0f, 0.0f, 2.0f);
		//glm::vec3 eyeVec = glm::vec3(0.0f, 0.0f, 0.0f);
		//glm::vec3 upVec = glm::vec3(0.0f, 1.0f, 0.0f);
		//glm::mat4 camera = glm::lookAt(centerVec, eyeVec, upVec);
	shader->Use();
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
#pragma endregion

	const char* FontPath = "c:\\windows\\Fonts\\Kalinga.ttf";
	g_TestFont = new Font(FontPath,0,14);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	g_TestFont->LoadCharacters(255);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Configure VAO/VBO for texture quads

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	std::string message1 = "Appends a copy of the source string to the destination string. The terminating null character in destination is overwritten by the first character of source, and a null character is included at the end of the new string formed by the concatenation of both in destination.";
	std::string message2 = "This extension will highlight all occurrences of a selected with a mouse or keyboard word in the current document and display a glyph on the left margin.";
	std::string message3 = "You have many options here. First, you could turn the map around and instead associate strings with integers, rather than integers with strings. Based on your use case, this seems like what you wanted to do in the first place. If you did that, then you could just use the square brackets operator to look up the associated value:";
	
	std::vector<Message> Messages;

	Messages.insert(Messages.begin(), Message(message1, 1, 1));
	Messages.insert(Messages.begin(), Message(message2, 1, 1));
	Messages.insert(Messages.begin(), Message(message3, 1, 1));
	
	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
		float offsety = 0;
		for (int i = 0; i < Messages.size(); i++)
		{
			if (i != 0)
			{
				offsety += (Messages[i-1].lines.size() + 1)*LINE_HEIGTH;
			}
			RenderText(shader, Messages[i], 1.f, WINDOW_HEIGHT - offsety , 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		RenderText2(shader, g_Command, 1.0f, 1.f, 1.f, glm::vec3(1.0f, 0.0f, 0.0f));

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}

float RenderText(Shader* shader, Message test, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	float width = 0;
	
	shader->Use();
	glUniform3f(glGetUniformLocation(shader->Program, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	for (unsigned int  i = 0; i < test.lines.size(); i++)
	{
		x = 5;
		y -= LINE_HEIGTH * scale;
		for (int  j = 0; j < test.lines[i].length(); j++)
		{
			Character ch = g_TestFont->Characters[test.lines[i][j]];
			width += (ch.Advance >> 6) * scale - (ch.Bearing.x) * scale;

			GLfloat xpos = x + ch.Bearing.x * scale;
			GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

			GLfloat w = ch.Size.x * scale;
			GLfloat h = ch.Size.y * scale;
			// Update VBO for each character
			GLfloat vertices[6][4] = 
			{
				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos,     ypos,       0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 1.0 },

				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 0.0 }
			};
			// Render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			// Update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// Render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.Advance >> 6) * scale ; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		}
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	return(width);
}


void RenderText2(Shader *shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	// Activate corresponding render state	
	shader->Use();
	glUniform3f(glGetUniformLocation(shader->Program, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = g_TestFont->Characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


