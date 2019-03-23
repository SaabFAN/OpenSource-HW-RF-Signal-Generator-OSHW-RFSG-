/*
 * RemoteControl.h
 *
 *  Created on: 16.03.2019
 *      Author: voyag
 */
#include <Arduino.h>
#ifndef REMOTECONTROL_H_
#define REMOTECONTROL_H_

class RemoteControl {
public:
	RemoteControl();
	virtual ~RemoteControl();
	void CheckSerial();
	void ReportStatus();
};

#endif /* REMOTECONTROL_H_ */
