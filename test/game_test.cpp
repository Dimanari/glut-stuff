#include "my_level.hpp"
using dimanari::Controller;
using dimanari_user::MyLevel;
int main(int argc, char *argv[])
{
	Controller::StartUp(argc, argv, "Game", GLUT_DOUBLE | GLUT_DEPTH, 800);
	Controller::HideCursor();
	//Controller::ToggleFS();
	Controller::SetLevel(new MyLevel());
	Controller::Go();
	Controller::Cleanup();
}