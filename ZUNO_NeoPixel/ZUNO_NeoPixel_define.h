#ifndef ZUNO_NEOPIXEL_DEFINE_H
#define ZUNO_NEOPIXEL_DEFINE_H

#include "CrtxTimer.h"
#include "CrtxUSART.h"

typedef uint16_t ZunoNeoOptionMax_t;

// The order of primary colors in the NeoPixel data stream can vary among
// device types, manufacturers and even different revisions of the same
// item.  The third parameter to the Adafruit_NeoPixel constructor encodes
// the per-pixel byte offsets of the red, green and blue primaries (plus
// white, if present) in the data stream -- the following #defines provide
// an easier-to-use named version for each permutation. e.g. NEO_GRB
// indicates a NeoPixel-compatible device expecting three bytes per pixel,
// with the first byte transmitted containing the green value, second
// containing red and third containing blue. The in-memory representation
// of a chain of NeoPixels is the same as the data-stream order; no
// re-ordering of bytes is required when issuing data to the chain.
// Most of these values won't exist in real-world devices, but it's done
// this way so we're ready for it (also, if using the WS2811 driver IC,
// one might have their pixels set up in any weird permutation).

// Bits 5,4 of this value are the offset (0-3) from the first byte of a
// pixel to the location of the red color byte.  Bits 3,2 are the green
// offset and 1,0 are the blue offset.  If it is an RGBW-type device
// (supporting a white primary in addition to R,G,B), bits 7,6 are the
// offset to the white byte...otherwise, bits 7,6 are set to the same value
// as 5,4 (red) to indicate an RGB (not RGBW) device.
// i.e. binary representation:
// 0bWWRRGGBB for RGBW devices
// 0bRRRRGGBB for RGB

// RGB NeoPixel permutations; white and red offsets are always same
// Offset:         W        R        G        B
#define NEO_RGB  ((0<<6) | (0<<4) | (1<<2) | (2)) ///< Transmit as R,G,B
#define NEO_RBG  ((0<<6) | (0<<4) | (2<<2) | (1)) ///< Transmit as R,B,G
#define NEO_GRB  ((1<<6) | (1<<4) | (0<<2) | (2)) ///< Transmit as G,R,B
#define NEO_GBR  ((2<<6) | (2<<4) | (0<<2) | (1)) ///< Transmit as G,B,R
#define NEO_BRG  ((1<<6) | (1<<4) | (2<<2) | (0)) ///< Transmit as B,R,G
#define NEO_BGR  ((2<<6) | (2<<4) | (1<<2) | (0)) ///< Transmit as B,G,R

// RGBW NeoPixel permutations; all 4 offsets are distinct
// Offset:         W          R          G          B
#define NEO_WRGB ((0<<6) | (1<<4) | (2<<2) | (3)) ///< Transmit as W,R,G,B
#define NEO_WRBG ((0<<6) | (1<<4) | (3<<2) | (2)) ///< Transmit as W,R,B,G
#define NEO_WGRB ((0<<6) | (2<<4) | (1<<2) | (3)) ///< Transmit as W,G,R,B
#define NEO_WGBR ((0<<6) | (3<<4) | (1<<2) | (2)) ///< Transmit as W,G,B,R
#define NEO_WBRG ((0<<6) | (2<<4) | (3<<2) | (1)) ///< Transmit as W,B,R,G
#define NEO_WBGR ((0<<6) | (3<<4) | (2<<2) | (1)) ///< Transmit as W,B,G,R

#define NEO_RWGB ((1<<6) | (0<<4) | (2<<2) | (3)) ///< Transmit as R,W,G,B
#define NEO_RWBG ((1<<6) | (0<<4) | (3<<2) | (2)) ///< Transmit as R,W,B,G
#define NEO_RGWB ((2<<6) | (0<<4) | (1<<2) | (3)) ///< Transmit as R,G,W,B
#define NEO_RGBW ((3<<6) | (0<<4) | (1<<2) | (2)) ///< Transmit as R,G,B,W
#define NEO_RBWG ((2<<6) | (0<<4) | (3<<2) | (1)) ///< Transmit as R,B,W,G
#define NEO_RBGW ((3<<6) | (0<<4) | (2<<2) | (1)) ///< Transmit as R,B,G,W

