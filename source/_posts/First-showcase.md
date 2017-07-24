---
title: First showcase
date: 2017-07-17 17:33:21
tags: opengl, c++
coverImage: https://www.opengl.org/img/opengl_logo.png
---

With this repo here I finally started getting deeper into graphics programming and so I already can show some results.

To get into OpenGL I've used the incredible good tutorials found [here](https://learnopengl.com).

## 1. Basic lighting, materials

I've made my way through those basic parts and produced nice colored cubes.
During my experiments with the lighting I ran into some minor bugs in the specular shading

{% asset_img Fail.gif [inverted_specular_shading] %}

Reason for this was, that my material data wasn't multiplied as stated at this [site](http://devernay.free.fr/cours/opengl/materials.html) (where I've picked the data).
This resulted in inverted specular shading due to that my numbers were instead of above _1.0_ under _1.0_.

After fixing this bug I went over to the next exciting topics. 

## 2. Loading models
I guess this is one of the most important milestones in self-study sessions about graphics programming.
However it's also one of the most annoying topics because there are plenty of 3d model formats. Thankfully there is a library called (assimp)[] which abstracts this for us.

The tutorial provided nice loading code (well compatible with the generated data structures during our sessions) which I instantly adopted because I'm lazy.
Nevertheless I was active enough to give the code a more functional style ignoring the object style.

Moreover it worked without big problems so I loaded in the example model from the tutorial. Instead of the popular teapot or monkeys or whateverelse-is-popular-out-there we loaded in a model from the more or less popular game crisis. 

{% asset_img crisis_model.png [crisis_model] %}

This is from a few days ago and you see that the lighting is pretty fine. Could be better yeah.

What's next? More interesting topics like skyboxes!

## 3. Skyboxes, environment mapping, dynamics

After nice model loading I went back to my nice cube starting to implement some skybox support. Of course the tutorial helped here again, telling us what is needed.
We had a lesson about cubemaps and simple reflection mathematics (which weren't that unfamiliar to me) which resulted finally in this.

{% asset_img first_skybox_rendering.png [first_skybox_rendering] %}

This time we see a nice cup (unfortunately without any coffee!) which was made by a friend of mine, Benjamin.
The cup doesn't reflect anything yet but this was just a proove of concept (both for the skybox and the model loading code).

### 4. Static and dynamic environment mapping

After I noticed it works, I went over to add some reflection mechanics to the fragment shader.
The algorithm here used was static environment mapping. It just uses a cubemap (here the skybox) to get data about the environment. The results are some static reflections. 

Unfortunately I didn't grabbed any picture of this one. Sorry :-(
However more interesting were the dynamic reflections which I added afterwards without further tutorial help. The algorithm there is called dynamic environment mapping.

It wasn't that difficult to achieve dynamic environment mapping. It works in general like this (with some important notes from me):
1. Render the scene offscreen to a cubemap, keep in mind to use here the skybox as initial cubemap.
- Use a 90° projection matrix, the resulting images must create a cube.
- Keep in mind that cube map images must have the *same width and height*!
- You need to render the scene 6-times, each time looking into a different direction! (front, back, left, right, top, bottom)
- Only the position of the camera is needed, you can safely ignore the rotation. Of course this only applies if you're calculating the reflection vectors without respecting camera rotation (which you normaly do to reduce any confusion, we want to stay always in the same virtual system).
2. Render the scene a second time but use the resulting cubemap from the first rendering.
- If you're using OpenGL don't forget to reset the framebuffer index so you're rendering to the real screen and not _off-screen_! 
3. Enjoy the results (if you rendered correctly to the cubemap).
- No popcorn yet!


{% asset_img ReflectionTest3.gif [ReflectionTest3] %}

You can see that the reflections work quite nicely.
