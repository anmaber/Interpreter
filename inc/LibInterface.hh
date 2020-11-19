#pragma once

#include <string>
#include "Interp4Command.hh"
#include <dlfcn.h>

/*!
 * \file
 * \brief Definicja klasy LibInterface
 *
 * Plik zawiera definicję klasy LibInterface.
 */

/*!
 * \brief Modeluje klasę dającą interfejs do użytku wtyczek.
 *
 *  Klasa modeluje interfejs do użytku wtyczek. Umożliwia dostęp do wtyczki oraz wykonywanie akcji na obiekcie mobilnym.
 */

class LibInterface
{
private:
    /*!
 * \brief Nazwa wtyczki - wykonywana komenda.
 */
    std::string _CmdName;
    /*!
 * \brief Uchwyt do biblioteki.
 */
    void *_pLibHnd;
    /*!
 * \brief 
 */
    Interp4Command *(*pCreateCmd)(void);

public:
    LibInterface() = default;
    /*!
 * \brief Metoda umożliwiająca wykonanie poleceń
 * \param[in] - referencja do strumienia zawierającego polecenia
 * \param[in] -- referencja do wskaźnika na obiekt, na którym mają zostać wykonane polecenia
 * \retval true -- jeżeli wykonywane operacje się powiodą
 * \retval false -- jeżeli wykonywane operacje się nie powiodą
 * 
 * Wyświetla składnię polecenia, następnie wczytywane są parametry ze strumienia. W razie niepowodzenia zwracane jest false.
 * W razie powodzenia wyświetlane jest dla jakiego obiektu mają być wykonane polecenia oraz zadane polecenie, następnie zwracane jest true.
 */
    bool execActions(std::istream &rIstrm, std::shared_ptr<MobileObj> &mobileObject);
    /*!
 * \brief Metoda inicjalizująca wtyczkę.
 * \param[in] -- nazwa wtyczki
 * \retval true -- jeżeli wczytanie wtyczki się powiedzie
 * \retval false -- jeżeli wczytanie wtyczki się nie powiedzie
 *
 * Metoda otwiera daną bibliotekę dzieloną i inicjalizuje wtyczkę. W razie niepowodzenia zwraca false.
 */
    bool initInterface(const std::string &CmdName);
    /*!
    * \brief Destruktor zwalniający pamięć po uchwycie do biblioteki.
    *
    *  
    */
    ~LibInterface();
};

bool LibInterface::initInterface(const std::string &CmdName)
{
    _pLibHnd = dlopen(CmdName.c_str(), RTLD_LAZY);
    if (!_pLibHnd)
    {
        return false;
    }
    void *pFun;
    pFun = dlsym(_pLibHnd, "CreateCmd");

    if (!pFun)
    {
        return false;
    }
    pCreateCmd = *reinterpret_cast<Interp4Command *(**)(void)>(&pFun);

    return true;
}

bool LibInterface::execActions(std::istream &rIstrm, std::shared_ptr<MobileObj> &mobileObject)
{
    Interp4Command *pCmd = pCreateCmd();
    std::cout << "Polecenie: " << std::endl;
    std::cout << std::endl;
    pCmd->PrintSyntax();

    if (!pCmd->ReadParams(rIstrm))
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
    if (_pLibHnd)
    {
        dlclose(_pLibHnd);
    }
}
