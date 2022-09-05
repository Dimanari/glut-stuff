#ifndef DIMA_PROJ_CONTROLLER_HPP
#define DIMA_PROJ_CONTROLLER_HPP
#include "GL_include.hpp"

/*
 * Simple Glut Interface by Dimanari(Daniell Bar)
 * this is a modular interface that allows for easy creation
 * and deployment of OpenGL based programs.
 * 
 * Please don't delete that segment.
 */
namespace dimanari
{
static const int MOUSE_MOVE = -1;
static const int MOUSE_L_CLICK = GLUT_LEFT_BUTTON;
static const int MOUSE_M_CLICK = GLUT_MIDDLE_BUTTON;
static const int MOUSE_R_CLICK = GLUT_RIGHT_BUTTON;

static const int MOUSE_UP = GLUT_UP;
static const int MOUSE_DOWN = GLUT_DOWN;

static const int KEY_UP = 0;
static const int KEY_DOWN = 1;
static const int KEY_SP_UP = 2;
static const int KEY_SP_DOWN = 3;
class Level
{
public:
	Level() {}
	virtual ~Level() {}
	virtual void Update(long time) = 0;
	virtual void Render() = 0;
	virtual void Keyboard(int key, int state, int x, int y) {}
	virtual void Mouse(int button, int state, int x, int y) {}
};
class Controller
{
public:
	static void ToggleFS();
	static void Stop();
	static void Tick();
	static void Update();
	static void Render();
	static void Keyboard(unsigned char key, int x, int y);
	static void SpKeyboard(int key, int x, int y);
	static void SpKeyboardUp(int key, int x, int y);
	static void KeyboardUp(unsigned char key, int x, int y);
	static void Mouse(int button, int state, int x, int y);
	static void MouseMove(int x, int y);
	static void SetLevel(Level *new_level);
	static void Release();
	static void StartUp(int argc, char *argv[],const char *name = "Controller Window", unsigned int displaymode = GLUT_DOUBLE ,int width = 500, int height = 500, int x = 200, int y = 200);
	static void Go() {glutMainLoop();}
	static inline int GetH() { return h_; }
	static inline int GetW() { return w_; }
private:
	Controller() {}
	static Level* current_level;
	static time_t last_time;
	static int w_;
	static int h_;
	static int window_id;
};
}
#endif //!DIMA_PROJ_CONTROLLER_HPP