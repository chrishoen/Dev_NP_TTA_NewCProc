//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "sxMsgDefs.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get a message ident as a string.

char* get_MsgId_asString(int aMsgId)
{
   switch (aMsgId)
   {
      case cMsgId_tst: return "tst";
      case cMsgId_gbc: return "gbc";
      case cMsgId_gsv: return "gsv";
      case cMsgId_gft: return "gft";
      case cMsgId_gsx: return "gsx";
      case cMsgId_gcs: return "gcs";
   }
   return "UNKNOWN";
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get a message ident as an integer.

int get_MsgId_asInt(const char* aMsgId)
{
   if (strcmp(aMsgId, get_MsgId_asString(cMsgId_tst)) == 0) return cMsgId_tst;
   if (strcmp(aMsgId, get_MsgId_asString(cMsgId_gbc)) == 0) return cMsgId_gbc;
   if (strcmp(aMsgId, get_MsgId_asString(cMsgId_gsv)) == 0) return cMsgId_gsv;
   if (strcmp(aMsgId, get_MsgId_asString(cMsgId_gft)) == 0) return cMsgId_gft;
   if (strcmp(aMsgId, get_MsgId_asString(cMsgId_gsx)) == 0) return cMsgId_gsx;
   if (strcmp(aMsgId, get_MsgId_asString(cMsgId_gcs)) == 0) return cMsgId_gcs;
   return 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
