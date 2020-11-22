#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}


/*!
 *
 */
Interp4Set::Interp4Set()
{}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _X_Coordinate << " " <<  _Y_Coordinate << " " << _OZ_Angle << endl;
}


/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Set::ExecCmd( MobileObj *pMobObj, AccessControl *pAccessControl)
{
    pAccessControl->LockAccess(); // Zamykamy dostęp do sceny, gdy wykonujemy
                                  // modyfikacje na obiekcie.
    std::stringstream cmd;

    auto endPosition = pMobObj->GetPositoin_m();
    endPosition[0] = _X_Coordinate;
    endPosition[1] = _Y_Coordinate;
    pMobObj->SetAng_Yaw_deg(_OZ_Angle);

    //TO DO -  cmd umiescic w obekcie mobilnym a potem to brać w senderze
    cmd << "Cube  "
    << pMobObj->Get_X_Size() << " "
    << pMobObj->Get_Y_Size() << " "
    << pMobObj->Get_Z_Size() << " "
    << endPosition[0] << " " 
    << endPosition[1] << " "
    << endPosition[2] << " "
    << pMobObj->GetAng_Roll_deg() << " "
    << pMobObj->GetAng_Pitch_deg() << " "
    << pMobObj->GetAng_Yaw_deg() << " "
    << pMobObj->Get_Red_Value() << " "
    << pMobObj->Get_Blue_Value() << " "
    << pMobObj->Get_Green_Value() << "\n";
    
    pMobObj->movingState = cmd.str();
    pAccessControl->MarkChange();
    pAccessControl->UnlockAccess();
    usleep(300);
    return true;
}


/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _X_Coordinate >> _Y_Coordinate >> _OZ_Angle;
  return !Strm_CmdsList.fail();
}


/*!
 *
 */
Interp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  WspolrzednaX  WspolrzednaY KatOZ" << endl;
}
