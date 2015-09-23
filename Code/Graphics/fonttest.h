#ifndef CHALLENGE_FONTTEST_H
#define CHALLENGE_FONTTEST_H

#define _CRT_SECURE_NO_WARNINGS
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb\stb_truetype.h>

void loadfont()
{
    unsigned char ttf_buffer[1<<20];
    fread(ttf_buffer, 1, 1<<20, fopen("c:/windows/fonts/ariel.ttf", "rb"));
    stbtt_fontinfo font;
    int width,height,xoff,yoff;
    stbtt_InitFont(&font, 0, stbtt_GetFontOffsetForIndex(ttf_buffer,0));
    unsigned char* bitmap;
    bitmap = stbtt_GetCodepointBitmap(&font, 0,stbtt_ScaleForPixelHeight(&font, 128.0f), 'a',
				      &width, &height, &xoff,&yoff);
    stbtt_FreeBitmap(bitmap,0);
}

#endif CHALLENGE_FONTTEST_H
 
