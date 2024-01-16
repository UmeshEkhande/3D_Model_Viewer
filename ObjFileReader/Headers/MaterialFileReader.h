#pragma once
#include "MaterialReader.h"
#include "pch.h"

class OBJFILEREADER_API MaterialFileReader : public MaterialReader
{
public:
    MaterialFileReader(const std::string& inFilePath);
    ~MaterialFileReader();
    virtual std::string operator() ( const std::string& matId, std::vector<material_t>& materials, std::map<std::string, int>& matMap);

    std::string LoadObj( std::vector<shape_t>& shapes,std::vector<material_t>& materials,const char* filename, const char* inFilePath = NULL);

    std::string LoadObj( std::vector<shape_t>& shapes, std::vector<material_t>& materials, std::istream& inStream, MaterialReader& readMatFn);

private:
    std::string mFilePath;
};

