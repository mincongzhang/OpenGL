#include <stdlib.h>
#include <GL/glut.h>

#define TORSO_RADIUS 1.7
#define TORSO_LENGTH 2.5
#define LEG_RADIUS  0.7
#define LEG_LENGTH 2.5
#define HEAD_RADIUS  1.7 
#define RING_OUTSIDE_RADIUS  0.7 
#define RING_INSIDE_RADIUS  0.07 
#define HORN_LENGTH  1.3 
#define HORN_RADIUS  0.25
#define TAIL_RADIUS  0.10
#define TAIL_LENGTH  1.25
#define EYE_RADIUS  0.10
#define EYE_GAP  0.40


GLUquadricObj *p; // pointer to quadric object
GLfloat theta[4] = {0.0, 0.0, 0.0, 0.0 };


//judge the movement of each part of the object
GLboolean torsoj = GL_FALSE;  
GLboolean legj = GL_FALSE;
GLboolean headj = GL_FALSE;
GLboolean movej = GL_FALSE;

//judge the direction
GLint t_direction = 1;
GLint l_direction = 1;
GLint h_direction = 1;
GLint m_direction = 1;

GLdouble move[] = {0.0, 0.0, 0.0};
GLdouble m=0.1;

GLint menu_id = 0;
GLint submenu_id = 0;


void tail()
{
   glRotatef (45.0, 1.0, 0.0, 0.0);   
   glTranslatef(0.0,0.3,-TAIL_LENGTH-0.1);
   glPushMatrix();
   glColor3ub (116, 60, 127);
   glScalef(TAIL_RADIUS,TAIL_RADIUS,TAIL_LENGTH);
   gluCylinder (p, 1, 1, 1, 20, 20);
   glPopMatrix();
   
   //ball in the tail      
   glPushMatrix();
    glColor3ub (119, 95, 159);
   glScalef(2.5*TAIL_RADIUS,2.5*TAIL_RADIUS,2.5*TAIL_RADIUS);
   glutSolidSphere(1,10,10);
   glPopMatrix();

}

void torso()
{
   glPushMatrix();
   glColor3ub (119, 95, 159);
   glScalef(TORSO_RADIUS+0.2,TORSO_RADIUS, TORSO_LENGTH);
   glutSolidSphere(1,10,10);
   glPopMatrix();
}

void leg()
{
  //leg
  glPushMatrix();
  glColor3ub (116, 60, 127);
  glTranslatef(0.0,-LEG_LENGTH,0.0);
  glScalef(LEG_RADIUS, LEG_LENGTH, LEG_RADIUS);
  glRotatef (-90.0, 1.0, 0.0, 0.0);
  gluCylinder (p, 1, 1, 1, 20, 20);
  glPopMatrix();
  
  //feet
  glPushMatrix();
   glColor3ub (119, 95, 159);
  glTranslatef(0.0,-LEG_LENGTH,0.0);
  glScalef(LEG_RADIUS, LEG_RADIUS, LEG_RADIUS);
  glutSolidSphere(1,10,10);
  glPopMatrix();
}

