#pragma once

#define INFI  ((unsigned int)-1)

struct InfoH {
	int pos;
	bool newline;
	InfoH() : pos(INFI), newline(false) {}
	int add_pos(int add) {
		pos += add;
		return pos;
	}
};

