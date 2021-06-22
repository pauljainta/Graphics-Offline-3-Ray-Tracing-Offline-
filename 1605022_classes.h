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
    void setColor(){};
    void setShine(){};
    void setCoEfficients(){};
};


class Sphere :public Object
{
   public:
       double radius;
       Vector3D center;
       Sphere(){};
    Sphere(Vector3D center, double radius)
    {
        reference_point = center;
        length = radius;
    }
    void draw()
    {

    }

};

class Triangle :public Object
{
   public:
       struct point points[3];
    Triangle(struct point points[3],double color[3],double coEfficients[4],int shine)
    {
        //this->points=points;
       // this->color=color;
        //this->coEfficients=coEfficients;
       // this->shine=shine;
    }
    Triangle(){};
    void draw()
    {

    }

};

class General :public Object
{
   public:
       General(){};
       double A ,B, C, D, E ,F ,G, H ,I ,J;
       Vector3D cube_reference_point;double length, width, height;

    void draw()
    {

    }

};

class Light{
    public:
    Vector3D light_pos;
    double color[3];

    Light(){};

};

void printTriangle(Triangle T)
{
    cout<<"Points"<<endl;
    for(int i=0;i<3;i++)
    {
        cout<<T.points[i].x<<" "<<T.points[i].y<<" "<<T.points[i].z<<endl;
    }
    cout<<"Colors"<<endl;
    for(int i=0;i<3;i++)
    {
        cout<<T.color[i]<<" ";
    }
    cout<<"Coeffiients"<<endl;
    for(int i=0;i<4;i++)
    {
         cout<<T.coEfficients[i]<<" ";
    }
    cout<<"shine "<<T.shine<<endl;

    cout<<endl;
}


void printSphere(Sphere S)
{
    cout<<"Center"<<endl;
    cout<<S.center.x<<" "<<S.center.y<<" "<<S.center.z<<endl;
    cout<<"radius"<<S.radius<<endl;

    cout<<"Colors"<<endl;
    for(int i=0;i<3;i++)
    {
        cout<<S.color[i]<<" ";
    }
    cout<<"Coeffiients"<<endl;
    for(int i=0;i<4;i++)
    {
         cout<<S.coEfficients[i]<<" ";
    }
    cout<<"shine "<<S.shine<<endl;

    cout<<endl;
}


void printGeneral(General G)
{
    cout<<" ABCD"<<endl;
    cout<<G.A<<" "<<G.B<<" "<<G.C<<" "<<G.D<<" "<<G.E<<" "<<G.F<<" "<<G.G<<" "<<G.H<<" "<<G.I<<" "<<G.J<<endl;

    cout<<"cubic point length ...."<<endl;

    cout<<G.cube_reference_point.x<<" "<<G.cube_reference_point.y<<" "<<G.cube_reference_point.z<<" "<<G.length<<" "<<G.width<<" "<<G.height<<endl;

    cout<<"Colors"<<endl;
    for(int i=0;i<3;i++)
    {
        cout<<G.color[i]<<" ";
    }
    cout<<"Coeffiients"<<endl;
    for(int i=0;i<4;i++)
    {
         cout<<G.coEfficients[i]<<" ";
    }
    cout<<"shine "<<G.shine<<endl;

    cout<<endl;
}


void printLight(Light L)
{
    cout<<"Position"<<endl;

        cout<<L.light_pos.x<<" "<<L.light_pos.y<<" "<<L.light_pos.z<<endl;

    cout<<"Colors"<<endl;
    for(int i=0;i<3;i++)
    {
        cout<<L.color[i]<<" ";
    }


    cout<<endl;
}



