/* Copyright (C) 2016 Maxime Busy
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FALCON_MODULE_H
#define FALCON_MODULE_H

extern "C" {

#include <stdio.h>
#include <windows.h>
#include <hdl/hdl.h>
#include <hdl\hdlErrors.h>
#include <hdl\hdlConstants.h>
#include <hdlu\hdlu.h>
#include <Python.h>

typedef struct HDContainer
{
	HDLDeviceHandle handle;
	double 			workspaceDims[6];
	double 			cursorPos[3];
	double 			transformMat[16];
	double 			force[3];
	bool 			bButton;

} HDContainer;

void 			   testHDLError(const char *str);
void 			   initHDContainer();
void 			   displayHdlState();
void 			   vecMultMatrix(double srcVec[3], double mat[16], double dstVec[3]);
HDLServoOpExitCode hapticScene(void *pUserData);

static PyObject *initDevice(PyObject *self,PyObject *args);
static PyObject *displayNbDevices(PyObject *self,PyObject *args);
static PyObject *getPosWC(PyObject *self,PyObject *args);
static PyObject *getButtonStates(PyObject *self,PyObject *args);
static PyObject *setForce(PyObject *self,PyObject *args);
static PyObject *stopDevice(PyObject *self,PyObject *args);

}

#endif // FALCON_MODULE_H