#include "GenesisEngine/gfx/Screen.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iterator>
#include "GenesisEngine/gfx/Model.h"
#include "GenesisEngine/gfx/Bitmap.h"
#include "GenesisEngine/gfx/Camera.h"

#define PI 3.14

Colorf Colorf::add(Colorf s){
    r+=s.r;
    g+=s.g;
    b+=s.b;
    return {r,g,b};
}

Colorf Colorf::sub(Colorf s){
    r-=s.r;
    g-=s.g;
    b-=s.b;
    return {r,g,b};
}

Colorf Colorf::div(float d){
    r/=d;
    g/=d;
    b/=d;
    return {r,g,b};
}

void Vec::add(Vec v){
    Vec::x+=v.x;
    Vec::y+=v.y;
    Vec::z+=v.z;
}

void Vec::sub(Vec v){
    Vec::x-=v.x;
    Vec::y-=v.y;
    Vec::z-=v.z;
}

float nround(float v,float n){
    v*=pow(10,n-1);
    v = round(v);
    v/=pow(10,n-1);
    return v;
}

void Vec::round(){
    x=std::roundf(x);
    y=std::roundf(y);
    //z=std::roundf(z);
    /*
    x = (int)(x+0.5f);
    y = (int)(y+0.5f);
    z = (int)(z+0.5f);
    */
}

void UVcoordf::add(UVcoordf a){
    u+=a.u;
    v+=a.v;
    w+=a.w;
}

UVcoordf UVcoordf::multi(int m){
    return {u*m,v*m,w*m};
}

UVcoordf UVcoordf::multf(float m){
    return {u*m,v*m,w*m};
}

void Vec::mult(float m){
    x*=m;
    y*=m;
    z*=m;
}

Screen::Screen(int w,int h,Uint32* p){
    width = w;
    height = h;
    half_width = width/2;
    half_height = height/2;
    pixels = p;
    std::cout << "Screen constructor called and pixel array address is passed" << std::endl;
}

void clipTriangle(){
    std::vector<Vec> vclip;
}

Screen::Screen(){
}

Screen::~Screen(){
    std::cout << "Screen destructor called" << std::endl;
    delete[] zbuffer;
}

void Screen::clear(int col){
    for(int i = 0;i < width*height;i++){
        pixels[i] = col;
    }
    shown_polygon = 0;
}
void Screen::put(int x,int y,int col){
    if((x < 0||x >= width)||(y < 0||y >= height))return;
    pixels[x+y*width] = col;
}

void Screen::put(int x,int y,int col,float z){
    if((x < 0||x >= width)||(y < 0||y >= height))return;
    int index = x+y*width;
    if(zbuffer[index] <= z)return;
    pixels[index] = col;
    zbuffer[index] = z;
}

void Screen::render(int x,int y,int tx,int ty,Bitmap* bmp){
    for(int j = 0;j < 8;j++){
        int py = y+j;
        if(py < 0||py >= height)continue;
        for(int i = 0;i < 8;i++){
            int px = x+i;
            if(px < 0||px >= width)continue;
            int xtex = tx+i;
            int ytex = ty+j;
            int col = bmp->pixels[xtex+ytex*bmp->w];
            if(col!=0xff000000)pixels[px+py*width] = col&drawcolor;
        }
    }
}

static const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789<>()?!:/-= ";

void Screen::text(int x,int y,std::string text){
    int length = text.length();
    for(int i = 0;i < length;i++){
        text[i] = std::toupper(text.at(i));
        int index = characters.find(text[i]);
        int dc = drawcolor;
        setDrawColor(0x666666);
        render(1+x+i*8,y+1,index*8,0,font_texture);
        setDrawColor(dc);
        render(x+i*8,y,index*8,0,font_texture);
    }
}

void Screen::line(Vec v1,Vec v2){
    float dx = v2.x-v1.x;
    float dy = v2.y-v1.y;
    float length = sqrt(dx*dx+dy*dy);
    float xstep = dx/length;
    float ystep = dy/length;
    for(int i = 0;i < length;i++){
        put(v1.x+xstep*i,v1.y+ystep*i,drawcolor);
    }
}

