


/*************************************************

MADE BY:
2014A7PS041P:Sanjog Yadav
2014A7S049P:Abhinav Tiwari


****************************************************/



#include <stdlib.h>
#include<stdio.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

#include<math.h>
#include<stdio.h>




#define PI 3.14159265
#define GL_BGR 0x80E0

//filled:->1 & wireframe:->0
int mode=1; 

//the half dimensions of the room whose centre is at (0,0,0)
float ix=40.0,iy=20.0,iz=20.0;
//eye position
float cx=-ix,cy=iy,cz=-iz+5;
float dCx=-ix,dCy=iy,dCz=-iz+5;

//first person angle
int fpAng=0;

//aim position
float ax=ix,ay=-iy,az=iz-5;
float dAx=ix,dAy=-iy,dAz=iz-5;

//sizeUp
float e=0.5;
//tail zDis
float tail=0;

//rotate animal1 's frame
int rAng=0;
//rotate animal2 's frame
int lAng=135;
int num=1;


//upperleg angles
float angA=0,angB=0,angC=0,angD=0;
//lowerleg angles
float angAl=0,angBl=0,angCl=0,angDl=0;

//walking animal 's coordinates
float wx=10,wy=-16,wz=10;
float dWx=10,dWy=-16,dWz=10;

//walk or run(t)
int walk=1;

//camera mode(c)
int walled=1;
//radius
int r=22;


//rotating objects
int cAng = 0;//cube
int fAng=0;//fan

//for the current texture
GLuint texture;

GLUquadric *quad;
GLUquadricObj *qobj;


// load a 256x256 RGB .RAW/.BMP file as a texture
GLuint LoadTextureRAW( const char * filename, int wrap,int width,int height )
{
    GLuint texture;
    unsigned char * data;
    FILE * file;
	
    // open texture data
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;

    // allocate buffer

    data = (unsigned char *)malloc( width * height * 3*sizeof(unsigned char) );

    // read texture data
    fread( data, width * height * 3, 1, file );
    fclose( file );

    // allocate a texture name
    glGenTextures( 1, &texture );

    // select our current texture
    glBindTexture( GL_TEXTURE_2D, texture );

    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                     GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the first mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                     wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                     wrap ? GL_REPEAT : GL_CLAMP );

    // build our texture mipmaps
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,
                       GL_BGR, GL_UNSIGNED_BYTE, data );

    // free buffer
    free( data );

    return texture;
}


void drawCube(float x)
{
   if(mode==1)
   	glutSolidCube(x);
   else
   	glutWireCube(x);

}

void drawCylinder(float radius1,float radius2,float height)
{
	if(mode==1)
	{
		gluCylinder(qobj,radius1,radius2,height, 8,5);
	}
	else
	{//wireframe
		gluQuadricDrawStyle(qobj,GLU_LINE);
		gluCylinder(qobj,radius1,radius2,height, 8,5);
	}
}

void drawSphere(float radius)
{
	if(mode==1)
	{
		glutSolidSphere(radius,16,10);
	}
	else
	{
		glutWireSphere(radius,16,10);
	}
}