void head()
{
  
  glPushMatrix();
  glColor3ub (116, 60, 127);
  glTranslatef(0.0,-0.3,1.3*HEAD_RADIUS);
  glScalef(HEAD_RADIUS-0.1, HEAD_RADIUS, HEAD_RADIUS-0.2);
  glutSolidSphere(1,20,20);
  glPopMatrix();
  
  //right eye
  glPushMatrix();
  glColor3ub (0.0, 0.0, 0.0);
  glTranslatef(-EYE_GAP,0.2*HEAD_RADIUS,2.1*HEAD_RADIUS);
  glScalef(EYE_RADIUS, EYE_RADIUS, EYE_RADIUS);
  glutSolidSphere(1,10,10);
  glPopMatrix();
  
  //left eye
  glPushMatrix();
  glColor3ub (0.0, 0.0, 0.0);
  glTranslatef(EYE_GAP,0.2*HEAD_RADIUS,2.1*HEAD_RADIUS);
  glScalef(EYE_RADIUS, EYE_RADIUS, EYE_RADIUS);
  glutSolidSphere(1,10,10);
  glPopMatrix();
  
  //ring in the nose
  glPushMatrix();
  glColor3ub (255, 236, 148);
  glTranslatef(0.0,-0.8*HEAD_RADIUS,2.2*HEAD_RADIUS);
  glRotatef (-20.0, 1.0, 0.0, 0.0);
  glutSolidTorus(RING_INSIDE_RADIUS,RING_OUTSIDE_RADIUS,40, 40);
  glPopMatrix();
  
  
  //horn
  glPushMatrix();
  glColor3ub (255, 236, 148);
  glTranslatef(-0.5*HORN_LENGTH,0.7*HEAD_RADIUS,1.7*HEAD_RADIUS);
  glRotatef (90.0, 0.0, 1.0, 0.0);
  glScalef(HORN_RADIUS, HORN_RADIUS, HORN_LENGTH);
  gluCylinder (p, 1, 1, 1, 20, 20);
  glPopMatrix();
  
  glPushMatrix();
  glColor3ub (255, 236, 148);
  glTranslatef(0.5*HORN_LENGTH,0.7*HEAD_RADIUS,1.7*HEAD_RADIUS);
  glRotatef (50.0, 0.0, 1.0, 0.0);
  glRotatef(theta[2], 1.0, 0.0, 0.0);
  glutSolidCone(HORN_RADIUS, 1*HORN_LENGTH, 20,20);
  glPopMatrix();
  
  glPushMatrix();
  glColor3ub (255, 236, 148);
  glTranslatef(-0.5*HORN_LENGTH,0.7*HEAD_RADIUS,1.7*HEAD_RADIUS);
  glRotatef (-50.0, 0.0, 1.0, 0.0);
  glRotatef(theta[2], 1.0, 0.0, 0.0);
  glutSolidCone(HORN_RADIUS, 1*HORN_LENGTH, 20,20);
  glPopMatrix();
  
}

void object()
{
  glTranslatef(move[0], move[1], move[2]);//object move
  glRotatef(theta[0], 0.0, 1.0, 0.0);//object rotate along the Y axis
  glColor3f (0.0, 0.0, 1.0);
  torso();
  
  glPushMatrix();
  glTranslatef(0.0, 0.0, -TORSO_LENGTH);//the porsition of the tail 
  glRotatef(theta[3], 0.0, 1.0, 0.0);
  tail(); 
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(0.5*TORSO_RADIUS, 0.0, 0.5*TORSO_LENGTH);//the porsition of leg1 
  glRotatef(10, 0.0, 0.0, 1.0);//slope 10 degree 
  glRotatef(theta[1], 1.0, 0.0, 0.0);
  leg();
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(-0.5*TORSO_RADIUS, 0.0, 0.5*TORSO_LENGTH);//the porsition of leg2
  glRotatef(-10, 0.0, 0.0, 1.0);//slope 10 degree
  glRotatef(theta[2], 1.0, 0.0, 0.0);
  leg();
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(-0.5*TORSO_RADIUS, 0.0, -0.5*TORSO_LENGTH);//the porsition of leg3
  glRotatef(-10, 0.0, 0.0, 1.0);//slope 10 degree
  glRotatef(theta[1], 1.0, 0.0, 0.0);
  glColor3f (0.0, 1.0, 0.0);
  leg();
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(0.5*TORSO_RADIUS, 0.0, -0.5*TORSO_LENGTH);//the porsition of leg4 
  glRotatef(10, 0.0, 0.0, 1.0);//slope 10 degree
  glRotatef(theta[2], 1.0, 0.0, 0.0);
  glColor3f (0.0, 1.0, 0.0);
  leg();
  glPopMatrix();
  
       
  glPushMatrix();
  glRotatef (-20.0, 1.0, 0.0, 0.0);//rise the head 
  glTranslatef(0.0, -0.7*HEAD_RADIUS, 0.5*TORSO_LENGTH);//the porsition of the head
  glRotatef(theta[3], 0.0, 0.0, 1.0);
  head();
  glPopMatrix();
}