void Screen::cline(float xstart,float xend,float ypos,Colorf lcol,Colorf rcol){
    if(ypos < 0||ypos >= height)return;
    if((xstart<0&&xend<0)||(xstart>width&&xend>width))return;
    xend=ceilf(xend);
    xstart=floorf(xstart);
    float length = xend-xstart;
    float r = lcol.r;
    float g = lcol.g;
    float b = lcol.b;
    float rs = (rcol.r-lcol.r)/length;
    float gs = (rcol.g-lcol.g)/length;
    float bs = (rcol.b-lcol.b)/length;
    for(int i = 0;i < length;i++){
        r+=rs;
        g+=gs;
        b+=bs;
        put(xstart+i,ypos,(int)(r*255)<<16|(int)(g*255)<<8|(int)(b*255));
    }
}

void Screen::cline(float xstart,float xend,float ypos){
    if(ypos < 0||ypos >= height)return;
    if((xstart<0&&xend<0)||(xstart>width&&xend>width))return;
    xend=ceilf(xend);
    xstart=floorf(xstart);
    float length = xend-xstart;
    for(int i = 0;i < length;i++){
        put(xstart+i,ypos,drawcolor);
    }
}

void Screen::tline(float xstart,float xend,float ypos,UVcoordf uvl,UVcoordf uvr){
    if(ypos < 0||ypos >= height)return; // y axis out of screen
    if((xstart<0&&xend<0)||(xstart>width&&xend>width))return;
    xend=ceilf(xend);
    xstart=floorf(xstart);
    float length = xend-xstart;
    float du = (uvr.u-uvl.u)/length;
    float dv = (uvr.v-uvl.v)/length;
    float dw = (uvr.w-uvl.w)/length;
    for(int i = 0;i < length;i++){
        float u = uvl.u+du*i;
        float v = uvl.v+dv*i;
        float w = uvl.w+dw*i;
        int x = xstart+i;
        if(x >= 0&&x < width)pixels[x+(int)ypos*width] = texture->getUV(u/w,v/w);
    }
}

void Screen::tline(float xstart,float xend,float ypos,UVcoordf uvl,UVcoordf uvr,float zl,float zr){
    if(ypos < 0||ypos >= height)return; // y axis out of screen
    if((xstart<0&&xend<0)||(xstart>width&&xend>width))return;
    xend=ceilf(xend);
    xstart=floorf(xstart);
    float length = xend-xstart;
    float du = (uvr.u-uvl.u)/length;
    float dv = (uvr.v-uvl.v)/length;
    float dw = (uvr.w-uvl.w)/length;
    float dz = (zr-zl)/length;
    for(int i = 0;i < length;i++){
        float u = uvl.u+du*i;
        float v = uvl.v+dv*i;
        float w = uvl.w+dw*i;
        float z = (zl+dz*i)/w;
        put(xstart+i,ypos,texture->getUV(u/w,v/w),z);
        /*
        int x = xstart+i;
        if(x >= 0&&x < width){
            int index = x+(int)ypos*width;
            if(zbuffer[index]>z){
            pixels[index] = texture->getUV(u/w,v/w);
            zbuffer[index] = z;
            }
        }
        */
    }
}

void Screen::setCamera(Vec v){
    camera = v;
}
void Screen::setCamera(Camera c){
    camera = c.getPosition();
    setAngle(c.getAngle());
}

void Screen::setAngle(Vec angle){
    CalcTrig(angle,trigs);
}

void Screen::addModel(Model model){
    //add model to the scene
    int offset = global_vertices.size(); //face offset
    global_vertices.insert(global_vertices.end(),model.vertices.begin(),model.vertices.end());
    for(int i = 0;i < model.faces.size();i++){
        Face orig = model.faces[i];
        orig.f1 = offset+orig.f1;
        orig.f2 = offset+orig.f2;
        orig.f3 = offset+orig.f3;
        global_faces.push_back(orig);
    }
}

void Screen::add(Vec* v,int mode){
    int offset = global_vertices.size();
    Face f = {mode,offset+0,offset+1,offset+2};
    for(int i = 0;i < mode;i++){
        global_vertices.push_back(v[i]);
    }
    if(mode==RENDERMODE_TEXTURED_TRIANGLE){
        f.uv1 = v[0].uvcoord;
        f.uv2 = v[1].uvcoord;
        f.uv3 = v[2].uvcoord;
    }
    global_faces.push_back(f);
}

