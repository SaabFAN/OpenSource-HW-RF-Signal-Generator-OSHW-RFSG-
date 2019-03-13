/*
 * ADF5355Driver.h
 *
 *  Created on: 13.03.2019
 *      Author: voyag
 */

#ifndef DRIVER_ADF5355_ADF5355DRIVER_H_
#define DRIVER_ADF5355_ADF5355DRIVER_H_

class ADF5355_Driver {
public:
	ADF5355_Driver();
	virtual ~ADF5355_Driver();
	bool Init();
};

#endif /* DRIVER_ADF5355_ADF5355DRIVER_H_ */