void drawRoom()
{
    glTranslatef(0.0, 0.0, 0.0);

	//enable texture mapping
	 glEnable(GL_TEXTURE_2D);  

	
	texture = LoadTextureRAW( "galaxy.bmp", 1 ,1024,256);


     glBegin(GL_QUADS);            
      // ceiling (y = iy)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glColor3f(1.0f, 1.0f, 1.0f);    

	glTexCoord2f(0.0f, 0.0f); glVertex3f( ix, iy, -iz);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( -ix, iy,  -iz);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( -ix, iy,  iz);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(ix, iy, iz);
   
      
	 glEnd();

	      glDeleteTextures( 1, &texture );
	 	 texture = LoadTextureRAW( "ground.bmp", 1,256,256 );

	 glBegin(GL_QUADS);

 
      // Floor(y = -iy)
      glColor3f(1.0f, 1.0f, 1.0f);     
      
	 glTexCoord2f(0.0f, 0.0f); glVertex3f( ix, -iy, iz);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( -ix, -iy,  iz);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( -ix, -iy,  -iz);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(ix, -iy, -iz);

	glEnd();

	      glDeleteTextures( 1, &texture );
	 	 texture = LoadTextureRAW( "wall.bmp", 1 ,256,256);
 
		  glBegin(GL_QUADS);
      // Front face  (z = iz)
      glColor3f(1.0f, 1.0f, 1.0f);     
     

    glTexCoord2f(0.0f, 0.0f); glVertex3f( ix, iy, iz);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( -ix, iy,  iz);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( -ix, -iy,  iz);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(ix, -iy, iz);
 
      // Back face (z = -iz)
      glColor3f(1.0f, 1.0f, 1.0f);    
      
  glTexCoord2f(0.0f, 0.0f); glVertex3f( ix, -iy, -iz);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( -ix, -iy,-  iz);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( -ix, iy,  -iz);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(ix, iy, -iz);

      // Left face (x = -ix)
      glColor3f(1.0f, 1.0f, 1.0f);    
 
	  glTexCoord2f(0.0f, 0.0f); glVertex3f( -ix, iy, iz);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( -ix, iy,-iz);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( -ix, -iy,  -iz);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-ix, -iy, iz);

      // Right face (x = ix)
      glColor3f(1.0f, 1.0f, 1.0f);  
      glVertex3f(ix,  iy, -iz);
      glVertex3f(ix,  iy,  iz);
      glVertex3f(ix, -iy,  iz);
      glVertex3f(ix, -iy, -iz);

	  glTexCoord2f(0.0f, 0.0f); glVertex3f( ix, iy, -iz);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( ix, iy, iz);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( ix, -iy, iz);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(ix, -iy, -iz);

   glEnd();  // End of drawing color-cuboid
 
   glDeleteTextures( 1, &texture );
   //disable texture mapping
   glDisable(GL_TEXTURE_2D);
}

void drawHead()
{

	 glTranslatef(-4*e,2*e,0*e);
	 qobj = gluNewQuadric();
  gluQuadricNormals(qobj, GLU_SMOOTH); 
	//make neck
glRotatef(-30.0,0,0,1);
glTranslatef(-1*e,0*e,0*e);

		glPushMatrix();
	    glScalef(2,0.5,2);
		glColor3f(0.718,0.5,0.042);
  	    drawCube(1*e);
		glPopMatrix();

glTranslatef(-1*e,0*e,0*e);
glRotatef(30.0,0,0,1);
	//make head
	 
glRotatef(-90,0,1,0);

	 glPushMatrix();
     glScalef(1,1,1);
	 glColor3f(0.718,0.4,0.042);
	 drawCylinder(2.0*e,0.8*e,3.0*e);
	 glPopMatrix();

	 glPushMatrix();
   gluDisk(qobj,0,2.0*e,16,10);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0,0,3.0*e);
   gluDisk(qobj,0,0.8*e,16,10);
   glPopMatrix();
 glRotatef(90,0,1,0);

	 //Eyes
	 glPushMatrix();
	 glColor3f(1,1,1);
	 glTranslatef(-0.85,0.45,0.50);
	 drawSphere(0.2);
	 glPopMatrix();

	 glPushMatrix();
	 glColor3f(1,1,1);
	 glTranslatef(-0.85,0.45,-0.50);
	 drawSphere(0.2);
	 glPopMatrix();

	 //Nose
	 glPushMatrix();
	 glColor3f(0,0,0);
	 glTranslatef(-2.7*e,0.55*e,0);
	 drawSphere(0.5*e);

	 glPopMatrix();

	 // Mouth

	 glPushMatrix();
	 glColor3f(1,1,1);
	 glScalef(2*e,1*e,1*e);
	 glTranslatef(-2.55*e,-1.3*e,0);
	 drawCube(0.5);
	 glPopMatrix();
	 
  

}

