#include <Source/Texture.h>
#include <Source/Common.hpp>
#include <assert.h>

namespace Challenge
{

//TODO(mate): srgb??
INTERNAL GLenum
getInternalFormat(Image::Format _format, bool _srgb)
{
	switch (_format)
	{
	case Image::Format_Greyscale:
		return( GL_LUMINANCE);
	case Image::Format_GreyscaleAlpha:
		return( GL_LUMINANCE_ALPHA);
	case Image::Format_RGB:
		return( _srgb ? GL_SRGB : GL_RGB);
	case Image::Format_RGBA:
		return( _srgb ? GL_SRGB_ALPHA : GL_RGBA);
	}
}

Texture::Texture()
	: m_object(0)
	, m_width(0)
	, m_height(0)
{
	glGenTextures(1, &m_object);
}

Texture::Texture(const Image& _image,
				 GLint _minMagFilter,
				 GLint _wrapMode)
	: m_object(0)
	, m_width(_image.getWidth())
	, m_height(_image.getHeight())
{
	glGenTextures(1, &m_object);

	assert(loadFromImage(_image, _minMagFilter, _wrapMode) && "Texture::Texture()");
}

bool 
Texture::loadFromFile(const char* _filename, 
					  GLint _minMagFilter, 
					  GLint _wrapMode )
{
	Image image;
	if (!image.loadFromFile(_filename)){
		return(false);
	}
	image.flipVertically();

	return(loadFromImage(image, _minMagFilter, _wrapMode));
}

bool 
Texture::loadFromImage(const Image& _image, 
						GLint _minMagFilter, 
						GLint wrapMode )
{
	if (_image.getFormat() <=0 || _image.getFormat() > 4 ){
		return(false);
	}
	m_width = (GLfloat)_image.getWidth();
	m_height = (GLfloat)_image.getHeight();

	glGenTextures(1, &m_object);
	glBindTexture(GL_TEXTURE_2D, m_object);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minMagFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _minMagFilter);

	glTexImage2D(GL_TEXTURE_2D, 0, getInternalFormat(_image.getFormat(), true),
				 (GLsizei)m_width, (GLsizei)m_height,
				 0,
				 getInternalFormat(_image.getFormat(), false),
				 GL_UNSIGNED_BYTE,
				 _image.getPixelPtr());

	glBindTexture(GL_TEXTURE_2D, 0);
	return(true);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_object);
}

void 
Texture::bind(GLuint _position)
{
	//TODO(mate): error message
	assert(_position < 31 && "Texture::bin");
	if (_position > 31) {
		_position = 31;
	}

	glActiveTexture(GL_TEXTURE0 + _position );
	glClientActiveTexture(GL_TEXTURE0 + _position);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, (m_object ? m_object : 0));
	glDisable(GL_TEXTURE_2D);
}
} //namespace Challenge