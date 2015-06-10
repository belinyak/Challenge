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

	inline u32 getWidth()		const { return( m_width	)	; }
	inline u32 getHeight()		const { return( m_height)	; }
	inline ImageFormat getFormat()	const { return( m_format)	; }
	inline u8* getPixelPtr()	const { return( m_pixels)	; }

	u8*  getPixel(u32 _column, u32 _row) const;
	void	setPixel(u32 _column, u32 _row,const u32* _pixel) const;

	void flipVertically();
	//TODO(mate): void rotate90CCW();

	//TODO(mate):  void copyRectFromImage(const Image& _src, u32 srcCol, u32 srcRow, u32 _destCol, u32 _destRow, u32 _width, u32 _height);
private:
	ImageFormat m_format;
	u32 m_width;
	u32 m_height;
	u8* m_pixels;
};
}

#endif // !#define CHALLENGE_IMAGE_H




