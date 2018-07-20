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
			int numVertices;
			int numTriangles;
			GLfloat * vertices;
			GLuint * indices;
		public:
			Mesh(default_mesh);
			~Mesh();
			
			int get_numVertices();
			int get_numTriangles();
			
			void draw();
	};
}

#endif // MESH_HPP
