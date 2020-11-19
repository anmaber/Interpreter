//TO DO format, użyć wszedzie pragma once
#include <iostream>
#include <cassert>
#include <string>
#include <sstream>

#include "xmlinterp.hh"
#include <list>

#define LINE_SIZE 500


bool ExecPreprocesor(const char *NazwaPliku, std::istringstream &IStrm4Cmds)
{
     std::string Cmd4Preproc = "cpp -P ";
     char Line[LINE_SIZE];
     std::ostringstream OTmpStrm;
     Cmd4Preproc += NazwaPliku;
     FILE *pProc = popen(Cmd4Preproc.c_str(), "r");
     if (!pProc)
          return false;
     while (fgets(Line, LINE_SIZE, pProc))
     {
          OTmpStrm << Line;
     }
     IStrm4Cmds.str(OTmpStrm.str());
     return pclose(pProc) == 0;
}

/*!
 * Czyta z pliku opis poleceń i dodaje je do listy komend,
 * które robot musi wykonać.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param CmdList - (\b we.) zarządca listy poleceń dla robota.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */


int main(int argc, char **argv)
{
     Set4LibInterfaces libInterfaces;
     Scene scene;

     Configuration Config(libInterfaces, scene);

     if (!ReadFile("../config/config.xml", Config))
          return 1;

     if (argc < 2)
     {
          std::cerr << "Too few arguments\n";
          return 1;
     }

     std::istringstream IStrm4Cmds;

     if (!ExecPreprocesor(argv[1], IStrm4Cmds))
     {
          std::cerr << "Cannot process\n";
          return 2;
     }

     std::cout << IStrm4Cmds.str() << "\n";

     for (std::string line; std::getline(IStrm4Cmds, line);)
     {
          std::string libName, objectName;
          std::istringstream ss(line);
          ss >> libName;
          ss >> objectName;

          std::shared_ptr<MobileObj> mobileObject = scene.findMobileObject(objectName);
          if (!mobileObject)
          {
               std::cerr << "couldnt find object: " << objectName << "\n";
               return 2;
          }
          std::shared_ptr<LibInterface> interface = libInterfaces.findInterface(libName);
          if (!interface)
          {
               std::cerr << "couldnt find lib: " << libName << "\n";
               return 2;
          }

          if (!interface->execActions(ss, mobileObject))
          {
               std::cerr << "couldnt execute action for: " << ss.str() << "\n";
               return 2;
          }
     }
     return 0;
}
