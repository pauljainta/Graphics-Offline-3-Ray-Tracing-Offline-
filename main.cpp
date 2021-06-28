#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<vector>
#include<fstream>
#include<stack>
#include<string>
#include<cstdlib>
#include<time.h>
#include<algorithm>

#include <windows.h>
#include <GL/glut.h>

#define pi (2*acos(0.0))

#define large_value 999999
#include "bitmap_image.hpp"
#include "1605022_classes.h"

using namespace std;
double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;
double viewAngle=180;


//notun kore lekha variables
ifstream scene("F:\\Graphics Offlines\\offline 3\\1605022\\scene.txt");

vector <Object*> objects;
vector <Light> lights;

int level_of_recursion,pixels_along_both_dimensions;

int no_of_objects,light_sources;




struct point pos,u,l,r;

void capture();


Vector3D Scale(Vector3D v,double factor)
{
	    Vector3D returnVec;

	    returnVec.x = v.x * factor;
	    returnVec.y = v.y * factor;
	    returnVec.z = v.z * factor;

	    return returnVec;
}




struct point cross_gun(struct point p1,struct point p2)
{
    struct point cross_P;

    cross_P.x = p1.y * p2.z - p1.z * p2.y;
    cross_P.y = p1.z * p2.x - p1.x * p2.z;
    cross_P.z = p1.x * p2.y - p1.y * p2.x;

    return cross_P;


}


double dotGun(struct point A, struct point B)
{

    double product = 0;
    product = product + (A.x*B.x)+(A.y*B.y)+(A.z*B.z);
    return product;
}

void RotateLR(int side)
{
     double ldot=dotGun(u,l);
     struct point lcross=cross_gun(u,l);

     double rdot=dotGun(u,r);
     struct point rcross=cross_gun(u,r);

    l.x=l.x*cos(side*angle)+lcross.x*sin(side*angle)+(u.x)*ldot*(1-cos(side*angle));
    l.y=l.y*cos(side*angle)+lcross.y*sin(side*angle)+(u.y)*ldot*(1-cos(side*angle));
    l.z=l.z*cos(side*angle)+lcross.z*sin(side*angle)+(u.z)*ldot*(1-cos(side*angle));

    r.x=r.x*cos(side*angle)+rcross.x*sin(side*angle)+(u.x)*rdot*(1-cos(side*angle));
    r.y=r.y*cos(side*angle)+rcross.y*sin(side*angle)+(u.y)*rdot*(1-cos(side*angle));
    r.z=r.z*cos(side*angle)+rcross.z*sin(side*angle)+(u.z)*rdot*(1-cos(side*angle));



}


void RotateLU(int side)
{
     double ldot=dotGun(r,l);
     struct point lcross=cross_gun(r,l);

     double udot=dotGun(r,u);
     struct point ucross=cross_gun(r,u);

    l.x=l.x*cos(side*angle)+lcross.x*sin(side*angle)+(r.x)*ldot*(1-cos(side*angle));
    l.y=l.y*cos(side*angle)+lcross.y*sin(side*angle)+(r.y)*ldot*(1-cos(side*angle));
    l.z=l.z*cos(side*angle)+lcross.z*sin(side*angle)+(r.z)*ldot*(1-cos(side*angle));

    u.x=u.x*cos(side*angle)+ucross.x*sin(side*angle)+(r.x)*udot*(1-cos(side*angle));
    u.y=u.y*cos(side*angle)+ucross.y*sin(side*angle)+(r.y)*udot*(1-cos(side*angle));
    u.z=u.z*cos(side*angle)+ucross.z*sin(side*angle)+(r.z)*udot*(1-cos(side*angle));


}


void animate(){


	glutPostRedisplay();
}


void RotateRU(int side)
{
     double rdot=dotGun(l,r);
     struct point rcross=cross_gun(l,r);

     double udot=dotGun(l,u);
     struct point ucross=cross_gun(l,u);

    r.x=r.x*cos(side*angle)+rcross.x*sin(side*angle)+(l.x)*rdot*(1-cos(side*angle));
    r.y=r.y*cos(side*angle)+rcross.y*sin(side*angle)+(l.y)*rdot*(1-cos(side*angle));
    r.z=r.z*cos(side*angle)+rcross.z*sin(side*angle)+(l.z)*rdot*(1-cos(side*angle));

    u.x=u.x*cos(side*angle)+ucross.x*sin(side*angle)+(l.x)*udot*(1-cos(side*angle));
    u.y=u.y*cos(side*angle)+ucross.y*sin(side*angle)+(l.y)*udot*(1-cos(side*angle));
    u.z=u.z*cos(side*angle)+ucross.z*sin(side*angle)+(l.z)*udot*(1-cos(side*angle));




}