#define NEO_GWRB ((1<<6) | (2<<4) | (0<<2) | (3)) ///< Transmit as G,W,R,B
#define NEO_GWBR ((1<<6) | (3<<4) | (0<<2) | (2)) ///< Transmit as G,W,B,R
#define NEO_GRWB ((2<<6) | (1<<4) | (0<<2) | (3)) ///< Transmit as G,R,W,B
#define NEO_GRBW ((3<<6) | (1<<4) | (0<<2) | (2)) ///< Transmit as G,R,B,W
#define NEO_GBWR ((2<<6) | (3<<4) | (0<<2) | (1)) ///< Transmit as G,B,W,R
#define NEO_GBRW ((3<<6) | (2<<4) | (0<<2) | (1)) ///< Transmit as G,B,R,W

#define NEO_BWRG ((1<<6) | (2<<4) | (3<<2) | (0)) ///< Transmit as B,W,R,G
#define NEO_BWGR ((1<<6) | (3<<4) | (2<<2) | (0)) ///< Transmit as B,W,G,R
#define NEO_BRWG ((2<<6) | (1<<4) | (3<<2) | (0)) ///< Transmit as B,R,W,G
#define NEO_BRGW ((3<<6) | (1<<4) | (2<<2) | (0)) ///< Transmit as B,R,G,W
#define NEO_BGWR ((2<<6) | (3<<4) | (1<<2) | (0)) ///< Transmit as B,G,W,R
#define NEO_BGRW ((3<<6) | (2<<4) | (1<<2) | (0)) ///< Transmit as B,G,R,W

// Add NEO_KHZ400 to the color order value to indicate a 400 KHz device.
// All but the earliest v1 NeoPixels expect an 800 KHz data stream, this is
// the default if unspecified. Because flash space is very limited on ATtiny
// devices (e.g. Trinket, Gemma), v1 NeoPixels aren't handled by default on
// those chips, though it can be enabled by removing the ifndef/endif below,
// but code will be bigger. Conversely, can disable the NEO_KHZ400 line on
// other MCUs to remove v1 support and save a little space.
#define NEO_KHZ800						0x0000 ///< 800 KHz data transmission
#define NEO_KHZ400						0x0100 ///< 400 KHz data transmission

#define NEO_BRIGHTNESS_DEFAULT			0xFF

typedef uint16_t						ZunoNeoCountLed;

typedef union							ZunoNeoColor_u
{

	uint32_t							color;
	struct
	{
		uint8_t							red;
		uint8_t							green;
		uint8_t							blue;
		uint8_t							white;
	};
}										ZunoNeoColor_t;


/* Similar to above, but for an 8-bit gamma-correction table.
   Copy & paste this snippet into a Python REPL to regenerate:
import math
gamma=2.6
for x in range(256):
    print("{:3},".format(int(math.pow((x)/255.0,gamma)*255.0+0.5))),
    if x&15 == 15: print
*/
static const uint8_t gNeoGammaTable[256] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,
	1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  3,  3,  3,  3,
	3,  3,  4,  4,  4,  4,  5,  5,  5,  5,  5,  6,  6,  6,  6,  7,
	7,  7,  8,  8,  8,  9,  9,  9, 10, 10, 10, 11, 11, 11, 12, 12,
	13, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20,
	20, 21, 21, 22, 22, 23, 24, 24, 25, 25, 26, 27, 27, 28, 29, 29,
	30, 31, 31, 32, 33, 34, 34, 35, 36, 37, 38, 38, 39, 40, 41, 42,
	42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
	58, 59, 60, 61, 62, 63, 64, 65, 66, 68, 69, 70, 71, 72, 73, 75,
	76, 77, 78, 80, 81, 82, 84, 85, 86, 88, 89, 90, 92, 93, 94, 96,
	97, 99,100,102,103,105,106,108,109,111,112,114,115,117,119,120,
	122,124,125,127,129,130,132,134,136,137,139,141,143,145,146,148,
	150,152,154,156,158,160,162,164,166,168,170,172,174,176,178,180,
	182,184,186,188,191,193,195,197,199,202,204,206,209,211,213,215,
	218,220,223,225,227,230,232,235,237,240,242,245,247,250,252,255};

#endif //ZUNO_NEOPIXEL_DEFINE_H