/*==============================================================================
Detestion:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "cmnPriorities.h"
#include "cxCProcParms.h"
#include "cxStatus.h"
#include "sxMsgDefs.h"

#include "cxTTACommThread.h"

namespace CX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute thread specific code at the beginning of seq1.

void TTACommThread::doSeq1Init()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute thread specific code at the beginning of seq1.

void TTACommThread::doSeq1Exit()
{
   // Test for an abort.
   if (mSeqExitCode == cSeqExitAborted)
   {
      // Advance the tta reboot state.
      if (gStatus.mTTARebootState == 1)
      {
         Prn::print(Prn::TTA1, "TTA tta reboot state************************** 2");
         gStatus.mTTARebootState = 2;
      }
   }
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace