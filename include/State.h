#ifndef STATE_H
#define STATE_H

#include <Arduino.h>
// ---------------------------------------------------------------------
// Live bay state
// ---------------------------------------------------------------------
extern String bayStatus;
extern String loadDecision;
extern int throttleLevel;
extern bool manualOverrideActive;
extern bool overloadActive;
extern float voltage, current, power, energyWh, temperature;

// ---------------------------------------------------------------------
// Timing / debounce bookkeeping
// ---------------------------------------------------------------------
extern unsigned long sessionStartMs;
extern float predictedArrivalProb;
extern int predictedDurationMin;
extern int lastHourOfDay;

// ---------------------------------------------------------------------
// Load optimization settings
// ---------------------------------------------------------------------
extern int peakTariffStartHr;
extern int peakTariffEndHr;
extern float predictionThreshold;
extern float overloadCurrentA;
extern float maxStationLoadW;



#endif