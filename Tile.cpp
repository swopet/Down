#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>
#define SQRT_3 1.73205080757
#define SQRT_2 1.41421356237

class Tile {
	private:
		GLfloat color[3];
		GLfloat base_height;
		GLfloat height;
	public:
		Tile (){
			base_height = 5;
			color[0] = 1.0;
			color[1] = 1.0;
			color[2] = 1.0;
		}
		void set_color(GLfloat new_color[]){
			color[0] = new_color[0];
			color[1] = new_color[1];
			color[2] = new_color[2];
		}
		void set_height(GLfloat new_height){
			base_height = new_height;
		}
		void draw(bool highlight = false){
			for (int i = 0; i < 2; i++){
				glLineWidth(2.0);
				glEnable(GL_COLOR_MATERIAL);
				glPushMatrix();
				if (i == 0){
					glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
					glLineWidth(2.0);
					glColor3f(0.0,0.0,0.0);
					glScalef(1.001,1.001,1.001);
				}
				else {
					glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
					if (highlight){
						glColor3f(1.0,1.0,1.0);
					}
					else{
						glColor3fv(color);
					}
				}
				
				glBegin(GL_QUADS);
				//bottom
				glNormal3f(0.0,-1.0,0.0);
				glVertex3f(-0.5,0.0,-0.5);
				glVertex3f(-0.5,0.0,0.5);
				glVertex3f(0.5,0.0,0.5);
				glVertex3f(0.5,0.0,-0.5);
				glEnd();
				//sides
				for (int i = 0; i < 4; i++){
					glPushMatrix();
					glNormal3f(-1.0,0.0,0.0);
					glRotatef(90*i,0.0,1.0,0.0);
					glBegin(GL_QUADS);
					glVertex3f(-0.5,0.0,-0.5);
					glVertex3f(-0.5,height,-0.5);
					glVertex3f(-0.5,height,0.5);
					glVertex3f(-0.5,0.0,0.5);
					glEnd();
					glPopMatrix();
				}
				//top
				glNormal3f(0.0,1.0,0.0);
				glBegin(GL_QUADS);
				glVertex3f(-0.5,height,-0.5);
				glVertex3f(-0.5,height,0.5);
				glVertex3f(0.5,height,0.5);
				glVertex3f(0.5,height,-0.5);
				glEnd();
				glPopMatrix();
			}
		}
		void update(int t){
			height = base_height;// + 1.0 + 0.5*sin((double)t*M_PI/360.0);
		}
};