void drawTail()
{	
	int i=0;

	 glTranslatef(4.5*e,0*e,0*e);
	 
	//make 4 consecutive cubes
	    for(i=0;i<4;i++)
		{
			if(i==3)
				glColor3f(0.511,0.542,0.542);
			else
				 glColor3f(0.718,0.4,0.042);
		    drawCube(1*e);
	        glTranslatef(1*e,0*e,tail*e); 
		}
}

//for the back left eg
void drawA()
{
	if(num==1)
	glRotatef(angA,0,0,1);
	else if(num==2)
    glRotatef(-45,0,0,1);
	    
  	glTranslatef(0*e,-2*e,0);


	
	glPushMatrix();
	glScalef(2,4,1);
	glColor3f(0.718,0.4,0.042);
	drawCube(1*e);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,2*e,0);
	glScalef(1,1,1);
	glColor3f(0.511,0.542,0.542);
	drawSphere(1.2*e);
	glPopMatrix();

	glTranslatef(0*e,-2*e,0*e);
	if(num==1)
	glRotatef(-angA,0,0,1);
	else if(num==2)
		glRotatef(45,0,0,1);
	
	if(num==1)
	glRotatef(angAl,0,0,1);
	else if(num==2)
		glRotatef(80,0,0,1);
	
	glTranslatef(0*e,-2*e,0*e);

	glPushMatrix();
	glScalef(1,4,1);
	glColor3f(0.718,0.5,0.042);
	drawCube(1*e);
	glPopMatrix();


	glPushMatrix();
	glScalef(1,1,1);
	glColor3f(0.511,0.542,0.542);
	glTranslatef(0,2*e,0);
	drawSphere(0.9*e);
	glPopMatrix();

	glTranslatef(-1*e,-1.75*e,0);
	
	glPushMatrix();
	glScalef(1,0.5,1);
	glColor3f(0.542,0.269,0.074);
	drawCube(1*e);
	glPopMatrix();

		if(num==1)
	glRotatef(-angAl,0,0,1);
	else if(num==2)
		glRotatef(-80,0,0,1);


}

//for front left leg

void drawB()
{
if(num==1)
	glRotatef(angB,0,0,1);
	else if(num==2)
    glRotatef(-45,0,0,1);

  	glTranslatef(0*e,-2*e,0);
	
	glPushMatrix();
	glScalef(1,4,1);
	glColor3f(0.718,0.4,0.042);
	drawCube(1*e);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,2*e,0);
	glScalef(1,1,1);
	glColor3f(0.511,0.542,0.542);
	drawSphere(1.0*e);
	glPopMatrix();

	glTranslatef(0*e,-2*e,0*e);
if(num==1)
	glRotatef(-angB,0,0,1);
	else if(num==2)
    glRotatef(45,0,0,1);


if(num==1)
	glRotatef(angBl,0,0,1);
	else if(num==2)
    glRotatef(-90,0,0,1);
	
glTranslatef(0*e,-2*e,0*e);

	glPushMatrix();
	glScalef(1,4,1);
	glColor3f(0.718,0.5,0.042);
	drawCube(1*e);
	glPopMatrix();

	glPushMatrix();
	glScalef(1,1,1);
	glColor3f(0.511,0.542,0.542);
	glTranslatef(0,2*e,0);
	drawSphere(0.9*e);
	glPopMatrix();

	glTranslatef(-1*e,-1.75*e,0);

	glPushMatrix();
	glScalef(1,0.5,1);
	glColor3f(0.542,0.269,0.074);
	drawCube(1*e);
	glPopMatrix();


	if(num==1)
	glRotatef(-angBl,0,0,1);
	else if(num==2)
    glRotatef(90,0,0,1);

}

