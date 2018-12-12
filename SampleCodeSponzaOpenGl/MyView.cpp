#include "MyView.hpp"
#include <scene/scene.hpp>
#include <tygra/FileHelper.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cassert>

MyView::MyView()
{
}

MyView::~MyView() {
}

void MyView::setScene(const scene::Context * scene)
{
    scene_ = scene;
}

void MyView::windowViewWillStart(tygra::Window * window)
{
    assert(scene_ != nullptr);

	GLint compile_status = GL_FALSE;

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertex_shader_string
		= tygra::createStringFromFile("resource:///sponza_vs.glsl");
	const char * vertex_shader_code = vertex_shader_string.c_str();
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
		= tygra::createStringFromFile("resource:///sponza_fs.glsl");
	const char * fragment_shader_code = fragment_shader_string.c_str();
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


	draw_sponza_ = glCreateProgram();
	glAttachShader(draw_sponza_, vertex_shader);
	glBindAttribLocation(draw_sponza_, kVertexPosition, "vertex_position");
	glBindAttribLocation(draw_sponza_, kVertexColour, "vertex_colour");
	glDeleteShader(vertex_shader);
	glAttachShader(draw_sponza_, fragment_shader);
	glBindFragDataLocation(draw_sponza_, kFragmentColour, "fragment_colour");
	glDeleteShader(fragment_shader);
	glLinkProgram(draw_sponza_);


	GLint link_status = GL_FALSE;
	glGetProgramiv(draw_sponza_, GL_LINK_STATUS, &link_status);
	if (link_status != GL_TRUE) {
		const int string_length = 1024;
		GLchar log[string_length] = "";
		glGetProgramInfoLog(draw_sponza_, string_length, NULL, log);
		std::cerr << log << std::endl;
	}

	//std::vector<glm::vec2> positions;
	//std::vector<unsigned int> elements;
	std::vector<glm::vec3> colour;

	scene::GeometryBuilder builder;

	const auto& source_mesh = builder.getAllMeshes();

	for (const auto& source_mesh : source_mesh)
	{
		MeshGL& NewMesh = meshes_[source_mesh.getId()];
		const auto& positions = source_mesh.getPositionArray();
		const auto& elements = source_mesh.getElementArray();
	

		glGenBuffers(1, &NewMesh.position_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, NewMesh.position_vbo);
		glBufferData(GL_ARRAY_BUFFER,
			positions.size() * sizeof(glm::vec3), // size of data in bytes
			positions.data(), // pointer to the data
			GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, kNullId);


		glGenBuffers(1, &NewMesh.element_vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NewMesh.element_vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			elements.size() * sizeof(unsigned int),
			elements.data(),
			GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kNullId);
		NewMesh.element_count = elements.size();

		glGenVertexArrays(1, &NewMesh.vao);
		glBindVertexArray(NewMesh.vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NewMesh.element_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, NewMesh.position_vbo);


		glEnableVertexAttribArray(kVertexPosition);
		glVertexAttribPointer(kVertexPosition, 2, GL_FLOAT, GL_FALSE,
			sizeof(glm::vec3), TGL_BUFFER_OFFSET(0));

		glBindVertexArray(kNullId);
	
	}

}

void MyView::windowViewDidReset(tygra::Window * window,
                                int width,
                                int height)
{
    glViewport(0, 0, width, height);
}

void MyView::windowViewDidStop(tygra::Window * window)
{
	glDeleteProgram(draw_sponza_);
	for (int i = 0; i < meshes_.size(); i++)
	{
		glDeleteBuffers(1, &meshes_[i].position_vbo);
		glDeleteBuffers(1, &meshes_[i].MyVBOid);
		glDeleteBuffers(1, &meshes_[i].element_vbo);
		glDeleteVertexArrays(1, &meshes_[i].vao);
	}

}

void MyView::windowViewRender(tygra::Window * window)
{
    assert(scene_ != nullptr);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

    glClearColor(0.f, 0.f, 0.25f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);

	GLint viewport_size[4];
	glGetIntegerv(GL_VIEWPORT, viewport_size);
	const float aspect_ratio = viewport_size[2] / (float)viewport_size[3];

	glm::mat4 projection_xform = glm::perspective(scene_->getCamera().getVerticalFieldOfViewInDegrees(), aspect_ratio, scene_->getCamera().getNearPlaneDistance(), scene_->getCamera().getFarPlaneDistance());
	glm::mat4 view_xform = glm::lookAt(scene_->getCamera().getPosition(), scene_->getCamera().getPosition() + scene_->getCamera().getDirection(), glm::vec3(0, 1, 0));
	for (const auto& instance : scene_->getAllInstances())
	{
		glm::mat4 model_xform = glm::mat4(instance.getTransformationMatrix());
		glm::mat4 combined_xform = projection_xform * view_xform * model_xform;


		glUseProgram(draw_sponza_);


		glm::vec3 yellow(1.0, 1.0, 0.0);
		GLuint shader_id = glGetUniformLocation(draw_sponza_, "uniform_shader");

		glUniform3fv(shader_id, 1, glm::value_ptr(yellow));

		GLuint mystery_xform_id = glGetUniformLocation(draw_sponza_,
			"model_xform");
		glUniformMatrix4fv(mystery_xform_id,
			1, GL_FALSE, glm::value_ptr(combined_xform));



		glBindVertexArray(meshes_[instance.getMeshId()].vao);

		glUniformMatrix4fv(mystery_xform_id,
			1, GL_FALSE, glm::value_ptr(combined_xform));
		glDrawElements(GL_TRIANGLES, meshes_[instance.getMeshId()].element_count, GL_UNSIGNED_INT, 0);
	}



}
