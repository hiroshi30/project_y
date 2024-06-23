#ifndef ENGINE_H
#define ENGINE_H


void engineInit(int width, int height, const char *title);
void engineExit(void);
void engineExitFailure(void);

bool engineWorking(void);
void engineEvents(void);
void engineTime(void);
void engineClear(void);
void engineSwapBuffers(void);

void enginePolygonsMeshView(void);
GLint engineGet_MAX_VERTEX_ATTRIBS(void);


#endif // ENGINE_H