void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);

			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);

			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}


void drawGrid()
{
	int i;
	if(drawgrid==1)
	{
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES);{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
			}
		}glEnd();
	}
}





void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
		    RotateLR(1);
            break;
        case '2':
            RotateLR(-1);
			break;
        case '3':
            RotateLU(1);
            break;
		case '4':
		    RotateLU(-1);
			break;
		case '5':
		    RotateRU(1);
			break;
		case '6':
		    RotateRU(-1);
			break;

		case '7':
            capture();
            break;

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			//cameraHeight -= 3.0;

			pos.x-=l.x;
			pos.y-=l.y;
			pos.z-=l.z;
			break;
		case GLUT_KEY_UP:// up arrow key
			//cameraHeight += 3.0;
			pos.x+=l.x;
			pos.y+=l.y;
			pos.z+=l.z;
			break;

		case GLUT_KEY_RIGHT:
			//cameraAngle += 0.03;
			pos.x+=r.x;
			pos.y+=r.y;
			pos.z+=r.z;
			break;
		case GLUT_KEY_LEFT:
			//cameraAngle -= 0.03;
			pos.x-=r.x;
			pos.y-=r.y;
			pos.z-=r.z;
			break;

		case GLUT_KEY_PAGE_UP:
		    pos.x+=u.x;
			pos.y+=u.y;
			pos.z+=u.z;
			break;

		case GLUT_KEY_PAGE_DOWN:
		    pos.x-=u.x;
			pos.y-=u.y;
			pos.z-=u.z;
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}



void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	gluLookAt(pos.x, pos.y, pos.z, pos.x + l.x, pos.y + l.y, pos.z + l.z, u.x, u.y, u.z);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();

    for(int i=0;i<objects.size();i++)
    {
        glPushMatrix();
        objects[i]->draw();
        glPopMatrix();
    }

     for(int i=0;i<lights.size();i++)
    {
        glPushMatrix();
        glPointSize(7);
        lights[i].draw();
        glPopMatrix();
    }













	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void skipNFileLines(int N)
{

    string s;
    s.reserve(30);

   //skip N lines
    for(int i = 0; i < N; ++i)
        getline(scene, s);


}

