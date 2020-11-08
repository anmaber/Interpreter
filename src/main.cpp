#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "MobileObj.hh"
#include <string>
#include <sstream>
#include "Set4LibInterfaces.hpp"
#include "Scene.hh"

using namespace std;


#define LINE_SIZE 500

bool ExecPreprocesor( const char * NazwaPliku, std::istringstream &IStrm4Cmds )
{
    std::string Cmd4Preproc = "cpp -P ";
    char Line[LINE_SIZE];
    std::ostringstream OTmpStrm;
    Cmd4Preproc += NazwaPliku;
    FILE* pProc = popen(Cmd4Preproc.c_str(),"r");
    if (!pProc) return false;
    while (fgets(Line,LINE_SIZE,pProc))
    {
        OTmpStrm << Line;
    }
    IStrm4Cmds.str(OTmpStrm.str());
    return pclose(pProc) == 0;
}

int main(int argc, char **argv)
{
  if(argc < 2)
  {
      std::cerr << "Too few arguments\n";
      return 1;
  }

  std::istringstream IStrm4Cmds;

  if(!ExecPreprocesor(argv[1], IStrm4Cmds))
  {
      std::cerr<< "Cannot process\n";
      return 2;
  }

  std::cout << IStrm4Cmds.str() << "\n";  

  Set4LibInterfaces libInerfaces;
  Scene scene;

  for (std::string line; std::getline(IStrm4Cmds, line); )
  {
     std::string libName, objectName;
     std:istringstream ss(line);
     ss >> libName;
     ss >> objectName;
     
     auto mobileObject = scene.findMobileObject(objectName);
     if(!mobileObject)
     {
       scene.addMobileObject(objectName);
     }
     mobileObject = scene.findMobileObject(objectName);
     auto interface = libInerfaces.findInterface(libName);
     if(!interface)
     {
       std::cerr << "couldnt find interface for: "  << libName << "\n";
       return 2;
     }
     if(!interface->execActions(ss, mobileObject))
     {
       std::cerr << "couldnt execute action for: " << ss.str()<< "\n";
       return 2;
     }
  }
  return 0;
}
