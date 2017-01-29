cls
mv Driver.exe Driver_old.exe

call cl *.cpp /FeDriver /EHsc /w

rm *.obj

echo --------------- Program Run ---------------
Driver.exe
