== What is included in this README ==
1. Build Instructions
2. Running Instructions

== 1. Building Instructions ==
To build the project you have to run 'make' without any arguments from
the base dir (the dir containing 'client/', 'include/', etc).

There are also the 'clean' and 'purge' targets which remove compiler
generated files ('purge' is more forceful and careless).

-- Special building options:
To disable sound, one sound build the project as follows:
		make ADD_CPPFLAGS=-DPACMAN_NO_SOUND

== 2. Running Instructions ==
To run the project one can just run 'make run' or directly execute
'./client/pacman' from the base dir.

It is important to run pacman from the base dir as it has to be the
working directory.

'make run' is faster because it doesn't spam stderr but everything is
recorded to a log file (./resouces/pacman.log)

If there are assertion failures about the sound (caused in
SoundManager.cpp), it is suggested to recompile using the no-sound option,
as described above.