//for the front right leg
void drawC()
{if(num==1)
	glRotatef(angC,0,0,1);
	else if(num==2)
    glRotatef(-45,0,0,1);

  	glTranslatef(0*e,-2*e,0);
	
	glPushMatrix();
	glScalef(1,4,1);
	glColor3f(0.718,0.4,0.042);
	drawCube(1*e);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,2*e,0);
	glScalef(1,1,1);
	glColor3f(0.511,0.542,0.542);
	drawSphere(1.0*e);
	glPopMatrix();

	glTranslatef(0*e,-2*e,0*e);
	if(num==1)
	glRotatef(-angC,0,0,1);
	else if(num==2)
    glRotatef(45,0,0,1);


	if(num==1)
	glRotatef(angCl,0,0,1);
	else if(num==2)
    glRotatef(-90,0,0,1);

	glTranslatef(0*e,-2*e,0*e);

	glPushMatrix();
	glScalef(1,4,1);
	glColor3f(0.718,0.5,0.042);
	drawCube(1*e);
	glPopMatrix();

	glPushMatrix();
	glScalef(1,1,1);
	glColor3f(0.511,0.542,0.542);
	glTranslatef(0,2*e,0);
	drawSphere(0.9*e);
	glPopMatrix();

	glTranslatef(-1*e,-1.75*e,0);

	glPushMatrix();
	glScalef(1,0.5,1);
	glColor3f(0.542,0.269,0.074);
	drawCube(1*e);
	glPopMatrix();

	if(num==1)
	glRotatef(-angCl,0,0,1);
	else if(num==2)
    glRotatef(90,0,0,1);

}

//back right leg
void drawD()
{
if(num==1)
	glRotatef(angD,0,0,1);
	else if(num==2)
    glRotatef(-45,0,0,1);

  	glTranslatef(0*e,-2*e,0);
	
	glPushMatrix();
	glScalef(2,4,1);
	glColor3f(0.718,0.4,0.042);
	drawCube(1*e);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,2*e,0);
	glScalef(1,1,1);
	glColor3f(0.511,0.542,0.542);
	drawSphere(1.2*e);
	glPopMatrix();

	glTranslatef(0*e,-2*e,0*e);
	if(num==1)
	glRotatef(-angD,0,0,1);
	else if(num==2)
    glRotatef(45,0,0,1);

	if(num==1)
	glRotatef(angDl,0,0,1);
	else if(num==2)
    glRotatef(80,0,0,1);

	glTranslatef(0*e,-2*e,0*e);

	glPushMatrix();
	glScalef(1,4,1);
	glColor3f(0.718,0.5,0.042);
	drawCube(1*e);
	glPopMatrix();

	glPushMatrix();
	glScalef(1,1,1);
	glColor3f(0.511,0.542,0.542);
	glTranslatef(0,2*e,0);
	drawSphere(0.9*e);
	glPopMatrix();

	glTranslatef(-1*e,-1.75*e,0);

	glPushMatrix();
	glScalef(1,0.5,1);
	glColor3f(0.542,0.269,0.074);
	drawCube(1*e);
	glPopMatrix();

	if(num==1)
	glRotatef(-angDl,0,0,1);
	else if(num==2)
    glRotatef(-80,0,0,1);

}


void drawLegs()
{   //back left
	glPushMatrix();
	   glTranslatef(3*e,0*e,2.5*e);
	     glPushMatrix();
		   drawA();
	     glPopMatrix(); 
	glPopMatrix();
	//front left
	glPushMatrix();
	   glTranslatef(-3*e,0*e,2.5*e);
	     glPushMatrix();
		   drawB();
	     glPopMatrix(); 
	glPopMatrix(); 
	//front right
	glPushMatrix();
	   glTranslatef(-3*e,0*e,-2.5*e);
	     glPushMatrix();
		   drawC();
	     glPopMatrix(); 
	glPopMatrix(); 
	//back left
	glPushMatrix();
	   glTranslatef(3*e,0*e,-2.5*e);
	     glPushMatrix();
		   drawD();
	     glPopMatrix(); 
	glPopMatrix(); 
	
	
}

