/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "smShare.h"
#include "SuperStateDefs.h"
#include "evtService.h"

#include "FactoryTestRecordCUESS.h"
#include "FactoryTestRecordCUSA.h"
#include "SysInfo.h"

#include "cxStatus.h"

#define  _CXSUPERSTATEEVALUATORDA_CPP_
#include "cxSuperStateEvaluatorDA.h"

namespace CX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

SuperStateEvaluatorDA::SuperStateEvaluatorDA()
{
   reset();
}

void SuperStateEvaluatorDA::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Evaluate superstates. The superstates are obtained from shared memory.

void SuperStateEvaluatorDA::doEvaluate(bool aFirstFlag)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Do this first.

   // Store copies of the last and current superstate.
   if (aFirstFlag)
   {
      Prn::print(Prn::DA1, "DA  Eval         first **********************");
      // If this is the first update then set the last and the current to
      // the current from shared memory.
      mDAX = SM::gShare->mSuperStateDA;
      mLastDAX = mDAX;
   }
   else
   {
      // If this is not the first update then set the last to the previous
      // current and set the current from shared
      // memory.
      mLastDAX = mDAX;
      mDAX = SM::gShare->mSuperStateDA;
   }

   // Local variables.
   bool tCState = false;
   int tSeverity = 0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Evaluate measurement variables.

   // Evaluate the superstate. Send an event accordingly.
   if (Evt::EventRecord* tRecord = Evt::trySendEvent(
      Evt::cEvt_Ident_DA_Temperature,
      mDAX.mTemperature > cDA_Temperature_ThreshHi))
   {
      tRecord->setArg1("%.1f", mDAX.mTemperature);
      tRecord->sendToEventLogThread();
   }

   // Evaluate the superstate. Send an event accordingly.
   if (Evt::EventRecord* tRecord = Evt::trySendEvent(
      Evt::cEvt_Ident_DA_MainVoltage,
      mDAX.mMainInputVoltage < cDA_MainVoltage_ThreshLo))
   {
      tRecord->setArg1("%.2f", mDAX.mMainInputVoltage);
      tRecord->sendToEventLogThread();
   }

   if (gStatus.mTTARebootState == 0)
   {
      // Evaluate the superstate. Send an event accordingly.
      if (Evt::EventRecord* tRecord = Evt::trySendEvent(
         Evt::cEvt_Ident_DA_MainCurrent,
         mDAX.mMainInputCurrent < cDA_MainCurrent_ThreshLo))
      {
         tRecord->setArg1("%.0f", mDAX.mMainInputCurrent * 1000);
         tRecord->sendToEventLogThread();
      }

      // Evaluate the superstate. Send an event accordingly.
      if (Evt::EventRecord* tRecord = Evt::trySendEvent(
         Evt::cEvt_Ident_DA_TowerVoltage,
         mDAX.mTowerVoltage < cDA_TowerVoltage_ThreshLo))
      {
         tRecord->setArg1("%.2f", mDAX.mTowerVoltage);
         tRecord->sendToEventLogThread();
      }

      // Evaluate the superstate. Send an event accordingly.
      if (Evt::EventRecord* tRecord = Evt::trySendEvent(
         Evt::cEvt_Ident_DA_TowerCurrent,
         mDAX.mTowerCurrent < cDA_TowerCurrent_ThreshLo))
      {
         tRecord->setArg1("%.0f", mDAX.mTowerCurrent * 1000);
         tRecord->sendToEventLogThread();
      }
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Evaluate amp class variables.

   // Evaluate the superstate. Send an event accordingly.
   if (mDAX.mAmpClass != mLastDAX.mAmpClass)
   {
      Prn::print(Prn::TTA1, "DA  AmpBClass**************************** %s",
         get_AmpClass_asString(mDAX.mAmpClass));

      tCState = abs(mDAX.mAmpClass) > 0;
      tSeverity = 0;
      switch (abs(mDAX.mAmpClass))
      {
      case 0: tSeverity = Evt::cEvt_SeverityInfo; break;
      case 1: tSeverity = Evt::cEvt_SeveritySevere; break;
      case 2: tSeverity = Evt::cEvt_SeverityCritical; break;
      }
      // Create new event record, set args, and send it to the event thread.
      if (Evt::EventRecord* tRecord = Evt::trySendEvent(
         Evt::cEvt_Ident_DA_AmpCurrent,
         tCState,
         tSeverity))
      {
         tRecord->setArg1("%.1f", mDAX.mAmpRegCurrent);
         tRecord->setArg2("%s", get_AmpClass_asString(mDAX.mAmpClass));
         tRecord->sendToEventLogThread();
      }
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Evaluate mode variables.

   // Update the mode info.
   SM::gShare->doUpdateModeInfoDA();

   // Evaluate the superstate. Send an event accordingly.
   if (mDAX.mOpMode != mLastDAX.mOpMode)
   {
      Prn::print(Prn::DA1, "DA  OpMode******************************* %s",
         get_OpMode_asString(mDAX.mOpMode));

      // Create new event record, set args, and send it to the event thread.
      if (Evt::EventRecord* tRecord = Evt::trySendEvent(Evt::cEvt_Ident_DA_OpMode))
      {
         tRecord->setArg1("%s", get_OpMode_asString(mDAX.mOpMode));
         tRecord->sendToEventLogThread();
      }
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Evaluate path variables.

   // Evaluate the superstate. Send an event accordingly.
   if (mDAX.mRFPath != mLastDAX.mRFPath)
   {
      Prn::print(Prn::DA1, "DA  RF Path ***************************** %s",
         get_DA_RFPath_asString(mDAX.mRFPath));

      // Create new event record, set args, and send it to the event thread.
      if (Evt::EventRecord* tRecord = Evt::trySendEvent(Evt::cEvt_Ident_DA_RFPath))
      {
         tRecord->setArg1("%s", get_DA_RFPath_asString(mDAX.mRFPath));
         tRecord->sendToEventLogThread();
      }
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Evaluate user attenuator.

   // Evaluate the superstate. Send an event accordingly.
   if (mDAX.mUserAtten != mLastDAX.mUserAtten)
   {
      Prn::print(Prn::DA1, "DA  User Atten ************************** %.1f", mDAX.mUserAtten);
      // Create new event record, set args, and send it to the event thread.
      if (Evt::EventRecord* tRecord = Evt::trySendEvent(Evt::cEvt_Ident_DA_UserAtten))
      {
         tRecord->setArg1("%.1f", mDAX.mUserAtten);
         tRecord->sendToEventLogThread();
      }
   }
   
   // Update the gain calculator.
   if (mDAX.mUserAtten != mLastDAX.mUserAtten || aFirstFlag)
   {
      // Update the gain calculator.
      Prn::print(Prn::DA1, "DA  Update       gain calc user atten");
      Calc::GainCalc* tCalc = &SM::gShare->mGainCalc;
      tCalc->doReadModifyWriteBegin();
      tCalc->mAttenSetting = mDAX.mUserAtten;
      tCalc->doReadModifyWriteEnd();
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Evaluate system type.

   // Update the sysinfo and gain calc.
   if (aFirstFlag)
   {
      // Update the sysinfo.
      Prn::print(Prn::DA1, "DA  Update       sysinfo with system type %s",
         get_DA_SystemType_asString(mDAX.mSystemType));
      gSysInfo.doReadModifyWriteBegin();
      gSysInfo.mESSFlag = mDAX.mSystemType == 1;
      gSysInfo.doReadModifyWriteEnd();

      if (gSysInfo.mESSFlag)
      {
         // Update the cu factory test record.
         gFactoryTestRecordCUESS.doReadFromJsonFile();
         Prn::print(Prn::CProc1, "CU  Update       factory test record ess");

         // Update the gain calculator.
         Prn::print(Prn::CProc1, "CU  Update       gain calc with factory test record ess");
         Calc::GainCalc* tCalc = &SM::gShare->mGainCalc;
         tCalc->doReadModifyWriteBegin();
         tCalc->readFrom(&gFactoryTestRecordCUESS);
         tCalc->doReadModifyWriteEnd();
      }
      else
      {
         // Update the gain calculator json file.
         gFactoryTestRecordCUSA.doReadFromJsonFile();
         Prn::print(Prn::CProc1, "CU  Update       factory test record sa");

         // Update the gain calculator json file.
         Prn::print(Prn::CProc1, "CU  Update       gain calc with factory test record sa");
         Calc::GainCalc* tCalc = &SM::gShare->mGainCalc;
         tCalc->doReadModifyWriteBegin();
         tCalc->readFrom(&gFactoryTestRecordCUSA);
         tCalc->doReadModifyWriteEnd();
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
