#include <Source/Image.h>

#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION

#include <stb\stb_image.h>

#include <assert.h>
#include <iostream>

namespace Challenge
{

Image::Image()
	: m_format(Format(0))
	, m_width(0)
	, m_height(0)
	, m_pixels(nullptr)
{}

Image::Image(u32 _width, u32 _height,
			 Format _format,
			 const u8* _pixels)
	: m_format(Format(0))
	, m_width(0)
	, m_height(0)
	, m_pixels(nullptr)
{
	loadFromMemory(_width, _height, _format, _pixels);
}

Image::Image(const Image& _other)
	: m_format(Format(0))
	, m_width(0)
	, m_height(0)
	, m_pixels(nullptr)
{
	loadFromMemory(_other.m_width, _other.m_height, _other.m_format, _other.m_pixels);
}

Image& Image::operator=(const Image& _other)
{
	loadFromMemory(_other.m_width, _other.m_height, _other.m_format, _other.m_pixels);
	return( *this );
}

Image::~Image()
{
	if (m_pixels)
	{
		delete[] m_pixels;
	}
}

bool
Image::loadFromFile(const char* _fileName)
{
	int width, height, format;
	u8* pixels = stbi_load(_fileName,
							  &width, &height,
							  &format,
							  0);

	if (!pixels)
	{
		std::cerr << stbi_failure_reason() << std::endl;
		return(false);
	}

//	assert(pixels && "Image::loadFromFile");

	loadFromMemory(width, height,
			  (Format)format,
			  pixels);
	stbi_image_free(pixels);

	if (m_pixels)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}

u8*
Image::getPixel(u32 _column, u32 _row) const
{
	if (_column >= m_width ||
		_row >= m_height)
	{
		return(nullptr);
	}
	return(m_pixels + (_row * m_width + _column)*m_format);
}

void
Image::setPixel(u32 _column, u32 _row,
				const u32* _pixel) const
{
	if (_column >= m_width ||
		_row >= m_height)
	{
		return;
	}

	u8* pixel = getPixel(_column, _row);
	std::memcpy(pixel, _pixel, m_format);

}

void 
Image::flipVertically()
{
	std::size_t pitch = m_width * m_format;
	u32 halfRows = m_height / 2;
	u8* rowBuffer = new u8[pitch];

	for (u32 i = 0; i < halfRows; i++)
	{
		u8* row = m_pixels + (i * m_width) * m_format;
		u8* oppositeRow = m_pixels + ((m_height - i - 1) * m_width) * m_format;

		std::memcpy(rowBuffer, row, pitch);
		std::memcpy(row, oppositeRow, pitch);
		std::memcpy(oppositeRow, rowBuffer, pitch);
	}

	delete[] rowBuffer;
}

bool
Image::loadFromMemory(u32 _width, u32 _height,
					  Format _format,
					  const u8* _pixels)
{

	assert(_width != 0 && "Image::setPixels -> width=0 ");
	assert(_height != 0 && "Image::setPixels -> height=0");
	assert((_format >= 0 && _format <= 4) && "Image::setPixels-> invalid format");

	m_width = _width;
	m_height = _height;
	m_format = _format;

	size_t imageSize = _width * _height * _format;

	if (m_pixels) {
		delete[] m_pixels;
	}
	m_pixels = new u8[imageSize];

	if (_pixels != nullptr) {
		std::memcpy(m_pixels, _pixels, imageSize);
	}
	return(true);
}
} //namespace Challenge
