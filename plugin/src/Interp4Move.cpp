#include <iostream>
#include "Interp4Move.hh"
#include "MobileObj.hh"
#include <sstream>

using std::cout;
using std::endl;

extern "C"
{
  Interp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Move"; }
}

/*!
 * \brief
 *
 *
 */
Interp4Command *CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}

/*!
 *
 */
Interp4Move::Interp4Move() : _Speed_mmS(0),
                             _PathLength_m(0)
{
}

/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Speed_mmS << " " << _PathLength_m << endl;
}

/*!
 *
 */
const char *Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Move::ExecCmd(MobileObj *pMobObj, AccessControl *pAccessControl)
{
  int period = static_cast<int>(1000000.0 / std::abs(_Speed_mmS));
  auto initialPosition = pMobObj->GetPositoin_m();

  double delta = 0;
  if (_Speed_mmS < 0)
  {
    _PathLength_m = -_PathLength_m;
    delta = -0.01;
  }
  else
  {
    delta = 0.01;
  }

  double destination = initialPosition[0] + _PathLength_m;

  while (true)
  {
    pAccessControl->LockAccess(); // Zamykamy dostęp do sceny, gdy wykonujemy
                                  // modyfikacje na obiekcie.
    auto currentPosition = pMobObj->GetPositoin_m();
    std::stringstream cmd;
    //TO DO -  cmd umiescic w obekcie mobilnym a potem to brać w senderze
    cmd << "Cube  "
    << pMobObj->Get_X_Size() << " "
    << pMobObj->Get_Y_Size() << " "
    << pMobObj->Get_Z_Size() << " "
    << currentPosition[0] + delta << " " 
    << currentPosition[1] << " "
    << currentPosition[2] << " "
    << pMobObj->GetAng_Roll_deg() << " "
    << pMobObj->GetAng_Pitch_deg() << " "
    << pMobObj->GetAng_Yaw_deg() << " "
    << pMobObj->Get_Red_Value() << " "
    << pMobObj->Get_Blue_Value() << " "
    << pMobObj->Get_Green_Value() << "\n";
    Vector3D partialDestination;
    partialDestination[0] = currentPosition[0] + delta;
    partialDestination[1] = currentPosition[1];
    partialDestination[2] = currentPosition[2];
    if (compareDouble(partialDestination[0], destination))
    {
      pAccessControl->UnlockAccess();
      break;
    }
    pMobObj->SetPosition_m(partialDestination);
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
bool Interp4Move::ReadParams(std::istream &Strm_CmdsList)
{
  Strm_CmdsList >> _Speed_mmS >> _PathLength_m;
  return !Strm_CmdsList.fail();
}

/*!
 *
 */
Interp4Command *Interp4Move::CreateCmd()
{
  return new Interp4Move();
}

/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
