cls
move Driver.exe Driver_old.exe

call cl *.cpp /FeDriver /EHsc /w
rem call cl *.cpp /FeDriver /EHsc /w /I "C:\dwl\lib\_external\cpp" /I "C:\dwl\lib\_external\cpp\libpng"
rem call cl "C:\dwl\lib\_external\cpp\libpng\*.c" *.cpp /FeDriver /EHsc /w /I "C:\dwl\lib\_external\cpp" /I "lib" /LD "lib/libpng3.dll"

del *.obj

echo --------------- Program Run ---------------
Driver.exe
rem python3 .\saveaspng.py
