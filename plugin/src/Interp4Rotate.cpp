#include <iostream>
#include "Interp4Rotate.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


/*!
 *
 */
Interp4Rotate::Interp4Rotate()
{}


/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _angularVelocity << " " << _angle << endl;
}


/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Rotate::ExecCmd( MobileObj *pMobObj, AccessControl *pAccessControl)
{
  int period = static_cast<int>(1000000.0 / std::abs(_angularVelocity));
  auto initialOrientation = pMobObj->GetAng_Yaw_deg();

  double delta = 0;
  if (_angularVelocity < 0)
  {
    _angle = -_angle;
    delta = -1;
  }
  else
  {
    delta = 1;
  }

  double destination = initialOrientation + _angle;

  while (true)
  {
    pAccessControl->LockAccess(); // Zamykamy dostęp do sceny, gdy wykonujemy
                                  // modyfikacje na obiekcie.
    auto currentOrientation = pMobObj->GetAng_Yaw_deg();
    auto currentPosition = pMobObj->GetPositoin_m();
    std::stringstream cmd;
    //TO DO -  cmd umiescic w obekcie mobilnym a potem to brać w senderze
    cmd << "Cube  "
    << pMobObj->Get_X_Size() << " "
    << pMobObj->Get_Y_Size() << " "
    << pMobObj->Get_Z_Size() << " "
    << currentPosition[0] << " " 
    << currentPosition[1] << " "
    << currentPosition[2] << " "
    << pMobObj->GetAng_Roll_deg() << " "
    << pMobObj->GetAng_Pitch_deg() << " "
    << pMobObj->GetAng_Yaw_deg() + delta << " "
    << pMobObj->Get_Red_Value() << " "
    << pMobObj->Get_Blue_Value() << " "
    << pMobObj->Get_Green_Value() << "\n";
    
    double partialDestination = currentOrientation + delta;

    if (compareDouble(partialDestination, destination))
    {
      pAccessControl->UnlockAccess();
      break;
    }
    pMobObj->SetAng_Yaw_deg(partialDestination);
    pMobObj->movingState = cmd.str();
    pAccessControl->MarkChange();
    pAccessControl->UnlockAccess();
    usleep(period);
  }
  return true;
}


/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _angularVelocity >> _angle;
  return !Strm_CmdsList.fail();
}


/*!
 *
 */
Interp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NazwaObiektu  predkoscKatowa katObrotu" << endl;
}