void drawAnimal(float x,float y ,float z)
{
   glColor3f(0, 0, 0);//black color

   glTranslatef(x,y,z);

   float temp;
   if(num==1)
   {
      //angular orientation of the animal
    temp=rAng%360;
	 glRotatef(temp,0,1,0);
   }
   else if(num==2)
   {
     temp=lAng%360;
	 glRotatef(temp,0,1,0);
    
   }
	 
	 qobj = gluNewQuadric();
  gluQuadricNormals(qobj, GLU_SMOOTH); 
   
  
  //make body

	glPushMatrix();
  glRotatef(90,0,1,0);
	glColor3f(0.542,0.269,0.074);
	glTranslatef(0,0,-4*e);
	drawCylinder(2.5*e,1.5*e,8*e);
   
	glPopMatrix();

   glPushMatrix();
   glTranslatef(4*e,0,0);
   glRotatef(90,0,1,0);
   gluDisk(qobj,0,1.5*e,16,10);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-4*e,0,0);
   glRotatef(90,0,1,0);
   gluDisk(qobj,0,2.5*e,16,10);
   glPopMatrix();


   glPushMatrix();
   //make head 
   drawHead();
   glPopMatrix(); 

   
   glPushMatrix();
   //make tail
   drawTail();
   glPopMatrix(); 

   glPushMatrix();
   //make legs n feet
   drawLegs();
   glPopMatrix();
   
}

void OnReshape(int w, int h)
{
	if (h==0) {
		h=1;
	}

	// set the drawable region of the window
	glViewport(0,0,w,h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// just use a perspective projection
	gluPerspective(45,(float)w/h,0.1,100);

}


void OnDraw() {

	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    // enable depth testing
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
	
	// set the camera position
	gluLookAt(	cx,cy,cz,	//	eye pos
				ax,ay,az,	//	aim point
				0,1,0);	//	up direction


//start
    glPushMatrix();  
    drawRoom();
    glPopMatrix();

	//animal 1 
	num=1;
	glPushMatrix();  
    drawAnimal(wx,wy,wz);
    glPopMatrix();

	//animal 2
	num=2;
	glPushMatrix();  
    drawAnimal(0,-17,-10);
    glPopMatrix();

	//rotating cube
	glPushMatrix(); 
	glTranslatef(0,0,0);
	glRotatef(45,0,0,1);
	glRotatef(45,1,0,0);
	
	glRotatef(cAng,0,1,0);
	//drawCube(5);
	 glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f( 1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f,  1.0f);
      glVertex3f( 1.0f, 1.0f,  1.0f);
 
      // Bottom face (y = -1.0f)
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);
 
      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);
 
      // Back face (z = -1.0f)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);
 
      // Left face (x = -1.0f)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
 
      // Right face (x = 1.0f)
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glVertex3f(1.0f,  1.0f, -1.0f);
      glVertex3f(1.0f,  1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
   glEnd();  // End of drawing color-cube

	glPopMatrix();
	
	//teapot
		glPushMatrix();
		glTranslatef(20,-18,-15);
		glRotatef(180,0,1,0);
     glColor3f(1,1,1);
	
	if(mode==1)
	{
	glEnable(GL_TEXTURE_2D);
	 
	 	 texture = LoadTextureRAW( "teapot2.bmp", 1,256,256 );
	
	 
     glutSolidTeapot(3);
    
	 glDeleteTextures( 1, &texture );
	 glDisable(GL_TEXTURE_2D);
	}
	else if(mode ==0)
	{
		glColor3f(1,0,0);
	  glutWireTeapot(3); 
	}
	glPopMatrix();

	 //ceiling fan
	glColor3f(1,1,1);
	 qobj = gluNewQuadric();
  gluQuadricNormals(qobj, GLU_SMOOTH); 
	 
	glPushMatrix();
	glTranslatef(0,20,0);


	glPushMatrix();
	glRotatef(90,1,0,0);
	gluCylinder(qobj,0.75,0.5,1,16,10);
	glPopMatrix();

	glTranslatef(0,-1,0);
	
	glPushMatrix();
	glRotatef(90,1,0,0);
	gluCylinder(qobj,0.2,0.2,2,16,10);
	glPopMatrix();

	glTranslatef(0,-2,0);
	
	glPushMatrix();
	glRotatef(90,1,0,0);
	gluCylinder(qobj,1,1,0.5,16,10);
	glPopMatrix();

	glTranslatef(0,-0.25,0);

	int i=0;
	for(i=0;i<3;i++)
	{
	glPushMatrix();
	glRotatef(120*i+fAng,0,1,0);

	glTranslatef(3,0,0);
	 glBegin(GL_QUADS);            
      glVertex3f( 2.0f, 0, -0.8f);
      glVertex3f(-2.0f, 0, -0.8f);
      glVertex3f(-2.0f, 0,  0.8f);
      glVertex3f( 2.0f, 0,  0.8f);
 
   glEnd();  
	glPopMatrix();

	}

    glPopMatrix();


	// currently we've been drawing to the back buffer, we need
	// to swap the back buffer with the front one to make the image visible
	glutSwapBuffers();
    //double buffering
}

