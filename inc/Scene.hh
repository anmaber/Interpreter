#pragma once

#include "MobileObj.hh"
#include "AccessControl.hh"
#include <map>
#include <memory>
#include <sstream>

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

class Scene : public AccessControl
{
private:
    /*!
 * \brief zbiór obiektów mobilnych dla których kluczami są ich nazwy.
 */
   

public:
    std::map<std::string, std::shared_ptr<MobileObj>> mobileObjects;
    /*!
 * \brief metoda umożliwiająca znalezienie danego obiektu mobilnego.
 * \param[in] objectName -- nazwa obiektu.
 * \retval std::shared_ptr<MobileObj> -- wskaźnik na znaleziony obiekt 
 * \retval nullptr -- jeżeli obiekt nie zostanie znaleziony
 */
    std::shared_ptr<MobileObj> findMobileObject(const std::string &objectName);
    /*!
 * \brief metoda umożliwiająca dodanie nowego obiektu mobilnego.
 * \param[in] objectName - nazwa obiektu
 * \param[in] size - rozmiar obiektu
 * \param[in] rgb - kolor obiektu
 */
    void addMobileObject(const std::string &objectName, std::string size, std::string rgb);
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

void Scene::addMobileObject(const std::string &objectName, std::string size, std::string rgb)
{
    if (!findMobileObject(objectName))
    {
        std::istringstream sizeStream(size);
        double x,y,z;
        sizeStream >> x >> y >> z;

        std::istringstream colorStream(rgb);
        int r,g,b;
        colorStream >> r >> g >> b;

        auto mobileObject = std::make_shared<MobileObj>();
        mobileObject->SetName(objectName);

        mobileObject->Set_X_Size(x);
        mobileObject->Set_Y_Size(y);
        mobileObject->Set_Z_Size(z);

        mobileObject->Set_Red_Value(r);
        mobileObject->Set_Green_Value(g);
        mobileObject->Set_Blue_Value(b);

        mobileObjects.insert({objectName, mobileObject});
    }
}