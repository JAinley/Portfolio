#pragma once

#include <scene/scene_fwd.hpp>
#include <tygra/WindowViewDelegate.hpp>
#include <tgl/tgl.h>
#include <glm/glm.hpp>
#include <map>

#include <vector>
#include <memory>

class MyView : public tygra::WindowViewDelegate
{
public:
    
    MyView();
    
    ~MyView();
    
    void setScene(const scene::Context * scene);

private:

    void windowViewWillStart(tygra::Window * window) override;
    
    void windowViewDidReset(tygra::Window * window,
                            int width,
                            int height) override;

    void windowViewDidStop(tygra::Window * window) override;
    
    void windowViewRender(tygra::Window * window) override;

private:

    const scene::Context * scene_;

	GLuint draw_sponza_{ 0 };

	struct MeshGL
	{
		// VertexBufferObject for the vertex positions
		GLuint position_vbo{ 0 };

		// VertexBufferObject for the elements (indices)
		GLuint element_vbo{ 0 };

		// VertexArrayObject for the shape's vertex array settings
		GLuint vao{ 0 };

		//my vbo
		GLuint MyVBOid{ 0 };

		// Needed for when we draw using the vertex arrays
		int element_count{ 0 };
	};
	
	MeshGL mesh_;

	std::map<scene::MeshId, MeshGL> meshes_;

	const static GLuint kNullId = 0;
	enum VertexAttribIndexes {
		kVertexPosition = 0,
		kVertexColour = 1
	};
	enum FragmentDataIndexes {
		kFragmentColour = 0
	};

};


//scene::GeometryBuilder builder;
//const auto& meshes_ = builder.getAllMeshes();
//for (const auto& meshes_ : meshes_) {
//	MeshGL& newMesh = meshes_[meshes_.getId()];

//}