void Screen::drawScene(){
    for(int i = 0;i < global_faces.size();i++){
        Face f = global_faces.at(i);
        if(f.mode==RENDERMODE_POINT){
            Vec point = global_vertices[f.f1];
            put(point.screenX,point.screenY,drawcolor);
        }
        if(f.mode==RENDERMODE_TRIANGLE){
            Vec v1 = global_vertices[f.f1];
            Vec v2 = global_vertices[f.f2];
            Vec v3 = global_vertices[f.f3];
            polygon(v1,v2,v3);
        }

        if(f.mode==RENDERMODE_TEXTURED_TRIANGLE){
            Vec v1 = global_vertices[f.f1];
            Vec v2 = global_vertices[f.f2];
            Vec v3 = global_vertices[f.f3];
            v1.uvcoord = f.uv1;
            v2.uvcoord = f.uv2;
            v3.uvcoord = f.uv3;
            if(texture_mapping){
                tpolygon(v1,v2,v3);
            }else{
                setDrawColor(0xcccccc);
                polygon(v1,v2,v3);
            }

            if(polygon_outlines){
                if(((v2.x-v1.x)*(v3.y-v2.y))-((v2.y-v1.y)*(v3.x-v2.x))<=0){
                setDrawColor(0xffffff);
                line(v1,v2);
                line(v1,v3);
                line(v2,v3);
                }
            }
        }

        if(f.mode==RENDERMODE_LINE){
        }
    }
}

void Screen::clearScene(){
    //clear global_faces and global_vertices
    global_faces.clear();
    global_vertices.clear();
}

void Screen::rotateScene(){
    for(int i = vertex_index;i < global_vertices.size();i++){
        rotateY(&global_vertices[i],trigs[3],trigs[4]);
        rotateX(&global_vertices[i],trigs[0],trigs[1]);
    }
}

void Screen::translateScene(){
    for(int i = vertex_index;i < global_vertices.size();i++){
        global_vertices[i].sub(camera);
    }
}

void Screen::clipScene(float zn,float zf){
    for(int i = 0;i < global_faces.size();i++){
        Face f = global_faces.at(i);
        if(f.mode==RENDERMODE_POINT){
            Vec point = global_vertices[f.f1];
            if(point.z<zn){
                global_faces.erase(global_faces.begin()+i);
                i--;
            }
        }

        if(f.mode==RENDERMODE_TEXTURED_TRIANGLE){
            //near clipping

            Vec v[3] = {global_vertices[f.f1],global_vertices[f.f2],global_vertices[f.f3]};

            int frontvertexcount = 0;

            for(int j = 0;j < 3;j++){
                if(v[j].z > zn)frontvertexcount++;
            }
            if(frontvertexcount!=3){
                global_faces.erase(global_faces.begin()+i);
                i--;
            }
        }
        
    }
}

void Screen::ProjectScene(){
    //std::cout << global_faces.size() << std::endl;
    for(int i = vertex_index;i < global_vertices.size();i++){
        ApplyPerspective(&global_vertices[i]);
    }
}

void Screen::CalcTrig(Vec a,float* tarr){
    tarr[0] = sinf(a.x);
    tarr[1] = cosf(a.x);
    tarr[2] = 0;
    tarr[3] = sinf(a.y);
    tarr[4] = cosf(a.y);
}

void flattop(Vec& v1,Vec& v2,Vec& v3){

}

