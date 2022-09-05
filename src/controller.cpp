#include <sys/time.h>
#include <cstdio>
#include "controller.hpp"

namespace dimanari
{
Level *Controller::current_level = NULL;
int Controller::w_;
int Controller::h_;
time_t Controller::last_time;
int Controller::window_id = 0;
void Controller::Update()
{
	struct timeval time_now{};
	gettimeofday(&time_now, nullptr);
	time_t msecs_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
	long time = msecs_time - last_time;
	last_time = msecs_time;
	current_level->Update(time);
}
void Controller::Render()
{
	current_level->Render();
	glutSwapBuffers();
}
void Controller::Keyboard(unsigned char key, int x, int y)
{
	current_level->Keyboard(key, KEY_DOWN, x, y);
}
void Controller::KeyboardUp(unsigned char key, int x, int y)
{
	current_level->Keyboard(key, KEY_UP, x, y);
}
void Controller::SpKeyboard(int key, int x, int y)
{
	current_level->Keyboard(key, KEY_SP_DOWN, x, y);
}
void Controller::SpKeyboardUp(int key, int x, int y)
{
	current_level->Keyboard(key, KEY_SP_UP, x, y);
}
void Controller::Mouse(int button, int state, int x, int y)
{
	current_level->Mouse(button, state, x, y);
}

void Controller::MouseMove(int x, int y)
{
	current_level->Mouse(-1, -1, x, y);
}

void Controller::SetLevel(Level *new_level)
{
	delete current_level;
	current_level = new_level;
}
void Controller::Release()
{
	delete current_level;
	current_level = NULL;
	printf("Released Level\n");
}
void Controller::Tick()
{
	Update();
	Render();
}

void Controller::Stop()
{
	glutExit();
}

void Controller::ToggleFS()
{
	glutFullScreenToggle();
}

void Controller::StartUp(int argc, char *argv[], const char *name, unsigned int displaymode, int width, int height, int x, int y)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(displaymode);
	
	glutInitWindowSize(width, height);
	w_ = width;
	h_ = height;
	glutInitWindowPosition(x, y);
	
	window_id = glutCreateWindow(name);
	
	glutDisplayFunc(Render);
	glutIdleFunc(Tick);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpKeyboard);
	glutSpecialUpFunc(SpKeyboardUp);
	glutKeyboardUpFunc(KeyboardUp);
	glutMouseFunc(Mouse);
	glutPassiveMotionFunc(MouseMove);
	glutMotionFunc(MouseMove);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	glutCloseFunc(Release);
	struct timeval time_now{};
	gettimeofday(&time_now, nullptr);
	last_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
}
}