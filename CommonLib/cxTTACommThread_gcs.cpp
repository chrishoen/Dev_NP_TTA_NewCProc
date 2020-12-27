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
// Send a request message to the slave, wait for the response message and
// process it. Return true if successful. This is called by the process
// loop qcall function, based on the state.

bool TTACommThread::doProcess_gcs()
{
   mLoopExitCode = cLoopExitNormal;

   try
   {
      // Test for a notification exception.
      mNotify.testException();

      // Set the thread notification mask.
      mNotify.setMaskOne("CmdAck", cRxMsgNotifyCode);

      // Encode a request message.
      mTxMsgEncoder.encodeMsg(SX::cMsgId_gcs);

      // Transmit the request message.
      sendString(mTxMsgEncoder.mTxBuffer);

      // Wait for the acknowledgement notification.
      mNotify.wait(cRxMsgTimeout);
   }
   catch(int aException)
   {
      mLoopExitCode = cLoopExitAborted;
      Prn::print(0, "EXCEPTION TTACommThread::doProcess_gcs %d %s", aException, mNotify.mException);
   }

   // Done.
   return mLoopExitCode == cLoopExitNormal;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace