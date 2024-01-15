#pragma once
#include <string>
#include <vector>
#include <map>
#include "pch.h"



class OBJFILEREADER_API MaterialReader
{

public:
    struct material_t
    {
        std::string name;

        float ambient[3];
        float diffuse[3];
        float specular[3];
        float transmittance[3];
        float emission[3];
        float shininess;
        float ior;                
        float dissolve;           
        int illum;

        std::string ambient_texname;
        std::string diffuse_texname;
        std::string specular_texname;
        std::string normal_texname;
        std::map<std::string, std::string> unknown_parameter;
    };


    struct mesh_t
    {
        std::vector<float>          positions;
        std::vector<float>          normals;
        std::vector<float>          texcoords;
        std::vector<unsigned int>   indices;
        std::vector<int>            material_ids; 
    };

    struct  shape_t
    {
        std::string  name;
        mesh_t       mesh;
    };

public:
    MaterialReader() {}
    virtual ~MaterialReader() {}
    virtual std::string operator() (const std::string& matId,std::vector<material_t>& materials, std::map<std::string, int>& matMap) = 0;
};