void Screen::polygon(Vec v1,Vec v2,Vec v3){

    v1.x = v1.screenX;
    v1.y = v1.screenY;

    v2.x = v2.screenX;
    v2.y = v2.screenY;

    v3.x = v3.screenX;
    v3.y = v3.screenY;

    if(((v2.x-v1.x)*(v3.y-v2.y))-((v2.y-v1.y)*(v3.x-v2.x))>0)return; //backface culling
    
    Vec temp;
    if(v1.y > v2.y){
        temp = v2;
        v2 = v1;
        v1 = temp;
    }
    if(v1.y > v3.y){
        temp = v3;
        v3 = v1;
        v1 = temp;
    }
    if(v2.y > v3.y){
        temp = v3;
        v3 = v2;
        v2 = temp;
    }

    float xr = v1.x;
    float xl = v1.x;

    if(SUBPIXEL_ACCURATE){
    v1.round();
    v2.round();
    v3.round();
    }

    if(v1.y==v2.y)v1.y-=0.1f;

    float y12 = (v2.y-v1.y);
    float y13 = (v3.y-v1.y);
    float y23 = (v3.y-v2.y);

    float a12 = (v2.x-v1.x)/y12;
    float a13 = (v3.x-v1.x)/y13;
    float a23 = (v3.x-v2.x)/y23;

    if(a12 > a13){
        for(float y = v1.y;y <= v2.y;y++){
            float yy = y-v1.y;
            cline(xl+a13*yy,xr+a12*yy,y);
        }
        xl+=a13*y12;
        xr+=a12*y12;
        for(float y = v2.y;y < v3.y;y++){
            float yy = y-v2.y;
            cline(xl+a13*yy,xr+a23*yy,y);
        }
    }else{
         for(float y = v1.y;y <= v2.y;y++){
            float yy = y-v1.y;
            cline(xl+a12*yy,xr+a13*yy,y);
        }
        xl+=a12*y12;
        xr+=a13*y12;
        for(float y = v2.y;y < v3.y;y++){
            float yy = y-v2.y;
            cline(xl+a23*yy,xr+a13*yy,y);
        }
    }
    shown_polygon++;
}

void Screen::tpolygon(Vec v1,Vec v2,Vec v3){
    
    v1.x = v1.screenX;
    v1.y = v1.screenY;
    v2.x = v2.screenX;
    v2.y = v2.screenY;
    v3.x = v3.screenX;
    v3.y = v3.screenY;

    if(((v2.x-v1.x)*(v3.y-v2.y))-((v2.y-v1.y)*(v3.x-v2.x))>0)return; //backface culling

    v1.uvcoord.u *= v1.zdiv;
    v1.uvcoord.v *= v1.zdiv;
    v1.uvcoord.w *= v1.zdiv;

    v2.uvcoord.u *= v2.zdiv;
    v2.uvcoord.v *= v2.zdiv;
    v2.uvcoord.w *= v2.zdiv;

    v3.uvcoord.u *= v3.zdiv;
    v3.uvcoord.v *= v3.zdiv;
    v3.uvcoord.w *= v3.zdiv;
    
    Vec temp;
    if(v1.y > v2.y){
        temp = v2;
        v2 = v1;
        v1 = temp;
    }
    if(v1.y > v3.y){
        temp = v3;
        v3 = v1;
        v1 = temp;
    }
    if(v2.y > v3.y){
        temp = v3;
        v3 = v2;
        v2 = temp;
    }

    float xr = v1.x;
    float xl = v1.x;
    float zr = v1.z;
    float zl = v1.z;
    

    //if(SUBPIXEL_ACCURATE){
    v1.round();
    v2.round();
    v3.round();
    //}

    if(v1.y==v2.y){
        //flattop(v1,v2,v3); //render flat top polygons
        v1.y--;
    }

    float y12 = v2.y-v1.y;
    float y13 = v3.y-v1.y;
    float y23 = v3.y-v2.y;

    float a12 = (v2.x-v1.x)/y12; //avoid floating point division overflow
    float a13 = (v3.x-v1.x)/y13;
    float a23 = (v3.x-v2.x)/y23;

    float z12 = (v2.z-v1.z)/y12;
    float z13 = (v3.z-v1.z)/y13;
    float z23 = (v3.z-v2.z)/y23;

    UVcoordf uv1 = v1.uvcoord;
    UVcoordf uv2 = v2.uvcoord;
    UVcoordf uv3 = v3.uvcoord;

    UVcoordf uvl = {uv1.u,uv1.v,uv1.w};
    UVcoordf uvr = {uv1.u,uv1.v,uv1.w};

    UVcoordf uv12 = {(uv2.u-uv1.u)/y12,(uv2.v-uv1.v)/y12,(uv2.w-uv1.w)/y12};
    UVcoordf uv13 = {(uv3.u-uv1.u)/y13,(uv3.v-uv1.v)/y13,(uv3.w-uv1.w)/y13};
    UVcoordf uv23 = {(uv3.u-uv2.u)/y23,(uv3.v-uv2.v)/y23,(uv3.w-uv2.w)/y23};

    //std::cout << zl << std::endl;

    if(a12 > a13){
        for(int y = v1.y;y < v2.y;y++){
            tline(xl,xr,y,uvl,uvr,zl,zr);
            xl+=a13;
            xr+=a12;
            zl+=z13;
            zr+=z12;
            uvr.add(uv12);
            uvl.add(uv13);
        }
        for(int y = v2.y;y < v3.y;y++){
            tline(xl,xr,y,uvl,uvr,zl,zr);
            xl+=a13;
            xr+=a23;
            zl+=z13;
            zr+=z23;
            uvr.add(uv23);
            uvl.add(uv13);
        }
    }else{
         for(int y = v1.y;y < v2.y;y++){
            tline(xl,xr,y,uvl,uvr,zl,zr);
            xl+=a12;
            xr+=a13;
            zl+=z12;
            zr+=z13;
            uvr.add(uv13);
            uvl.add(uv12);
        }
        for(int y = v2.y;y < v3.y;y++){
            tline(xl,xr,y,uvl,uvr,zl,zr);
            xl+=a23;
            xr+=a13;
            zl+=z23;
            zr+=z13;
            uvr.add(uv13);
            uvl.add(uv23);
        }
    }
    
    shown_polygon++;
}

