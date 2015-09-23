#ifndef CHALLENGE_TEXTURE_H
#define CHALLENGE_TEXTURE_H

#include <Game/NonCopyable.hpp>
#include <Graphics/Image.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Texture : public NonCopyable
{
public:
    Texture();
    Texture(const Image& _image, GLint _minMagFilter = GL_LINEAR, GLint wrapMode = GL_CLAMP_TO_EDGE);
#if 1
    bool loadFromFile(const char* _filename, GLint _minMagFilter = GL_LINEAR, GLint _wrapMode = GL_CLAMP_TO_EDGE);
    bool loadFromImage(const Image& _image, GLint _minMagFilter = GL_LINEAR, GLint _wrapMode = GL_CLAMP_TO_EDGE);
#else
    bool loadFromFile(const char* _filename, GLint _minMagFilter = GL_NEAREST, GLint _wrapMode = GL_REPEAT);
    bool loadFromImage(const Image& _image, GLint _minMagFilter = GL_NEAREST, GLint _wrapMode = GL_REPEAT);
#endif
	
    virtual ~Texture();

    void bind(GLuint _position);

    inline GLuint getObject()	const { return( m_object)	; }
    inline GLfloat getWidth()	const { return( m_width)	; }
    inline GLfloat getHeight()	const { return( m_height)	; }

private:
    GLuint   m_object;
    GLsizei  m_width;
    GLsizei  m_height;
};
#endif // !CHALLENGE_TEXTURE_H
