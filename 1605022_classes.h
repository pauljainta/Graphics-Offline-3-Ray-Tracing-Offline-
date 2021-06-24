#include<iostream>
using namespace std;
struct Vector3D
{
    double x,y,z;
    Vector3D(){

    }
    Vec(double xx,double yy,double zz)
    {
        x=xx;
        y=yy;
        z=zz;
    }
};

struct point
{
    double x,y,z;
    point()
    {

    }
    point(double xx,double yy,double zz)
    {
        x=xx;
        y=yy;
        z=zz;
    }


};

class Object
{
    public:
    Vector3D reference_point; // should have x, y, z
    double height, width, length;
    double color[3];
    double coEfficients[4]; // reflection coefficients
    int shine; // exponent term of specular component
    Object(){};
    virtual void draw(){};
    void setColor(double R,double G,double B)
    {
        color[0]=R;
        color[1]=G;
        color[2]=B;

    };
    void setShine(int s)
    {
        shine=s;
    };
    void setCoEfficients(double x,double y,double z,double w)
    {
        coEfficients[0]=x;
        coEfficients[1]=y;
        coEfficients[2]=z;
        coEfficients[3]=w;

    };

    void setLength(double l)
    {
        length = l;
    }

    void setWidth(double w)
    {
        width = w;
    }

    void setHeight(double h)
    {
        height = h;
    }

   virtual void print(){};
};


class Sphere :public Object
{
   public:
    Sphere(){};
    Sphere(Vector3D center, double radius)
    {
        reference_point.x = center.x;
        reference_point.y=center.y;
        reference_point.z=center.z;
        length = radius;
    }
    void draw()
    {
        glTranslatef(reference_point.x, reference_point.y, reference_point.z);
        struct point points[100][100];
        int i,j;
        double h,r;
        double stacks=60;
        double slices=20;

        //generate points
        for(i=0;i<=stacks;i++)
        {
            h=length*sin(((double)i/(double)stacks)*(pi/2));
            r=length*cos(((double)i/(double)stacks)*(pi/2));
            for(j=0;j<=slices;j++)
            {
                points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
                points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
                points[i][j].z=h;
            }
        }
        //draw quads using generated points
        for(i=0;i<stacks;i++)
        {
            glColor3f(color[0],color[1],color[2]);
            for(j=0;j<slices;j++)
            {
                glBegin(GL_QUADS);{
                    //upper hemisphere
                    glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
                    glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
                    glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
                    glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                    //lower hemisphere
                    glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
                    glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
                    glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
                    glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
                }glEnd();
            }
        }

    }

    void print()
    {
        cout<<"Center"<<endl;
        cout<<reference_point.x<<" "<<reference_point.y<<" "<<reference_point.z<<endl;
        cout<<"radius"<<length<<endl;

        cout<<"Colors"<<endl;
        for(int i=0;i<3;i++)
        {
            cout<<color[i]<<" ";
        }
        cout<<"Coeffiients"<<endl;
        for(int i=0;i<4;i++)
        {
             cout<<coEfficients[i]<<" ";
        }
        cout<<"shine "<<shine<<endl;

        cout<<endl;
    }

};

class Triangle :public Object
{
    public:
       struct Vector3D points[3];
    Triangle(Vector3D p[3])
    {

        for(int i=0;i<3;i++)
        {

            points[i].x=p[i].x;
            points[i].y=p[i].y;
            points[i].z=p[i].z;

        }
    }
    Triangle(){};
    void draw()
    {
        glBegin(GL_TRIANGLES);
        glColor3f(color[0], color[1], color[2]);
        glVertex3f(points[0].x, points[0].y, points[0].z);
        glVertex3f(points[1].x, points[1].y, points[1].z);
        glVertex3f(points[2].x, points[2].y, points[2].z);
        glEnd();

    }

