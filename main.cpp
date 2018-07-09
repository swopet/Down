#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>
#define SQRT_3 1.73205080757
#define SQRT_2 1.41421356237

sf::RenderWindow * window;
double aspect;
int frame = 0;

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

Player * player;

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

class Scene {
private:
    Tile * tiles;
    int width;
    int length;
public:
    Scene(int new_width = 10, int new_length = 10){
        width = new_width;
        length = new_length;
        tiles = (Tile *)malloc(width*length*sizeof(Tile));
        GLfloat heights[width*length];
        GLfloat new_height;
        for (int x = 0; x < width; x++){
            for (int z = 0; z < length; z++){
                new_height = 5.0;
                
                heights[x*length+z] = new_height;
                
            }
        }
        for (int x = 0; x < width; x++){
            for (int z = 0; z < length; z++){
                int curr_x;
                int curr_z;
                //smooth it out a bit here
                new_height = 0.0;
                curr_x = x;
                curr_z = z;
                new_height += 0.4*heights[curr_x*length+curr_z];
                if (x == 0) curr_x = x;
                else curr_x = x-1;
                new_height += 0.15*heights[curr_x*length+curr_z];
                if (x == width-1) curr_x = x;
                else curr_x = x+1;
                new_height += 0.15*heights[curr_x*length+curr_z];
                curr_x = x;
                if (z == 0) curr_z = z;
                else curr_z = z-1;
                new_height += 0.15*heights[curr_x*length+curr_z];
                if (z == length-1) curr_z = z;
                else curr_z = z+1;
                new_height += 0.15*heights[curr_x*length+curr_z];
                GLfloat new_color[] = {1.0-new_height/10.0,0.0,new_height/10.0};
                tiles[x*length+z].set_height(new_height);
                tiles[x*length+z].set_color(new_color);
            }
        }
    }
    void draw(){
        for (int x = 0; x < width; x++){
            for (int z = 0; z < length; z++){
                glPushMatrix();
                glTranslatef(x,0.0,z);
                tiles[x*length+z].draw(((int)player->pos.x ==x && (int)player->pos.z==z));
                glPopMatrix();
            }
        }
    }
    void update(){
        for (int x = 0; x < width; x++){
            for (int z = 0; z < length; z++){
                tiles[x*length+z].update(frame);
            }
        }
    }
};

Scene * demo_scene;

void update(){
    frame++;
    demo_scene->update();
}


void draw_scene(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,window->getSize().x,window->getSize().y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0,1.0,-aspect,aspect,-100.0,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glScalef(0.1,0.1,0.1);
    glRotatef(30.0,1.0,0.0,0.0);
    player->transform();
	
	player->draw();
    demo_scene->draw();
}

void init(){
    srand(time(NULL));
    aspect = (double)window->getSize().x/(double)window->getSize().y;
    demo_scene = new Scene(20,20);
	player = new Player();
    glClearColor(0.0,0.0,0.0,1.0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

int main()
{
    sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 0;
	settings.antialiasingLevel = 8;
	settings.majorVersion = 3;
	settings.minorVersion = 0;
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "One Windowy Boi", sf::Style::Default, settings);
    init();
    while (window->isOpen())
    {
        sf::Event event;
        bool moved = false;
		sf::Vector2f move_dir(0.0,0.0);
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			move_dir += sf::Vector2f(0.0,1.0);
			moved = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			move_dir += sf::Vector2f(0.0,-1.0);
			moved = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			player->rotate(-0.5);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			player->rotate(0.5);
		}
		if (moved){
			player->move(move_dir);
		}
        update();
        draw_scene();
        window->display();
    }
}