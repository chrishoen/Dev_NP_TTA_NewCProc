#include "stdafx.h"

#include "sxMsgDefs.h"

#include "cxCProcParms.h"
#include "cxTTACommThread.h"
#include "cxDACommThread.h"
#include "cxOverrides.h"
#include "cmnPriorities.h"
#include "evtAlarmFileReader.h"

#include "CmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

CmdLineExec::CmdLineExec()
{
}

void CmdLineExec::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class is the program command line executive. It processes user
// command line inputs and executes them. It inherits from the command line
// command executive base class, which provides an interface for executing
// command line commands. It provides an override execute function that is
// called by a console executive when it receives a console command line input.
// The execute function then executes the command.

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("RESET"))    reset();
   if (aCmd->isCmd("LOOP"))     executeLoopState(aCmd);
   if (aCmd->isCmd("OVER"))     executeOverrides(aCmd);

   if (aCmd->isCmd("GO1"))      executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))      executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))      executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))      executeGo4(aCmd);
   if (aCmd->isCmd("GO5"))      executeGo5(aCmd);

   if (aCmd->isCmd("READ1"))    executeRead1(aCmd);
   if (aCmd->isCmd("READ2"))    executeRead2(aCmd);
   if (aCmd->isCmd("SHOW"))     executeShow(aCmd);
   if (aCmd->isCmd("PARMS"))    executeParms(aCmd);
   if (aCmd->isCmd("HELP"))     executeHelp(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRead1(Ris::CmdLineCmd* aCmd)
{
   Evt::AlarmFileReader tReader;
   std::vector<Evt::AlarmRecord> tVector;
   tReader.doReadFromAlarmFile(tVector);

   for (auto& tElement : tVector)
   {
      tElement.show(0);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRead2(Ris::CmdLineCmd* aCmd)
{
   Evt::AlarmFileReader tReader;
   std::vector<Evt::AlarmRecord> tVector;
   tReader.doReadFromAlarmFile(tVector);

   int tLoopSize = my_imin(4, tVector.size());
   for (int i = 0; i < tLoopSize; i++)
   {
      Evt::AlarmRecord& tRecord = tVector[i];
      tRecord.show(0);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeLoopState(Ris::CmdLineCmd* aCmd)
{
   CX::gDACommThread->mLoopState = SX::get_MsgId_asInt(aCmd->argString(1));
   Prn::print(0, "%s", SX::get_MsgId_asString(CX::gDACommThread->mLoopState));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeOverrides(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->numArg() == 0)
   {
      Prn::print(0, "");
      Prn::print(0, " over int float");
      Prn::print(0, "");
      Prn::print(0, " 1 mTTATemperature        float");
      Prn::print(0, " 2 mTTAMainVoltage        float");
      Prn::print(0, " 3 mTTAMainCurrent        float");
      Prn::print(0, " 4 mDATemperature         float");
      Prn::print(0, " 5 mDAMainInputVoltage    float");
      Prn::print(0, " 6 mDAMainInputCurrent    float");
      Prn::print(0, " 7 mDATowerVoltage        float");
      Prn::print(0, " 8 mDATowerCurrent        float");
      Prn::print(0, "");
      Prn::print(0, " over reset");
      Prn::print(0, " over show");
      Prn::print(0, "");
      return;
   }

   if (aCmd->isArgString(1,"reset"))
   {
      CX::gOverrides.reset();
      Prn::print(0, "reset");
      return;
   }

   if (aCmd->isArgString(1, "show"))
   {
      CX::gOverrides.show();
      return;
   }

   switch (aCmd->argInt(1))
   {
   case 1: CX::gOverrides.mTTATemperature = aCmd->argFloat(2); break;
   case 2: CX::gOverrides.mTTAMainVoltage = aCmd->argFloat(2); break;
   case 3: CX::gOverrides.mTTAMainCurrent = aCmd->argFloat(2); break;
   case 4: CX::gOverrides.mDATemperature = aCmd->argFloat(2); break;
   case 5: CX::gOverrides.mDAMainInputVoltage = aCmd->argFloat(2); break;
   case 6: CX::gOverrides.mDAMainInputCurrent = aCmd->argFloat(2); break;
   case 7: CX::gOverrides.mDATowerVoltage = aCmd->argFloat(2); break;
   case 8: CX::gOverrides.mDATowerCurrent = aCmd->argFloat(2); break;
   }

   CX::gOverrides.show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShow(Ris::CmdLineCmd* aCmd)
{
   CX::gCProcParms.show();
}
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeParms(Ris::CmdLineCmd* aCmd)
{
   CX::gCProcParms.reset();
   CX::gCProcParms.readSection("default");
   CX::gCProcParms.show();
}
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeHelp(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "help ***********************************");
   Prn::print(0, "");
   Prn::print(0, "show                     -- show some stuff");
   Prn::print(0, "parms                    -- show cproc parms");
   Prn::print(0, "over                     -- show overrides help");
}

