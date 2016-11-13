# Copyright (C) 2016 Maxime Busy
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

#!/usr/bin/env python
# coding: utf8

import sys
import os
import inspect

moduleDir        = os.path.dirname(inspect.getfile(inspect.currentframe()))
falconModulePath = os.path.abspath(os.path.join(moduleDir, 'lib_falcon/bin'))

sys.path.insert(0, falconModulePath)

from falconModule import *



class FalconController:
	"""
	Class allowing the user to interact with the Falcon Joystick directly from 
	Python
	"""

	def __init__(self):
		"""
		Constructor
		"""

		pass


	def initDevice(self):
		"""
		Start the device
		"""

		initDevice()


	def displayNbDevices(self):
		"""
		Displays the number of connected devices

		Returns:
			nDevices - The number of devices
		"""

		return displayNbDevices()


	def getJoystickPosition(self):
		"""
		Get the joystick position

		Returns:
			joystickPosition : the joystick position in cartesian coordinates
		"""

		return getPosWC()


	def getButtonsState(self):
		"""
		Get the button pressed by the user

		Returns:
			buttonsState - int corresponding to the combination of the pressed
			buttons (0 : no buttons pressed, etc...)
		"""

		return getButtonStates()


	def setForce(self, xForce, yForce, zForce):
		"""
		Apply a force on the joystick

		Parameters:
			xForce - The force on the x axis
			yForce - The force on the y axis
			zForce - The force on the z axis
		"""

		setForce(xForce, yForce, zForce)


	def stopDevice(self):
		"""
		Stops the device 
		"""

		stopDevice()

