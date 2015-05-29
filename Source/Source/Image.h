#ifndef CHALLENGE_IMAGE_H
#define CHALLENGE_IMAGE_H

#include <Source/Types.hpp>

namespace Challenge
{
class Image
{
public:
	//Note(mate): bytes/pixel
	enum Format
	{
		Format_Greyscale = 1,
		Format_GreyscaleAlpha = 2,
		Format_RGB = 3,
		Format_RGBA = 4,
	};

	Image();
	Image(u32 _width, u32 _height, Format _format, const u8* _pixels = nullptr);
	Image(const Image& _other);
	Image& operator=(const Image& _other);
	~Image();

	bool loadFromFile(const char* _fileName);
	bool loadFromMemory(u32 _width, u32 _height, Format _format, const u8* _pixels);

	inline u32 getWidth() const { return m_width; }
	inline u32 getHeight() const { return m_height; }
	inline Format getFormat() const { return m_format; }
	inline u8* getPixelPtr() const { return m_pixels; }

	u8*  getPixel(u32 _column, u32 _row) const;
	void	setPixel(u32 _column, u32 _row,const u32* _pixel) const;

	void flipVertically();
	//TODO(mate): void rotate90CCW();

	//TODO(mate):  void copyRectFromImage(const Image& _src, u32 srcCol, u32 srcRow, u32 _destCol, u32 _destRow, u32 _width, u32 _height);
private:
	Format m_format;
	u32 m_width;
	u32 m_height;
	u8* m_pixels;
};
}

#endif // !#define CHALLENGE_IMAGE_H




