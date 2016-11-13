# Python bindings for the Falcon joystick (Novint)

## Description
Allows the user to interact with the joystick directly from Python.

## Install
On Windows, only use the following command (in the Python folder) to generate the binding module :
> mingw32-make

Then execute the python test script :
> python test_script.py


## Troubleshooting

### Undefined reference to '_head_C__build27_cpython_PCBuild_libpython27_a'
follow the instructions given at : http://sebsauvage.net/python/mingw.html