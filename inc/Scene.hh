#pragma once

#include "MobileObj.hh"
#include <map>
#include <memory>

/*!
 * \file
 * \brief Definicja klasy Scene
 *
 * Plik zawiera definicję Scene.
 */

/*!
 * \brief Modeluje zbiór typu klucz - wartość dla obiektów mobilnych.
 *
 *  Klasa modeluje zbiór obiektów mobilnych wtyczek dla których kluczami są ich nazwy.
 */

class Scene
{
private:
    /*!
 * \brief zbiór obiektów mobilnych dla których kluczami są ich nazwy.
 */
    std::map<std::string, std::shared_ptr<MobileObj>> mobileObjects;

public:
    /*!
 * \brief metoda umożliwiająca znalezienie danego obiektu mobilnego.
 * \param[in] objectName -- nazwa obiektu.
 * \retval std::shared_ptr<MobileObj> -- wskaźnik na znaleziony obiekt 
 * \retval nullptr -- jeżeli obiekt nie zostanie znaleziony
 */
    std::shared_ptr<MobileObj> findMobileObject(const std::string &objectName);
    /*!
 * \brief metoda umożliwiająca dodanie nowego obiektu mobilnego.
 * \param[in] objectName - nazwa obiektu.
 */
    void addMobileObject(const std::string &objectName);
    Scene() = default;
    ~Scene() = default;
};

std::shared_ptr<MobileObj> Scene::findMobileObject(const std::string &objectName)
{
    auto iter = mobileObjects.find(objectName);
    if (iter != mobileObjects.end())
    {
        return iter->second;
    }
    return nullptr;
}

void Scene::addMobileObject(const std::string &objectName)
{
    if (!findMobileObject(objectName))
    {
        auto mobileObject = std::make_shared<MobileObj>();
        mobileObject->SetName(objectName);
        mobileObjects.insert({objectName, mobileObject});
    }
}