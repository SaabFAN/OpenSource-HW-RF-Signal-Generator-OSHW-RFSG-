/*
 * RemoteControl.h
 *
 *  Created on: 16.03.2019
 *      Author: voyag
 */
#include <Arduino.h>
#ifndef REMOTECONTROL_H_
#define REMOTECONTROL_H_
#include "SignalControls/AnalogBoardDriver.h"
#include "SignalControls/SignalControl.h"

class RemoteControl {
public:
	RemoteControl();
	virtual ~RemoteControl();
	void Init();
	void CheckSerial();
	void ReportStatus();
};

#endif /* REMOTECONTROL_H_ */
