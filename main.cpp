// Possible solution to labs 1 and 2
// If you have your glew, freeglut and GLM librarie setup, this should work if you just replace your main.cpp with this file
// The solution is not complete, e.g. you should put your shaders in text files and create a shader class using https://learnopengl.com/Getting-started/Shaders
// But it should help you better understand using multiple shader programmes, uniform variables and multible vertex buffers, keyboard/mouse control
// The main/most important content is in the init() and display() functions
// keyboard control using z and x keys

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>

// These three includes will give us (almost?) everything we need from the GLM library for now
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <maths_funcs.h>

// Assimp includes
#include <assimp/cimport.h> // scene importer
#include <assimp/scene.h> // collects data
#include <assimp/postprocess.h> // various extra operations

#include "Terrain.h"
#include "war_src/CollisionSquare.h"
#include "Camera.h"
#include "war_src/GLMetaseq.h"
#include "war_src/BombArray.h"
#include "Tank.h"
#include "AutoTank.h"
#include "war_src/AutoWarControl.h"


static unsigned int gViewMode = 0;
static float gFogDensity = 0.000005;
static int gWinWidth = 1200;
static int gWinHeight = 600;
static float gMoveDelta = 2.0;
static float gAngleTankDelta = 3.0;


//object
Terrain myTerrain;
CollisionSquare groundCollSquare;
static float gRadViewAngle;
static TVector gCameraPosition;
BombArray bombArray;
CollisionBoxArray collisionBoxArray;
Tank myTank;
AutoTank autoTank;
AutoTank autoTank2;

static float gAutoBombVelocityMag = 1.8;
static float gBombVelocityMag = 2.0;
static float gAngleGunDelta = 5.0;
static float gBombVelocityMagDelta = 0.4;
static float gTimeStep = 0.6;
static float topdownViewHeight = 300;
static float diffuse_value = 0.1;
static float specular_value = 0.1;
static float ambient_value = 0.1;
AutoWarControl autoWarControl;

static TVector gCenterPoint(mapX * mapScale*0.5, 5.0,  -mapZ * mapScale*0.5);

static float tankHeightPos;
Camera camera(gCenterPoint.X(), 30.0, gCenterPoint.Z(), gCenterPoint.X()+100.0, 10.0, gCenterPoint.Z(),0.0,1.0,0.0);
static TVector gAcceleBomb(0.0, -0.02, 0.0);

using namespace std;

void draw()
{
    if(myTank.getlife()){
        glEnable(GL_DEPTH_TEST);

        //draw terrain
        glDisable(GL_LIGHTING);
        myTerrain.drawTerrain();
        glEnable(GL_LIGHTING);

        glDisable(GL_FOG);
        bombArray.draw();
        glEnable(GL_FOG);

        myTank.draw();

        //draw autoTank
        autoTank.draw();
        autoTank2.draw();

        glDisable(GL_DEPTH_TEST);
    }
    else{
        for(int i = 0; i < 3; i ++){
            glEnable(GL_DEPTH_TEST);

            //draw terrain
            glDisable(GL_LIGHTING);
            myTerrain.drawTerrain();
            glEnable(GL_LIGHTING);

            glDisable(GL_FOG);
            bombArray.draw();
            glEnable(GL_FOG);

            myTank.draw();

            //draw autoTank
            autoTank.draw();
            autoTank2.draw();

            glDisable(GL_DEPTH_TEST);
        }
    }

}

void caculateCameraView(unsigned int viewMode) {
    switch(viewMode) {
        case 0:
            // first person view
            gRadViewAngle = M_PI * myTank.getAngleWithX() / 180.0 - M_PI;
            gCameraPosition.setX(myTank.getPosition().X() + 150 * cos(gRadViewAngle));
            gCameraPosition.setY(myTank.getPosition().Y() + 30.0);
            gCameraPosition.setZ(myTank.getPosition().Z() - 150 * sin(gRadViewAngle));

            camera.changePosition(gCameraPosition);
            camera.changeTarget(gCameraPosition.X() - 150.0 * cos(gRadViewAngle), gCameraPosition.Y(),
                                gCameraPosition.Z() + 150.0 * sin(gRadViewAngle));
            camera.changeUpDirection(0, 1, 0);
            break;
        case 1:
            //  top-down view
            //  eye position    tank.posx, 300, tank.posz
            //  target position tank.posx, 0,   tank.posz
            //  upDirection     1  0  0
            gRadViewAngle = M_PI * myTank.getAngleWithX() / 180.0 - M_PI;
            gCameraPosition.setX(myTank.getPosition().X());
            gCameraPosition.setY(topdownViewHeight);
            gCameraPosition.setZ(myTank.getPosition().Z());
            camera.changePosition(gCameraPosition);
            camera.changeTarget(gCameraPosition.X(), 0,
                                gCameraPosition.Z());
            camera.changeUpDirection(1, 0, 0);
            break;
    }
}


