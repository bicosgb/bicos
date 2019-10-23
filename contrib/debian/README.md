
Debian
====================
This directory contains files used to package bicoscoind/bicoscoin-qt
for Debian-based Linux systems. If you compile bicoscoind/bicoscoin-qt yourself, there are some useful files here.

## bicoscoin: URI support ##


bicoscoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bicoscoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bicoscoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/bicoscoin128.png` to `/usr/share/pixmaps`

bicoscoin-qt.protocol (KDE)

