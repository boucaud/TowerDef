@echo off
rem Do not edit! This batch file is created by CASIO fx-9860G SDK.


if exist TOWERDEF.G1A  del TOWERDEF.G1A

cd debug
if exist FXADDINror.bin  del FXADDINror.bin
"C:\Program Files\CASIO\fx-9860G SDK\OS\SH\Bin\Hmake.exe" Addin.mak
cd ..
if not exist debug\FXADDINror.bin  goto error

"C:\Program Files\CASIO\fx-9860G SDK\Tools\MakeAddinHeader363.exe" "Z:\home\adrien\Dropbox\GBros\Programming\Casio\ADBOOK\towerDef"
if not exist TOWERDEF.G1A  goto error
echo Build has completed.
goto end

:error
echo Build was not successful.

:end

