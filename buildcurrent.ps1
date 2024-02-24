Remove-Item dbg/$args.exe, dbg/*.obj, dbg/*.ilk, dbg/*.pdb

$IncDir = "C:\src\vcpkg\installed\x64-windows-static\include"
$LibDir = "C:\src\vcpkg\installed\x64-windows-static\lib"
$LibDir2 = "C:\glad\4.5\include"

cl.exe src/$args.cpp /DSFML_STATIC /DGLEW_BUILD /Zi /W4 /FC /Fodbg\ `
    /I$IncDir /I$LibDir2 /external:anglebrackets /external:W0 `
    /std:c++20 /EHsc `
    /link /LIBPATH:$LibDir `
    sfml-system-s.lib sfml-graphics-s.lib sfml-window-s.lib sfml-audio-s.lib `
    winmm.lib gdi32.lib opengl32.lib freetype.lib user32.lib Advapi32.lib `
    openal32.lib flac.lib vorbisenc.lib vorbisfile.lib vorbis.lib ogg.lib ole32.lib `
    ws2_32.lib Shell32.lib zlib.lib libpng16.lib `
    brotlicommon-static.lib brotlienc-static.lib brotlidec-static.lib `
    bz2.lib `
    fmt.lib `
    glew32.lib `
    /MACHINE:X64 /out:dbg/$args.exe