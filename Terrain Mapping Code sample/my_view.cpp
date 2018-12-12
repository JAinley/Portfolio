#include "my_view.hpp"
#include "PerlinNoise.h"
#include <tygra/FileHelper.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>


MyView::MyView()
{
}

MyView::~MyView() {
}

void MyView::setScene(const scene::Context * scene)
{
    scene_ = scene;
}

void MyView::toggleShading()
{
    shade_normals_ = !shade_normals_;
}

void MyView::windowViewWillStart(tygra::Window * window)
{
    assert(scene_ != nullptr);

    GLint compile_status = 0;
    GLint link_status = 0;

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertex_shader_string
        = tygra::createStringFromFile("resource:///terrain_vs.glsl");
    const char *vertex_shader_code = vertex_shader_string.c_str();
    glShaderSource(vertex_shader, 1,
                   (const GLchar **)&vertex_shader_code, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status != GL_TRUE) {
        const int string_length = 1024;
        GLchar log[string_length] = "";
        glGetShaderInfoLog(vertex_shader, string_length, NULL, log);
        std::cerr << log << std::endl;
    }

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragment_shader_string
        = tygra::createStringFromFile("resource:///terrain_fs.glsl");
    const char *fragment_shader_code = fragment_shader_string.c_str();
    glShaderSource(fragment_shader, 1,
                   (const GLchar **)&fragment_shader_code, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status != GL_TRUE) {
        const int string_length = 1024;
        GLchar log[string_length] = "";
        glGetShaderInfoLog(fragment_shader, string_length, NULL, log);
        std::cerr << log << std::endl;
    }

    terrain_sp_ = glCreateProgram();
    glAttachShader(terrain_sp_, vertex_shader);
    glDeleteShader(vertex_shader);
    glAttachShader(terrain_sp_, fragment_shader);
    glDeleteShader(fragment_shader);
    glLinkProgram(terrain_sp_);

    glGetProgramiv(terrain_sp_, GL_LINK_STATUS, &link_status);
    if (link_status != GL_TRUE) {
        const int string_length = 1024;
        GLchar log[string_length] = "";
        glGetProgramInfoLog(terrain_sp_, string_length, NULL, log);
        std::cerr << log << std::endl;
    }


    // X and -Z are on the ground, Y is up
    const float sizeX = scene_->getTerrainSizeX();
    const float sizeY = scene_->getTerrainSizeY();
    const float sizeZ = scene_->getTerrainSizeZ();


	//makes a instance of perlin noise class
	PerlinNoise pn;

	//sets perlin noise, change these values to get a different noise
	pn.Set(1, 2, 1, 8, 8);

    const auto& bezier_patches = scene_->getTerrainPatches();
    const size_t number_of_patches = bezier_patches.size();

    tygra::Image displace_image =
        tygra::createImageFromPngFile(scene_->getTerrainDisplacementMapName());

	//set the plane size
	int count = 0;
	std::vector < glm::vec3> cpa{ 16 };
	std::vector < glm::vec3> cpb{ 16 };

	// set cpa, cpb
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			cpa[count] = bezier_patches[0].at(x, y);
			cpb[count++] = bezier_patches[1].at(x, y);
		}
	}

	const int subV = 255; //sizeZ / 2;
	const int subU = 255; //sizeX / 2;

	// an array for the vertices and set the size of the elements
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> positions((subU + 1) * (subV + 1));
	const int vertex_count = (subU + 1) * (subV + 1);
	const int quads = subU * subV;
	const int traingles = quads * 2;
	std::vector<GLuint> Elements (traingles * 3);
	std::vector<glm::vec2> uV((subU + 1) * (subV + 1));
	std::vector<glm::vec3> normals((subU + 1) * (subV + 1));


	//creating a loop that goes through all the subU values, changes heigh, perlin noise and postions
	for (int h = 0; h < (subU + 1); h++)
	{
		for (int i = 0; i < (subV + 1); i++)
		{
			//set the height using the heightmap of texture
			int height = *(uint8_t*)displace_image.pixel((255.f / subU) * i, (255.f / subV) * h);

			uV[h * (subU + 1) + i].x = i / float(subU - 1);
			uV[h * (subU + 1) + i].y = h / float(subV - 1);

			//this is the perlin noise height initialization and setting for all the points in the loop.
			double perlinheight = (double)height + pn.GetHeight(h, i);

			//below is combining perlin noise and the terrain height together.
			positions[h * (subU + 1) + i] = glm::vec3{ i * sizeX / subU, perlinheight * 2, h * -sizeZ / subV };
			normals[h*(subU + 1) + i] = { 0,1,0 };
		}
	}
	//loop through the SubU and SubV to apply bezier
	for (int j = 0; j < (subU + 1) * (subV + 1); j++)
	{
		glm::vec3 pos;
		//if uv is lower than 0.5, sets to below the equation
		if (uV[j].x < 0.5f)
		{
			float u{ uV[j].x*2.0f };
			pos = BezierSurface(cpa, u, uV[j].y);
		}
		//else the uv value is higher thsn 0.5, sets below as above
		else
		{
			float u{ (uV[j].x - 0.5f)*2.0f };
			pos = BezierSurface(cpb, u, uV[j].y);
		}
		//sets its new positions
		positions[j] = positions[j] + pos;
	}

	// loops through and fills the elements vector 
	for(int i = 0; i < subU; i++)
	{
		for(int j = 0; j < subV; j++)
		{
			if (i % 2 == j % 2) {
				Elements[(i * (subU)+j) * 6] = i * (subU + 1) + j;
				Elements[(i * (subU)+j) * 6 + 1] = i * (subU + 1) + j + 1;
				Elements[(i * (subU)+j) * 6 + 2] = i * (subU + 1) + j + subU + 2;
				Elements[(i * (subU)+j) * 6 + 3] = i * (subU + 1) + j;
				Elements[(i * (subU)+j) * 6 + 4] = i * (subU + 1) + j + subU + 2;
				Elements[(i * (subU)+j) * 6 + 5] = i * (subU + 1) + j + subU + 1;
			}
			else {
				Elements[(i * (subU)+j) * 6] = i * (subU + 1) + j;
				Elements[(i * (subU)+j) * 6 + 1] = i * (subU + 1) + j + 1;
				Elements[(i * (subU)+j) * 6 + 2] = i * (subU + 1) + j + subU + 1;
				Elements[(i * (subU)+j) * 6 + 3] = i * (subU + 1) + j + 1;
				Elements[(i * (subU)+j) * 6 + 4] = i * (subU + 1) + j + subU + 2;
				Elements[(i * (subU)+j) * 6 + 5] = i * (subU + 1) + j + subU + 1;
			}
		}
	}

	//resize the normals vector
	normals.resize(vertex_count);
	for (int m = 0; m < positions.size(); m++)
	{
		normals.push_back(glm::vec3(0, 0, 0));
	}
	

	//loops through vector and calculates normals for the positions adjacent
	for (int n = 0; n < Elements.size(); n += 3)
	{
		glm::vec3 p1 = positions[Elements[n]];
		glm::vec3 p2 = positions[Elements[n + 1]];
		glm::vec3 p3 = positions[Elements[n + 2]];
		glm::vec3 edge1 = p2 - p1;
		glm::vec3 edge2 = p3 - p1;
		glm::vec3 vectors = glm::cross(edge1, edge2);

		normals[Elements[n]] += vectors;
		normals[Elements[n + 1]] += vectors;
		normals[Elements[n + 2]] += vectors;
	}

	//normalises normal positions again
	for (int i = 0; i < normals.size(); i++)
	{
		glm::normalize(normals[i]);
	}


	glGenBuffers(1, &terrain_mesh_.element_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrain_mesh_.element_vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Elements.size() * sizeof(GLuint), Elements.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	terrain_mesh_.element_count = Elements.size();
	glGenBuffers(1, &terrain_mesh_.position_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, terrain_mesh_.position_vbo);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glGenBuffers(1, &terrain_mesh_.normal_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, terrain_mesh_.normal_vbo);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glGenVertexArrays(1, &terrain_mesh_.vao);
	glBindVertexArray(terrain_mesh_.vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrain_mesh_.element_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, terrain_mesh_.position_vbo);
	glEnableVertexAttribArray(kVertexPosition);
	glVertexAttribPointer(kVertexPosition, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), TGL_BUFFER_OFFSET(0));
	glBindBuffer(GL_ARRAY_BUFFER, terrain_mesh_.normal_vbo);
	glEnableVertexAttribArray(kVertexNormal);
	glVertexAttribPointer(kVertexNormal, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), TGL_BUFFER_OFFSET(0));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void MyView::windowViewDidReset(tygra::Window * window,
                                int width,
                                int height)
{
    glViewport(0, 0, width, height);
}

