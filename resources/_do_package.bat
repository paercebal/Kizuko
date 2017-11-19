SET PATH=C:\Program Files\7-Zip;%PATH%
PUSHD ..
del Kizuko.zip
rmdir /s /q .\Kizuko
md Kizuko
POPD
xcopy *.exe ..\Kizuko /E /Q
xcopy *.dll ..\Kizuko /E /Q
xcopy *.txt ..\Kizuko /E /Q
xcopy *.bat ..\Kizuko /E /Q
xcopy *.json ..\Kizuko /E /Q
xcopy *.ogg ..\Kizuko /E /Q
xcopy *.png ..\Kizuko /E /Q
xcopy *.ttf ..\Kizuko /E /Q

PUSHD ..\Kizuko
SET DT=%date%_%time:~0,2%-%time:~3,2%-%time:~6,2%
SET DT=%DT: =0%
7z.exe a -r Kizuko-%DT%.zip *.*
POPD