void GameDisplay()
{
    glViewport(0, 0, gWinWidth, gWinHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)gWinWidth/(double)gWinHeight, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    caculateCameraView(gViewMode);
    camera.view();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    draw();
    glutSwapBuffers();
}

void mySetLight()
{
//    GLfloat diffuse[]={0.9, 0.9, 0.9, 1.0};
//    GLfloat specular[]={1.0, 1.0, 1.0, 1.0};
    GLfloat diffuse[]={diffuse_value, diffuse_value, diffuse_value, 1.0};
    GLfloat specular[]={specular_value, specular_value, specular_value, 1.0};
    GLfloat ambient[]={ambient_value, ambient_value, ambient_value, 0.1};
    GLfloat position[]= {0, 0.0, 0.0, 1.0};

    glLightfv(GL_LIGHT0,GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
//    glEnable(GL_COLOR_MATERIAL);//启用颜色追踪
//    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
}

void gameInit()
{
    //set the sky color
    float blue[4] = {0.5,0.5,1.0,0.0};
    glClearColor(0.5, 0.5, 1.0, 0.0);

    glShadeModel(GL_SMOOTH);

    mqoInit();

    glEnable(GL_FOG);
    glFogfv(GL_FOG_COLOR,blue);
    glFogf(GL_FOG_MODE, GL_EXP2);
    glFogf(GL_FOG_START, 1.0);
    glFogf(GL_FOG_END, 5.0);
    glFogf(GL_FOG_DENSITY, gFogDensity);

    //initial terrain
    myTerrain.initializeTerrain("D:/Projects/Graphics/BattleZone/Models/Texture/Terrain/snow1.tga", "D:/Projects/Graphics/BattleZone/Models/Texture/Terrain/trees.tga");

    groundCollSquare.setParameters(TVector(0.0, 1.0, 0.0), gCenterPoint);

    //initial bomb array
    bombArray.setParForBombType(tankBomb_Type, gAcceleBomb, "D:/Projects/Graphics/BattleZone/Models/Texture/Explosion/tankBombEx.tga", "D:/Projects/Graphics/BattleZone/Models/Sound/bombTank.wav");

    bombArray.setParForCollision(&groundCollSquare, &collisionBoxArray);

    tankHeightPos = myTerrain.GetHeight(gCenterPoint.X()+100.0, gCenterPoint.Z());

    myTank.setParameters("D:/Projects/Graphics/BattleZone/Models/Mqo/Tank/bodyTank.mqo", "D:/Projects/Graphics/BattleZone/Models/Mqo/Tank/gunTank.mqo", TVector(gCenterPoint.X()+100.0, tankHeightPos + 9.0, gCenterPoint.Z()), 0.0, &myTerrain, gBombVelocityMag,  &bombArray, &collisionBoxArray);
    myTank.setGunLong(20.0);
    myTank.setAutoBombVelocityMag(gAutoBombVelocityMag);
    myTank.initTank();

    autoTank.setParameters("D:/Projects/Graphics/BattleZone/Models/Mqo/AutoTank/t70.mqo", TVector(gCenterPoint.X()+100.0, tankHeightPos + 6.4, gCenterPoint.Z()), 0.08, &myTerrain, &bombArray, &collisionBoxArray);
    autoTank.initAutoTank();
    autoTank.setTargetObject(&myTank);

    autoTank2.setParameters("D:/Projects/Graphics/BattleZone/Models/Mqo/AutoTank/t70.mqo", TVector(gCenterPoint.X()+100.0, tankHeightPos + 6.4, gCenterPoint.Z()), 0.08, &myTerrain, &bombArray, &collisionBoxArray);
    autoTank2.initAutoTank();
    autoTank2.setTargetObject(&myTank);

    autoWarControl.setParameters(&myTank);
    autoWarControl.addAutoTank(&autoTank);
    autoWarControl.addAutoTank(&autoTank2);
    autoWarControl.init();
    autoWarControl.autoTankStart(2);

    myTank.startFight();
    mySetLight();

}
void myReshape(int width, int height)
{
    gWinWidth=width;
    gWinHeight=height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width/(GLfloat)height, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mySpecialKeyboard(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_LEFT:				//move to left
            myTank.plusAngleWithX(gAngleTankDelta);
            break;
        case GLUT_KEY_RIGHT:			//move to right
            myTank.plusAngleWithX(-gAngleTankDelta);
            break;
        case GLUT_KEY_UP:				//move to up
            myTank.move_front_back(gMoveDelta);
            break;
        case GLUT_KEY_DOWN:				//move to right
            myTank.move_front_back(-gMoveDelta);
            break;
        case GLUT_KEY_F1:				//view 1
            gViewMode = 0;
            break;
        case GLUT_KEY_F2:				//view 2
            gViewMode = 1;
            break;
        case GLUT_KEY_F3:
            topdownViewHeight -= 10;
            break;
        case GLUT_KEY_F4:
            topdownViewHeight += 10;
            break;
        case GLUT_KEY_F5:				//view
            diffuse_value += 0.1;
            if (diffuse_value > 1.0)
                diffuse_value = 0.0;
            mySetLight();
            cout << "light_value = " << diffuse_value << " " << specular_value << " " << ambient_value << endl;
            break;
        case GLUT_KEY_F6:				//view 2
            specular_value += 0.1;
            if (specular_value > 1.0)
                specular_value = 0.0;
            mySetLight();
            cout << "light_value = " << diffuse_value << " " << specular_value << " " << ambient_value << endl;
            break;
        case GLUT_KEY_F7:
            ambient_value += 0.1;
            if (ambient_value > 1.0)
                ambient_value = 0.0;
            mySetLight();
            cout << "light_value = " << diffuse_value << " " << specular_value << " " << ambient_value << endl;
            break;
    }
}

void myKeyboard(unsigned char key,int x,int y)
{
    switch (key)
    {
        case 'a':				//move to left
            myTank.move_left_right(-gMoveDelta);
            break;
        case 'd':				//move to right
            myTank.move_left_right(gMoveDelta);
            break;
        case 'w':				//move to up
            myTank.move_front_back(gMoveDelta);
            break;
        case 's':				//move back
            myTank.move_front_back(-gMoveDelta);
            break;
        case 'g':					//decrease gun angle
            myTank.plusGunAngle(-gAngleGunDelta);
            break;
        case 'G':					//increase gun angle
            myTank.plusGunAngle(gAngleGunDelta);
            break;
        case ' ':					//shot generally bomb
            myTank.shot();
            break;
        case 'v':					//decrease generally bomb velocity
            myTank.plusBombVelocityMag(-gBombVelocityMagDelta);
            break;
        case 'V':					//increase generally bomb velocity
            myTank.plusBombVelocityMag(gBombVelocityMagDelta);
            break;

        case 'f':					//decrease fog density
            if(gFogDensity > 0.0005)
            {
                gFogDensity -= 0.0005;
                glFogf(GL_FOG_DENSITY, gFogDensity);
            }
            break;
        case 'F':					//increase fog density
            if(gFogDensity < 0.99)
            {
                gFogDensity += 0.001;
                glFogf(GL_FOG_DENSITY, gFogDensity);
            }
            break;
        case 'r':					//reset game
            myTank.startFight();
            break;
        case 27:					//exit game
            exit(0);
            break;

        default:
            break;
    }
}

void myIdle()
{
    caculateCameraView(gViewMode);
    bombArray.checkCollision(gTimeStep);
    autoTank.update(gTimeStep);
    autoTank2.update(gTimeStep);
    autoWarControl.update(gTimeStep);
    glutPostRedisplay();
}

//显示至少一个 3D 多边形网格——您可以生成此网格或从文件加载场景/对象；
//允许使用键盘/鼠标或其他设备对部分 3D 场景进行交互式操作（即变换）；
//包括至少一个复杂的对象，其层次结构正在发生变化；
//场景必须有光照和阴影； 包括漫射和镜面物体；

//支持至少两个不同的相机视图，例如，
//a) 第一人称视角，允许用户在场景中行走或飞行； b）自上而下的视图（例如俯视图）

//Allow interactive manipulation of part of the 3D scene (i.e. transforms) using keyboard/mouse or some other device;
//


//Finished
//Display at least one 3D polygon mesh - you may generate this or load scene/objects from a file;
//Include at least one complex object with a hierarchical structure undergoing transformations;
//Support at least two different camera views, e.g.,
//a) first person view with camera movements allowing user to walk or fly through the scene; b) top down view (e.g. overhead map)
//The scene must be lit and shaded; including diffuse and specular objects;




int main(int argc, char** argv) {

	// Set up the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(gWinWidth, gWinHeight);
    glutInitWindowPosition(0, 0);
	glutCreateWindow("BattleZone");

    gameInit();

	// Register Call Back funtions
	glutDisplayFunc(GameDisplay);
    glutReshapeFunc(myReshape);
    glutIdleFunc(myIdle);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKeyboard);

	GLenum res = glewInit();
	// Check for any errors
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}
	glutMainLoop();
	return 0;
}












