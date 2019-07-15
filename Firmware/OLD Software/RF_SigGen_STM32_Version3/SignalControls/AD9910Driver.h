/*
 * AD9910Driver.h
 *
 *  Created on: 16.03.2019
 *      Author: voyag
 */

#ifndef AD9910DRIVER_H_
#define AD9910DRIVER_H_

#define AD9910_CS PA8
#define AD9910_IOUP PA9
#define AD9910_OSK PA10
#define AD9910_DRH PB15
#define AD9910_DRC PB5
#define AD9910_DRO PB8
#define AD9910_RSO PB9
#define AD9910_PLL 0x08 // Bitmask for the second GPIO-Expander - PLL-Lock Detect of AD9910. LOW = UNLOCK
#define AD9910_RST 0x40 // Bitmask for the second GPIO-Expander - I/O-Reset Pin of AD9910

class AD9910Driver {
public:
	AD9910Driver();
	virtual ~AD9910Driver();
	bool Init(unsigned long reference_frequency);
	void SetMode(char mode);
	void Configure(int selector, int value);
	bool SetAmplitude(char amplitude);
	void SetFrequency(unsigned long frequency);
	void SetPhase(float phase_angle);
	bool CheckLock();
	bool CheckMux();
	unsigned long GetFrequency();
	char GetAmplitude();
	int GetPhase();
};

#endif /* AD9910DRIVER_H_ */