void setAim(int i)
{
  if(i==0)
  {
     ax=wx-(cx-wx);
    ay=wy-(cy-wy);
    az=wz-(cz-wz);
  }
  else if(i==1)
  {
     ax=-cx;
     ay=-cy;
     az=-cz;
  }
}


//walking functionality
int ac=1,bd=0;
void moveLegs()
{
  
	if(ac==1 && bd==0)
	{
      angA-=5;
	  angC-=5;
      angB+=5;
	  angD+=5;

	  
	  if(angA<=-30)
	  {
		  ac=0;
		  bd=1;
	  }
	}

	else if(ac==0 && bd==1)
	{
      angA+=5;
	  angC+=5;
      angB-=5;
	  angD-=5;

	  if(angD<=-30)
	  {
		  ac=1;
		  bd=0;
	  }
	}
}

//running legs
int bc=0,ad=1;
void runLegs()
{
		if(ad==1 && bc==0)
	{
      angA-=10;
	  angD-=10;
      angB+=7.5;
	  angC+=7.5;

	  if(angA<-40)
	  {
		  ad=0;
		  bc=1;
	  }
	}

	else if(ad==0 && bc==1)
	{
      angA+=10;
	  angD+=10;
      angB-=7.5;
	  angC-=7.5;

	  if(angA>40)
	  {
		  ad=1;
		  bc=0;
	  }
	}
}

//walk forward
void walkF()
{
	if(abs(wx) < ix-12*e && abs(wz) < iz-12*e)
			{
				wx-=0.4*e*cos(PI*rAng/180);
				wz+=0.4*e*sin(PI*rAng/180);

				if(walled==0)
				{
			drawCylinder(0.2,0.2,2);
		   cx-=0.4*e*cos(PI*rAng/180);
				   cz+=0.4*e*sin(PI*rAng/180);
				   setAim(0);
				}

				if(abs(wx) < ix-12*e && abs(wz) < iz-12*e)
		        moveLegs();
				else{
				 wx+=0.4*e*cos(PI*rAng/180);
				wz-=0.4*e*sin(PI*rAng/180);
				 
				if(walled==0)
				  { 
				        cx+=0.4*e*cos(PI*rAng/180);
				        cz-=0.4*e*sin(PI*rAng/180);
				   setAim(0);    
 				  }
				}

		    }
   	
}

//walk backward
void walkB()
{
	if(abs(wx) < ix-12*e && abs(wz) < iz- 12*e)
			{
				wx+=0.4*e*cos(PI*rAng/180);
				wz-=0.4*e*sin(PI*rAng/180);

				if(walled==0)
				{
				   cx+=0.4*e*cos(PI*rAng/180);
				   cz-=0.4*e*sin(PI*rAng/180);
				   setAim(0);
				}

				if(abs(wx) < ix-12*e && abs(wz) < iz- 12*e)
				moveLegs();
				else{
				  wx-=0.4*e*cos(PI*rAng/180);
				wz+=0.4*e*sin(PI*rAng/180);

				if(walled==0)
				{
				   cx-=0.4*e*cos(PI*rAng/180);
				   cz+=0.4*e*sin(PI*rAng/180);
				   setAim(0);
				}

				}
		    }
}


