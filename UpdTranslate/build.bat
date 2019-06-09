@echo OFF
set /p build=< build
set /a "summ=%build%+1"
echo %summ% > build
echo %build%
