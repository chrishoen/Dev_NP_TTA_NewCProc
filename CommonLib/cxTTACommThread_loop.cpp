/*==============================================================================
Detestion:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "smShare.h"
#include "sxMsgDefs.h"

#include "cxCProcParms.h"

#include "cxTTACommThread.h"

namespace CX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Process loop qcall function. Execute an infinite loop that sends a request
// to the slave, waits for the response, and processes it. It calls one
// of the process subroutines, based on the state. It executes in the
// context of the long thread. The purpose of this is to provide long
// thread execution context for message processing. It is only executed
// once, at thhread initialization.

void TTACommThread::executeProcessLoop()
{
   Prn::print(0, "TTACommThread::executeProcessLoop BEGIN");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Do this first.

   // Initialize the synchronization objects.
   mLoopWaitable.initialize(cSlowLoopPeriod);
   mNotify.clearFlags();

   try
   {
      // Loop to transmit and receive.
      while (true)
      {
         //*********************************************************************
         //*********************************************************************
         //*********************************************************************
         // Wait.

         // Wait for timer or abort.
         mLoopWaitable.waitForTimerOrSemaphore();
         if (mLoopWaitable.wasSemaphore())
         {
            // The waitable semahore was posted for an abort.
            throw 668;
         }

         // Guard.
         if (!mConnectionFlag) continue;

         //*********************************************************************
         //*********************************************************************
         //*********************************************************************
         // Send a request to the slave, wait for the response and process it.

         if (mLoopState == SX::cMsgId_gcs)
         {
            doProcess_gcs();
         }
         else if (mLoopState == SX::cMsgId_gsx)
         {
            doProcess_gsx();
         }

      }
   }
   catch (int aException)
   {
      if (aException == 668)
      {
         Prn::print(0, "EXCEPTION TTACommThread::executeProcessLoop %d %s", aException, mNotify.mException);
      }
   }

   // Finalize the synchronization objects.
   mLoopWaitable.finalize();
   mNotify.clearFlags();

   Prn::print(0, "CommSeqThread::doProcessAcquire END");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace