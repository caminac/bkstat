set QPATH=C:\mobile\Qt\Qt5.5.1\5.5\mingw492_32\bin
set BASE=%1%
%QPATH%\uic -o ui_%BASE%.h %BASE%.ui
%QPATH%\moc.exe -o moc\moc_%BASE%.cpp %BASE%.h
