//TO DO format, użyć wszedzie pragma once
#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
#include "Set4LibInterfaces.hpp"
#include "Scene.hh"
#include "xmlinterp.hh"
#include "sender.hpp"
#include <list>
#include "exceptions.hpp"

#define LINE_SIZE 500

bool ExecPreprocesor(const char *NazwaPliku, std::stringstream &IStrm4Cmds)
{
     std::string Cmd4Preproc = "cpp -P ";
     char Line[LINE_SIZE];
     std::stringstream OTmpStrm;
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

int main(int argc, char **argv)
{
     Set4LibInterfaces libInterfaces;
     Scene scene;

     Configuration Config;

     std::stringstream IStrm4Cmds;
     std::cout << "Port: " << PORT << std::endl;
     int Socket4Sending;

     if (!ReadFile("../config/config.xml", Config))
     {
          std::cerr<<"Couldnt read configuration file \n";

     }
          

     libInterfaces.configure(Config);
     scene.configure(Config);

     if (!OpenConnection(Socket4Sending))
          return 1;

     Sender ClientSender(Socket4Sending, &scene);
     std::thread Thread4Sending(Fun_CommunicationThread, &ClientSender);


     if (argc < 2)
     {
          std::cerr << "Too few arguments\n";
          return 1;
     }

     if (!ExecPreprocesor(argv[1], IStrm4Cmds))
     {
          std::cerr << "Cannot process\n";
          return 2;
     }
     std::cout << IStrm4Cmds.str() << "\n";

     std::string libName, objectName;
     while (IStrm4Cmds >> libName >> objectName)
     {
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

          if (!interface->execActions(IStrm4Cmds, mobileObject, &scene))
          {
               std::cerr << "couldnt execute action"
                         << "\n";
          }
     }
     usleep(100000);

     std::cout << "Close\n"
               << std::endl; // To tylko, aby pokazac wysylana instrukcje
     Send(Socket4Sending, "Close\n");
     ClientSender.CancelCountinueLooping();
     Thread4Sending.join();
     close(Socket4Sending);

     return 0;
}
