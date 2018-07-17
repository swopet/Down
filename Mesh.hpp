#ifndef MESH_HPP
#define MESH_HPP
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

namespace Mesh{
	enum default_mesh {
		CUBE_MESH,
		EMPTY
	};
	class Mesh
	{
	private:
		int num_vertices;
		int num_triangles;
		GLfloat * vertices;
		GLuint * indices;
	public:
		Mesh(default_mesh);
		~Mesh();
		void draw();
	};
}

#endif // MESH_HPP
