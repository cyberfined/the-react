#include "headers/utils.h"

void circle_draw(float r) {
	int i;
	float x, y;
    glBegin(GL_LINES);
    for (i = 0; i < 180; i++) {
    	x = r * cos(i);
    	y = r * sin(i);
    	glVertex2f(x, y);
    }
    glEnd();
}

void polygon_draw(float *vertices, int count) {
	int x2, y2;
	int i;
	count*=5;

	glBegin(GL_LINES);

	for(i = 0; i < count; i+=5) {
		x2 = i+5 < count ? i+5 : 0;
		y2 = x2 + 1;
		glColor3f(vertices[i+2], vertices[i+3], vertices[i+4]);/* x, y, red, green, blue */
		glVertex2f(vertices[i], vertices[i+1]);
		glVertex2f(vertices[x2], vertices[y2]);
	}

	glEnd();
}
