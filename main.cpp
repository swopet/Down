#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>

sf::RenderWindow * window;
double aspect;
int frame = 0;


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
    void draw(){
        glEnable(GL_COLOR_MATERIAL);
        glColor3fv(color);
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
    }
    void update(int t){
        height = base_height + 1.0 + 0.5*sin((double)t*M_PI/360.0);
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
                new_height = 0 + rand()%11;
                
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
                glTranslatef(-width/2+x,0.0,-length/2+z);
                tiles[x*length+z].draw();
                glPopMatrix();
            }
        }
    }
    void update(){
        for (int x = 0; x < width; x++){
            for (int z = 0; z < length; z++){
                tiles[x*length+z].update(frame+(x+z)*30);
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
    glRotatef(45.0,0.0,1.0,0.0);
    demo_scene->draw();
}

void init(){
    srand(time(NULL));
    aspect = (double)window->getSize().x/(double)window->getSize().y;
    demo_scene = new Scene(20,20);
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
        
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
        }
        update();
        draw_scene();
        window->display();
    }
}