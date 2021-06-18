mkdir build
del build\cli.zip
path=%path%;"c:\program files\winzip"
wzzip build\cli.zip cli.hpp cli.cpp examples\*\* 
