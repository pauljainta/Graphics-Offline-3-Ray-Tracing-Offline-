#include<iostream>
using namespace std;
double QuadraticEqnSolution(double a,double b,double c)
{

    double discriminant = b*b - 4*a*c;

     if (discriminant >= 0)
     {
        double n=-b - sqrt(discriminant);
        if(n>0)
        {
            return n/(2*a);
        }
        n=-b + sqrt(discriminant);

        if(n>0)
        {
            return n/(2*a);
        }

     }

     return -1;


}
struct Vector3D
{
    double x,y,z;
    Vector3D(){

    }
    Vector3D(double xx,double yy,double zz)
    {
        x=xx;
        y=yy;
        z=zz;
    }
};

struct Vector3D crossMultiply(struct Vector3D v1,struct Vector3D v2)
{
    struct Vector3D crossProductVec;

    crossProductVec.x = v1.y * v2.z - v1.z * v2.y;
    crossProductVec.y = v1.z * v2.x - v1.x * v2.z;
    crossProductVec.z = v1.x * v2.y - v1.y * v2.x;

    return crossProductVec;


}

struct Vector3D normalizeVec(struct Vector3D v)
{
    Vector3D returnVec;
    double VecValue=sqrt(pow(v.x,2)+pow(v.y,2)+pow(v.z,2));
    returnVec.x=v.x/VecValue;
    returnVec.y=v.y/VecValue;
    returnVec.z=v.z/VecValue;
    return returnVec;

}

class Ray{
    public:
    Vector3D start;
    Vector3D dir;
    Ray(Vector3D s,Vector3D d)
    {

        start.x=s.x;
        start.y=s.y;
        start.z=s.z;

        dir.x=d.x;
        dir.y=d.y;
        dir.z=d.z;

        dir=normalizeVec(dir);

    }

    void setStart(Vector3D s)
    {

        start.x=s.x;
        start.y=s.y;
        start.z=s.z;
    }
     void setStart(double x,double y,double z)
    {

        start.x=x;
        start.y=y;
        start.z=z;
    }

    void setDir(Vector3D d)
    {

        dir.x=d.x;
        dir.y=d.y;
        dir.z=d.z;
    }

    void setDir(double x,double y,double z)
    {

        dir.x=x;
        dir.y=y;
        dir.z=z;
    }

};

double dotMultiply(struct Vector3D v1, struct Vector3D v2)
{

    double product = 0;
    product = product + (v1.x*v2.x)+(v1.y*v2.y)+(v1.z*v2.z);
    return product;
}

struct Vector3D VecAddition(struct Vector3D v1,struct Vector3D v2,int addOrSubtract)
{
    struct Vector3D returnVec;
    returnVec.x=v1.x+(addOrSubtract)*v2.x;
    returnVec.y=v1.y+(addOrSubtract)*v2.y;
    returnVec.z=v1.z+(addOrSubtract)*v2.z;
    return returnVec;


}

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

