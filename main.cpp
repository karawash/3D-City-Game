/////////////////////////////// BY AHMAD KARAWASH  ////////////////////////////////////////////////
///A SMALL CITY CAR GAME
///YOU MAY USE THESE CABS FROM THE KEYBOARD SMALL LETTER (CASE SENSITVE) :
///-  w :to go forward
///-  d :to go right
///-  a :to go left
///-  m :to increase spead
///-  l :to move camera left
///-  r :to move camera right
///-  s :to break

/// NOTE: this work is done depending on my on skills in c language and opengl  and it take more than 10 days of work
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "imageloader.h"

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
//#include "text3d.h"
using namespace std;
#define SND_LOOP 8
#define SND_ASYNC 1


#define	checkImageWidth  64
#define	checkImageHeight 64
GLubyte checkImage[checkImageHeight][checkImageWidth][3];

static GLdouble zoomFactor = 0.07;//1.0;
static GLint height;

 
float _angle = 0;             
GLuint  FloorId,
SkyId,
WaterId,
treeId,
WallId,carId,bldId,bldId1,
wall2Id,wall3Id,treeflrId,
wall4Id,woodId,carsId;           //The OpenGL id of the texture

GLuint Room;

   float x=0;
   float y=1,k1=0,k2=8,k3=0;
   float q=0;
   float p=90;
int e=80,d=80,e1=-80,d1=-80;
double PI=3.14159265359;         // define PI

           
GLfloat speed;                   // speed to move
            
int k=0;
float a=0,b=1,a1=90,s=0,z=0,a3=90,t1;
float angle=0.0; 
float r;
float slide=-0.8;
///Makes the image into a texture, and returns the id of the texture
///all what i used to load images exists on video tutorial rock
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGB,
				 image->width, image->height,
				 0,
				 GL_RGB,
				 GL_UNSIGNED_BYTE,
				 image->pixels);
	return textureId;
}

  
 

void initRendering() {
	glClearColor (0.0, 0.0, 0.0, 0.0);
   	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	
	Image* imagefl  = loadBMP("flr2.bmp");//i draw this picture by paint
	FloorId = loadTexture(imagefl);
	delete imagefl;
	
	Image* images = loadBMP("mer.bmp");//Sky2
	carsId = loadTexture(images);
	delete images;
	
	Image* imagewl = loadBMP("build1.bmp");//pic
	WallId= loadTexture(imagewl);
	delete imagewl;
	
	Image* imagewt = loadBMP("build2.bmp");//
	wall2Id= loadTexture(imagewt);
	delete imagewt;
	
	Image* imagewtt = loadBMP("wood.bmp");
	woodId= loadTexture(imagewtt);
	delete imagewtt;

	Image* imagefi = loadBMP("tree6.bmp");
	treeId = loadTexture(imagefi);
	delete imagefi;
    
	Image* imagecar = loadBMP("car.bmp");
    carId = loadTexture(imagecar);
	delete imagecar;

	Image* imagebuild = loadBMP("build3.bmp");
    bldId = loadTexture(imagebuild);
	delete imagebuild;

	Image* imagebuild1 = loadBMP("build4.bmp");
    bldId1 = loadTexture(imagebuild1);
	delete imagebuild1;

	Image* imagetreeflr = loadBMP("treeflr.bmp");
    treeflrId = loadTexture(imagetreeflr);
	delete imagetreeflr;

	Image* imagesky = loadBMP("sky.bmp");
    SkyId = loadTexture(imagesky);
	delete imagesky;

}

void handleResize(int w, int h) {
	glColor3f(0.0,0.0,1.0);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void drawScene() {
	 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	///lighting used from video tutorial rocks
	GLfloat ambientLight[] = {1.2f, 1.2f, 9.2f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glColor3f(0.0,0.0,1.0);
	GLfloat directedLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
	
	///math equation polar coordinates r=rad(x^2+y^2) 
	r=sqrt((double)(x*x)+(double)(y*y));
	glRotatef(q, 0.0f, -b,0); //rotation of camera while car moving
	
	char s[16][9]={"Opengl","  ","  ","Project","  ","  ","done","  ","  ","by","  ","  ","Ahmad","  ","  ","Karawash"};
	
glPushMatrix();
glTranslatef(-2,slide,-5);
	glScalef(0.0009,0.0009,0);
	int k1=1,k3=30; 
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 8; j++) {
		    glColor3f(j*k1,0,i*k3);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i][j]);
	
		}
	}
	glPopMatrix();
