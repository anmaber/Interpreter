#pragma once

#include "MobileObj.hh"
#include "AccessControl.hh"
#include "Configuration.hh"
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
    /*!
 * \brief metoda umożliwiająca skonfigurowanie sceny.
 * \param[in] config - konfiguracja
 */
    bool configure(Configuration& config);

    /*!
 * \brief metoda umożliwiająca dodanie nowego obiektu mobilnego.
 * \param[in] objectName - nazwa obiektu
 * \param[in] size - rozmiar obiektu
 * \param[in] rgb - kolor obiektu
 */
    bool addMobileObject(const std::string &objectName, std::string size, std::string rgb);

    std::map<std::string, std::shared_ptr<MobileObj>> mobileObjects;
    /*!
 * \brief metoda umożliwiająca znalezienie danego obiektu mobilnego.
 * \param[in] objectName -- nazwa obiektu.
 * \retval std::shared_ptr<MobileObj> -- wskaźnik na znaleziony obiekt 
 * \retval nullptr -- jeżeli obiekt nie zostanie znaleziony
 */
    std::shared_ptr<MobileObj> findMobileObject(const std::string &objectName);

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

bool Scene::addMobileObject(const std::string &objectName, std::string size, std::string rgb)
{
    if (!findMobileObject(objectName))
    {
        std::istringstream sizeStream(size);
        double x,y,z;
        if(!(sizeStream >> x >> y >> z) || x < 0 || y<0 || z<0)
        {
            std::cerr << "wrong size in mobile object configuration \n";
            return false;
        }

        std::istringstream colorStream(rgb);
        int r,g,b;
        if(!(colorStream >> r >> g >> b))
        {
            std::cerr << "wrong color in mobile object configuration \n";
            return false;
        }

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
    return true;
}

bool Scene::configure(Configuration& config)
{
    bool result = false;
    for(auto& [name, size, color]: config.sceneConfiguration)
    {
        result = addMobileObject(name, size, color);
    }
    return result;
}