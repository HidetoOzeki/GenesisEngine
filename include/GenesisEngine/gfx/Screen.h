#ifndef SCREEN_H
#define SCREEN_H
#include <SDL2/SDL.h>
#include <vector>
#include <string>
class Model;
class Bitmap;
class Camera;

#define say(x) std::cout << x << std::endl;

struct Colorf{
    float r,g,b;
    float w = 1;
    Colorf add(Colorf);
    Colorf sub(Colorf);
    Colorf div(float d);
};

struct UVcoordf {
    float u,v;
    float w = 1;
    void add(UVcoordf a);
    UVcoordf multi(int);
    UVcoordf multf(float);
};

struct Vec{
    float x,y,z;
    Colorf color;
    UVcoordf uvcoord;
    float screenX,screenY;
    float zdiv;
    void add(Vec);
    void sub(Vec);
    void mult(float m);
    void div(float d);
    void round();
};

struct Face{ //consider renaming it "Shape" or other similar meaning
    int mode;
    int f1,f2,f3;
    UVcoordf uv1,uv2,uv3;// individual polygon better not have or calculate UVcoordinates 
};

struct Point2i{
    int x,y;
};

struct Point2f{
    float x,y;
};

class Screen{
    int width;
    int height;

    int half_width;
    int half_height;

    Uint32* pixels;

    Vec camera;
    Vec angles;
    float trigs[3*3];

    int vertex_index = 0;

    std::vector<Vec> global_vertices;
    std::vector<Face> global_faces;

    float* VertexBuffer;
    int VertexBufferSize;

    int* IndexBuffer;
    int IndexBufferSize;

    float z0 = 0;
    float fov = 0;

    float znear = -10.0f;
    float zfar = 100.0f;

    int drawcolor = 0xffffff;
    Bitmap* texture;
    Bitmap* font_texture;

    public:

    bool texture_mapping = true;
    bool polygon_outlines = false;
    bool show_vertices = false;
    bool show_depth = true;
    bool flat_shading = false;

    int shown_polygon = 0;

    float* zbuffer;

    static const int RENDERMODE_POINT = 1;
    static const int RENDERMODE_LINE = 2;
    static const int RENDERMODE_TRIANGLE = 3;
    static const int RENDERMODE_TEXTURED_TRIANGLE = 4;

    bool SUBPIXEL_ACCURATE = false;

    Screen();
    Screen(int w,int h,Uint32* p);
    ~Screen();

    void setTexture(Bitmap* t){
        texture = t;
    }

    void setFontTexture(Bitmap* ft){
        font_texture = ft;
    }

    int getFaceCount(){
        return global_faces.size();
    }

    void setDrawColor(int color){
        drawcolor=color;
    }

    void render(int x,int y,int tx,int ty,Bitmap* bmp);

    void text(int x,int y,std::string text);

    void clear(int col);
    void clearZbuffer();
    void put(int,int,int);
    void put(int,int,int,float z);
    void line(Vec v1,Vec v2);
    void tline(float xstart,float xend,float ypos,UVcoordf uvl,UVcoordf uvr); //TODO textured line

    void tline(float xstart,float xend,float ypos,UVcoordf uvl,UVcoordf uvr,float zl,float zr);
    void cline(float xstart,float yend,float ypos,Colorf lcol,Colorf rcol);
    void cline(float xstart,float yend,float ypos);
    void polygon(Vec v1,Vec v2,Vec v3);
    void cpolygon(Vec v1,Vec v2,Vec v3); //TODO colored polygon
    void tpolygon(Vec v1,Vec v2,Vec v3); //TODO textured polygon

    void setFieldOfView(float);
    void ApplyPerspective(Vec* v);
    Vec ApplyPerspective(Vec v);

    void setCamera(Vec v); //set Camera position
    void setCamera(Camera c);
    void setAngle(Vec angle); //set Camera Angle


    void addModel(Model model); //add Model vertices and faces to the scene DONT SPECIFY RENDERMODE HERE
    void add(Vec* v,int mode); // DONT SPECIFY RENDERMODE HERE

    void bindVertexBuffer(float* vb,int size){
        VertexBuffer = vb; //memory of previous pointer should be freed at some point
        VertexBufferSize=size;
    }

    void bindIndexBuffer(int* index,int size){
        IndexBuffer = index; //memory of previous pointer should be freed at some point
        VertexBufferSize=size;
    }

    void bindTexture(Bitmap* tex){
        texture = tex;
    }

    void DrawIndexBuffer(int rendermode,int indexoffset,int indices);

    //addIndice function : add face information (batch render-able)

    /*

    batch rendering example (render two colored/textured rectangle with triangle polygons)

    //vertex element order : x,y,z,r,g,b,u,v,

    //storing textureid to every vertex doesnt make sense

    float vertices[] = {
        -1.0f ,-1.0f , 1.0f , 255 , 0 , 0,
        1.0f ,-1.0f , 1.0f , 255 , 0 , 0,
        1.0f ,1.0f , 1.0f , 255 , 0 , 0,
        -1.0f ,1.0f , 1.0f , 255 , 0 , 0,

        1.0f ,-1.0f , 1.0f , 0 , 255 , 0,
        3.0f ,-1.0f , 1.0f , 0 , 255 , 0,
        3.0f ,1.0f , 1.0f , 0 , 255 , 0,
        1.0f ,1.0f , 1.0f , 0 , 255 , 0
    }

    screen.bindVertexBuffer(vertices,sizeof(vertices)/sizeof(*vertices));

    screen.rotate();
    screen.translate();

    int indices[] = {
        0,1,2,2,3,0, //two triangle each row
        4,5,6,6,7,4
    }

    screen.bindIndexBuffer(indices,sizeof(indices)/sizeof(*indices));

    screen.DrawIndexBuffer(RENDERMODE_TRIANGLE,0,12); //draw all as triangle
    screen.DrawIndexBuffer(RENDERMODE_POINT,0,12); //draw all as point
    screen.DrawIndexBuffer(RENDERMODE_LINE,0,6); //draw 2 triangle as line

    //changing texture

    screen.bindTexture(CrateBox);
    screen.DrawIndexBuffer(RENDERMODE_TEXTURED_TRIANGLE,0,6); // draw 1 square with bound texture
    screen.bindTexture(DynamiteBox);
    screen.DrawIndexBuffer(RENDERMODE_TEXTURED_TRIANGLE,6,6); // draw 1 square with bound texture

    */

    void PushScene();

    void rotatef(float x,float y,float z);
    void translatef(float x,float y,float z);

    void PopScene();

    void translateScene(); // translate (Vec.sub) all global_vertices
    void rotateScene(); // rotate all global_vertices **rotating order :: Y to X**

    void clipScene(float zn,float zf); //TODO Clip all global_faces

    void ProjectScene();//perspective_project all global_vertices

    void drawScene(); //draw Scene // Specify RENDERMODE Here
    void clearScene(); //clear Scene

    void CalcTrig(Vec a,float* tarr); //pass array of Trigonometric value of an angle

    void rotateX(Vec* v,float sin,float cos);
    void rotateY(Vec* v,float sin,float cos);

    void rotateX(Vec* v,float angle);
    void rotateY(Vec* v,float angle);

    void msse_mult(float* d,float* l,float* r);
    void msse_div(float* d,float* l,float* r);
};

#endif