slide-=0.01;
	

	 
	///////////////////////////////////////////////////////////////////////////////////////////
	////the  car
	//////////////////////////////////////////////////////////////////////////////////////////
	glPushMatrix(); 
    glColor3f(1.0,1.0,1.0);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, carId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	
	  glBegin(GL_POLYGON);    
	  glNormal3f( 0.0f, 1.0f, 0.0f);      
      glTexCoord2f( 0.0f, 0.5f); glVertex3f(-2.5f,-2.0f, -15.0f);
      glTexCoord2f(0.6f, 0.5f); glVertex3f(2.50f,-2.0f, -15.0f);
	  glTexCoord2f(0.6f, 0.8f); glVertex3f(2.50f, 1.0f, -15.0f);	  
	  glTexCoord2f(0.5f, 1.0f); glVertex3f(1.30f, 3.0f, -15.0f);
      glTexCoord2f( 0.3f, 1.0f);glVertex3f(0.0f,3.0f, -15.0f);
	  glTexCoord2f(0.13f, 1.0f);glVertex3f(-1.5f, 3.0f, -15.0f);
	  glTexCoord2f( 0.0f, 0.8f);glVertex3f(-2.50f, 1.0f, -15.0f);
	  
 	   
   glDisable(GL_TEXTURE_2D);
