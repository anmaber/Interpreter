#pragma once

#include <string>
#include "Interp4Command.hh"
#include <dlfcn.h>

class LibInterface
{
private:
    std::string _CmdName;
    void *_pLibHnd;
    Interp4Command *(*pCreateCmd)(void);
public:
    LibInterface();
    bool execActions(std::istream &rIstrm, std::shared_ptr<MobileObj>& mobileObject);
    bool initInterface(const std::string& CmdName);
    ~LibInterface();
};

LibInterface::LibInterface()
{}

bool LibInterface::initInterface(const std::string& CmdName)
{
    std::string libName("libInterp4");
    libName.append(CmdName);
    libName.append(".so");
    _pLibHnd = dlopen(libName.c_str(),RTLD_LAZY); 
    if(!_pLibHnd)
    {
        return false;
    }
    void *pFun;
    pFun = dlsym(_pLibHnd,"CreateCmd");

    if(!pFun)
    {
        return false;
    }
    pCreateCmd = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);

    return true;
}

bool LibInterface::execActions(std::istream &rIstrm, std::shared_ptr<MobileObj>& mobileObject)
{
    Interp4Command *pCmd = pCreateCmd();
    std::cout << "Polecenie: " << std::endl;
    std::cout << std::endl;
    pCmd->PrintSyntax();
  
    if(!pCmd->ReadParams(rIstrm))
    {
        return false;
    }

    std::cout << "Wykonanie dla obiektu: " << mobileObject->GetName() << std::endl;
    std::cout << std::endl;
    pCmd->PrintCmd();
    std::cout << std::endl;
    delete pCmd;
    return true;
}

LibInterface::~LibInterface()
{
    if(_pLibHnd)
    {
        dlclose(_pLibHnd);
    }
}
