// ObjReader.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "ObjReader.h"


// This is an example of an exported variable
OBJREADER_API int nObjReader=0;

// This is an example of an exported function.
OBJREADER_API int fnObjReader(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
ObjReader::ObjReader()
{
    return;
}
