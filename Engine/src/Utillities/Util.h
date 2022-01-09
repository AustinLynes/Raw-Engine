#pragma once


namespace Util {

	static unsigned int ConvertToARGB(unsigned int bgra_color) {
		unsigned int finalColor = 0;

		unsigned int A = (bgra_color & 0x000000FF) << 0x18u;	    // AA______ << 24
		unsigned int R = (bgra_color & 0x0000FF00) << 0x8u;			// __GG___  << 8
		unsigned int G = (bgra_color & 0x00FF0000) >> 0x8u;			// ____RR__ >> 8
		unsigned int B = (bgra_color & 0xFF000000) >> 0x18u;	    // ______BB >> 24

		finalColor = A | R | G | B;

		return finalColor;
	}

}