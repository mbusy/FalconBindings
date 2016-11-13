# Python bindings for the Falcon joystick (Novint)

## Description
Allows the user to interact with the joystick directly from Python.

## Install
On Windows, only use the following command (in the Python folder) to generate the binding module :
> mingw32-make

Put the folder with your python modules (site-packages/)\\
Use the module :

'''python
from FalconBindings import falcon_controller
 
controller = falcon_controller.FalconController()
 
if controller.displayNbDevices() == 0:
	return
 
controller.initDevice()
joystickPosition = controller.getJoystickPosition()
buttonsState     = controller.getButtonsState()
controller.setForce(1, 1, 1)
controller.stopDevice()
'''

## Troubleshooting

### Undefined reference to '_head_C__build27_cpython_PCBuild_libpython27_a'
follow the instructions given at : http://sebsauvage.net/python/mingw.html