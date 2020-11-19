#pragma once

#include <map>
#include <string>
#include <memory>
#include "LibInterface.hh"

/*!
 * \file
 * \brief Definicja klasy Set4LibInterfaces
 *
 * Plik zawiera definicję Set4LibInterfaces.
 */

/*!
 * \brief Modeluje zbiór typu klucz -- wartość dla interfejsów wtyczek.
 *
 *  Klasa modeluje zbiór interfejsów wtyczek dla których kluczami są ich nazwy.
 */

class Set4LibInterfaces
{
private:
    /*!
 * \brief zbiór interfejsów wtyczek dla których kluczami są ich nazwy.
 */
    std::map<std::string, std::shared_ptr<LibInterface>> set4LibInterfaces;

public:
    Set4LibInterfaces() = default;
    /*!
 * \brief metoda umożliwiająca znalezienie danego interfejsu.
 * \param[in] libName -- nazwa wtyczki
 * \retval std::shared_ptr<LibInterface> -- wskaźnik na znaleziony interfejs wtyczki
 * \retval nullptr -- jeżeli nie zostanie znaleziony interfejs
 */
    std::shared_ptr<LibInterface> findInterface(const std::string &libName);
    /*!
 * \brief metoda umożliwiająca dodanie nowego interfejsu
 * \param[in] libName - nazwa wtyczki
 * \retval true -- jeżeli dodanie interfejsu się powiedzie
 * \retval false -- jeżeli dodanie interfejsu się nie powiedzie
 */
    bool addInterface(const std::string &libname);
    ~Set4LibInterfaces() = default;
};

std::shared_ptr<LibInterface> Set4LibInterfaces::findInterface(const std::string &cmdName)
{
    std::string libName("libInterp4");
    libName.append(cmdName);
    libName.append(".so");
    auto iter = set4LibInterfaces.find(libName);
    if (iter != set4LibInterfaces.end())
    {
        return iter->second;
    }

    return nullptr;
}

bool Set4LibInterfaces::addInterface(const std::string &libname)
{
    auto libInterface = std::make_shared<LibInterface>();
    if (!libInterface->initInterface(libname))
    {
        return false;
    }
    set4LibInterfaces.insert({libname, libInterface});
    return true;
}
