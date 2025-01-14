# MineCraft-One-Week-Challenge

I challenged myself to see if I could create Minecraft in just one week... So lets go!

Video: https://www.youtube.com/watch?v=Xq3isov6mZ8

Note: I continued to edit after the 7 days, however the version seen in the video is found here https://github.com/Hopson97/MineCraft-One-Week-Challenge/tree/eb01640580cc5ad403f6a8b9fb58af37e2f03f0c

And the "optimized" version can be found here: https://github.com/Hopson97/MineCraft-One-Week-Challenge/tree/792df07e9780b444be5290fd05a3c8598aacafc8 (~1 week later version) 

There also is a version of this game with very good graphics, and things like a day/night cycle. However, it was causing rendering issues for many people. This version can be found here:
https://github.com/Hopson97/MineCraft-One-Week-Challenge/tree/aa50ad8077ef0e617a9cfc336bdb7db81c313017

## Other People's Projects

This was made in a week, as a challenge for a video. There do exist other, more mature and developed Minecraft clones written in C++.

MineTest here: https://github.com/minetest/minetest

## Building and Running

### Windows (Visual Studio)

The easiest way to build is to use [vcpkg](https://vcpkg.io/en/index.html) and install dependencies through this:

```bash
vcpkg install sfml
vcpkg install imgui
vcpkg install glm
vcpkg integrate install
```

Then open the Visual Studio project file to build and run.

### Linux

#### Pre-requisites

Install Vcpkg and other required packages using your distribution's package manager:

```sh
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh

# These are required to build some packages
sudo apt install cmake make autoconf libtool pkg-config

# The following are required for SFML
sudo apt install libx11-dev xorg-dev freeglut3-dev libudev-dev
```

Ensure paths are set correctly:

```sh
export VCPKG_ROOT=/path/to/vcpkg
export PATH=$VCPKG_ROOT:$PATH
```

RECOMMENDED: Add the above lines to your `.bashrc` or `.zshrc` file:

```sh
echo 'export VCPKG_ROOT=/path/to/vcpkg' >> ~/.bashrc
echo 'export PATH=$VCPKG_ROOT:$PATH' >> ~/.bashrc
```

#### Build and Run

To build, at the root of the project:

```sh
vcpkg install # First time only
sh scripts/build.sh
```

To run, at the root of the project:

```sh
sh scripts/run.sh
```

To build and run in release mode, simply add the `release` suffix:

```sh
sh scripts/build.sh release
sh scripts/run.sh release
```

## The Challenge

### Day One

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

### Day Two

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


### Day Three

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

### Day 4

The first thing I did on day 4 was create a sky box using OpenGL cube maps.

After this, I started work on the world generation, eg adding height map and trees.

![Skybox and world gen](http://i.imgur.com/mzUwqPo.png)

End of day stats:

Title | Data
------------ | -------------
Time programming Today | 3:14:15
Lines of Code Today | 523
Total Time programming | 14:07:51
Total Lines of Code | 2489

### Day 5

I started off the day by cleaning up some of the chunk code, and then proceeded to make the world infinite, but
I felt it was not needed, so I simply went back to a fixed-sized world.

I then added an item system. My implementation probably was not great for this, but it was my first time
at creating that sort of the thing.

Basically, when a player breaks a block, it gets added to their inventory. When they place a block, a block
is placed.

Title | Data
------------ | -------------
Time programming Today | 2:54:14
Lines of Code Today | 560
Total Time programming | 17:02:05
Total Lines of Code | 3049

### Day 6

Mostly optimizations, such as view-frustum culling and making the mesh building faster.

### Day 7

Focus on improving how it looks, eg adding directional lighting

Also implemented concurrency :)