    void print()
    {
        cout<<"Points"<<endl;
        for(int i=0;i<3;i++)
        {
            cout<<points[i].x<<" "<<points[i].y<<" "<<points[i].z<<endl;
        }
        cout<<"Colors"<<endl;
        for(int i=0;i<3;i++)
        {
            cout<<color[i]<<" ";
        }
        cout<<"Coeffiients"<<endl;
        for(int i=0;i<4;i++)
        {
             cout<<coEfficients[i]<<" ";
        }
        cout<<"shine "<<shine<<endl;

        cout<<endl;
    }



};

class Floor :public Object
{
    public:
        double floorWidth;
    Floor(double fWidth, double tileWidth)
    {
        floorWidth=fWidth;
        length=tileWidth;
        reference_point.x=-floorWidth/2;
        reference_point.y=-floorWidth/2;
        reference_point.z=0;

    }
    void draw()
    {

        for(double var_along_x=reference_point.x ; var_along_x<=floorWidth/2 ; var_along_x+=length)
        {
            for(double var_along_y=reference_point.y ; var_along_y<=floorWidth/2 ; var_along_y+=length)
            {

                glBegin(GL_QUADS);
                {
                    glColor3f(color[0],color[1],color[2]);
                    glVertex3f(var_along_x, var_along_y , 0);
                    glVertex3f(var_along_x , var_along_y+length , 0);
                    glVertex3f(var_along_x+length , var_along_y+length , 0);
                    glVertex3f(var_along_x+length , var_along_y , 0);
                }
                glEnd();
                if(color[0]==0.3) setColor(0.7,0.8,0.9);
                else setColor(0.3,0.4,0.5);
            }
        }

    }

    void print()
    {
        cout<<"Points"<<endl;
        for(int i=0;i<3;i++)
        {
            cout<<reference_point.x<<" "<<reference_point.y<<" "<<reference_point.z<<endl;
        }
        cout<<"Colors"<<endl;
        for(int i=0;i<3;i++)
        {
            cout<<color[i]<<" ";
        }
        cout<<"Coeffiients"<<endl;
        for(int i=0;i<4;i++)
        {
             cout<<coEfficients[i]<<" ";
        }
        cout<<"shine "<<shine<<endl;

        cout<<endl;
    }



};

class General :public Object
{
   public:
       General(){};
       double A ,B, C, D, E ,F ,G, H ,I ,J;
       General(double a,double b,double c,double d,double e,double f,double g,double h,double i,double j)
       {
          A=a;
          B=b;
          C=c;
          D=d;
          E=e;
          F=f;
          G=g;
          H=h;
          I=i;
          J=j;

       }

    void draw()
    {

    }

    void print()
    {
        cout<<" ABCD"<<endl;
        cout<<A<<" "<<B<<" "<<C<<" "<<D<<" "<<E<<" "<<F<<" "<<G<<" "<<H<<" "<<I<<" "<<J<<endl;

        cout<<"cubic point length ...."<<endl;

        cout<<reference_point.x<<" "<<reference_point.y<<" "<<reference_point.z<<" "<<length<<" "<<width<<" "<<height<<endl;

        cout<<"Colors"<<endl;
        for(int i=0;i<3;i++)
        {
            cout<<color[i]<<" ";
        }
        cout<<"Coeffiients"<<endl;
        for(int i=0;i<4;i++)
        {
             cout<<coEfficients[i]<<" ";
        }
        cout<<"shine "<<shine<<endl;

        cout<<endl;
    }


};

class Light{
    public:
    Vector3D light_pos;
    double color[3];

    Light(){};

    void draw()
    {

        glBegin(GL_POINTS);
        glColor3f(color[0] ,color[1] ,color[2]);

        glVertex3f(light_pos.x , light_pos.y ,light_pos.z);

        glEnd();

    }

    void printLight()
    {
        cout<<"Position"<<endl;

        cout<<light_pos.x<<" "<<light_pos.y<<" "<<light_pos.z<<endl;

        cout<<"Colors"<<endl;
        for(int i=0;i<3;i++)
        {
            cout<<color[i]<<" ";
        }


        cout<<endl;
    }

};













