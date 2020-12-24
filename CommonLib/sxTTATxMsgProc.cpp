/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "sxMsgDefs.h"

#include "sxTTATxMsgProc.h"

namespace SX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

TTATxMsgProc::TTATxMsgProc()
{
   mTxBuffer[0] = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Fill the transmit buffer with the full string for the given message
// ident. This can then be transmitted. Return a pointer to the buffer.

const char* TTATxMsgProc::getMsg(int aMsgId, const char* aPayload)
{
   strcpy(mTxBuffer, ";01");
   strncat(mTxBuffer, get_MsgId_asString(aMsgId), cMaxStringSize - 1);

   if (aPayload)
   {
      strncat(mTxBuffer, aPayload, cMaxStringSize - 1);
   }

   return mTxBuffer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace