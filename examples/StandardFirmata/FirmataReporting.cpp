/*
  FirmataReporting.cpp - Firmata library
  Copyright (C) 2006-2008 Hans-Christoph Steiner.  All rights reserved.
  Copyright (C) 2013 Norbert Truchsess. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/

#include "FirmataConfig.h"
#include <Firmata.h>
#include "FirmataReporting.h"

FirmataReportingClass::FirmataReportingClass()
{
  samplingInterval = 19;
}

boolean FirmataReportingClass::handleSysex(byte command, byte argc, byte* argv)
{
  if (command == SAMPLING_INTERVAL) {
    if (argc > 1) {
      samplingInterval = argv[0] + (argv[1] << 7);
      if (samplingInterval < MINIMUM_SAMPLING_INTERVAL) {
        samplingInterval = MINIMUM_SAMPLING_INTERVAL;
      }
    } else {
      //Firmata.sendString("Not enough data");
    }
    return true;
  }
  return false;
}

boolean FirmataReportingClass::elapsed()
{
  currentMillis = millis();
  if (currentMillis - previousMillis > samplingInterval) {
    previousMillis += samplingInterval;
    return true;
  }
  return false;
}

FirmataReportingClass FirmataReporting;