void MyView::windowViewDidStop(tygra::Window * window)
{
    glDeleteProgram(terrain_sp_);
    glDeleteBuffers(1, &terrain_mesh_.position_vbo);
    glDeleteBuffers(1, &terrain_mesh_.normal_vbo);
    glDeleteBuffers(1, &terrain_mesh_.element_vbo);
    glDeleteVertexArrays(1, &terrain_mesh_.vao);
}

void MyView::windowViewRender(tygra::Window * window)
{
    assert(scene_ != nullptr);

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    const float aspect_ratio = viewport[2] / (float)viewport[3];


	// had to add onto the far plane as the terrain wasnt rendering all the way
    const auto& camera = scene_->getCamera();
    glm::mat4 projection_xform = glm::perspective(
        glm::radians(camera.getVerticalFieldOfViewInDegrees()),
        aspect_ratio,
        camera.getNearPlaneDistance(),
        camera.getFarPlaneDistance() + 100000.f);
    glm::vec3 camera_pos = camera.getPosition();
    glm::vec3 camera_at = camera.getPosition() + camera.getDirection();
    glm::vec3 world_up{ 0, 1, 0 };
    glm::mat4 view_xform = glm::lookAt(camera_pos, camera_at, world_up);


    glClearColor(0.f, 0.f, 0.25f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, shade_normals_ ? GL_FILL : GL_LINE);

    glUseProgram(terrain_sp_);

    GLuint shading_id = glGetUniformLocation(terrain_sp_, "use_normal");
    glUniform1i(shading_id, shade_normals_);



    glm::mat4 world_xform = glm::mat4(1);
    glm::mat4 view_world_xform = view_xform * world_xform;

    GLuint projection_xform_id = glGetUniformLocation(terrain_sp_,
                                                      "projection_xform");
    glUniformMatrix4fv(projection_xform_id, 1, GL_FALSE,
                       glm::value_ptr(projection_xform));

    GLuint view_world_xform_id = glGetUniformLocation(terrain_sp_,
                                                      "view_world_xform");
    glUniformMatrix4fv(view_world_xform_id, 1, GL_FALSE,
                       glm::value_ptr(view_world_xform));

    if (terrain_mesh_.vao) {
        glBindVertexArray(terrain_mesh_.vao);
        glDrawElements(GL_TRIANGLES, terrain_mesh_.element_count,
                       GL_UNSIGNED_INT, 0);
    }
}


// Bezier equations

glm::vec3 MyView::BezierCurve(const std::vector<glm::vec3>& cp, float u)
{
	float curve[4];
	curve[0] = (1 - u)*(1 - u)*(1 - u);
	curve[1] = (3 * u)*(1 - u)*(1 - u);
	curve[2] = (3 * u * u)* (1 - u);
	curve[3] = (u * u * u);
	glm::vec3 result = cp[0] * curve[0] +
		cp[1] * curve[1] +
		cp[2] * curve[2] +
		cp[3] * curve[3];
	return result;
}


//takes control points and uses uv to define surface, returns cp grid of 4x4

glm::vec3 MyView::BezierSurface(const std::vector<glm::vec3> &cp, float u, float v)
{
	std::vector<glm::vec3> curve{ 4 };
	for (int o = 0; o < 4; o++)
	{
		// 4 points for the beziercurve
		std::vector<glm::vec3> cpus{ 4 };
		cpus[0] = cp[o * 4];
		cpus[1] = cp[o * 4 + 1];
		cpus[2] = cp[o * 4 + 2];
		cpus[3] = cp[o * 4 + 3];
		curve[o] = BezierCurve(cpus, u);
	}
	//returning the curve
	return BezierCurve(curve, v);

}
