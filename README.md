# Kizuko

Important: This project is under construction, including its organization/layout. Also, MIT License.

Kizuko is inspired by the japanese 地図帳 (chizuchō), which means (according to Wiktionary), an atlas (i.e. a map). It was previous named MassEffectClusters as its initial responsibility was to display an isometric Mass Effect-style cluster map (i.e. stars in the same neighborhood).


## Third parties

To handle the 3rd parties, I use VCPKG, which is a no-nonsense package manager that does exactly what I want, without hindering me. If you are developping on a Windows machine, give it a try. You'll like it.

Anyway, this project depends on the following third parties:

1. freetype
1. gtest
1. jpeg62
1. libbz2
1. libpng16
1. SFML
1. zlib
1. Boost

(some are the names of the DLLs VCPKG brought for me in my bin directory. The list fluctuate as I try alternatives)

## Configurations

This is a x64-only project. Sorry for the 32-bit users out there (the code should remain 32-friendly, though).

There are three configurations: "Release" and "Debug" are mostly the normal Visual Studion (not CMake) configurations. "ReleaseDev" is a "Release" configuration where optimizations were disabled, for debugging purposes.

## Platform

This is a Windows only program for the following reasons:

1. I use VCPKG as my package manager (I'm still learning, though)
1. I actually like Visual Studio/MSBuild project file format
1. CMake is crap (see below)

... But the code is cross platform, so it should work everywhere. If you want to try it on your platform, do not hesitate to create your own CMake files, and contribute. I will update them as needed (but I'll never use them).

## Important

Note: This project will be heavily modified:

1. It will probably become a generic map executable
1. In addition to clusters, I will probably add a galactic map, a star system map (as in Mass Effect), so I will probably rename the whole bunch of DLLs and EXEs.
1. I will

## Why is CMake crap?

Despite its very interesting cross-platform nature, I don't use CMake for my projects.

There's a lot of reasons for that, but the main one for me is that it generates ridiculously bloated and wrong Visual Studio project files (probably coming from Visual C++ 6.0, as in, 1998). For example, the "Release" configuration doesn't produce debug symbols, which is absurdingly stupid.

## Your project is a mess!

Ok, I don't really care about the exact 3rd parties dependencies, because VCPKG solves them for me.

Currently, I'm trying to solve a specific problem, which is displaying 3D/isometric maps on a screen, for a tabletop RPG game. Which means my Tabletop RPG game and my players are my priority.

I'm sharing it on github because I need a source manager. The bonus is that in case it interests someone, the sources are available. If there is a need, I will clean up the dependencies, whatever is needed for anyone to use it on any (reasonable) platform. Until then, my priority is my Tabletop RPG game.
