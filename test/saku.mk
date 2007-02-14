bins += #sakutest 
# sakutest : \
# 	../src/AnimationFilm.o \
# 	../src/AnimationFilmHolder.o \
# 	../src/Animator.o \
# 	../src/AnimatorHolder.o \
# 	../src/CollisionChecker.o \
# 	../src/FrameRangeAnimator.o \
# 	../src/Sprite.o \
# 	../src/SurfaceLoader.o \
# 	../src/commons.o \
# 	../src/SpriteHolder.o \
# 	../src/MovingAnimator.o

CXXFLAGS += -I./
sakutest : sakutest_setup.o $(wildcard ../src/*.o) sakutest_handleInput.o 
sakutest.o : ../client/pacman.cpp
