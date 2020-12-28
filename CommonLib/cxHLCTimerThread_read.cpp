/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "risProgramTime.h"
#include "smShare.h"
#include "cxCProcParms.h"
#include "evtService.h"
#include "evtEventStore.h"

#include "cxHLCTimerThread.h"

namespace CX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread timer execution. This is called periodically.

void HLCTimerThread::doRead(int aTimeCount)
{
	//***************************************************************************
	//***************************************************************************
	//***************************************************************************
	// Do this first.

	// Nick name.
	HLCInfo& tH = SM::gShare->mHLCInfo;

	if (!gCProcParms.mHLCOverrideEnable)
	{
		//************************************************************************
		//************************************************************************
		//************************************************************************
		// Update the input from the sensor.

		// Read from the sensor.
		mInput = mHLC.getRFReading();
	}
	else
	{
		//************************************************************************
		//************************************************************************
		//************************************************************************
		// Update the input from the overrides.

		// Override the inputs.
		mInput = tH.mOverrideInput;

		//************************************************************************
		//************************************************************************
		//************************************************************************
		// Update the input from a simulated sinusoid.

		// Override the inputs.
		if (gCProcParms.mHLCSimSinEnable)
		{
			double tPeriod = gCProcParms.mHLCSimSinPeriod;
			double tOffset = (gCProcParms.mHLCSimSinAmpHi + gCProcParms.mHLCSimSinAmpLo) / 2;
			double tAmplitude = (gCProcParms.mHLCSimSinAmpHi - gCProcParms.mHLCSimSinAmpLo) / 2;
			double tTime = Ris::getCurrentProgramTime();
			double tPhase = 2 * 3.1415926535 * tTime / tPeriod;
			double tInput = tOffset + tAmplitude * sin(tPhase);
			mInput = tInput;
		}
	}

	// Store the input.
	tH.mInput = mInput;

	Prn::print(Prn::HLC1, "HLC input %d  %.2f", aTimeCount,mInput);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace