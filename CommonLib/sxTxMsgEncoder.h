#pragma once

/*==============================================================================
Provides a class for an atmel transmit messages encoder.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a class that provides a function that encodes a transmit message
// into a member transmit buffer. It is intended that this is used by the 
// the comm thread to encode messages. It is not thread safe.

class TxMsgEncoder
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   static const int cMaxStringSize = 2000;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Full message string to be transmitted.
   char mTxBuffer[cMaxStringSize];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   TxMsgEncoder();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Encode a transmit message string. Fill the transmit buffer with the
   // full string for the given message ident. The string content consists
   // of header, payload, and crc footer. This can then be transmitted. This
   // does not append a crlf at the end of the string, the serial thread does
   // that. Return a pointer to the buffer.
   const char* encodeMsg(int aMsgId, const char* aPayload = 0);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


