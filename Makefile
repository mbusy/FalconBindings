CC       = g++ -shared
SRC 	 = lib_falcon/src/falconModule.cpp
PYD 	 = falconModule.pyd
PATH_PYD = lib_falcon/bin/
INC 	 = lib_falcon/include/
PY_INC 	 = C:/Python27/include/
HEADERS  = lib_falcon/src/
LIB 	 = lib_falcon/lib/
PY_LIB 	 = C:/Python27/libs/
LINK 	 = -lhdl
PY_LINK  = -lpython27

all:

ifeq ($(OS),Windows_NT)
	echo 'Compiling for $(OS)...'
	$(CC) $(SRC) -o $(PATH_PYD)/$(PYD) -I $(INC) -I $(PY_INC) -I $(HEADERS) -L $(LIB) $(LINK) -L $(PY_LIB) $(PY_LINK)

else
	echo 'not implemented for $(OS) for now'

endif

clean:

ifeq ($(OS),Windows_NT)
	del $(PATH_PYD)/$(PYD)

else

endif