//run forward
void runF()
{
		if(abs(wx) < ix-12*e && abs(wz) < iz-12*e)
			{
				wx-=0.8*e*cos(PI*rAng/180);
				wz+=0.8*e*sin(PI*rAng/180);

				if(walled==0)
				{
				   cx-=0.8*e*cos(PI*rAng/180);
				   cz+=0.8*e*sin(PI*rAng/180);
				   setAim(0);
				}
				
				if(abs(wx) < ix-12*e && abs(wz) < iz-12*e)
		        runLegs();
				else{
				 wx+=0.8*e*cos(PI*rAng/180);
				wz-=0.8*e*sin(PI*rAng/180);

				  if(walled==0)
				{
				   cx+=0.8*e*cos(PI*rAng/180);
				   cz-=0.8*e*sin(PI*rAng/180);
				   setAim(0);
				}
				}

		    }
}

//run backward
void runB()
{
	if(abs(wx) < ix-12*e && abs(wz) < iz- 12*e)
			{
				wx+=0.8*e*cos(PI*rAng/180);
				wz-=0.8*e*sin(PI*rAng/180);


				if(walled==0)
				{
				   cx+=0.8*e*cos(PI*rAng/180);
				   cz-=0.8*e*sin(PI*rAng/180);
				   setAim(0);
				}

				if(abs(wx) < ix-12*e && abs(wz) < iz- 12*e)
				runLegs();
				else{
				  wx-=0.8*e*cos(PI*rAng/180);
				wz+=0.8*e*sin(PI*rAng/180);

				  if(walled==0)
				{
				   cx-=0.8*e*cos(PI*rAng/180);
				   cz+=0.8*e*sin(PI*rAng/180);
				   setAim(0);
				}
				}
		    }
}

void OnKeyPress(unsigned char key,int x,int y) {
	switch(key) {
     //wy wont be affected.animal will move in the x-z plane
	// move animal forward
	case 'f':
 		if(walk==1)
			walkF();
		else
			runF();
 		break;
    //  move animal backwards
	case 'b':
		if(walk==1)
			walkB();
		else
			runB();
		break;
       //toggle between walk and run
	case 't':
		if(walk==1)
			walk=0;
		else
			walk=1;

		 angA=0;
		angB=0;
		angC=0;
		angD=0;

		break;
     //toggle between filled and wireframe mode
	case 'w':
	     if(mode==1)
	     	mode=0;
	     else
	     	mode=1;
	     break;	
     //toggle between walled and free camera mode
	case 'c':
		if(walled==1)
			{
				walled =0;
				cx=wx+20*e*cos(PI*rAng/180);
				cy=wy+8*e;
				cz=wz-20*e*sin(PI*rAng/180);
				setAim(0);
		}
		else{
			walled =1;
			cx=dCx;
		    cy=dCy;
		    cz=dCz;

			setAim(1);
		}
		break;
    //reset to start	
	case 'r':
		cx=dCx;
		cy=dCy;
		cz=dCz;

		setAim(1);

		angA=0;
		angB=0;
		angC=0;
		angD=0;

		wx=dWx;
		wy=dWy;
		wz=dWz;

		rAng=0;
		walled=1;
		break;
    //turn left
	case 'a':
		rAng+=5;
		break;
   //turn right
	case 'd':
		rAng-=5;
		break;
	//exit
	case 'q':
		exit(EXIT_SUCCESS);
		break;
	default:
		break;
	}

	// ask glut to redraw the screen for us... 
	glutPostRedisplay();
}

//third person camera movements

int sxA=90,syA=90;
void animC(int i)
{
  switch(i)
  {
	  //left key(x-z plane)
  case 1:
	  fpAng+=5;
	  fpAng%=360;
	  		   cx=wx+20*e*cos(PI*fpAng/180);
			   cz=wz-20*e*sin(PI*fpAng/180);
				setAim(0);
		

	  break;
	  //right key
  case 2:
	  fpAng-=5;
	  fpAng%=360;
	  		   cx=wx+20*e*cos(PI*fpAng/180);
			   cz=wz-20*e*sin(PI*fpAng/180);
				setAim(0);
	  break;
	  //up key
  case 3:
	  break;
	  //down key
  case 4:
	  break;
  default:
	  break;
  }

}

