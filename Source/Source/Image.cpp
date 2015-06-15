#include <Source/Image.h>

#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION

#include <stb\stb_image.h>

#include <assert.h>
#include <iostream>

namespace Challenge
{

Image::Image()
	: format(ImageFormat(0))
	, width(0)
	, height(0)
	, pixels(nullptr)
{}

Image::Image(u32 _width, u32 _height,
			 ImageFormat _format,
			 const u8* _pixels)
	: format(ImageFormat(0))
	, width(0)
	, height(0)
	, pixels(nullptr)
{
	loadFromMemory(_width, _height, _format, _pixels);
}

Image::Image(const Image& _other)
	: format(ImageFormat(0))
	, width(0)
	, height(0)
	, pixels(nullptr)
{
	loadFromMemory(_other.width, _other.height, _other.format, _other.pixels);
}

Image& Image::operator=(const Image& _other)
{
	loadFromMemory(_other.width, _other.height, _other.format, _other.pixels);
	return( *this );
}

Image::~Image()
{
	if (pixels)
	{
		delete[] pixels;
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
			  (ImageFormat)format,
			  pixels);
	stbi_image_free(pixels);

	if (pixels)
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
	if (_column >= width ||
		_row >= height)
	{
		return(nullptr);
	}
	return(pixels + (_row * width + _column)* (usize)format);
}

void
Image::setPixel(u32 _column, u32 _row,
				const u32* _pixel) const
{
	if (_column >= width ||
		_row >= height)
	{
		return;
	}

	u8* pixel = getPixel(_column, _row);
	std::memcpy(pixel, _pixel, (usize)format);

}

void 
Image::flipVertically()
{
	std::size_t pitch = width * (usize)format;
	u32 halfRows = height / 2;
	u8* rowBuffer = new u8[pitch];

	for (u32 i = 0; i < halfRows; i++)
	{
		u8* row = pixels + (i * width) * (usize)format;
		u8* oppositeRow = pixels + ((height - i - 1) * width) * (usize)format;

		std::memcpy(rowBuffer, row, pitch);
		std::memcpy(row, oppositeRow, pitch);
		std::memcpy(oppositeRow, rowBuffer, pitch);
	}

	delete[] rowBuffer;
}

bool
Image::loadFromMemory(u32 _width, u32 _height,
					  ImageFormat _format,
					  const u8* _pixels)
{

	assert(_width != 0 && "Image::setPixels -> width=0 ");
	assert(_height != 0 && "Image::setPixels -> height=0");

	width = _width;
	height = _height;
	format = _format;

	size_t imageSize = _width * _height * (usize)_format;

	if (pixels) {
		delete[] pixels;
	}
	pixels = new u8[imageSize];

	if (_pixels != nullptr) {
		std::memcpy(pixels, _pixels, imageSize);
	}
	return(true);
}
} //namespace Challenge
