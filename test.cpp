#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

#pragma warning(disable:4996)

typedef struct {
	int top;
	int bottom;
	int left;
	int right;
}Rect;

void wipeData(uint8_t* fullscreen, int fullstride, int w, int h, Rect rect, char type) {
	uint8_t wipeData[4];
	switch (type) {
		case 'R': wipeData[0] = 0xff, wipeData[1] = 0x00, wipeData[2] = 0x00, wipeData[3] = 0xff; break;
		case 'G': wipeData[0] = 0x00, wipeData[1] = 0xff, wipeData[2] = 0x00, wipeData[3] = 0xff; break;
		case 'B': wipeData[0] = 0x00, wipeData[1] = 0x00, wipeData[2] = 0xff, wipeData[3] = 0xff; break;
		default: break;
	}

	uint8_t* src = rect.top * fullstride + fullscreen;
	for (int i = 0; i < (rect.bottom - rect.top); ++i) {
		for (int j = rect.left; j < rect.right; ++j) {
			src[4 * j + 0] |= wipeData[0];
			src[4 * j + 1] |= wipeData[1];
			src[4 * j + 2] |= wipeData[2];
			src[4 * j + 3] |= wipeData[3];
		}
		src += fullstride;
	}
}

uint8_t g_buf[1920 * 1080 * 4];
int main() {
	FILE* fp = fopen("1_1920x1080.rgb", "wb");
	memset(g_buf, 0, 1920 * 1080 * 4);
	Rect rect{ 959, 1001, 576, 640 };
	wipeData(g_buf, 1920 * 4, 1920, 1080, rect, 'G');
	wipeData(g_buf, 1920 * 4, 1920, 1080, rect, 'B');
	fwrite(g_buf, 1, 1920 * 1080 * 4, fp);
	return 0;
}