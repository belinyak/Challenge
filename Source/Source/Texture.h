#ifndef CHALLENGE_TEXTURE_H
#define CHALLENGE_TEXTURE_H

#include <Source/NonCopyable.hpp>
#include <Source/Image.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace Challenge
{
class Texture : public NonCopyable
{
public:
	Texture();
	Texture(const Image& _image, GLint _minMagFilter = GL_LINEAR, GLint wrapMode = GL_CLAMP_TO_EDGE);

	bool loadFromFile(const char* _filename, GLint _minMagFilter = GL_LINEAR, GLint _wrapMode = GL_CLAMP_TO_EDGE);
	bool loadFromImage(const Image& _image, GLint _minMagFilter = GL_LINEAR, GLint _wrapMode = GL_CLAMP_TO_EDGE);

	virtual ~Texture();

	void bind(GLuint _position);

	inline GLuint getObject()	const { return( m_object)	; }
	inline GLfloat getWidth()	const { return( m_width)	; }
	inline GLfloat getHeight()	const { return( m_height)	; }

private:
	GLuint m_object;
	GLfloat m_width;
	GLfloat m_height;
};
} //namespace Challenge
#endif // !CHALLENGE_TEXTURE_H
