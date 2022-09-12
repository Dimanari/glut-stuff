#include <cmath>
#include <sys/time.h>
#include "my_level.hpp"

namespace dimanari_user
{
glm::mat4 m_vec[3] = {glm::identity<glm::mat4>()};

dimanari::Texture_ to_struct(Texture& t, string name = "ma_texture")
{
	dimanari::Texture_ mt;
	mt.id = t.Data();
	mt.type = name;
	return mt;
}

Point3D& operator+=(Point3D& this_, const Point3D& that_)
{
	this_.x += that_.x;
	this_.y += that_.y;
	return this_;
}
static void SetFace(Face &face, unsigned int vert, const glm::vec3 &pos, const glm::vec3 &norm, const glm::vec2 &tex)
{
	face.vertecies[0 + 8 * vert] = pos[0];
	face.vertecies[1 + 8 * vert] = pos[1];
	face.vertecies[2 + 8 * vert] = pos[2];
	face.vertecies[3 + 8 * vert] = norm[0];
	face.vertecies[4 + 8 * vert] = norm[1];
	face.vertecies[5 + 8 * vert] = norm[2];
	face.vertecies[6 + 8 * vert] = tex[0];
	face.vertecies[7 + 8 * vert] = tex[1];
}
static void FaceNormal(Face *faces, glm::vec3& normal, int face_id)
{
	float vertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,


		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,


		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,


		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,


		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,


		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f
	};
	
	int face_side = face_id;
	for(int face_num = 0; 6 > face_num; ++face_num)
	{
	SetFace(
		faces[(3 > face_num) ? (1) : (0)],

		(3 > face_num) ? (face_num) : (face_num - 3),
		
		glm::vec3(
			vertices[0 + (5) * face_num + 30 * face_side],
			vertices[1 + (5) * face_num + 30 * face_side],
			vertices[2 + (5) * face_num + 30 * face_side]),

		normal,

		glm::vec2(vertices[3 + (5) * face_num + 30 * face_side], vertices[4 + (5) * face_num + 30 * face_side])
		);
	}	
}
static Face* GenFace(int face_id)
{
	
	Face* ret = new Face[2];
	glm::vec3 normal;
	switch(face_id)
	{
	case 0:
		normal = glm::vec3(0.0,0.0,-1.0);
		break;
	case 1:
		normal = glm::vec3(0.0,0.0,1.0);
		break;
	case 2:
		normal = glm::vec3(-1.0,0.0,0.0);
		break;
	case 3:
		normal = glm::vec3(1.0,0.0,0.0);
		break;
	case 4:
		normal = glm::vec3(0.0,-1.0,0.0);
		break;
	case 5:
		normal = glm::vec3(0.0,1.0,0.0);
		break;
	default:
		delete ret;
		return NULL;
		break;
	}
	FaceNormal(ret, normal, face_id);
	return ret;
}

void FaceToVert(vector<dimanari::Vertex> &vect, Face face)
{
	dimanari::Vertex vert;
	for(unsigned int index = 0;index < 3; ++index)
	{
		vert.Position.x = face.vertecies[0 + 8 * index];
		vert.Position.y = face.vertecies[1 + 8 * index];
		vert.Position.z = face.vertecies[2 + 8 * index];

		vert.Normal.x = face.vertecies[3 + 8 * index];
		vert.Normal.y = face.vertecies[4 + 8 * index];
		vert.Normal.z = face.vertecies[5 + 8 * index];
		
		vert.TexCoords.x = face.vertecies[6 + 8 * index];
		vert.TexCoords.y = face.vertecies[7 + 8 * index];

		vect.push_back(vert);
	}
}

vector<dimanari::Vertex> MakeFrom(Face **face, unsigned int per_array = 2, unsigned int arrays = 6)
{
	vector<dimanari::Vertex> vect;
	vect.clear();

	for(unsigned int i = 0;i < arrays; ++i)
	{
		for(unsigned int j = 0;j < per_array; ++j)
		{
			FaceToVert(vect, face[i][j]);
		}
	}

	return vect;
}
vector<dimanari::Vertex> MakeCube()
{
	Face **faces = new Face*[6];
	for(int i=0;i<6;i++)
	{
		faces[i] = GenFace(i);
	}

	vector<dimanari::Vertex> vect = MakeFrom(faces);
	for(int i=0;i<6;i++)
	{
		delete[] faces[i];
	}
	delete []faces;
	return vect;
}