void loadData()
{
    string object_type;
    string fileLine;

    getline(scene,fileLine);
    size_t pos = 0;
    pos = fileLine.find(" ");
    cout<<fileLine.substr(0,pos);
    level_of_recursion = stoi(fileLine.substr(0,pos));

    cout<<level_of_recursion<<endl;

    getline(scene,fileLine);
    pos = 0;
    pos = fileLine.find(" ");
    pixels_along_both_dimensions = stoi(fileLine.substr(0,pos));
    cout<<pixels_along_both_dimensions<<endl;


    skipNFileLines(1);
    getline(scene,fileLine);
    pos = fileLine.find(" ");
    no_of_objects= stoi(fileLine.substr(0,pos));

    cout<<no_of_objects<<endl;

    for(int obj_count=1;obj_count<=no_of_objects;obj_count++)
    {
        getline(scene,fileLine);
        pos = fileLine.find(" ");
        object_type= fileLine.substr(0,pos);
        cout<<object_type<<endl;

        if(object_type=="sphere")
        {
            Vector3D center;
            double radius;
            double color[3];
            double coEfficients[4];
            int shine;

            //take center

            getline(scene,fileLine);
            pos = 0;
            pos = fileLine.find(" ");
            center.x= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            center.y= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            center.z= stod(fileLine.substr(0,pos));

            //take radius
            getline(scene,fileLine);
            pos = 0;
            pos = fileLine.find(" ");
            radius= stod(fileLine.substr(0,pos));

            //take color


            getline(scene,fileLine);
            pos = 0;
            pos = fileLine.find(" ");
            color[0]= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            color[1]= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            color[2]= stod(fileLine.substr(0,pos));

            //take coeff

            getline(scene,fileLine);
            pos = 0;
            pos = fileLine.find(" ");
            coEfficients[0]= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            coEfficients[1]= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            coEfficients[2]= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            coEfficients[3] = stod(fileLine.substr(0,pos));

            //take shine

            getline(scene,fileLine);
            pos = 0;
            pos = fileLine.find(" ");
            shine= stod(fileLine.substr(0,pos));

            Object *S;

            S=new Sphere(center,radius);

            S->setCoEfficients(coEfficients[0],coEfficients[1],coEfficients[2],coEfficients[3]);
            S->setColor(color[0],color[1],color[2]);

            S->setShine(shine);

            objects.push_back(S);

           // S->print();
            skipNFileLines(1);





        }
        else if(object_type=="triangle")
        {
            cout<<"t te dhukse"<<endl;
            struct Vector3D trianglePoints[3];
            double color[3];
            double coEfficients[4];
            int shine;
            for(int i=0;i<3;i++)
            {

                getline(scene,fileLine);
                pos = 0;
                pos = fileLine.find(" ");
                double x = stod(fileLine.substr(0,pos));
                fileLine.erase(0, pos + 1);

                pos = fileLine.find(" ");
                double y = stod(fileLine.substr(0,pos));
                fileLine.erase(0, pos + 1);

                pos = fileLine.find(" ");
                double z = stod(fileLine.substr(0,pos));

                trianglePoints[i].x=x;
                trianglePoints[i].y=y;
                trianglePoints[i].z=z;



            }


            //take color
            getline(scene,fileLine);
            pos = 0;
            pos = fileLine.find(" ");
            color[0]= stod(fileLine.substr(0,pos));
            cout<<color[0]<<endl;
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            color[1]= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            color[2] = stod(fileLine.substr(0,pos));

            //take coefficients
            getline(scene,fileLine);
            pos = 0;
            pos = fileLine.find(" ");
            coEfficients[0]= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            coEfficients[1]= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            coEfficients[2]= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            coEfficients[3] = stod(fileLine.substr(0,pos));

            //take shininess

            getline(scene,fileLine);
            pos = 0;
            pos = fileLine.find(" ");
            shine= stod(fileLine.substr(0,pos));



            Object *T;
          /*  for(int i=0;i<3;i++)
            {
                cout<<trianglePoints[i].x<<" "<<trianglePoints[i].y<<" "<<trianglePoints[i].z<<endl;

            }*/

            T=new Triangle(trianglePoints);

            T->setCoEfficients(coEfficients[0],coEfficients[1],coEfficients[2],coEfficients[3]);
            T->setColor(color[0],color[1],color[2]);

            T->setShine(shine);

            objects.push_back(T);

            //T->print();
            skipNFileLines(1);





        }
        else if(object_type=="general")
        {

            cout<<"general e dhukse"<<endl;

            double A,B,C,D,E,F,G,H,I,J;
            Vector3D reference_point;
            double height,width,length;
            double color[3];
            double coEfficients[4];
            int shine;


            //take A B C D...

            getline(scene,fileLine);
            pos = 0;
            pos = fileLine.find(" ");
            A= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            B= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            C= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            D= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            E= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            F= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            G= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            H= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            I= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            J= stod(fileLine.substr(0,pos));

            //take habijabi


            getline(scene,fileLine);
            pos = 0;
            pos = fileLine.find(" ");
            reference_point.x= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            reference_point.y= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            reference_point.z= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            length= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            width= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            height= stod(fileLine.substr(0,pos));


             //take color
            getline(scene,fileLine);
            pos = 0;
            pos = fileLine.find(" ");
            color[0]= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            color[1]= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            color[2] = stod(fileLine.substr(0,pos));

            //take coefficients
            getline(scene,fileLine);
            pos = 0;
            pos = fileLine.find(" ");
            coEfficients[0]= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            coEfficients[1]= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            coEfficients[2]= stod(fileLine.substr(0,pos));
            fileLine.erase(0, pos + 1);

            pos = fileLine.find(" ");
            coEfficients[3] = stod(fileLine.substr(0,pos));

            //take shininess

            getline(scene,fileLine);
            pos = 0;
            pos = fileLine.find(" ");
            shine= stod(fileLine.substr(0,pos));

            Object *g;

            g=new General(A,B,C,D,E,F,G,H,I,J);

            g->setCoEfficients(coEfficients[0],coEfficients[1],coEfficients[2],coEfficients[3]);
            g->setColor(color[0],color[1],color[2]);
            g->setLength(length);
            g->setHeight(height);
            g->setWidth(width);

            g->setShine(shine);

            objects.push_back(g);

           // g->print();
            skipNFileLines(1);



        }


        else
        {


        }


    }

    //take light sources
    getline(scene,fileLine);
    pos = 0;
    pos = fileLine.find(" ");
    light_sources= stoi(fileLine.substr(0,pos));

    cout<<light_sources<<endl;


    //take light sources attribute

    for(int i=1;i<=light_sources;i++)
    {
        Light L;

        //take position
        getline(scene,fileLine);
        pos = 0;
        pos = fileLine.find(" ");
        L.light_pos.x=stod(fileLine.substr(0,pos));
        fileLine.erase(0, pos + 1);

        pos = fileLine.find(" ");
        L.light_pos.y= stod(fileLine.substr(0,pos));
        fileLine.erase(0, pos + 1);

        pos = fileLine.find(" ");
        L.light_pos.z= stod(fileLine.substr(0,pos));

        //take color

        getline(scene,fileLine);
        pos = 0;
        pos = fileLine.find(" ");
        L.color[0]=stod(fileLine.substr(0,pos));
        fileLine.erase(0, pos + 1);

        pos = fileLine.find(" ");
        L.color[1]= stod(fileLine.substr(0,pos));
        fileLine.erase(0, pos + 1);

        pos = fileLine.find(" ");
        L.color[2]= stod(fileLine.substr(0,pos));

        lights.push_back(L);
        //L.printLight();

    }

    Object *F;
    F=new Floor(700,20);

    F->setCoEfficients(0.1,0.2,0.3,0.4);
    F->setColor(0.3,0.3,0.3);

    F->setShine(7);

    objects.push_back(F);




    scene.close();


}



