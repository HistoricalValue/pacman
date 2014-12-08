# Pacman (again)

This is a university project, which was about receating the classical "pacman" game. It is not maintained (very well) since 2007 (or 2009). Periodically we check that it still builds and runs under newer versions on GCC and GNUmake.

**It is a mess**. The code is provided here for reference, sentimental reasons, and, of course, historical value.

**Also**, warning, there are binary files in thie repository, making it f-ing huge. Because in the olden times students had no idea about those things.

## Building
### Dependencies
SDL, SDL mixer and SDL ttf are required. In arch, one could install there as

    sudo pacman -S sdl_mixer sdl_ttf

Also, building and <code>make run</code> (see below) require the bash shell.

### Make
Just <code>make</code> from the project directory. To build without sound (SDL mixer support didn't use to be that great in 2007), try <code>make nosound</code>.

## Running
When and if building successfully completes, try <code>./client/pacman</code> from the _project directory_ (that's important). Alternatively try <code>make run</code> to have a less logging spam, which is instead redirected to a file.


## Love
This was done along with "zar" and "aman". Music was originally composed by "aman". Artwork was kindly provided by Terhi Lehkonen and Markku Immonen.

## Original
This project was originally being developed under/over/into bazaar, and can be found [here](https://code.launchpad.net/~isidev/454pacmane2008/trunk).
