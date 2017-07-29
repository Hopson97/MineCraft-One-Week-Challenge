# MineCraft-One-Week-Challenge

I challenged myself to see if I could create Minecraft in just one week... So lets go!

# Day One

End of day one commit: https://github.com/Hopson97/MineCraft-One-Week-Challenge/tree/44ace72573833796da05a97972be5765b05ce94f

The first day was spent setting up boilerplate code such as the game state/ game screen system, and the basic rendering engines, starting off with a mere quad.

The day was finished off by creating a first person camera.

![Quad](http://i.imgur.com/fJDgA2a.png)

End of day stats:

Title | Data
------------ | -------------
Time programming Today | 3:21:51
Lines of Code Today | 829
Total Time programming | 3:21:51
Total Lines of Code | 829

# Day Two

End of day two commit: https://github.com/Hopson97/MineCraft-One-Week-Challenge/tree/98055215f735335de80193221a30c0bb8586fba5

The second day was spent setting up the basic ChunkSection and various block classes.

I also worked out the coordinates for a cube, and thus created a cube renderer.

I finished up the day attempting to create a mesh builder for the chunk; however, this did not go well at all, and two had ended before I got it to work correctly.

![Messed up chunk](http://i.imgur.com/UsKHJrR.png)

End of day stats:

Title | Data
------------ | -------------
Time programming Today | 4:16:07
Lines of Code Today | 732
Total Time programming | 7:37:58
Total Lines of Code | 1561


# Day Three

End of day three commit: https://github.com/Hopson97/MineCraft-One-Week-Challenge/commit/78bd637581542576372d75cf7638f76381e933b4

To start the day off, I fixed the chunk drawing. Turns out I was telling OpenGL the indices were ```GL_UNSIGNED_BYTE```, but they were actually ```GL_UNSIGNED_INT```. This took 3 hours to work out...

![gl bytesss](http://i.imgur.com/PD44aRg.png)

Anyways, after this I got the game working with more chunks. I now have an area of 16x16 chunks, made out of chunk sections of 16x16x16 blocks.

To finish the day off, I got some naive block editing to work.

![Block editing](http://i.imgur.com/ilTJr8i.png)

End of day stats:

Title | Data
------------ | -------------
Time programming Today | 3:15:38
Lines of Code Today | 410
Total Time programming | 10:53:36
Total Lines of Code | 1974


