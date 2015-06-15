#ifndef CHALLENGE_IMAGE_H
#define CHALLENGE_IMAGE_H

#include <Source/Types.hpp>

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
	Image(u32 _width, u32 _height, ImageFormat _format, const u8* _pixels = nullptr);
	Image(const Image& _other);
	Image& operator=(const Image& _other);
	~Image();

	bool loadFromFile(const char* _fileName);
	bool loadFromMemory(u32 _width, u32 _height, ImageFormat _format, const u8* _pixels);

	inline u32 getWidth() const { 
		return(width); 
	}
	inline u32 getHeight() const {
		return(height); 
	}
	inline ImageFormat getFormat() const { 
		return(format); 
	}
	inline u8* getPixelPtr() const {
		return(pixels); 
	}

	u8*  getPixel(u32 _column, u32 _row) const;
	void	setPixel(u32 _column, u32 _row, const u32* _pixel) const;

	void flipVertically();

//TODO(mate): ReadOnly or private
	ImageFormat format;
	u32 width;
	u32 height;
	u8* pixels;
};
}

#endif // !#define CHALLENGE_IMAGE_H




