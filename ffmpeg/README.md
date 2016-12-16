SDL VERSION 1.2.15-r9
gcc simplest_ffmpeg_player.c -g -o smp.out -lSDLmain -lSDL -lavformat -lavcodec -lavutil -lswscale

./smp.out test.flv
