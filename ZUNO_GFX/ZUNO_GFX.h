#ifndef _ZUNO_GFX_H_
#define _ZUNO_GFX_H_

#include "Arduino.h"
#define max(a, b) (((a) > (b)) ? (a) : (b))


class ZUNO_GFX : public Print
{
	typedef struct	font_chunk_s
	{
		uint32_t	st_sim;
		uint32_t	end_sim;
		uint32_t	byte_st;
	}				font_chunk;

	typedef struct	ZUNO_font_S
	{
		uint8_t			width;
		uint8_t			height;
		uint8_t			col_sim;
		uint8_t			bytes_simbol;
		uint8_t			ranges;
		font_chunk		*chunks;
		const uint8_t	*font_buf;
		
	}				ZUNO_fonts;
	protected:
		uint16_t	cur_x;
		uint16_t	cur_y;
		uint16_t	s_width;
		uint16_t	s_height;	
		ZUNO_fonts	font;
		// void printChar(uint8_t ch);
		virtual uint8_t printChar(const uint8_t *sim_buf);
		// inline void printChar(uint8_t ch) {printChar((uint32_t)ch);};
		uint8_t		*buffer;
		size_t		buff_size;
		uint8_t charLen(char *ch);
		uint32_t utf8toUnicode(char *ch);
		uint8_t unicodeLen(int in);
		uint8_t retchunk(uint32_t unicode);
		
	private:
	public:
		ZUNO_GFX(uint16_t width, uint16_t height);
		~ZUNO_GFX();
		using	Print::write;
		uint8_t write(uint32_t unicode);
		size_t write(const uint8_t *buffer, size_t size);
		inline uint8_t write(uint8_t chr) {return(write((uint32_t)chr));};
		virtual void drawPixel(int16_t x, int16_t y, uint8_t color);
		void writePixel(int16_t x, int16_t y, uint8_t color);
		void drawBitmap(uint16_t x, uint16_t y,uint8_t w, uint8_t h,
												 uint8_t *pic, uint8_t color);
		void writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color);
		void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, 
																uint16_t color);
		void writeFastVLine(int16_t x, int16_t y, int16_t h, uint8_t color);
		void drawFastVLine(int16_t x, int16_t y, int16_t h, uint8_t color);
		void writeFastHLine(int16_t x, int16_t y, int16_t w, uint8_t color);
		void drawFastHLine(int16_t x, int16_t y, int16_t w, uint8_t color);
		void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
		void fillScreen(uint8_t color);
		void drawCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color);
		void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
													int16_t r, uint16_t color);
		void drawCircleHelper(int16_t x0, int16_t y0, int16_t r,
											uint8_t cornername, uint8_t color);
		void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
													int16_t r, uint16_t color);
		void writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h,
															uint16_t color);
		void fillCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color);
		void fillCircleHelper(int16_t x0, int16_t y0, int16_t r,
								uint8_t corners, int16_t delta, uint8_t color);
		void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
		void setFont(uint8_t *font_name);
		void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
									int16_t x2, int16_t y2, uint16_t color);
		void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
										int16_t x2, int16_t y2, uint16_t color);
		void	clearDisp() {memset(buffer, 0x00, buff_size);};
		int16_t	width(void) const { return s_width; };
		int16_t	height(void) const { return s_height; };
		int16_t	getCursorX(void) const { return cur_x; };
		int16_t	getCursorY(void) const { return cur_y; };
		void	setCursor(uint16_t x, uint16_t y) {cur_x = x; cur_y = y;};
		uint8_t *getBuffer() {return buffer;};
};

#endif