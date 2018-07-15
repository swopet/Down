#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>
#define SQRT_3 1.73205080757
#define SQRT_2 1.41421356237

class Player {
	private:
		double angle;
		float speed = 0.15;
	public:
		sf::Vector3f pos;
		Player(){
			pos = sf::Vector3f(10.0,5.0,10.0);
			angle = 45.0;
		}
		~Player() {
			//Destructor
		}
		void transform(){
			glRotatef(-angle,0.0,1.0,0.0);
			glTranslatef(-pos.x,-pos.y,-pos.z);
		}
		void move(sf::Vector2f dir){
			double move_angle = atan2(dir.y,dir.x);
			double angle_radians = angle * M_PI/180.0;
			pos += speed*sf::Vector3f(cos(move_angle+angle_radians),0.0,-sin(move_angle+angle_radians));
		}
		void rotate(double degrees){
			angle += degrees;
			if (angle < 0.0) angle = angle + 360.0;
			if (angle > 360.0) angle = angle - 360.0;
		}
		void draw(){
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			glPushMatrix();
			glTranslatef(pos.x,pos.y,pos.z);
			glTranslatef(0.0,0.5,0.0);
			glColor3f(0.0,1.0,0.8);
			glBegin(GL_TRIANGLES);
			glNormal3f(0.0,-1.0,0.0);
			glVertex3f(-0.5,0.0,0.5/SQRT_3);
			glVertex3f(0.0,0.0,0.5/SQRT_3-SQRT_3/2.0);
			glVertex3f(0.5,0.0,0.5/SQRT_3);
			glNormal3f(SQRT_3/2.0,0.5,0.0);
			glVertex3f(0.5,0.0,0.5/SQRT_3);
			glVertex3f(0.0,SQRT_3,0.0);
			glVertex3f(-0.5,0.0,0.5/SQRT_3);
			glNormal3f(-SQRT_3*SQRT_2/4.0,0.5,-SQRT_3*SQRT_2/4.0);
			glVertex3f(-0.5,0.0,0.5/SQRT_3);
			glVertex3f(0.0,SQRT_3,0.0);
			glVertex3f(0.0,0.0,0.5/SQRT_3-SQRT_3/2.0);
			glNormal3f(SQRT_3*SQRT_2/4.0,0.5,-SQRT_3*SQRT_2/4.0);
			glVertex3f(0.0,0.0,0.5/SQRT_3-SQRT_3/2.0);
			glVertex3f(0.0,SQRT_3,0.0);
			glVertex3f(0.5,0.0,0.5/SQRT_3);
			glEnd();
			glPopMatrix();
		}
	};