void Screen::DrawIndexBuffer(int rendermode,int index,int indices){
    //Draw Geometry from indexbuffer, index offset to specified amount of indices 
    //perform projection and clipping and rasterizing
}

void Screen::setFieldOfView(float f){
    if(f<=1)f=1;
    fov = f;
    z0 = (width/2.0)/(tanf((fov/2.0)*M_PI/180.0));
}

void Screen::ApplyPerspective(Vec* v){
    float calc = (z0/v->z);
    v->zdiv = calc;
    v->x = v->screenX = v->x*calc+half_width;
    v->y = v->screenY = v->y*calc+half_height;
    //v->z = 1.0f/v->z;
}

Vec Screen::ApplyPerspective(Vec v){
    float calc = (z0/v.z);
    float x = v.x*calc+half_width;
    float y = v.y*calc+half_height;
    v.screenX = x;
    v.screenY = y;
    return v;
}

void Screen::rotateX(Vec* v,float sin,float cos){
    float y = cos*v->y-sin*v->z;
    float z = sin*v->y+cos*v->z;
    v->y = y;
    v->z = z;
}

void Screen::rotateY(Vec* v,float sin,float cos){
    float x = cos*v->x+sin*v->z;
    float z = -sin*v->x+cos*v->z;
    v->x = x;
    v->z = z;
}

void Screen::rotateX(Vec* v,float angle){
    float s = sinf(angle);
    float c = cosf(angle);
    float y = c*v->y-s*v->z;
    float z = s*v->y+c*v->z;
    v->y = y;
    v->z = z;
}

void Screen::rotateY(Vec* v,float angle){
    float s = sinf(angle);
    float c = cosf(angle);
    float x = c*v->x+s*v->z;
    float z = -s*v->x+c*v->z;
    v->x = x;
    v->z = z;
}

void Screen::PushScene(){
    vertex_index = global_vertices.size();
}

void Screen::rotatef(float x,float y,float z){
    float angles[9];
    Vec a = {x,y,z};
    CalcTrig(a,angles);
    for(int i = vertex_index;i < global_vertices.size();i++){
        rotateY(&global_vertices[i],angles[3],angles[4]);
        rotateX(&global_vertices[i],angles[0],angles[1]);
    }
}

void Screen::translatef(float x,float y,float z){
    Vec a = {x,y,z};
    for(int i = vertex_index;i < global_vertices.size();i++){
        global_vertices[i].add(a);
    }
}

void Screen::PopScene(){
    vertex_index = 0;
}