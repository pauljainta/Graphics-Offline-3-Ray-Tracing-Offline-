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