Vector3D VectorFromPoint(struct point p)
{
    Vector3D v(p.x,p.y,p.z);
    return v;

}

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
    virtual double intersect(Ray,double*,int){};
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

    double intersect(Ray ray,double* color,int r_level)
    {
        Vector3D vector_from_center_to_ray = VecAddition(ray.start,reference_point,-1);




        double a = dotMultiply(ray.dir,ray.dir);

        double b = 2.0 *dotMultiply(ray.dir,vector_from_center_to_ray);

        double c = dotMultiply(vector_from_center_to_ray,vector_from_center_to_ray) - pow(length,2);

        color[0]=this->color[0];
        color[1]=this->color[1];
        color[2]=this->color[2];


        return QuadraticEqnSolution(a,b,c);

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
    double intersect(Ray ray,double* color,int l)
    {
        Vector3D e1 = VecAddition(points[1],points[0],-1);
        Vector3D e2 = VecAddition(points[2],points[0],-1);

        Vector3D h =crossMultiply(ray.dir,e2);

        double a = dotMultiply(h,e1);


        color[0]=this->color[0];
        color[1]=this->color[1];
        color[2]=this->color[2];

        if(abs(a)>=0.00001)
        {

            Vector3D d =VecAddition(ray.start,points[0],-1);

            double alpha = dotMultiply(h,d)/a;

            if (alpha < 0.0 || alpha > 1.0)
            {
                return -1.0;
            }

            Vector3D q = crossMultiply(d,e1);

            double beta =dotMultiply(ray.dir,q)/a;

            if(beta < 0.0 || (alpha+beta) > 1.0)
            {
                return -1.0;
            }

            double t = dotMultiply(q,e2)/a;

            if(t > 0.00001)
            {
                return t;
            }

            return -1;


        }

        return -1;




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


        for(double var_along_y=reference_point.y ; var_along_y<=floorWidth/2 ; var_along_y+=length)
        {
            for(double var_along_x=reference_point.x ; var_along_x<=floorWidth/2 ; var_along_x+=length)
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

   double intersect(Ray ray,double* color,int r_level)
    {
            Vector3D origin(0, 0, 0);
            Vector3D normal(0, 0, 1);



            if(abs(dotMultiply(normal,ray.dir)) > 0.000001)
            {

               double t = dotMultiply(normal,VecAddition(origin,ray.start,-1))/dotMultiply(normal,ray.dir);

                Vector3D intersecting_point(ray.start.x + t*ray.dir.x, ray.start.y + t*ray.dir.y, 0);

                if( abs(intersecting_point.y) > floorWidth/2 || abs(intersecting_point.x) > floorWidth/2)
                    return -1.0;

                int row = floor((intersecting_point.x - reference_point.x)/length);
                int col = floor((intersecting_point.y - reference_point.y)/length);

                if((row+col)%2 == 0)
                {
                    for(int i=0;i<3;i++)
                    {
                        color[i] = 0.2;
                    }
                }
                else
                {
                    for(int i=0;i<3;i++)
                    {
                        color[i] = 0.8;
                    }
                }

                return t;
        }
        return -1;


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

    double intersect(Ray ray,double* color,int r_level)
    {
        double rx = ray.start.x;
        double ry = ray.start.y;
        double rz = ray.start.z;

        double dx = ray.dir.x;
        double dy = ray.dir.y;
        double dz = ray.dir.z;

        double a = A*dx*dx + B*dy*dy + C*dz*dz + D*dx*dy + E*dy*dz + F*dz*dx;

        double b = 2*(A*rx*dx + B*ry*dy + C*rz*dz)
                 + D*(rx*dy + ry*dx) + E*(ry*dz + rz*dy) +  F*(rz*dx + rx*dz)
                 + G*dx + H*dy + I*dz;

        double c = A*rx*rx + B*ry*ry + C*rz*rz
                 + D*rx*ry + E*ry*rz + F*rz*rx
                 + G*rx + H*ry + I*rz + J;




        return QuadraticEqnSolution(a,b,c);


      /*  double discriminant = b*b - 4*a*c;


        if(discriminant < 0.0)
        {
            return -1.0;
        }

        double numerator1 = -b - sqrt(discriminant);
        double numerator2 = -b + sqrt(discriminant);

        double t1 = numerator1/(2.0 * a);
        double t2 = numerator2/(2.0 * a);


        double t = -1.0;

        if(t1 < 0 && t2 < 0)
        {
            return -1.0;
        }

        if(t1 < 0)
        {
            t = t2;
        }

        if(t2 < 0)
        {
            t = t1;
        }

        if(t1 >= 0 && t2 >= 0)
        {
            Point intersecting_point1(rx + t1*dx, ry + t1*dy, rz + t1*dz);
            Point intersecting_point2(rx + t2*dx, ry + t2*dy, rz + t2*dz);

            Point temp1 = intersecting_point1.sub(reference_point);
            Point temp2 = intersecting_point2.sub(reference_point);

            if(length > 0)
            {
                if(abs(temp1.x) > length && abs(temp2.x) > length)
                    return -1.0;

                if(abs(temp1.x) > length)
                    t = t2;

                else if(abs(temp2.x) > length)
                    t = t1;

                else
                    t = min(t1, t2);
            }

            if(width > 0)
            {
                if(abs(temp1.y) > width && abs(temp2.y) > width)
                    return -1.0;

                if(abs(temp1.y) > width)
                    t = t2;

                else if(abs(temp2.y) > width)
                    t = t1;

                else
                    t = min(t1, t2);
            }

            if(height > 0)
            {
                if(abs(temp1.z) > height && abs(temp2.z) > height)
                    return -1.0;

                if(abs(temp1.z) > height)
                    t = t2;

                else if(abs(temp2.z) > height)
                    t = t1;

                else
                    t = min(t1, t2);
            }
        }

        return t;

*/
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













