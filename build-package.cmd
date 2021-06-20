mkdir build
del build\cli.zip
path=%path%;"c:\program files\winzip"
wzzip build\cli.zip src\* examples\*\* extras\*\*\*
