#ifndef DIMA_PROJ_MY_LEVEL_HPP
#define DIMA_PROJ_MY_LEVEL_HPP
#include "controller.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "model.hpp"
#include "framebuf.hpp"

namespace dimanari_user
{
using dimanari::Controller;
using dimanari::Level;
using dimanari::Shader;
using dimanari::ShaderVBO;
using dimanari::Texture;
using dimanari::SimpleMesh;
using dimanari::DepthMap;
using dimanari::ShadowTexture;

struct Point3D
{
	float x;
	float y;
	float z;
};

struct Point2D
{
	float x;
	float y;
};

struct Face
{
	float vertecies[3 * 8];
};

class MyLevel : public Level
{
public:
	MyLevel();
	virtual ~MyLevel();
	virtual void Update(long time);
	virtual void Render();
	virtual void Mouse(int button, int state, int x, int y);
	virtual void Keyboard(int key, int state, int x, int y);
private:
	void RenderFlatBG();
	Texture wall;
	ShaderVBO cube_shader;
	SimpleMesh cube;
	float yaw;
	float pitch;
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	bool use_mouse;
	long tick_num;
	bool keys[4];
	float angle;
};
}
#endif //!DIMA_PROJ_MY_LEVEL_HPP