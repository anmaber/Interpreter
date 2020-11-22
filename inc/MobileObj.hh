#pragma once

#include <string>
#include "Vector3D.hh"
#include <vector>
#include <string>


/*!
 * \file
 * \brief Zawiera definicję klasy MobileObj
 *
 * Plik zawiera definicję klasy MobileObj.
 * Definicja to może być rozszerzona i zmienione mogą
 * być nazwy pól. Obowiązkowe są jedynie nazwy metod.
 */




   /*!
    * \brief Klasa modelująca obiekt mobilny.
    * 
    */
    class MobileObj {

        double _X_Size = 0;

        double _Y_Size = 0;

        double _Z_Size = 0;

        int _Red_Value = 0;
        int _Green_Value = 0;
        int _Blue_Value = 0;

       /*!
        * \brief Kąt \e yaw reprezentuje rotację zgodnie z ruchem wskazówek zegara
        *        wokół osi \e OZ.
	*
	* Kąt \e yaw reprezentuje rotację zgodnie z ruchem wskazówek zegara
        * wokół osi \e OZ. Wartość kąta wyrażona jest w stopniach.
        */
       double _Ang_Yaw_deg = 0;

       /*!
        * \brief Kąt \e pitch reprezentuje rotację zgodnie z ruchem wskazówek zegara
        *        wokół osi \e OY.
	*
	* Kąt \e pitch reprezentuje rotację zgodnie z ruchem wskazówek zegara
        * wokół osi \e OY. Wartość kąta wyrażona jest w stopniach.
        */
       double _Ang_Pitch_deg = 0;

       /*!
        * \brief Kąt \e roll reprezentuje rotację zgodnie z ruchem wskazówek zegara
        *        wokół osi \e OX.
	*
	* Kąt \e roll reprezentuje rotację zgodnie z ruchem wskazówek zegara
        * wokół osi \e OX. Wartość kąta wyrażona jest w stopniach.
        */
       double _Ang_Roll_deg = 0;

       /*!
        * \brief Współrzędne aktualnej pozycji obiektu.
	*
	* Współrzędne aktualnej pozycji obiektu. Przyjmuje się,
	* że współrzędne wyrażone są w metrach.
        */
       Vector3D  _Position_m;

       /*!
        * \brief Nazwa obiektu, która go indentyfikuje.
        *
        * Nazwa obiektu, która go indentyfikuje. Z tego względu musi
        * musi to być nazwa unikalna wśród wszystkich obiektów na scenie.
        */
       std::string  _Name;

     public:
        double Get_X_Size() const {return _X_Size;}
        double Get_Y_Size() const {return _Y_Size;}
        double Get_Z_Size() const {return _Z_Size;}

        void Set_X_Size(double X_Size) { _X_Size = X_Size;}
        void Set_Y_Size(double Y_Size) { _Y_Size = Y_Size;}
        void Set_Z_Size(double Z_Size) { _Z_Size = Z_Size;}

        int Get_Red_Value() const {return _Red_Value;}
        int Get_Green_Value() const {return _Green_Value;}
        int Get_Blue_Value() const {return _Blue_Value;}
        
        void Set_Red_Value(int Red_Value) {_Red_Value = Red_Value;}
        void Set_Green_Value(int Green_Value) {_Green_Value = Green_Value;}
        void Set_Blue_Value(int Blue_Value) {_Blue_Value = Blue_Value;}

      /*!
       * \brief Udostępia wartość kąta \e roll.
       *
       * Udostępia wartość kąta \e roll. Jest ona wyrażona w stopniach.
       */
       double GetAng_Roll_deg() const { return _Ang_Roll_deg; }
      /*!
       * \brief Udostępia wartość kąta \e pitch.
       *
       * Udostępia wartość kąta \e pitch. Jest ona wyrażona w stopniach.
       */
       double GetAng_Pitch_deg() const { return _Ang_Pitch_deg; }
       /*!
       * \brief Udostępia wartość kąta \e yaw.
       *
       * Udostępia wartość kąta \e yaw. Jest ona wyrażona w stopniach.
       */
       double GetAng_Yaw_deg() const { return _Ang_Yaw_deg; }

      /*!
       * \brief Zmienia wartość kąta \e roll.
       *
       * Zmienia wartość kąta \e roll.
       * \param[in] Ang_Roll_deg - nowa wartość kąta \e roll wyrażona w stopniach.
       */
       void SetAng_Roll_deg(double Ang_Roll_deg) { _Ang_Roll_deg = Ang_Roll_deg; }
      /*!
       * \brief Zmienia wartość kąta \e pitch.
       *
       * Zmienia wartość kąta \e pitch.
       * \param[in] Ang_Pitch_deg - nowa wartość kąta \e pitch wyrażona w stopniach.
       */
       void SetAng_Pitch_deg(double Ang_Pitch_deg) { _Ang_Pitch_deg = Ang_Pitch_deg; }
      /*!
       * \brief Zmienia wartość kąta \e yaw.
       *
       * Zmienia wartość kąta \e yaw.
       * \param[in] Ang_Yaw_deg - nowa wartość kąta \e yaw wyrażona w stopniach.
       */
       void SetAng_Yaw_deg(double Ang_Yaw_deg) { _Ang_Yaw_deg = Ang_Yaw_deg; }

      /*!
       * \brief Udostępnia współrzędne położenia obiektu w trybie tylko do odczytu.
       *
       * Udostępnia współrzędne punktu, który definiuje położenia obiektu
       * w trybie tylko do odczytu.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       */
       const Vector3D & GetPositoin_m() const { return _Position_m; }
      /*!
       * \brief Udostępnia współrzędne położenia obiektu w trybie modyfikacji.
       *
       * Udostępnia współrzędne punktu, który definiuje położenia obiektu
       * w trybie modyfikacji.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       */
       Vector3D & UsePosition_m() { return _Position_m; }
      /*!
       * \brief Zmienia współrzędne położenia obiektu.
       *
       * Zmienia współrzędne punktu, który definiuje położenia obiektu.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       * \param[in] rPos_m - współrzędne nowgo położenia. Przyjmuje się,
       *                     że są one wyrażone w metrach.
       */
       void SetPosition_m(const Vector3D &rPos_m) { _Position_m = rPos_m; }


      /*!
       * \brief Zmienia nazwę obiektu.
       *
       *  Zmienia nazwę obiektu.
       *  \param[in] sName - nowa nazwa obiektu.
       */
       void SetName(const std::string& sName) { _Name = sName; }
       /*!
        * \brief Udostępnia nazwę obiektu.
	*
	* Udostępnia nazwę obiektu w trybie tylko do odczytu.
        */
       const std::string & GetName() const { return _Name; }

       std::string movingState {"Cube  0 0 0  0 0 0  0 0 0  0 0 0\n"};
    };
