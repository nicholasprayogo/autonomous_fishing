/*
 * bitmap.h
 *
 *  Created on: 17-Jun-2019
 *      Author: poe
 */

#ifndef BITMAP_H_
#define BITMAP_H_

const unsigned char logo [] = {


		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x0f,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x0f,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xcf,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xcf,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xcf,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xcf,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xcf,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xcf,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xcf,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xcf,
			0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0x83, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0x83, 0xf8, 0x73, 0xf1, 0xfd, 0xfc, 0x7f, 0x3f, 0xe0, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0x83, 0xfc, 0x77, 0xf9, 0xff, 0xfe, 0xff, 0xbf, 0xf0, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0xff, 0xbc, 0xff, 0xfd, 0xff, 0xfe, 0xff, 0xbf, 0xf0, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0xff, 0xbc, 0xef, 0x3d, 0xe3, 0x80, 0xe3, 0xfc, 0xf0, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0xff, 0x1e, 0xef, 0xfd, 0xc3, 0xfd, 0xe3, 0xfc, 0x70, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0x9f, 0x1f, 0xef, 0xfd, 0xc1, 0xff, 0xe3, 0xfc, 0x70, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0x8f, 0x1f, 0xcf, 0xfd, 0xc0, 0x7f, 0xe3, 0xfc, 0x70, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0x87, 0x8f, 0xcf, 0xbd, 0xc3, 0xde, 0xf7, 0xfc, 0x70, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0x83, 0x87, 0xc7, 0xf9, 0xc3, 0xfe, 0xff, 0xbc, 0x70, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0x83, 0x87, 0x83, 0xf9, 0xc1, 0xfc, 0x7f, 0x3c, 0x70, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0x83, 0xbe, 0x03, 0x80, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0x83, 0x80, 0x07, 0x80, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0x83, 0x80, 0x07, 0x80, 0x00, 0x00, 0x00, 0x01, 0xe7, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0x83, 0x80, 0x07, 0x80, 0x00, 0x00, 0x00, 0x01, 0xe7, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0x83, 0x81, 0xc0, 0x00, 0x01, 0xc0, 0x00, 0xf0, 0x07, 0x00, 0x00, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0x83, 0xbf, 0xe7, 0xb8, 0xf7, 0xf3, 0xfb, 0xfd, 0xff, 0xfc, 0x38, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0x83, 0xbf, 0xf7, 0xb8, 0xff, 0xfb, 0xff, 0xfd, 0xff, 0xfe, 0x78, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0x83, 0xbe, 0xf7, 0xb9, 0xef, 0x7b, 0xe7, 0x9d, 0xe7, 0x1e, 0x78, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0x83, 0xbc, 0x77, 0xbd, 0xef, 0xff, 0xc7, 0xf9, 0xe7, 0x1e, 0x70, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0x83, 0xbc, 0x77, 0x9f, 0xef, 0xff, 0xc3, 0xfd, 0xe7, 0x0f, 0xf0, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0x83, 0xbc, 0x77, 0x9f, 0xcf, 0xff, 0xc0, 0xfd, 0xe7, 0x07, 0xe0, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0xc7, 0xbc, 0x77, 0x8f, 0x8e, 0x3b, 0xc7, 0x9d, 0xe7, 0x07, 0xe0, 0x03, 0xff, 0xcf,
			0xf8, 0x03, 0xff, 0xbc, 0x77, 0x8f, 0x8f, 0xfb, 0xc7, 0xfd, 0xe7, 0xe7, 0xe0, 0x03, 0xff, 0xcf,
			0xf8, 0x01, 0xff, 0x3c, 0x77, 0x8f, 0x07, 0xf3, 0xc3, 0xfd, 0xe7, 0xe3, 0xc0, 0x00, 0x00, 0x0f,
			0xf8, 0x00, 0xfe, 0x3c, 0x77, 0x87, 0x03, 0xe3, 0xc1, 0xf9, 0xe3, 0xe3, 0xc0, 0x00, 0x03, 0xff,
			0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x03, 0xff,
			0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x03, 0xff,
			0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x03, 0xff,
			0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff,
			0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff,
			0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff,
			0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff,
			0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff,
			0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

#endif /* BITMAP_H_ */