#pragma once

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class implements evaluation of superwants. It does calculations
// based on superwants values and generates corresponding events.

class SuperWantsEvaluatorTTA
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // Constructor.
   SuperWantsEvaluatorTTA();
   void reset();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Evaluate superwants. The superwants are obtained from shared memory.
   void doEvaluate(bool aFirstFlag);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance

#ifdef _CXSUPERWANTSEVALUATORTTA_CPP_
          SuperWantsEvaluatorTTA gSuperWantsEvaluatorTTA;
#else
   extern SuperWantsEvaluatorTTA gSuperWantsEvaluatorTTA;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

