#include "State.h"

String bayStatus = "FREE";
String loadDecision = "ALLOW";
int throttleLevel = 100;
bool manualOverrideActive = false;
bool overloadActive = false;
float voltage = 0.0, current = 0.0, power = 0.0, energyWh = 0.0, temperature = 0.0;

unsigned long sessionStartMs = 0;
// edge ai variables
float predictedArrivalProb = 0.0;
int predictedDurationMin = 0;
 int lastHourOfDay = 12;

// optimization defaults
int peakTariffStartHr = 18;
int peakTariffEndHr = 21;
float predictionThreshold = 0.5;
float overloadCurrentA = 16;
float maxStationLoadW = 3000; 