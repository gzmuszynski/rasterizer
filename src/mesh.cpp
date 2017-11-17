#include "mesh.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <iterator>


mesh::mesh(std::string filename)
{
    std::ifstream file;

    file.open(filename);

    std::cout << "file is opened? " << file.is_open() << std::endl;

    std::string line;

    std::vector<float4> normals;
    std::vector<float4> texcoords;
    std::vector<color>  colors;

    while(!file.eof())
    {
        std::getline(file, line);

        std::vector<std::string> vstrings = split(line,' ');

        if(!vstrings.empty())
        {
            std::string first = vstrings[0];
            if(first == "v")
            {
                vertex *v = new vertex(std::stof(vstrings[2]),
                                      std::stof(vstrings[3]),
                                      std::stof(vstrings[4]));
                v->col = 0xffffffff;

                vertices.push_back(v);
            }
            else if(first == "vn")
            {
                float4 n = {std::stof(vstrings[1]),
                            std::stof(vstrings[2]),
                            std::stof(vstrings[3])};

                normals.push_back(n);
            }
            else if(first == "vt")
            {
                float4 t = {std::stof(vstrings[1]),
                            std::stof(vstrings[2]),
                            std::stof(vstrings[3])};

                texcoords.push_back(t);
            }
            else if(first == "c")
            {
                std::string s = vstrings[1];
                unsigned int col;
                std::stringstream ss;
                ss << std::hex << s;
                ss >> col;
                color c = {col};

                colors.push_back(c);
            }
            else if(first == "f")
            {
                std::vector<std::string> vs1 = split(vstrings[1], '/');
                std::vector<std::string> vs2 = split(vstrings[2], '/');
                std::vector<std::string> vs3 = split(vstrings[3], '/');

                vertex *a  = vertices [stoi(vs1[0])-1];
                vertex *b  = vertices [stoi(vs2[0])-1];
                vertex *c  = vertices [stoi(vs3[0])-1];

                float4 an = normals  [stoi(vs1[2])-1];
                float4 bn = normals  [stoi(vs1[2])-1];
                float4 cn = normals  [stoi(vs1[2])-1];

                float4 at = texcoords[stoi(vs1[1])-1];
                float4 bt = texcoords[stoi(vs1[1])-1];
                float4 ct = texcoords[stoi(vs1[1])-1];

                a->norm = an; b->norm = bn; c->norm = cn;
                a->uv   = at; b->uv   = bt; c->uv   = ct;

                triangle *t = new triangle(a, b, c);
                triangles.push_back(t);
            }
            else if(first == "cf")
            {
                std::vector<std::string> cf = split(vstrings[1], '/');

                triangle *t = triangles[stoi(cf[0])-1];
                color    c = colors   [stoi(cf[1])-1];

                t->A->col = c;
                t->B->col = c;
                t->C->col = c;
            }
            else if(first == "#")
            {
                std::cout << line << std::endl;
            }
        }
    }
}

mesh::mesh(float a, float b, float c)
{

    vertex *R = new vertex(a,0.0f,0.0f);
    vertex *T = new vertex(0.0f,b,0.0f);
    vertex *B = new vertex(0.0f,0.0f,c);
    vertex *L = new vertex(0.0f,0.0f,0.0f);

    R->col = 0xFFFF0000;
    T->col = 0xFF00FF00;
    L->col = 0xFF0000FF;
    B->col = 0xFFFFFFFF;

    vertices.push_back(R);
    vertices.push_back(T);
    vertices.push_back(B);
    vertices.push_back(L);

    triangle *front  = new triangle(L,T,R);
    triangle *side   = new triangle(B,T,L);
    triangle *bottom = new triangle(B,L,R);

    triangles.push_back(front);
    triangles.push_back(side);
    triangles.push_back(bottom);
}
