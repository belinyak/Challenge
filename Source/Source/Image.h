#ifndef CHALLENGE_IMAGE_H
#define CHALLENGE_IMAGE_H

#include <cstdint>
#include <cstddef>

namespace Challenge
{
enum class ImageFormat
{
	None = 0,
	Greyscale = 1,
	GreyscaleAlpha = 2,
	RGB = 3,
	RGBA = 4,
};

class Image
{
public:
	//Note(mate): bytes/pixel

	Image();
	Image(std::uint32_t _width, std::uint32_t _height, ImageFormat _format, const std::uint8_t* _pixels = nullptr);
	Image(const Image& _other);
	Image& operator=(const Image& _other);
	~Image();

	bool loadFromFile(const char* _fileName);
	bool loadFromMemory(std::uint32_t _width, std::uint32_t _height, ImageFormat _format, const std::uint8_t* _pixels);

	inline std::uint32_t getWidth() const { 
		return(m_width);
	}
	inline std::uint32_t getHeight() const {
		return(m_height);
	}
	inline ImageFormat getFormat() const { 
		return(m_format);
	}
	inline std::uint8_t* getPixelPtr() const {
		return(m_pixels);
	}

	std::uint8_t*  getPixel(std::uint32_t _column, std::uint32_t _row) const;
	void	setPixel(std::uint32_t _column, std::uint32_t _row, const std::uint32_t* _pixel) const;

	void flipVertically();

private:
	ImageFormat m_format;
	std::uint32_t m_width;
	std::uint32_t m_height;
	std::uint8_t* m_pixels;
};
}

#endif // !#define CHALLENGE_IMAGE_H




