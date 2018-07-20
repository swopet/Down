#include "Mesh.hpp"
//I should put this somewhere else
void multiply_vector(GLfloat * vec, GLfloat * matrix){
	sf::Vector3f buffer;
	buffer.x = vec[0]*matrix[0] + vec[1]*matrix[4] + vec[2]*matrix[8] + 1*matrix[12];
	buffer.y = vec[0]*matrix[1] + vec[1]*matrix[5] + vec[2]*matrix[9] + 1*matrix[13];
	buffer.z = vec[0]*matrix[2] + vec[1]*matrix[6] + vec[2]*matrix[10] + 1*matrix[14];
	vec[0]=buffer.x;
	vec[1]=buffer.y;
	vec[2]=buffer.z;
}

namespace Mesh{
	Mesh::Mesh(default_mesh mesh_type=EMPTY)
	{
		switch(mesh_type){
			case EMPTY:
				numVertices = 0;
				numTriangles = 0;
				vertices = NULL;
				indices = NULL;
				break;
			case CUBE_MESH:
				numVertices = 24;
				numTriangles = 12;
				vertices = (GLfloat *)malloc(10*numVertices*sizeof(GLfloat));
				indices = (GLuint *)malloc(3*numTriangles*sizeof(GLuint));
				for (int i = 0; i < 6; i++){
					glMatrixMode(GL_MODELVIEW);
					glPushMatrix();
					glLoadIdentity();
					if (i!=0){
						glRotatef(90.0*i,0.0,1.0,0.0);
						glRotatef(90.0,1.0,0.0,0.0);
					}
					GLfloat curr_matrix[16];
					glGetFloatv(GL_MODELVIEW_MATRIX,curr_matrix);
					for (int j = 0; j < 4; j++){
						int ind = (i*4+j)*10;
						//COLOUR
						vertices[ind] = 1.0;
						vertices[ind+1] = 1.0;
						vertices[ind+2] = 1.0;
						vertices[ind+3] = 1.0;
						//NORMAL
						vertices[ind+4] = 0.0;
						vertices[ind+5] = 1.0;
						vertices[ind+6] = 0.0;
						//VERTEX
						vertices[ind+7] = (j==0 || j==3) ? -0.5 : 0.5;
						vertices[ind+8] = 0.5;
						vertices[ind+9] = (j==0 || j==1) ? -0.5 : 0.5;
						multiply_vector(&vertices[ind+4],curr_matrix);
						multiply_vector(&vertices[ind+7],curr_matrix);
					}
					glPopMatrix();
					indices[i*6] = i*4;
					indices[i*6+1] = i*4+1;
					indices[i*6+2] = i*4+2;
					indices[i*6+3] = i*4+2;
					indices[i*6+4] = i*4+3;
					indices[i*6+5] = i*4;
				}
				break;
		}
	}

	Mesh::~Mesh()
	{
	}
	
	int Mesh::get_numTriangles() {
		return numTriangles;
	}
	
	int Mesh::get_numVertices() {
		return numVertices;
	}
	
	void Mesh::draw(){
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glInterleavedArrays(GL_C4F_N3F_V3F,0,vertices);
		glDrawElements(GL_TRIANGLES,3*numTriangles,GL_UNSIGNED_INT,indices);
	}
}

