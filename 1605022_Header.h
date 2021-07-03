
#include<iostream>
#include <algorithm>
using namespace std;

double QuadraticEqnSolution(double a,double b,double c)
{
         if(a==0)
         {
            if(-2*b>0) return 0;
            else return -2*b;
         }

         double discriminant = b*b - 4*a*c;


         if (discriminant >= 0)
         {
            double n1=-b - sqrt(discriminant);
            double n2=-b + sqrt(discriminant);


            if(n1>0)
            {
                return n1/(2*a);
            }

            n2=-b + sqrt(discriminant);

            if(n2>0)
            {
                return n2/(2*a);
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

Vector3D Scale(Vector3D v,double factor)
{
	    Vector3D returnVec;

	    returnVec.x = v.x * factor;
	    returnVec.y = v.y * factor;
	    returnVec.z = v.z * factor;

	    return returnVec;
}

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
        dir=normalizeVec(dir);
    }

    void setDir(double x,double y,double z)
    {

        dir.x=x;
        dir.y=y;
        dir.z=z;
        dir=normalizeVec(dir);
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

extern vector<Light> lights;

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

extern vector<Object*> objects;

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

    double intersect(Ray ray,double* Objcolor,int r_level)
    {
        Vector3D vector_from_center_to_ray = VecAddition(ray.start,reference_point,-1);




        double a = dotMultiply(ray.dir,ray.dir);

        double b = 2.0 *dotMultiply(ray.dir,vector_from_center_to_ray);

        double c = dotMultiply(vector_from_center_to_ray,vector_from_center_to_ray) - pow(length,2);



    //    color[0]=this->color[0];
    //    color[1]=this->color[1];
     //   color[2]=this->color[2];

        double t=QuadraticEqnSolution(a,b,c);


        if(r_level != 0)
        {


            if(t==-1) return -1;

            Vector3D intersecting_point=VecAddition(ray.start,Scale(ray.dir,t),1);



            Objcolor[0] = this->color[0] * coEfficients[0];
            Objcolor[1] = this->color[1] * coEfficients[0];
            Objcolor[2] = this->color[2] * coEfficients[0];

            Vector3D normal_at_intersecting_point=normalizeVec(VecAddition(intersecting_point,reference_point,-1));



            for(int i=0 ; i<lights.size() ; i++)
            {
                Vector3D rs(lights[i].light_pos.x,lights[i].light_pos.y,lights[i].light_pos.z);
                Vector3D rd=VecAddition(intersecting_point,lights[i].light_pos,-1);


                Ray ray1(rs,rd);



                double current_t = (intersecting_point.x - ray1.start.x) / ray1.dir.x;
                double* dummyColor = new double[3];
                bool isObscured = false;

                for(int j=0 ; j<objects.size() ; j++)
                {
                    double t_l = objects[j]->intersect( ray1, dummyColor , 0);

                    if(t_l > 0 && floor(t_l) < floor(current_t))
                    {
                        isObscured = true;
                        break;
                    }
                }

                delete dummyColor;

                if(isObscured)
                {
                    continue;
                }

                double lambart_value=dotMultiply(normal_at_intersecting_point,ray1.dir);



                Vector3D rayr=VecAddition(ray1.dir,Scale(normal_at_intersecting_point,2*lambart_value),-1);

                double phong_value=dotMultiply(rayr,ray.dir);

                Objcolor[0] = Objcolor[0] + lights[i].color[0]*coEfficients[1]*abs(lambart_value)*this->color[0];
                Objcolor[1] = Objcolor[1] + lights[i].color[1]*coEfficients[1]*abs(lambart_value)*this->color[1];
                Objcolor[2] = Objcolor[2] + lights[i].color[2]*coEfficients[1]*abs(lambart_value)*this->color[2];



                Objcolor[0] = Objcolor[0] + lights[i].color[0]*coEfficients[2]* pow(abs(phong_value) , this->shine);
                Objcolor[1] = Objcolor[1] + lights[i].color[1]*coEfficients[2]* pow(abs(phong_value) , this->shine);
                Objcolor[2] = Objcolor[2] + lights[i].color[2]*coEfficients[2]* pow(abs(phong_value) , this->shine);



            }

            extern int level_of_recursion;

           // cout<<level_of_recursion<<endl;

            if(r_level >= level_of_recursion)
            {
                return t;
            }


              //reflection er suru

            Vector3D dir_of_reflection=VecAddition(ray.dir,Scale(normal_at_intersecting_point,2*dotMultiply(normal_at_intersecting_point,ray.dir)),-1);

            Ray reflected_ray(VecAddition(intersecting_point,dir_of_reflection,1),dir_of_reflection);






            int index_of_nearest_object = -1;
            double current_t2 , minimum_t = large_value;

            double* reflected_color = new double[3];
            double* dummyColor2 = new double[3];

            for(int j=0 ; j<objects.size() ; j++)
            {
                current_t2 = objects[j]->intersect(reflected_ray , dummyColor2 , 0);
                if(current_t2 > 0 && current_t2 < minimum_t)
                {
                    minimum_t = current_t2;
                    index_of_nearest_object = j;
                }
            }

            delete dummyColor2;

            if(index_of_nearest_object != -1)
            {
                minimum_t = objects[index_of_nearest_object]->intersect(reflected_ray , reflected_color , r_level+1);

                Objcolor[0] = Objcolor[0] + reflected_color[0]*coEfficients[3];
                Objcolor[1] = Objcolor[1] + reflected_color[1]*coEfficients[3];
                Objcolor[2] = Objcolor[2] + reflected_color[2]*coEfficients[3];
            }

           // delete reflected_color;

        }

        return t;

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
    double intersect(Ray ray,double* Objcolor,int r_level)
    {
        Vector3D e1 = VecAddition(points[1],points[0],-1);
        Vector3D e2 = VecAddition(points[2],points[0],-1);

        Vector3D h =crossMultiply(ray.dir,e2);

        double a = dotMultiply(h,e1);


       // color[0]=this->color[0];
      //  color[1]=this->color[1];
      //  color[2]=this->color[2];

        if(abs(a)>=0.00001)
        {

            Vector3D d =VecAddition(ray.start,points[0],-1);

            double alpha = dotMultiply(h,d)/a;

            if ( alpha > 1.0)
            {
                return -1;
            }
            if(alpha < 0.0)
            {
                return -1;
            }

            Vector3D q = crossMultiply(d,e1);

            double beta =dotMultiply(ray.dir,q)/a;

            if(beta < 0.0)
            {
                return -1;
            }

            if((alpha+beta) > 1.0)
            {
                return -1;
            }

            double t = dotMultiply(q,e2)/a;


            if(r_level != 0)
            {

                if(t==-1) return -1;

               Vector3D intersecting_point=VecAddition(ray.start,Scale(ray.dir,t),1);



                Objcolor[0] = this->color[0] * coEfficients[0];
                Objcolor[1] = this->color[1] * coEfficients[0];
                Objcolor[2] = this->color[2] * coEfficients[0];

                Vector3D normal_at_intersecting_point=normalizeVec(crossMultiply(e1,e2));

            //    Vector3D normal_at_intersecting_point=normalizeVec(VecAddition(intersecting_point,reference_point,-1));



                for(int i=0 ; i<lights.size() ; i++)
                {
                    Vector3D rs(lights[i].light_pos.x,lights[i].light_pos.y,lights[i].light_pos.z);
                    Vector3D rd=VecAddition(intersecting_point,lights[i].light_pos,-1);


                    Ray ray1(rs,rd);



                    double current_t = (intersecting_point.x - ray1.start.x) / ray1.dir.x;
                    double* dummyColor = new double[3];
                    bool isObscured = false;

                    for(int j=0 ; j<objects.size() ; j++)
                    {
                        double t_l = objects[j]->intersect( ray1, dummyColor , 0);

                        if(t_l > 0 && floor(t_l) < floor(current_t))
                        {
                            isObscured = true;
                            break;
                        }
                    }
                    delete dummyColor;

                    if(isObscured)
                    {
                        continue;
                    }

                    double lambart_value=dotMultiply(normal_at_intersecting_point,ray1.dir);



                    Vector3D rayr=VecAddition(ray1.dir,Scale(normal_at_intersecting_point,2*lambart_value),-1);

                    double phong_value=dotMultiply(rayr,ray.dir);

                    Objcolor[0] = Objcolor[0] + lights[i].color[0]*coEfficients[1]*abs(lambart_value)*this->color[0];
                    Objcolor[1] = Objcolor[1] + lights[i].color[1]*coEfficients[1]*abs(lambart_value)*this->color[1];
                    Objcolor[2] = Objcolor[2] + lights[i].color[2]*coEfficients[1]*abs(lambart_value)*this->color[2];



                    Objcolor[0] = Objcolor[0] + lights[i].color[0]*coEfficients[2]* pow(abs(phong_value) , this->shine);
                    Objcolor[1] = Objcolor[1] + lights[i].color[1]*coEfficients[2]* pow(abs(phong_value) , this->shine);
                    Objcolor[2] = Objcolor[2] + lights[i].color[2]*coEfficients[2]* pow(abs(phong_value) , this->shine);

                }

                extern int level_of_recursion;

                //cout<<level_of_recursion<<endl;

                if(r_level >= level_of_recursion)
                {
                    return t;
                }


                  //reflection er suru

                Vector3D dir_of_reflection=VecAddition(ray.dir,Scale(normal_at_intersecting_point,2*dotMultiply(normal_at_intersecting_point,ray.dir)),-1);

                Ray reflected_ray(VecAddition(intersecting_point,dir_of_reflection,1),dir_of_reflection);




                int index_of_nearest_object = -1;
                double current_t2 , minimum_t = large_value;

                double* reflected_color = new double[3];
                double* dummyColor2 = new double[3];

                for(int j=0 ; j<objects.size() ; j++)
                {
                    current_t2 = objects[j]->intersect(reflected_ray , dummyColor2 , 0);
                    if(current_t2 > 0 && current_t2 < minimum_t)
                    {
                        minimum_t = current_t2;
                        index_of_nearest_object = j;
                    }
                }

                delete dummyColor2;

                if(index_of_nearest_object != -1)
                {
                    minimum_t = objects[index_of_nearest_object]->intersect(reflected_ray , reflected_color , r_level+1);

                    Objcolor[0] = Objcolor[0] + reflected_color[0]*coEfficients[3];
                    Objcolor[1] = Objcolor[1] + reflected_color[1]*coEfficients[3];
                    Objcolor[2] = Objcolor[2] + reflected_color[2]*coEfficients[3];
                }

               // delete reflected_color;

            }


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
            int col = floor((var_along_y - reference_point.y)/length);
            for(double var_along_x=reference_point.x ; var_along_x<=floorWidth/2 ; var_along_x+=length)
            {
                int row = floor((var_along_x - reference_point.x)/length);

                int rc_checker=(row+col)%2;
                if(rc_checker!=0)
                {
                    setColor(0.3,0.3,0.3);

                }
                else{
                    setColor(0.7,0.7,0.7);
                }


                glBegin(GL_QUADS);
                {
                    glColor3f(color[0],color[1],color[2]);
                    glVertex3f(var_along_x, var_along_y , 0);
                    glVertex3f(var_along_x , var_along_y+length , 0);
                    glVertex3f(var_along_x+length , var_along_y+length , 0);
                    glVertex3f(var_along_x+length , var_along_y , 0);
                }
                glEnd();


            }
        }

    }

   double intersect(Ray ray,double* Objcolor,int r_level)
    {
            Vector3D origin(0, 0, 0);
            Vector3D normal(0, 0, 1);



            if(abs(dotMultiply(normal,ray.dir)) > 0.000001)
            {

                double t = dotMultiply(normal,VecAddition(origin,ray.start,-1))/dotMultiply(normal,ray.dir);

                Vector3D intersecting_point(ray.start.x + t*ray.dir.x, ray.start.y + t*ray.dir.y, 0);



                if(abs(intersecting_point.x) > floorWidth/2)
                    return -1;


                if(abs(intersecting_point.y) > floorWidth/2)
                        return -1;

                int rowCount = floor((intersecting_point.x - reference_point.x)/length);
                int colCount = floor((intersecting_point.y - reference_point.y)/length);

                int rc_checker=(rowCount+colCount)%2;

                if(rc_checker != 0)
                {
                    color[0]=0.3;
                    color[1]=0.3;
                    color[2]=0.3;
                }
                else
                {
                    color[0]=0.7;
                    color[1]=0.7;
                    color[2]=0.7;
                }

                if(r_level != 0)
                {
                    if(t==-1) return -1;

                   Vector3D intersecting_point=VecAddition(ray.start,Scale(ray.dir,t),1);



                    Objcolor[0] = this->color[0] * coEfficients[0];
                    Objcolor[1] = this->color[1] * coEfficients[0];
                    Objcolor[2] = this->color[2] * coEfficients[0];

                    Vector3D normal_at_intersecting_point=normal;



                    for(int i=0 ; i<lights.size() ; i++)
                    {
                        Vector3D rs(lights[i].light_pos.x,lights[i].light_pos.y,lights[i].light_pos.z);
                        Vector3D rd=VecAddition(intersecting_point,lights[i].light_pos,-1);


                        Ray ray1(rs,rd);



                        double current_t = (intersecting_point.x - ray1.start.x) / ray1.dir.x;
                        double* dummyColor = new double[3];
                        bool isObscured = false;

                        for(int j=0 ; j<objects.size() ; j++)
                        {
                            double t_l = objects[j]->intersect( ray1, dummyColor , 0);

                            if(t_l > 0 && floor(t_l) < floor(current_t))
                            {
                                isObscured = true;
                                break;
                            }
                        }

                        delete dummyColor;

                        if(isObscured)
                        {
                            continue;
                        }

                        double lambart_value=dotMultiply(normal_at_intersecting_point,ray1.dir);



                        Vector3D rayr=VecAddition(ray1.dir,Scale(normal_at_intersecting_point,2*lambart_value),-1);

                        double phong_value=dotMultiply(rayr,ray.dir);

                        Objcolor[0] = Objcolor[0] + lights[i].color[0]*coEfficients[1]*abs(lambart_value)*this->color[0];
                        Objcolor[1] = Objcolor[1] + lights[i].color[1]*coEfficients[1]*abs(lambart_value)*this->color[1];
                        Objcolor[2] = Objcolor[2] + lights[i].color[2]*coEfficients[1]*abs(lambart_value)*this->color[2];



                        Objcolor[0] = Objcolor[0] + lights[i].color[0]*coEfficients[2]* pow(abs(phong_value) , this->shine);
                        Objcolor[1] = Objcolor[1] + lights[i].color[1]*coEfficients[2]* pow(abs(phong_value) , this->shine);
                        Objcolor[2] = Objcolor[2] + lights[i].color[2]*coEfficients[2]* pow(abs(phong_value) , this->shine);

                    }

                     extern int level_of_recursion;

                   // cout<<level_of_recursion<<endl;

                    if(r_level >= level_of_recursion)
                    {
                        return t;
                    }


                      //reflection er suru

                    Vector3D dir_of_reflection=VecAddition(ray.dir,Scale(normal_at_intersecting_point,2*dotMultiply(normal_at_intersecting_point,ray.dir)),-1);

                    Ray reflected_ray(VecAddition(intersecting_point,dir_of_reflection,1),dir_of_reflection);

                    int index_of_nearest_object = -1;
                    double current_t2 , minimum_t = large_value;

                    double* reflected_color = new double[3];
                    double* dummyColor2 = new double[3];

                    for(int j=0 ; j<objects.size() ; j++)
                    {
                        current_t2 = objects[j]->intersect(reflected_ray , dummyColor2 , 0);
                        if(current_t2 > 0 && current_t2 < minimum_t)
                        {
                            minimum_t = current_t2;
                            index_of_nearest_object = j;
                        }
                    }

                    delete dummyColor2;

                    if(index_of_nearest_object != -1)
                    {
                        minimum_t = objects[index_of_nearest_object]->intersect(reflected_ray , reflected_color , r_level+1);

                        Objcolor[0] = Objcolor[0] + reflected_color[0]*coEfficients[3];
                        Objcolor[1] = Objcolor[1] + reflected_color[1]*coEfficients[3];
                        Objcolor[2] = Objcolor[2] + reflected_color[2]*coEfficients[3];
                    }

                  //  delete reflected_color;

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


    double GeneralQuadraticEqnSolution(double a,double b,double c,double rsx,double rsy,double rsz,double rdx,double rdy,double rdz)
    {
         double discriminant = b*b - 4*a*c;


         if (discriminant >= 0)
         {
            double n1=-b - sqrt(discriminant);
            double n2=-b + sqrt(discriminant);

            double t1 = n1/(2.0 * a);
            double t2 = n2/(2.0 * a);

            if(t1 < 0 && t2 < 0 )
            {

                return -1;
            }
            if(t1 < 0)
            {
                return t2;
            }
            else if(t2 < 0)
            {
                return t1;
            }
            else if(t1 >= 0 && t2 >= 0)
            {
                Vector3D intersecting_point1(rsx + t1*rdx, rsy + t1*rdy, rsz + t1*rdz);
                Vector3D intersecting_point2(rsx + t2*rdx, rsy + t2*rdy, rsz + t2*rdz);

                Vector3D vector_along_ip1_rp = VecAddition(intersecting_point1,reference_point,-1);
                Vector3D vector_along_ip2_rp = VecAddition(intersecting_point2,reference_point,-1);

                double t=-1;

                if(length > 0)
                {
                    if(abs(vector_along_ip1_rp.x) > length && abs(vector_along_ip2_rp.x) > length)
                        return -1;

                    else if(abs(vector_along_ip2_rp.x) > length)
                        t = t1;

                    else if(abs(vector_along_ip1_rp.x) > length)
                        t = t2;

                    else
                        t = min(t1, t2);
                }

                if(width > 0)
                {
                    if(abs(vector_along_ip1_rp.y) > width && abs(vector_along_ip2_rp.y) > width)
                        return -1;

                    else if(abs(vector_along_ip2_rp.y) > width)
                        t = t1;

                    else if(abs(vector_along_ip1_rp.y) > width)
                        t = t2;

                    else
                        t = min(t1, t2);
                }

                if(height > 0)
                {
                    if(abs(vector_along_ip1_rp.z) > height && abs(vector_along_ip2_rp.z) > height)
                        return -1;

                    else if(abs(vector_along_ip1_rp.z) > height)
                        t = t2;

                    else if(abs(vector_along_ip2_rp.z) > height)
                        t = t1;

                    else
                        t = min(t1, t2);
                }



                return t;

            }

            else cout<<"to eta tmi age bolba na"<<endl;

         }

         return -1;


    }

    double intersect(Ray ray,double* Objcolor,int r_level)
    {
        double rsx = ray.start.x;
        double rsy = ray.start.y;
        double rsz = ray.start.z;

        double rdx = ray.dir.x;
        double rdy = ray.dir.y;
        double rdz = ray.dir.z;

        double a = A*rdx*rdx + B*rdy*rdy + C*rdz*rdz + D*rdx*rdy + E*rdy*rdz + F*rdz*rdx;

        double b = 2*(A*rsx*rdx + B*rsy*rdy + C*rsz*rdz)
                 + D*(rsx*rdy + rsy*rdx) + E*(rsy*rdz + rsz*rdy) +  F*(rsz*rdx + rsx*rdz)
                 + G*rdx + H*rdy + I*rdz;

        double c = A*rsx*rsx + B*rsy*rsy + C*rsz*rsz
                 + D*rsx*rsy + E*rsy*rsz + F*rsz*rsx
                 + G*rsx + H*rsy + I*rsz + J;

       // color[0]=this->color[0];
       // color[1]=this->color[1];
      //  color[2]=this->color[2];


        double discriminant = b*b - 4*a*c;


         if (discriminant >= 0)
         {
            double n1=-b - sqrt(discriminant);
            double n2=-b + sqrt(discriminant);

            double t1 = n1/(2.0 * a);
            double t2 = n2/(2.0 * a);

            if(t1 < 0 && t2 < 0 )
            {

                return -1;
            }
            if(t1 < 0)
            {
                return t2;
            }
            else if(t2 < 0)
            {
                return t1;
            }
            else if(t1 >= 0 && t2 >= 0)
            {
                Vector3D intersecting_point1(rsx + t1*rdx, rsy + t1*rdy, rsz + t1*rdz);
                Vector3D intersecting_point2(rsx + t2*rdx, rsy + t2*rdy, rsz + t2*rdz);

                Vector3D vector_along_ip1_rp = VecAddition(intersecting_point1,reference_point,-1);
                Vector3D vector_along_ip2_rp = VecAddition(intersecting_point2,reference_point,-1);

                double t=-1;

                if(length > 0)
                {
                    if(abs(vector_along_ip1_rp.x) > length && abs(vector_along_ip2_rp.x) > length)
                        return -1;

                    else if(abs(vector_along_ip2_rp.x) > length)
                        t = t1;

                    else if(abs(vector_along_ip1_rp.x) > length)
                        t = t2;

                    else
                        t = min(t1, t2);
                }

                if(width > 0)
                {
                    if(abs(vector_along_ip1_rp.y) > width && abs(vector_along_ip2_rp.y) > width)
                        return -1;

                    else if(abs(vector_along_ip2_rp.y) > width)
                        t = t1;

                    else if(abs(vector_along_ip1_rp.y) > width)
                        t = t2;

                    else
                        t = min(t1, t2);
                }

                if(height > 0)
                {
                    if(abs(vector_along_ip1_rp.z) > height && abs(vector_along_ip2_rp.z) > height)
                        return -1;

                    else if(abs(vector_along_ip1_rp.z) > height)
                        t = t2;

                    else if(abs(vector_along_ip2_rp.z) > height)
                        t = t1;

                    else
                        t = min(t1, t2);
                }

                if(r_level != 0)
                {
                    if(t==-1) return -1;

                   Vector3D intersecting_point=VecAddition(ray.start,Scale(ray.dir,t),1);



                    Objcolor[0] = this->color[0] * coEfficients[0];
                    Objcolor[1] = this->color[1] * coEfficients[0];
                    Objcolor[2] = this->color[2] * coEfficients[0];

                    double del_x=2*A*intersecting_point.x + D*intersecting_point.y + E*intersecting_point.z + G;

                    double del_y=2*B*intersecting_point.y + D*intersecting_point.x + F*intersecting_point.z + H;

                    double del_z=2*C*intersecting_point.z + E*intersecting_point.x + F*intersecting_point.y + I;


                    Vector3D normal_at_intersecting_point(del_x,del_y,del_z);

                    normal_at_intersecting_point=normalizeVec(normal_at_intersecting_point);



                    for(int i=0 ; i<lights.size() ; i++)
                    {
                        Vector3D rs(lights[i].light_pos.x,lights[i].light_pos.y,lights[i].light_pos.z);
                        Vector3D rd=VecAddition(intersecting_point,lights[i].light_pos,-1);


                        Ray ray1(rs,rd);



                        double current_t = (intersecting_point.x - ray1.start.x) / ray1.dir.x;
                        double* dummyColor = new double[3];
                        bool isObscured = false;

                        for(int j=0 ; j<objects.size() ; j++)
                        {
                            double t_l = objects[j]->intersect( ray1, dummyColor , 0);

                            if(t_l > 0 && floor(t_l) < floor(current_t))
                            {
                                isObscured = true;
                                break;
                            }
                        }

                        delete dummyColor;

                        if(isObscured)
                        {
                            continue;
                        }

                        double lambart_value=dotMultiply(normal_at_intersecting_point,ray1.dir);



                        Vector3D rayr=VecAddition(ray1.dir,Scale(normal_at_intersecting_point,2*lambart_value),-1);

                        double phong_value=dotMultiply(rayr,ray.dir);

                        Objcolor[0] = Objcolor[0] + lights[i].color[0]*coEfficients[1]*abs(lambart_value)*this->color[0];
                        Objcolor[1] = Objcolor[1] + lights[i].color[1]*coEfficients[1]*abs(lambart_value)*this->color[1];
                        Objcolor[2] = Objcolor[2] + lights[i].color[2]*coEfficients[1]*abs(lambart_value)*this->color[2];



                        Objcolor[0] = Objcolor[0] + lights[i].color[0]*coEfficients[2]* pow(abs(phong_value) , this->shine);
                        Objcolor[1] = Objcolor[1] + lights[i].color[1]*coEfficients[2]* pow(abs(phong_value) , this->shine);
                        Objcolor[2] = Objcolor[2] + lights[i].color[2]*coEfficients[2]* pow(abs(phong_value) , this->shine);

                    }


                    extern int level_of_recursion;

                   // cout<<level_of_recursion<<endl;

                    if(r_level >= level_of_recursion)
                    {
                        return t;
                    }


                      //reflection er suru

                    Vector3D dir_of_reflection=VecAddition(ray.dir,Scale(normal_at_intersecting_point,2*dotMultiply(normal_at_intersecting_point,ray.dir)),-1);

                    Ray reflected_ray(VecAddition(intersecting_point,dir_of_reflection,1),dir_of_reflection);

                    int index_of_nearest_object = -1;
                    double current_t2 , minimum_t = large_value;

                    double* reflected_color = new double[3];
                    double* dummyColor2 = new double[3];

                    for(int j=0 ; j<objects.size() ; j++)
                    {
                        current_t2 = objects[j]->intersect(reflected_ray , dummyColor2 , 0);
                        if(current_t2 > 0 && current_t2 < minimum_t)
                        {
                            minimum_t = current_t2;
                            index_of_nearest_object = j;
                        }
                    }

                    delete dummyColor2;

                    if(index_of_nearest_object != -1)
                    {
                        minimum_t = objects[index_of_nearest_object]->intersect(reflected_ray , reflected_color , r_level+1);

                        Objcolor[0] = Objcolor[0] + reflected_color[0]*coEfficients[3];
                        Objcolor[1] = Objcolor[1] + reflected_color[1]*coEfficients[3];
                        Objcolor[2] = Objcolor[2] + reflected_color[2]*coEfficients[3];
                    }

                    //delete reflected_color;

                }

                return t;

            }

            else cout<<"to eta tmi age bolba na"<<endl;

         }

         return -1;





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















