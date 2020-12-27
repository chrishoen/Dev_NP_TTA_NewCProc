#pragma once

/*==============================================================================
Serial message definitions.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Serial message definitions.

namespace SX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Msg identifiers. Associated with each event is a level that defines 
// alarm status. Alarm and Critical are used to classify active alarms.

static const int cMsgId_none = 0;
static const int cMsgId_tst = 1;
static const int cMsgId_gbc = 2;
static const int cMsgId_gft = 3;
static const int cMsgId_gsx = 4;
static const int cMsgId_gcs = 5;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers.

// Get a message ident as a string.
char* get_MsgId_asString(int aMsgId);

// Get a message ident as an integer.
int get_MsgId_asInt(const char* aMsgId);

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