MyLevel::MyLevel() : wall("resources/wall.bmp"),
	cube_shader("shader/model_instance.vs", "shader/textured_lighting.fs"),
	cube(MakeCube(), to_struct(wall)),
	use_mouse(false), tick_num(0), angle(0.0)
{
	glEnable(GL_DEPTH_TEST);
	yaw = 90.0f;
	pitch = 0.0f;
	cameraPos = glm::vec3(0.0f, 0.0f, -3.0f);
	glm::vec3 direction = glm::vec3(
		cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
		sin(glm::radians(pitch)),
		sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
	cameraFront = glm::normalize(direction);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	for(int i=0;i<4;++i)
	{
		keys[i] = false;
	}
	for(int i=0;i<3;i++)
	{
		m_vec[i] = glm::translate(glm::mat4(1), glm::vec3(0.0,0.0,3.0));
		m_vec[i] = glm::rotate(glm::mat4(1), (float)(i * M_PI_2 * 3.0f), glm::vec3(0.0f,1.0f,0.0f) ) * m_vec[i];
	}
}

MyLevel::~MyLevel()
{

}
#define time_reset (M_PI * 20.0)
void MyLevel::Update(long time)
{
	tick_num += time;
	if(tick_num > 10)
	{
		const float cameraSpeed = 0.005f * tick_num; // adjust accordingly
		if (keys[0])
			cameraPos += cameraSpeed * cameraFront;
		if (keys[1])
			cameraPos -= cameraSpeed * cameraFront;
		if (keys[2])
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (keys[3])
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

		angle = 0.01;
		tick_num = 0;
		for(int i=0;i<3;i++)
		{
			m_vec[i] = glm::rotate(glm::mat4(1), angle, glm::vec3(0.0,1.0,0.0) ) * m_vec[i];
		}
		cube.VectorSetup(m_vec,3);
	
	}
}

void MyLevel::Render()
{
	RenderFlatBG();

	

	//cameraPos.y += 0.01;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)Controller::GetW() / Controller::GetH(), 0.1f, 100.0f);

	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	cube_shader.use();
	cube_shader.setFloat3("viewPos", cameraPos);
	cube_shader.setMatrixF4("projection", projection);
	cube_shader.setMatrixF4("view", view);
	cube_shader.setFloat3("light_pos", cameraUp + cameraPos);
	cube_shader.setFloat("ambientStrength", 0.2f);
	
	cube.DrawInst(cube_shader, 3);
}

void MyLevel::RenderFlatBG()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Shader::unuse();
	glDepthMask(GL_FALSE);  
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_TRIANGLES);
		glVertex3f(-1.0, -1.0, 0.0);
		glVertex3f(-1.0, 1.0, 0.0);
		glVertex3f(1.0, -1.0, 0.0);

		glVertex3f(-1.0, 1.0, 0.0);
		glVertex3f(1.0, -1.0, 0.0);
		glVertex3f(1.0, 1.0, 0.0);
	glEnd();
	glDepthMask(GL_TRUE);
}

void MyLevel::Mouse(int button, int state, int x, int y)
{
	if(dimanari::MOUSE_MOVE == state)
	{
		static const float mouse_responsive = 0.001;
		static const float max_pitch = 60.0f;
		float xoffset = (x - Controller::GetW() / 2) / (float)(Controller::GetW());
		float yoffset = (Controller::GetH() / 2 - y) / (float)(Controller::GetH());
		
		if(abs(xoffset) > mouse_responsive || abs(yoffset) > mouse_responsive)
		{
			float sensitivity = 10.0f;

			xoffset *= sensitivity;
			yoffset *= sensitivity;

			yaw += xoffset;
			pitch += yoffset;
			if(pitch > max_pitch)
				pitch = max_pitch;
			else if(pitch < -max_pitch)
				pitch = -max_pitch;
			if(yaw > 360.0)
			{
				yaw -= 360.0;
			}
			else if(yaw < 0.0)
			{
				yaw += 360.0;
			}
			glm::vec3 direction;
			direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			direction.y = sin(glm::radians(pitch));
			direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			cameraFront = glm::normalize(direction);
			glutWarpPointer(Controller::GetW() / 2, Controller::GetH() / 2);
		}
	}
	if(dimanari::MOUSE_DOWN == state)
	{
		if(dimanari::MOUSE_L_CLICK == button)
		{
			//points[1] = points[0];
		}
		if(dimanari::MOUSE_R_CLICK == button)
		{
			//points[2] = points[0];
		}
	}
}

void MyLevel::Keyboard(int key, int state, int x, int y)
{
	switch(key)
	{
	case 'w':
		keys[0] = state == dimanari::KEY_DOWN;
		break;
	case 's':
		keys[1] = state == dimanari::KEY_DOWN;
		break;
	case 'a':
		keys[2] = state == dimanari::KEY_DOWN;
		break;
	case 'd':
		keys[3] = state == dimanari::KEY_DOWN;
		break;

	case 27:
		Controller::Stop();
		break;
	case GLUT_KEY_F10:
		if(dimanari::KEY_SP_DOWN == state)
			Controller::ToggleFS();
		break;
	case '\t':
		if(dimanari::KEY_DOWN == state)
			use_mouse = !use_mouse;
		break;
	default:
		break;
	}
}
}