//wall attached camera movements
void wallC(int i)
{
  switch(i)
  {
  case 1:
	  //cy=iy
		if((abs(cx)<ix || cx==ix )&& cz==iz)
		{
		   cx-=1;
		}
		else if((abs(cz)<iz || cz==iz )&& cx==-ix)
		{
		   cz-=1;
		}
		else if((abs(cx)<ix || cx==-ix )&& cz==-iz)
		{
		  cx+=1;
		}
		else if((abs(cz)<iz || cz==-iz )&& cx==ix)
		{
		  cz+=1;
		}
		
	  break;
  case 2:
	  //cy=iy
		if((abs(cz)<iz || cz==iz )&& cx==ix)
		{
		   cz-=1;
		}
		else if((abs(cx)<ix || cx==ix )&& cz==-iz)
		{
		   cx-=1;
		}
		else if((abs(cz)<iz || cz==-iz )&& cx==-ix)
		{
		  cz+=1;
		}
		else if((abs(cx)<ix || cx==-ix )&& cz==iz)
		{
		  cx+=1;
		}
	  break;
  case 3:
	  if(cy<iy)
		cy+=1;
	  break;
  case 4:
	  	if(cy>-iy)
		cy-=1;
	  break;
  default:
	  break;
  }

 setAim(1);
}


void keyspecial(int key, int x, int y)
{
  int i = 0;
  switch (key) {

	  case GLUT_KEY_LEFT:
		  if(walled==1)
			  wallC(1);
		  else
			  animC(1);
		break;

	case GLUT_KEY_RIGHT:
		if(walled==1)
			  wallC(2);
		  else
			  animC(2);
		break;
	case GLUT_KEY_UP:
		if(walled==1)
			  wallC(3);
		  else
			  animC(3);
		
	 break;
   	case GLUT_KEY_DOWN:
		if(walled==1)
			  wallC(4);
		  else
			  animC(4);
	
		break;

  }
  // ask glut to redraw the screen for us... 
    glutPostRedisplay();
}

//initialisation
void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glColor3f(1,1,1);
	
	glPointSize(1.0f);
	// enable depth testing
	glEnable(GL_DEPTH_TEST);
	

   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections


}

//idle function 
int increase=1;
void animation(void)
{
	if(increase==1)
	{
	  tail+=0.1;
	  if(tail>=0.7)
		  increase=0;
	}
	else if(increase==0)
	{
	  tail-=0.1; 
	  if(tail<=-0.7)
		  increase=1;
	}

	cAng+=5;
	cAng%=360;

	fAng+=5;
	fAng%=360;

	glutPostRedisplay();
}

int main(int argc,char** argv) {

	// initialise glut
	glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_DEPTH|GLUT_RGBA|GLUT_DOUBLE);

     //set window position on screen
	glutInitWindowPosition(100, 100);
	// set the initial window size
	glutInitWindowSize(800,600);
    // create the window
	glutCreateWindow("C-Camera||Direction Keys- Navigation||T- toggle run||A,D - Turn||R-Reset||F-Forward||B-Backward||Q-Quit");
	//glutCreateWindow("4-Legged Animal Locomotion in Closed Environment");

     init();
    
	glutDisplayFunc(OnDraw);

	glutReshapeFunc(OnReshape);

	// set the function for the key presses
	glutKeyboardFunc(OnKeyPress);

	//the camera functionality
	 glutSpecialFunc(keyspecial);
	glutIdleFunc(animation);
	glutMainLoop();  //to keep the program running


	return 0;
}



/**************************************************

MADE BY:
2014A7PS041P:Sanjog Yadav
2014A7S049P:Abhinav Tiwari


/*****************************************************/
