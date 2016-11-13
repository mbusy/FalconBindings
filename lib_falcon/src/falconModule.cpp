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

extern "C" {

#include "falconModule.h"

static int 				  pButtons;
static double			  lastTime;
static double 			  posDC[3];
static double 			  posWC[3];
static double 			  force[3];
static HDContainer 	   	  g_device;
static HDLServoOpExitCode g_touchOp;



void testHDLError(const char* str)
{
	HDLError hdlError = HDL_NO_ERROR;
	hdlError          = hdlGetError();

	if(hdlError != HDL_NO_ERROR)
	{
		char msg[200];
		sprintf(msg, "HDAL ERROR %d", hdlError);
		MessageBox(NULL, str, msg, MB_OK);
	}
}



void initHDContainer()
{
	g_touchOp = HDL_INVALID_HANDLE;
	lastTime  = 0;

	for(int i = 0; i < 3; i++)
	{
		g_device.force[i] = 0;
	}

	g_device.handle = hdlInitNamedDevice(0);
	testHDLError("Container initialization");
}



void displayHdlState()
{
	printf("#-----------#\n");
	printf("| HDL STATE |\n");
	printf("#-----------#\n");

	switch(hdlGetState())
	{
		case HDAL_ISREADY:
			printf("device ready\n");
			break;

		case HDAL_UNINITIALIZED:
			printf("device uninitialized\n");
			break;

		case HDAL_SERVO_NOT_STARTED:
			printf("hdlStart not called earlier\n");
			break;

		case HDAL_NOT_CALIBRATED:
			printf("device needs autocalibration (the device might not be correctly powered)\n");
			break;

		default:
			printf("unrecognized option\n");
			break;
	}
}



void vecMultMatrix(double srcVec[3], double mat[16], double dstVec[3])
{
	dstVec[0] = mat[0] * srcVec[0] 
        	  + mat[4] * srcVec[1]
              + mat[8] * srcVec[2]
              + mat[12];
    
    dstVec[1] = mat[1] * srcVec[0]
              + mat[5] * srcVec[1]
              + mat[9] * srcVec[2]
              + mat[13];

    dstVec[2] = mat[2] * srcVec[0]
              + mat[6] * srcVec[1]
              + mat[10] * srcVec[2]
              + mat[14];	
}



HDLServoOpExitCode hapticScene(void *pUserData)
{
	if(g_device.handle != HDL_INVALID_HANDLE)
	{
		hdlMakeCurrent(g_device.handle);
		hdlToolPosition(posDC);
		testHDLError("hdlToolPosition");
		vecMultMatrix(posDC, g_device.transformMat, posWC);
		hdlSetToolForce(g_device.force);
		testHDLError("hdlSetToolForce");
	}
	return HDL_SERVOOP_CONTINUE;
}



static PyObject *initDevice(PyObject *self,PyObject *args)
{ 
    initHDContainer();
    hdlStart();
    Sleep(1000);

    displayHdlState();

    if(g_device.handle != HDL_INVALID_HANDLE)
    	hdlMakeCurrent(g_device.handle);

    g_touchOp = hdlCreateServoOp(hapticScene, (void *)0, false);
    testHDLError("hdlCreateServoOp");

    return Py_BuildValue("");
}



static PyObject *displayNbDevices(PyObject *self,PyObject *args)
{ 
	printf("#---------------------------------#\n");
	printf("| Number of connected devices : %d |\n", hdlCountDevices());
	printf("#---------------------------------#\n");

	return Py_BuildValue("i", hdlCountDevices());
}



static PyObject *getPosWC(PyObject *self,PyObject *args)
{
	float posRobot[3];

	posRobot[0] = (float) posDC[2];
	posRobot[1] = (float) posDC[0];
	posRobot[2] = (float) posDC[1];

	return Py_BuildValue("[f,f,f]", posRobot[0], posRobot[1], posRobot[2]);
}



static PyObject *getButtonStates(PyObject *self,PyObject *args)
{
	hdlToolButtons(&pButtons);
	return Py_BuildValue("i", pButtons);
}



static PyObject *setForce(PyObject *self,PyObject *args)
{
	PyArg_ParseTuple(args,"ddd", &force[0], &force[1], &force[2]);
	g_device.force[0] = -force[1];
	g_device.force[1] =  force[2];
	g_device.force[2] = -force[0];

	return Py_BuildValue("");
}



static PyObject *stopDevice(PyObject *self,PyObject *args)
{ 
    if(g_touchOp != HDL_INVALID_HANDLE)
    {
    	HDLServoOpExitCode(g_touchOp);
    	g_touchOp = HDL_INVALID_HANDLE;
    }

    hdlStop();

    if(g_device.handle != HDL_INVALID_HANDLE)
    	hdlUninitDevice(g_device.handle);

    return Py_BuildValue("");
}



static PyMethodDef module_falconModule[] = {
    {"initDevice",initDevice,METH_VARARGS,NULL},
    {"displayNbDevices",displayNbDevices,METH_VARARGS,NULL},
    {"getPosWC",getPosWC,METH_VARARGS,NULL},
    {"getButtonStates",getButtonStates,METH_VARARGS,NULL},
    {"setForce",setForce,METH_VARARGS,NULL},
    {"stopDevice",stopDevice,METH_VARARGS,NULL},
    {NULL,NULL,0,NULL}
};



void initfalconModule()
{
  (void) Py_InitModule("falconModule", module_falconModule);
}

}