void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0.02;




	pos.x=100;
    pos.y=100;
    pos.z=0;

    u.x=0;
    u.y=0;
    u.z=1;

    l.x=(-1)/sqrt(2);
    l.y=(-1)/sqrt(2);
    l.z=0;

    r.x=(-1)/sqrt(2);
    r.y=(1)/sqrt(2);
    r.z=0;





	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

void capture()
{
    double Windowidth=800, Windowheight=800;

    bitmap_image image(Windowidth, Windowheight);

    double planeDistance = (Windowidth/2.0) / (tan((80 * (pi / viewAngle))/2.0));

    Vector3D Scaled_Vector_l = Scale(VectorFromPoint(l),planeDistance);

    Vector3D Scaled_Vector_r = Scale(VectorFromPoint(r),Windowidth*0.5);

    Vector3D Scaled_Vector_u = Scale(VectorFromPoint(u),Windowheight*0.5);


    Vector3D top_left = VecAddition(Scaled_Vector_l,VectorFromPoint(pos),1);
    top_left=VecAddition(top_left,Scaled_Vector_r,-1);
    top_left=VecAddition(Scaled_Vector_u,top_left,1);

    double du = Windowidth/pixels_along_both_dimensions;
    double dv = Windowheight/pixels_along_both_dimensions;

    Vector3D  Scaled_Vector_r_du = Scale(VectorFromPoint(r),0.5*du);
    Vector3D Scaled_Vector_u_dv = Scale(VectorFromPoint(u),0.5*dv);


    top_left=VecAddition(top_left,Scaled_Vector_r_du,1);
    top_left=VecAddition(top_left,Scaled_Vector_u_dv,-1);

    int nearest;
    double t, tMin;

    for(int i=0;i<Windowidth;i++)
    {
        for(int j=0;j<Windowheight;j++)
        {
            tMin = large_value;

            Vector3D curr_pixel=VecAddition(top_left,Scale(VectorFromPoint(r),i*du),1);
            curr_pixel=VecAddition(curr_pixel,Scale(VectorFromPoint(u),j*dv),-1);

            Vector3D ray_dir=VecAddition(curr_pixel,VectorFromPoint(pos),-1);

            Ray ray(VectorFromPoint(pos), ray_dir);
            nearest = -1;

            double* color = new double[3];
            double* dummyColor = new double[3];

            for(int k=0 ; k<objects.size(); k++)
            {
                t = objects[k]->intersect(ray , dummyColor , 1);

                if(t > 0)
                {
                    if(t<tMin)
                    {
                         tMin = t;
                         nearest = k;
                    }
                }
            }

            if(nearest != -1)
            {
                tMin = objects[nearest]->intersect(ray , color , 1);

                color[0]*=255;
                color[1]*=255;
                color[2]*=255;


                image.set_pixel(i,j,color[0],color[1],color[2]);
            }
        }
    }




    image.save_image("F:\\Graphics Offlines\\offline 3\\1605022\\out.bmp");

    image.clear();

    cout<<"hoise"<<endl;
}


int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");
	init();
	loadData();


	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);
	glutIdleFunc(animate);	//display callback function
             		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
