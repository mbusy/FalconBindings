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

import unittest
import falcon_controller

class TestFalconModule(unittest.TestCase):

	def instanciationTest(self):
		"""
		Test the instanciation of the falcon controller object
		"""

		self.controller = falcon_controller.FalconController()
		self.assertIsInstance(self.controller, 
			falcon_controller.FalconController)


	def countingTest(self):
		"""
		Test the computation of the number of connected devices
		"""

		self.nDevices = self.controller.displayNbDevices()
		self.assertIsInstance(self.nDevices, int)


	def initialisationTest(self):
		"""
		Test the initialisation of the controller
		"""

		if self.nDevices == 0:
			print "No connected devices, end of the test"
			return

		self.controller.initDevice()


	def positionTest(self):
		"""
		Test the recuperation of the joystick's coordinates
		"""

		if self.nDevices == 0:
			return

		joystickPosition = self.controller.getJoystickPosition()
		self.assertIsInstance(joystickPosition, list)

		print 'joystick position : ' + str(joystickPosition)


	def buttonsTest(self):
		"""
		Test the recuperation of the button's state
		"""

		if self.nDevices == 0:
			return

		buttonsState = self.controller.getButtonsState()
		self.assertIsInstance(buttonsState, int)

		print 'buttons state : ' + str(buttonsState)


	def forceTest(self):
		"""
		Test applying forces on the joystick
		"""
		if self.nDevices == 0:
			return

		self.controller.setForce(1, 1, 1)


	def stopTest(self):
		"""
		Test stopping the controller
		"""

		if self.nDevices == 0:
			return
	
		self.controller.stopDevice()


	def test_falconModule(self):
		"""
		Launches the tests
		"""

		self.instanciationTest()
		self.countingTest()
		self.initialisationTest()
		self.positionTest()
		self.buttonsTest()
		self.forceTest()
		self.stopTest()



if __name__ == "__main__":
	unittest.main()