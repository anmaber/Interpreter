#include <iostream>
#include "Interp4Pause.hh"
#include "MobileObj.hh"

extern "C"
{
  Interp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Pause"; }
}

/*!
 * \brief
 *
 *
 */
Interp4Command *CreateCmd(void)
{
  return Interp4Pause::CreateCmd();
}

/*!
 *
 */
Interp4Pause::Interp4Pause()
{
}

/*!
 *
 */
void Interp4Pause::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  std::cout << GetCmdName() << " " << _PauseTime_ms << std::endl;
}

/*!
 *
 */
const char *Interp4Pause::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Pause::ExecCmd(MobileObj *pMobObj, AccessControl *pAccessControl)
{
  pAccessControl->LockAccess(); // Zamykamy dostęp do sceny, gdy wykonujemy
                                // modyfikacje na obiekcie.
  usleep(_PauseTime_ms * 1000);
  pAccessControl->UnlockAccess();

  return true;
}

/*!
 *
 */
bool Interp4Pause::ReadParams(std::istream &Strm_CmdsList)
{
  Strm_CmdsList >> _PauseTime_ms;
  if(_PauseTime_ms < 0)
  {
    std::cerr << "time cannot be less than 0 \n";
    return false;
  }
  return !Strm_CmdsList.fail();
}

/*!
 *
 */
Interp4Command *Interp4Pause::CreateCmd()
{
  return new Interp4Pause();
}

/*!
 *
 */
void Interp4Pause::PrintSyntax() const
{
  std::cout << "   Pause  NazwaObiektu  czasPauzy[ms]" << std::endl;
}
