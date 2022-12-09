#include "GenesisEngine/gfx/Model.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

Model::Model(){

}

std::vector<std::string> split(const std::string &s,char delimiter){
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;
    while(getline(ss,item,delimiter)){
        result.push_back(item);
    }
    return result;
}

Model::Model(const char* filename){

    int vcount = 0;
    int fcount = 0;
    int qcount = 0;
    std::fstream file;
    file.open(filename,std::ios::in);
    std::vector<UVcoordf> vts;

    bool countline = std::strcmp(filename,"res/toyota-ae86/source/AE86.obj")==0;
    int curline = 0;

    if(file.is_open()){
        std::string line;
        while(getline(file,line)){
            curline++;
            if(line[0]=='#')continue;
            std::vector<std::string> parsed = split(line,' ');
            
            for(int i = 0;i < parsed.size();i++){
                if(parsed[i]==""){
                    parsed.erase(parsed.begin()+i);
                }
            }
            
            if(parsed.size()==0)continue;

            if(parsed[0]=="o"){
                oname = parsed[1];
            }

            if(parsed[0]=="v"){
                vcount++;
                float r = 1;
                float g = 1;
                float b = 1;

                if(parsed.size()>4){
                r = stof(parsed[4])/255;
                g = stof(parsed[5])/255;
                b = stof(parsed[6])/255;
                }

                Vec v = {stof(parsed[1]),stof(parsed[2]),stof(parsed[3]),{r,g,b}};
                vertices.push_back(v);
            }

            if(parsed[0]=="vt"){
                UVcoordf vt = {stof(parsed[1]),stof(parsed[2]),1.0};
                vts.push_back(vt);
            }

            if(parsed[0]=="f"&&parsed.size()==5)qcount++;

            if(parsed[0]=="f"){
                fcount++;
                std::vector<std::string> subst1 = split(parsed[1],'/');
                std::vector<std::string> subst2 = split(parsed[2],'/');
                std::vector<std::string> subst3 = split(parsed[3],'/');
                std::vector<std::string> subst4;
                std::vector<std::string> subst5;

                if(parsed.size()>=5)subst4 = split(parsed[4],'/');
                if(parsed.size()>=6)subst5 = split(parsed[5],'/');

                if(subst1.size()>1){
                    if(parsed.size()==4){
                    //std::cout << "detected face with texture coordinates" << std::endl;
                    Face f = {Screen::RENDERMODE_TEXTURED_TRIANGLE,stoi(subst1[0])-1,stoi(subst2[0])-1,stoi(subst3[0])-1,vts.at(stoi(subst1[1])-1),vts.at(stoi(subst2[1])-1),vts.at(stoi(subst3[1])-1)};
                    faces.push_back(f);
                    }else if(parsed.size()==5){
                        //triangulate quad
                        Face f1 = {Screen::RENDERMODE_TEXTURED_TRIANGLE,stoi(subst1[0])-1,stoi(subst2[0])-1,stoi(subst3[0])-1,vts.at(stoi(subst1[1])-1),vts.at(stoi(subst2[1])-1),vts.at(stoi(subst3[1])-1)};
                        Face f2 = {Screen::RENDERMODE_TEXTURED_TRIANGLE,stoi(subst4[0])-1,stoi(subst1[0])-1,stoi(subst3[0])-1,vts.at(stoi(subst4[1])-1),vts.at(stoi(subst1[1])-1),vts.at(stoi(subst3[1])-1)};
                        faces.push_back(f1);
                        faces.push_back(f2);
                    }else if(parsed.size()==6){
                        //triangulate pentagon
                        int verts[5] = {stoi(subst1[0])-1,stoi(subst2[0])-1,stoi(subst3[0])-1,stoi(subst4[0])-1,stoi(subst5[0])-1};
                        UVcoordf texcoords[5] = {vts.at(stoi(subst1[1])-1),vts.at(stoi(subst2[1])-1),vts.at(stoi(subst3[1])-1),vts.at(stoi(subst4[1])-1),vts.at(stoi(subst5[1])-1)};
                        Face f1 = {Screen::RENDERMODE_TEXTURED_TRIANGLE,verts[0],verts[1],verts[2],texcoords[0],texcoords[1],texcoords[2]};
                        Face f2 = {Screen::RENDERMODE_TEXTURED_TRIANGLE,verts[0],verts[2],verts[3],texcoords[0],texcoords[2],texcoords[3]};
                        Face f3 = {Screen::RENDERMODE_TEXTURED_TRIANGLE,verts[0],verts[3],verts[4],texcoords[0],texcoords[3],texcoords[4]};
                        faces.push_back(f1);
                        faces.push_back(f2);
                        faces.push_back(f3);
                        
                    }
                }else{
                    if(parsed.size()==4){
                    Face f = {Screen::RENDERMODE_TRIANGLE,stoi(parsed[1])-1,stoi(parsed[2])-1,stoi(parsed[3])-1};
                    faces.push_back(f);
                    }
                }

            }
            if(parsed[0]=="t"){
                hasTexture=true;
            }
        }
    }
    file.close();
    std::cout << "The Object [" << oname << "] " << "has " << vcount <<" vertices"<< std::endl;
    std::cout << "The Object [" << oname << "] " << "has " << fcount <<" faces"<< std::endl;
    std::cout << "The Object [" << oname << "] " << "has " << vts.size() <<" texture_coordinates"<< std::endl;
    std::cout << "The Object [" << oname << "] " << "has " << qcount <<" quad faces"<< std::endl;
    if(!hasTexture)std::cout << "The Object [" << oname << "] " << "does not specify texture file" << std::endl;
}

void Model::fromText(const char* text){
    
}

void Model::scale(float s){
    for(int i = 0;i < vertices.size();i++){
        vertices[i].mult(s);
    }
}