glEnd();	
glPopMatrix(); 

 

 	glPushMatrix();
	glTranslatef(a, 0.0, b);
    glRotatef(angle, 0.0, b, 0.0);  
    
	 
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, FloorId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_QUADS);
      ////////////////////////////////////////////////////////////
      // floor 
	  ///////////////////////////////////////////////////////////
      
	   glNormal3f( 0.0f, 1.0f, 0.0f);       
      glTexCoord2f( 0.0f, 0.0f); glVertex3f(-300.0f,-2.0f,0.0f);
      glTexCoord2f(100.0f, 0.0f); glVertex3f( 300.0f,-2.0f, 0.0f);
      glTexCoord2f(100.0f,100.0f); glVertex3f( 300.0f,-2.0f,-1100.0f);
      glTexCoord2f( 0.0f,100.0f); glVertex3f(-300.0f,-2.0f,-1100.0f);

	     
	  glNormal3f( 0.0f, 1.0f, 0.0f);       
      glTexCoord2f( 0.0f, 0.0f); glVertex3f(-300.0f,-2.0f, -1100.0f);
      glTexCoord2f(80.0f, 0.0f); glVertex3f( 300.0f,-2.0f, -1100.0f);
      glTexCoord2f(80.0f,80.0f); glVertex3f( 300.0f,-2.0f,-1500.0f);
      glTexCoord2f( 0.0f,80.0f); glVertex3f(-300.0f,-2.0f,-1500.0f);

     
	  glNormal3f( 0.0f, 1.0f, 0.0f);       
      glTexCoord2f( 0.0f, 0.0f); glVertex3f(-300.0f,-2.0f, -1500.0f);
      glTexCoord2f(100.0f, 0.0f); glVertex3f( 300.0f,-2.0f, -1500.0f);
      glTexCoord2f(100.0f,100.0f); glVertex3f( 300.0f,-2.0f,-2600.0f);
      glTexCoord2f( 0.0f,100.0f); glVertex3f(-300.0f,-2.0f,-2600.0f);


	  glEnd();
   glDisable(GL_TEXTURE_2D);
   ///////////////////////////////////////////////////////////////////
   /////tree floor
   ///////////////////////////////////////////////////////////////////
   glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, treeflrId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_QUADS);
  
   glNormal3f( 0.0f, 1.0f, 0.0f);      // normal points up Y axis
      glTexCoord2f( 0.0f, 0.0f); glVertex3f(20.0f,-1.9f, -300.0f);
      glTexCoord2f(50.0f, 0.0f); glVertex3f( 300.0f,-1.9f, -300.0f);
      glTexCoord2f(50.0f,50.0f); glVertex3f( 300.0f,-1.9f,-560.0f);
      glTexCoord2f( 0.0f,50.0f); glVertex3f(20.0f,-1.9f,-560.0f);

      glTexCoord2f( 0.0f, 0.0f); glVertex3f(-20.0f,-1.9f, -300.0f);
      glTexCoord2f(50.0f, 0.0f); glVertex3f( -300.0f,-1.9f, -300.0f);
      glTexCoord2f(50.0f,50.0f); glVertex3f( -300.0f,-1.9f,-560.0f);
      glTexCoord2f( 0.0f,50.0f); glVertex3f(-20.0f,-1.9f,-560.0f);


	  glEnd();
   glDisable(GL_TEXTURE_2D);
  
  ////////////////////////////////////////////////
  /////buildings   
  //////////////////////////////////////////////// 	

   glPushMatrix();
	int x=80,z;
	for(int i=1;i<4;i++){
    
   glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, WallId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		z=i*80;
	glTranslatef(x, 0.0, -z);

    glBegin(GL_QUADS);
  
	  glNormal3f(0.0f, 1.0f, 0.0f);     
      glTexCoord2f( 0.0f, 0.0f); glVertex3f( -50.0f,-2.0f,25.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -50.0f,-2.0f, -25.0f);
      glTexCoord2f(1.0f, 5.0f); glVertex3f( -50.0f, 60.0f, -25.0f);
      glTexCoord2f( 0.0f, 5.0f); glVertex3f( -50.0f, 60.0f,25.0f);
      
       glTexCoord2f( 0.0f, 0.0f); glVertex3f( 50.0f,-2.0f,25.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -50.0f,-2.0f, 25.0f);
      glTexCoord2f(1.0f, 5.0f); glVertex3f( -50.0f, 60.0f, 25.0f);
      glTexCoord2f( 0.0f, 5.0f); glVertex3f( 50.0f, 60.0f,25.0f);

      glTexCoord2f( 0.0f, 0.0f); glVertex3f( 50.0f,-2.0f,25.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( 50.0f,-2.0f, -25.0f);
      glTexCoord2f(1.0f, 5.0f); glVertex3f( 50.0f, 60.0f, -25.0f);
      glTexCoord2f( 0.0f, 5.0f); glVertex3f( 50.0f, 60.0f,25.0f);
   
	   glTexCoord2f( 0.0f, 0.0f); glVertex3f( 50.0f,-2.0f,-25.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -50.0f,-2.0f, -25.0f);
      glTexCoord2f(1.0f, 5.0f); glVertex3f( -50.0f, 60.0f, -25.0f);
      glTexCoord2f( 0.0f, 5.0f); glVertex3f( 50.0f, 60.0f,-25.0f);
      
      
	  glEnd();
	 glTranslatef(-x, 0.0, z);
glDisable(GL_TEXTURE_2D);
 
 glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wall2Id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(-x, 0.0, -z);
    glBegin(GL_QUADS);
  
	  glNormal3f(0.0f, 1.0f, 0.0f);     
      glTexCoord2f( 0.0f, 0.0f); glVertex3f( -50.0f,-2.0f,25.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -50.0f,-2.0f, -25.0f);
      glTexCoord2f(1.0f, 5.0f); glVertex3f( -50.0f, 60.0f, -25.0f);
      glTexCoord2f( 0.0f, 5.0f); glVertex3f( -50.0f, 60.0f,25.0f);
      
       glTexCoord2f( 0.0f, 0.0f); glVertex3f( 50.0f,-2.0f,25.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -50.0f,-2.0f, 25.0f);
      glTexCoord2f(1.0f, 5.0f); glVertex3f( -50.0f, 60.0f, 25.0f);
      glTexCoord2f( 0.0f, 5.0f); glVertex3f( 50.0f, 60.0f,25.0f);

      glTexCoord2f( 0.0f, 0.0f); glVertex3f( 50.0f,-2.0f,25.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( 50.0f,-2.0f, -25.0f);
      glTexCoord2f(1.0f, 5.0f); glVertex3f( 50.0f, 60.0f, -25.0f);
      glTexCoord2f( 0.0f, 5.0f); glVertex3f( 50.0f, 60.0f,25.0f);
   
	   glTexCoord2f( 0.0f, 0.0f); glVertex3f( 50.0f,-2.0f,-25.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -50.0f,-2.0f, -25.0f);
      glTexCoord2f(1.0f, 5.0f); glVertex3f( -50.0f, 60.0f, -25.0f);
      glTexCoord2f( 0.0f, 5.0f); glVertex3f( 50.0f, 60.0f,-25.0f);
      glTranslatef(0, 0.0, 0);
 
	  glEnd();
      glTranslatef(x, 0.0, z);
 glDisable(GL_TEXTURE_2D);
	}
/////////////////////////////////////////////////////////
////tree
////////////////////////////////////////////////////////
	for(int i=4;i<20;i++){int p=40;
		for(p;p<300;p+=40){	
    
   glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, treeId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	z=3*80+40+14*i;
	glTranslatef(p, 0.0, -z); 

   glBegin(GL_QUADS);
  
	  glNormal3f(0.0f, 1.0f, 0.0f);     
      glTexCoord2f( 0.0f, 0.0f); glVertex3f( -5.0f,2.0f,5.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -5.0f,2.0f, -5.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( -5.0f, 6.0f, -5.0f);
      glTexCoord2f( 0.0f, 1.0f); glVertex3f( -5.0f, 6.0f,5.0f);
      
       glTexCoord2f( 0.0f, 0.0f); glVertex3f( 5.0f,2.0f,5.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -5.0f,2.0f, 5.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( -5.0f, 6.0f,5.0f);
      glTexCoord2f( 0.0f, 1.0f); glVertex3f( 5.0f, 6.0f,5.0f);

      glTexCoord2f( 0.0f, 0.0f); glVertex3f( 5.0f,2.0f,5.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( 5.0f,2.0f, -5.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( 5.0f, 6.0f, -5.0f);
      glTexCoord2f( 0.0f, 1.0f); glVertex3f( 5.0f, 6.0f,5.0f);
   
	   glTexCoord2f( 0.0f, 0.0f); glVertex3f( 5.0f,2.0f,-5.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -5.0f,2.0f, -5.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( -5.0f, 6.0f, -5.0f);
      glTexCoord2f( 0.0f, 1.0f); glVertex3f( 5.0f, 6.0f,-5.0f);
      
    //base of tree
	   glTexCoord2f( 0.0f, 0.0f); glVertex3f( 5.0f,2.0f,-5.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -5.0f,2.0f, -5.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( -5.0f, 2.0f, 5.0f);
      glTexCoord2f( 0.0f, 1.0f); glVertex3f( 5.0f, 2.0f,5.0f);
      glEnd();
	
	  //wood of tree
   glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, woodId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   
    glBegin(GL_QUADS);
  

	  glNormal3f(0.0f, 1.0f, 0.0f);     
      glTexCoord2f( 0.0f, 0.0f); glVertex3f( -2.0f,-2.0f,2.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -2.0f,-2.0f, -2.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( -2.0f, 2.0f, -2.0f);
      glTexCoord2f( 0.0f, 1.0f); glVertex3f( -2.0f, 2.0f,2.0f);
      
       glTexCoord2f( 0.0f, 0.0f); glVertex3f( 2.0f,-2.0f,2.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -2.0f,-2.0f, 2.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( -2.0f, 2.0f,2.0f);
      glTexCoord2f( 0.0f, 1.0f); glVertex3f( 2.0f, 2.0f,2.0f);

      glTexCoord2f( 0.0f, 0.0f); glVertex3f( 2.0f,-2.0f,2.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.0f,-2.0f, -2.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f, 2.0f, -2.0f);
      glTexCoord2f( 0.0f, 1.0f); glVertex3f( 2.0f, 2.0f,2.0f);
   
	   glTexCoord2f( 0.0f, 0.0f); glVertex3f( 2.0f,-2.0f,-2.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -2.0f,-2.0f, -2.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( -2.0f, 2.0f, -2.0f);
      glTexCoord2f( 0.0f, 1.0f); glVertex3f( 2.0f, 2.0f,-2.0f);

	  glEnd();
	  glTranslatef(-p, 0.0, z);
	
	  glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, treeId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	 
	glTranslatef(-p, 0.0, -z);

   glBegin(GL_QUADS);
  
	  glNormal3f(0.0f, 1.0f, 0.0f);     
      glTexCoord2f( 0.0f, 0.0f); glVertex3f( -5.0f,2.0f,5.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -5.0f,2.0f, -5.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( -5.0f, 6.0f, -5.0f);
      glTexCoord2f( 0.0f, 1.0f); glVertex3f( -5.0f, 6.0f,5.0f);
      
       glTexCoord2f( 0.0f, 0.0f); glVertex3f( 5.0f,2.0f,5.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -5.0f,2.0f, 5.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( -5.0f, 6.0f,5.0f);
      glTexCoord2f( 0.0f, 1.0f); glVertex3f( 5.0f, 6.0f,5.0f);

      glTexCoord2f( 0.0f, 0.0f); glVertex3f( 5.0f,2.0f,5.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( 5.0f,2.0f, -5.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( 5.0f, 6.0f, -5.0f);
      glTexCoord2f( 0.0f, 1.0f); glVertex3f( 5.0f, 6.0f,5.0f);
   
	   glTexCoord2f( 0.0f, 0.0f); glVertex3f( 5.0f,2.0f,-5.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -5.0f,2.0f, -5.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( -5.0f, 6.0f, -5.0f);
      glTexCoord2f( 0.0f, 1.0f); glVertex3f( 5.0f, 6.0f,-5.0f);
      
    ////base of tree
	   glTexCoord2f( 0.0f, 0.0f); glVertex3f( 5.0f,2.0f,-5.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -5.0f,2.0f, -5.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( -5.0f, 2.0f, 5.0f);
      glTexCoord2f( 0.0f, 1.0f); glVertex3f( 5.0f, 2.0f,5.0f);
      glEnd();
	  
   glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, woodId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   
	 
    glBegin(GL_QUADS);
  

	  glNormal3f(0.0f, 1.0f, 0.0f);     
      glTexCoord2f( 0.0f, 0.0f); glVertex3f( -2.0f,-2.0f,2.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -2.0f,-2.0f, -2.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( -2.0f, 2.0f, -2.0f);
      glTexCoord2f( 0.0f, 1.0f); glVertex3f( -2.0f, 2.0f,2.0f);
      
       glTexCoord2f( 0.0f, 0.0f); glVertex3f( 2.0f,-2.0f,2.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -2.0f,-2.0f, 2.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( -2.0f, 2.0f,2.0f);
      glTexCoord2f( 0.0f, 1.0f); glVertex3f( 2.0f, 2.0f,2.0f);

      glTexCoord2f( 0.0f, 0.0f); glVertex3f( 2.0f,-2.0f,2.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.0f,-2.0f, -2.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f, 2.0f, -2.0f);
      glTexCoord2f( 0.0f, 1.0f); glVertex3f( 2.0f, 2.0f,2.0f);
   
	   glTexCoord2f( 0.0f, 0.0f); glVertex3f( 2.0f,-2.0f,-2.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -2.0f,-2.0f, -2.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( -2.0f, 2.0f, -2.0f);
      glTexCoord2f( 0.0f, 1.0f); glVertex3f( 2.0f, 2.0f,-2.0f);

      
	  glEnd();
glTranslatef(p, 0.0, z);
}
}
 
glDisable(GL_TEXTURE_2D);
/////////////////////////////////////////////////////////////////////////////
////buildings
////////////////////////////////////////////////////////////////////////////
	for(int i=8;i<32;i++){
    
   glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, bldId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		z=i*80;
	glTranslatef(x, 0.0, -z);

    glBegin(GL_QUADS);
  
	  glNormal3f(0.0f, 1.0f, 0.0f);     
      glTexCoord2f( 0.0f, 0.0f); glVertex3f( -50.0f,-2.0f,25.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -50.0f,-2.0f, -25.0f);
      glTexCoord2f(1.0f, 5.0f); glVertex3f( -50.0f, 60.0f, -25.0f);
      glTexCoord2f( 0.0f, 5.0f); glVertex3f( -50.0f, 60.0f,25.0f);
      
       glTexCoord2f( 0.0f, 0.0f); glVertex3f( 50.0f,-2.0f,25.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -50.0f,-2.0f, 25.0f);
      glTexCoord2f(1.0f, 5.0f); glVertex3f( -50.0f, 60.0f, 25.0f);
      glTexCoord2f( 0.0f, 5.0f); glVertex3f( 50.0f, 60.0f,25.0f);

      glTexCoord2f( 0.0f, 0.0f); glVertex3f( 50.0f,-2.0f,25.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( 50.0f,-2.0f, -25.0f);
      glTexCoord2f(1.0f, 5.0f); glVertex3f( 50.0f, 60.0f, -25.0f);
      glTexCoord2f( 0.0f, 5.0f); glVertex3f( 50.0f, 60.0f,25.0f);
   
	   glTexCoord2f( 0.0f, 0.0f); glVertex3f( 50.0f,-2.0f,-25.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -50.0f,-2.0f, -25.0f);
      glTexCoord2f(1.0f, 5.0f); glVertex3f( -50.0f, 60.0f, -25.0f);
      glTexCoord2f( 0.0f, 5.0f); glVertex3f( 50.0f, 60.0f,-25.0f);
      
      
	  glEnd();
	 glTranslatef(-x, 0.0, z);
glDisable(GL_TEXTURE_2D);
 
 glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, bldId1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(-x, 0.0, -z);
    glBegin(GL_QUADS);
  
	  glNormal3f(0.0f, 1.0f, 0.0f);     
      glTexCoord2f( 0.0f, 0.0f); glVertex3f( -50.0f,-2.0f,25.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -50.0f,-2.0f, -25.0f);
      glTexCoord2f(1.0f, 5.0f); glVertex3f( -50.0f, 60.0f, -25.0f);
      glTexCoord2f( 0.0f, 5.0f); glVertex3f( -50.0f, 60.0f,25.0f);
      
       glTexCoord2f( 0.0f, 0.0f); glVertex3f( 50.0f,-2.0f,25.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -50.0f,-2.0f, 25.0f);
      glTexCoord2f(1.0f, 5.0f); glVertex3f( -50.0f, 60.0f, 25.0f);
      glTexCoord2f( 0.0f, 5.0f); glVertex3f( 50.0f, 60.0f,25.0f);

      glTexCoord2f( 0.0f, 0.0f); glVertex3f( 50.0f,-2.0f,25.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( 50.0f,-2.0f, -25.0f);
      glTexCoord2f(1.0f, 5.0f); glVertex3f( 50.0f, 60.0f, -25.0f);
      glTexCoord2f( 0.0f, 5.0f); glVertex3f( 50.0f, 60.0f,25.0f);
   
	   glTexCoord2f( 0.0f, 0.0f); glVertex3f( 50.0f,-2.0f,-25.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( -50.0f,-2.0f, -25.0f);
      glTexCoord2f(1.0f, 5.0f); glVertex3f( -50.0f, 60.0f, -25.0f);
      glTexCoord2f( 0.0f, 5.0f); glVertex3f( 50.0f, 60.0f,-25.0f);
      glTranslatef(0, 0.0, 0);
 
	  glEnd();
      glTranslatef(x, 0.0, z);
 glDisable(GL_TEXTURE_2D);
	}


/////////////////////////////////////////////////////////////////////////////////////////
//////sky  layer 
/////////////////////////////////////////////////////////////////////////////////////////
   glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, SkyId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
	 
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 2250.0f, 60.0f,  5250.0f);
      glTexCoord2f(100.0f, 0.0f); glVertex3f(-2250.0f, 60.0f,  5250.0f);
      glTexCoord2f(100.0f, 100.0f); glVertex3f(-2250.0f, 60.0f, -5250.0f);
      glTexCoord2f(0.0f, 100.0f); glVertex3f( 2250.0f, 60.0f, -5250.0f);
      
	  glTexCoord2f(0.0f, 0.0f); glVertex3f(-3250.0f, 0.0f,  5250.0f);
      glTexCoord2f(100.0f, 0.0f); glVertex3f(-3250.0f, 0.0f,  -5250.0f);
      glTexCoord2f(100.0f, 100.0f); glVertex3f(-2250.0f, 60.0f,  5250.0f);
      glTexCoord2f(0.0f, 100.0f); glVertex3f(-2250.0f, 60.0f, -5250.0f);

	  glEnd();
 
	glEnd();
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
   
   
	glutSwapBuffers();
}

 
  

 
void update() {
	//if(b>-1000){k1+=0.2;drawScene();}
	switch (k){
	   
       case 1:
		   b+=0.4;
		   drawScene();
		   break;
	   
	   case 2:
		    b+=0.4;
		   drawScene();
		   break;
	   
	   case 4: b+=0.4;
		   drawScene();
		   break;
	   
	   case 5:
		   b+=t1;
		   t1-=0.001;//to not stop suddenly
           if(t1<=0)t1=0;
		   drawScene();
		   break;

	   case 6:
           b+=0.2;
           drawScene();
		   break;

	   case 7:
		   b+=0.8;
           drawScene();
		   break;
	 //  case 8:
	//	   q-=2;
	//	   drawScene();
	//	   break;
	//   case 9:
	//	   q+=2;
    //      drawScene();
	//	   break;
	   case 10:
		   b+=0.4;
           drawScene();
		   break;


}
}
 
	void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		  
		
		case 100:   
           k=2;
		   t1=0.2;// to use in slow break
		   y=(int)b* sin((float)a3*PI/180);   ///y coordinate found by math equation  to find my place in 2d 
    	   x=(int)b* cos((float)a3*PI/180);   ///x coordinate found by math equation  to find my place in 2d 
			if(x>85)break;
			
			a1+=0.5;
			a3--;      ///a3 is an angle used in polar coordinates
		   angle+=0.08;
		   k2++;
           glutIdleFunc(update);
		   //PlaySound("car_idle.wav",NULL,SND_ASYNC);
		   break;
			
   

		case 97:   //work same as left arrow turns player left
          
          k=4;t1=0.2;
		  y=(int)b*sin((float)a3*PI/180);
		    x=(int)b* cos((float)a3*PI/180);
			if(x<-85)break;   ///to make boundaries
			
			a1-=0.8;
			k2--;
			a3++;
		  angle-=0.08;
		  glutIdleFunc(update);
          //PlaySound("car_idle.wav",NULL,SND_ASYNC);
		  break;
   

		case 120:   
          k=3; 
		  glutIdleFunc(update);
           break;
           
   

		  	case 119:  
           k=1;t1=0.2;
		    y=(int)b*sin((float)a3*PI/180);
		    x=(int)b* cos((float)a3*PI/180);
			//if(y>100) break;
		
		   glutIdleFunc(update);
		   PlaySound("high1.wav",NULL,SND_ASYNC|8);
			   
			   break;
           
           
        
		case 115:     // end key is center
           k=5; 
          PlaySound("brake.wav",NULL,SND_ASYNC);
		  glutIdleFunc(update);
		  break;
          
		case 114:
			k=6;
			q+=2;
			glutIdleFunc(update);
            break;

		case 108:
            k=6;q-=2;
			glutIdleFunc(update);
            break;
		case 109:
			k=7;
			glutIdleFunc(update);
            PlaySound("car_idle.wav",NULL,SND_ASYNC|8);
			break;
		
		case 98:
			PlaySound("beep.wav",NULL,SND_ASYNC);
			break;
		 


	}
}
	void specialKey(int key, int x, int y) { // called on special key pressed
   
     
    switch(key) {
        case GLUT_KEY_UP : 	// Arrow key left to go right
           k=1;t1=0.2;
		    y=(int)b*sin((float)a3*PI/180);
		    x=(int)b* cos((float)a3*PI/180);
			//if(y>100) break;
		
		   glutIdleFunc(update);
		   PlaySound("high1.wav",NULL,SND_ASYNC|8);
			   
			   break;

         
        case GLUT_KEY_RIGHT :    	// Arrow key right is pressed
            k=2;
		   t1=0.2;// to use in slow break
		   y=(int)b* sin((float)a3*PI/180);   ///y coordinate found by math equation  to find my place in 2d 
    	   x=(int)b* cos((float)a3*PI/180);   ///x coordinate found by math equation  to find my place in 2d 
			if(x>85)break;
			
			a1+=0.5;
			a3--;      ///a3 is an angle used in polar coordinates
		   angle+=0.08;
		   k2++;
           glutIdleFunc(update);
          break;

        case GLUT_KEY_LEFT :        	// Arrow key up is pressed
            k=4;t1=0.2;
		  y=(int)b*sin((float)a3*PI/180);
		    x=(int)b* cos((float)a3*PI/180);
			if(x<-85)break;   ///to make boundaries
			
			a1-=0.8;
			k2--;
			a3++;
		  angle-=0.08;
		  glutIdleFunc(update);
          break;

        case GLUT_KEY_DOWN :    	// Arrow key down is pressed
            k=5; 
          PlaySound("brake.wav",NULL,SND_ASYNC);
		  glutIdleFunc(update);
          break;    
	}
	}

	void mouse(int button, int state, int x, int y) {
switch (button) {
case GLUT_LEFT_BUTTON:
if (state == GLUT_DOWN)
k=10;
q+=2;
			 
			glutIdleFunc(update);
            break;

case GLUT_RIGHT_BUTTON:
if (state == GLUT_DOWN)
k=10;
q-=2;
            glutIdleFunc(update);
            break;

default:
            break;
}
}

 

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Ahmad_Karawash's city");
	initRendering();
	PlaySound("startup.wav",NULL,SND_ASYNC);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutMouseFunc(mouse);
	glutSpecialFunc(specialKey);
	glutReshapeFunc(handleResize);
	glutMainLoop();
	return 0;
}
