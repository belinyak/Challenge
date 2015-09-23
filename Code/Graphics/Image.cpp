#include <Graphics/Image.h>

#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION

#include <stb\stb_image.h>

#include <assert.h>
#include <iostream>

Image::Image()
    : m_format(ImageFormat(0))
    , m_width(0)
    , m_height(0)
    , m_pixels(nullptr)
{}

Image::Image(std::uint32_t _width, std::uint32_t _height,
	     ImageFormat _format,
	     const std::uint8_t* _pixels)
    : m_format(ImageFormat(0))
    , m_width(0)
    , m_height(0)
    , m_pixels(nullptr)
{
    loadFromMemory(_width, _height, _format, _pixels);
}

Image::Image(const Image& _other)
    : m_format(ImageFormat(0))
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
    std::uint8_t* pixels = stbi_load(_fileName,
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

std::uint8_t*
Image::getPixel(std::uint32_t _column, std::uint32_t _row) const
{
    if (_column >= m_width ||
	_row >= m_height)
    {
	return(nullptr);
    }
    return(m_pixels + (_row * m_width + _column)* (std::size_t)m_format);
}

void
Image::setPixel(std::uint32_t _column, std::uint32_t _row,
		const std::uint32_t* _pixel) const
{
    if (_column >= m_width ||
	_row >= m_height)
    {
	return;
    }

    std::uint8_t* pixel = getPixel(_column, _row);
    std::memcpy(pixel, _pixel, (std::size_t)m_format);

}

void 
Image::flipVertically()
{
    std::size_t pitch = m_width * (std::size_t)m_format;
    std::uint32_t halfRows = m_height / 2;
    std::uint8_t* rowBuffer = new std::uint8_t[pitch];

    for (std::uint32_t i = 0; i < halfRows; i++)
    {
	std::uint8_t* row = m_pixels + (i *m_width) * (std::size_t)m_format;
	std::uint8_t* oppositeRow = m_pixels + ((m_height - i - 1) * m_width) * (std::size_t)m_format;

	std::memcpy(rowBuffer, row, pitch);
	std::memcpy(row, oppositeRow, pitch);
	std::memcpy(oppositeRow, rowBuffer, pitch);
    }

    delete[] rowBuffer;
}

bool
Image::loadFromMemory(std::uint32_t _width, std::uint32_t _height,
		      ImageFormat _format,
		      const std::uint8_t* _pixels)
{

    assert(_width != 0 && "Image::setPixels -> width=0 ");
    assert(_height != 0 && "Image::setPixels -> height=0");

    m_width = _width;
    m_height = _height;
    m_format = _format;

    size_t imageSize = _width * _height * (std::size_t)_format;

    if (m_pixels) {
	delete[] m_pixels;
    }
    m_pixels = new std::uint8_t[imageSize];

    if (_pixels != nullptr) {
	std::memcpy(m_pixels, _pixels, imageSize);
    }
    return(true);
}
