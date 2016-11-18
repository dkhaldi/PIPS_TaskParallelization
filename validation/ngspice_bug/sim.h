#ifndef _SIM_H
#define _SIM_H

enum simulation_types {
  SV_NOTYPE,
  SV_TIME,
  SV_FREQUENCY,
  SV_VOLTAGE,
  SV_CURRENT,
  SV_OUTPUT_N_DENS,
  SV_OUTPUT_NOISE,
  SV_INPUT_N_DENS,
  SV_INPUT_NOISE,
  SV_POLE,
  SV_ZERO,
  SV_SPARAM,
  SV_TEMP,
  SV_RES,
  SV_IMPEDANCE,	//Añadido por A.Roldán
  SV_ADMITANCE,	//Añadido por A.Roldán
  SV_POWER	    //Añadido por A.Roldán
};

#endif
