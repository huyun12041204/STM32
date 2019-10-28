@echo off ?
echo ---------------------------------------------------- ?
echo Press any key to delete all files with ending: ?
echo ?*.aps *.idb *.ncp *.obj *.pch *.tmp *.sbr ?
echo ?*.tmp *.pdb *.bsc *.ilk *.res *.ncb *.opt ??
echo ?*.suo *.manifest *.dep ? ..
echo ?Buildlog.htm *Build_log.htm?
echo ?*.obj *.pch *.idb *.pdb *.res *.dep *.manifest ?
echo ?*.bsc *.ilk *.SBR *.lst *.ncb *.sdf *.tlog ?
echo ?*.exp *.lastbuildstate *.log *.suo *.psess?
echo ? *.ipch *.db *.svn-base ?
echo There are Visual C++ and Visual Studio junk ?
echo ---------------------------------------------------- ?
pause ?
del /F /S /Q *.aps *.idb *.ncp *.obj *.pch *.sbr *.tmp *.pdb *.bsc *.ilk *.res *.ncb *.opt *.suo *.manifest *.dep *.lastbuildstate *.tlog?
del /F /S /Q Buildlog.htm *Build_log.htm *.manifest *.lst *.ncb *.sdf *.tlog *.exp *.db *.suo *.sdf

echo ---------------------------------------------------- ?
echo Press any key to delete all files with ending: ?
echo ?*.bak *.ddk  *.edk *.lst *.lnp *.mpf *.mpj *.obj *.omf   ?
echo ?*.plg *.rpt *.tmp  *.__i *.crf *.o *.d *.axf *.tra ?
echo ? *.dep JLinkLog.txt *.iex *.htm *.sct *.map ?
echo There are Keil junk ?
echo ---------------------------------------------------- ?
pause ?
del /F /S /Q *.bak *.ddk  *.edk *.lst *.lnp *.mpf *.mpj *.obj *.omf
del /F /S /Q *.plg *.rpt *.tmp  *.__i *.crf *.o *.d *.axf *.tra 
del /F /S /Q  *.dep JLinkLog.txt *.iex *.htm *.sct *.map 
pause ?