void display()
{  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  object();
  glutSwapBuffers();
}


void init()
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  p = gluNewQuadric();
 }

void reshape(int w, int h)
{
  glViewport (0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();  
  
  //resharp the window
  if (w <= h){
  glOrtho(-7.0, 7.0, -7.0* (GLfloat) h / (GLfloat) w, 7.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
  }
  else {
  glOrtho(-7.0*(GLfloat) w / (GLfloat) h, 7.0*(GLfloat) w / (GLfloat) h, -7.0, 7.0, -10.0, 10.0);
  }
  glutPostRedisplay();
}

//a fast way to rotate ,translate and move using keyboard
void mykey(unsigned char key, int x, int y)
{
     
   switch(key) {
   case 'r':
		torsoj = !torsoj;
	break;
   case 'l':
		legj = !legj;
	break;
   case 'h':
        headj = !headj;
	break;
   case 't':
        movej = !movej;
	break;	
    }
}



void mymenu(int id)
{
	if(id == 1) {
		movej=!movej;
		}
	if(id == 2) {
		torsoj=!torsoj;
		}
}
void mysubmenu(int id)
{
	if(id == 1) legj=!legj;
	if(id == 2) headj=!headj;
}

void menu_system(){
	submenu_id = glutCreateMenu(mysubmenu);
	glutAddMenuEntry("Leg move(l)", 1);
	glutAddMenuEntry("head and tail move(h)", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
    menu_id = glutCreateMenu(mymenu);
    glutAddMenuEntry("Translating(t)", 1);
    glutAddMenuEntry("Rotating(r)", 2);
	glutAddSubMenu ("Bending", submenu_id);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void stop(){
     //all movement stop
     }

void torso_rotate(){
    theta[0] += 1;
    if (theta[0] > 360) theta[0] -= 360;
  }

     
void leg_rotate(){
      //leg1 rotate 
    if (l_direction > 0) {
       theta[1] += 1;
       if (theta[1] > 15) {
          l_direction = -1;
          theta[1] -= 1;
       }
    }
    else {
       theta[1] -= 1;
       if (theta[1] < -15) {
          l_direction = 1;
          theta[1] += 1;
       }
    }

      //leg2 rotate 
    if (l_direction > 0) {
       theta[2] -= 1;
       if (theta[2] > 15) {
          l_direction = -1;
          theta[2] -= 1;
       }
    }
    else {
       theta[2] += 1;
       if (theta[2] < -15) {
          l_direction = 1;
          theta[2] -= 1;
       }
}
}

void head_rotate(){
       if (h_direction > 0) {
       theta[3] += 1;
       if (theta[3] > 70) {
          h_direction = -1;
          theta[3] -= 1;
       }
    }
    else {
       theta[3] -= 1;
       if (theta[3] < -70) {
          h_direction = 1;
          theta[3] += 1;
       }
    }
}

void object_move(){
       if (m_direction > 0) {  //initial m_direction = 1;
       move[2] += m;
       if (move[2] > 5) {
          m_direction = -1;
          move[2] -= m;
       }
    }
    else {
       move[2] -= m;
       if (move[2] < -5) {
          m_direction = 1;
          move[2] += m;
       }
    }
  leg_rotate();
  head_rotate();
  
  }


void idle()
{
    
 if (torsoj){
    torso_rotate();
 }
 else {
  stop();  
 }

 if (legj){
    leg_rotate();
 }
 else {
  stop();  
 }
 
 if (headj){
    head_rotate();
 }
 else {
  stop();  
 }

 if (movej){
    object_move();
 }
 else {
  stop();  
 }
  glutPostRedisplay();
}

int main(int argc, char **argv)
{

  glutInit(&argc, argv); 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutCreateWindow("cow");
  glutKeyboardFunc(mykey);
  glutIdleFunc(idle);
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape);
  glEnable(GL_DEPTH_TEST); /* Enable hidden-surface removal */
  menu_system();
  init();
  glutMainLoop();
}


