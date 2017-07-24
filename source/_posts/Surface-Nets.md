---
title: Naive Surface Nets
date: 2017-07-18 16:37:24
thumbnailImage: https://www.opengl.org/img/opengl_logo.png
thumbnailImagePosition: bottom
metaAlignment: center
coverSize: partial
coverImage: PlayingWithShaders.PNG
clearReading: true
---
# Isosurface extraction
### 1. How do naive surface nets work?
#### Problem:
We want a easy algorithm for iso surface extraction that people can understand. 

Solution is surface nets!

#### Idea: <p align="justify">
Approach is following, consider an amount of 3D voxel data. Just like in the famous Marching Cubes algorithm we're going to iterate blockwise over our voxel data (results in a 3D grid system).
Each block consists of 8 voxels - a 3D cube. To extract a surface out from this data we asume that each block (with edge intersections) returns a single vertex. Each vertex from a cube is linked to the next block so in the end we have only _quads_ which can be easily drawn. Furthermore we also assume that the block vertex is most likely to be in the middle of the cube (so x = 0.5, y = 0.5 and z = 0.5 considering normalized values). This system already gives us a valid algorithm for extracting a surface out of 3D voxel data, see image below.
</p>

{% asset_img NonInterpolatedPlayingWithShaders.PNG [Block Torus] %}
<p align="justify">
However if we want special interpolation the situation get's a bit more complicated.

Main idea here is just to interpolate between each intersection edge, e.g. between vertex a and vertex b where each has a specific scalar value.

To understand the interpolation algorithm used here we first need to cover something else too.
</p>

## 2. The Vertex and edge intersection lookup table <p align="justify">
The edge intersection detection, interpolation and face generation relies upon a lookup table for speedup. In the implementation there are provided two lookup tables each relying on a specific order of the vertex and edge indicies (for the cube). The first one maps an edge index to the correct vertex pair, the second table matches the vertex mask to the edge intersection mask.
Vertex mask means here which vertices are not in the surface (their bits are not set).
</p>

## 3. The Vertex and edge index order <p align="justify">
The calculation of the edge table only works if we define a specific number order for our vertices.
The underlying picture shows the defined vertex number order for our implementation.
</p>

{% asset_img CubeIndexOrder.png [Index order vertices] %}

### 3.1 Explaining the Vertex order
The order of those indices have a logical reason. Each axis correspondends to a single bit:
- first bit for x
- second bit for y
- third bit for z

> **Note**: This does work because we have a maximum of 8 edges in a cube which can be represented by log(8) / log(2) bits (which is 3)!

<br>
### 3.2 Example
Just to get conform with this unusual mapping of coordinates here an example:

**Question**:
Where is vertex _3_ located?

**Thoughts**:
=> To get the coordinates we have to look into it's binary representation

**Answer**:

| z | y | x |
|---|---|---|
| 0 | 1 | 1 |

It's telling us to move one towards us (x), then to move one left (y).
The height is zero (z).

The edges have a specific order too which is respectively in the implementation. The picture below shows the edge number order.


## 4. The optimized interpolation
```fsharp
// Fast interpolation algorithm, multiplication is done in the end
let interpolateVertices () =
    let rec iterate i e_count (vertices:float[]) =
        if i < 12 then
            if hasFlag PowerOfTwo.[i] edge_mask then
                let e0, e1 = cubeEdgesSurfacenets.[i]
                let g0, g1 = block.[e0], block.[e1]
                let diff = g0 - g1
                // Here we can specify whether an interpolation should be discarded if the values are too near
                if abs diff > 1e-6 then 
                    let t = g0 / diff
                    let res = 
                        [|  for j in 0..2 do
                                let k = PowerOfTwo.[j]
                                let a = hasFlag k e0 //(e0 &&& k)
                                let b = hasFlag k e1 //(e1 &&& k)
                                let res = 
                                    if (a <> b) then 
                                        t
                                    elif a then
                                        1.
                                    else
                                        0.0
                                yield vertices.[j] + res |]
                    iterate (i + 1) (e_count + 1) res
                else
                    iterate (i + 1) (e_count + 1) vertices
            else
                iterate (i + 1) e_count vertices
        else
            vertices, e_count
    let vertices, e_count = iterate 0 0 [| 0.0; 0.0; 0.0 |]
    let s = 1.0 / float e_count

    // finally normalize the values again and afterwards translate them centric to the grid.
    float z1 + s * vertices.[0] - zMaxHalf,
    float y1 + s * vertices.[1] - yMaxHalf,
    float x1 + s * vertices.[2] - xMaxHalf
```

Let's take a look into the interpolation algorithm provided here. Because it isn't straightforward, I'll try to explain here what's happening.

With naive surface nets we assume that the vertex is in the middle, due to this we have special conditions.
The workflow is following:
- 1th The vertex values are initial zero
- 2th We apply all interpolation first and normalize the new values last.
- 3th We use the edge intersection mask to get the specific vertex indicies to those
- 4th The vertex indicies are distributed special and so we can do following:
-- We shift 1.0 in x direction if both indicies first bit is set. 
    So all edges towards infinite positive x. 
    or in short - it's either edge 3, 10, 7 or 4 - 
-- We shift 1.0 in y direction if both indicies second bit is set.
    So all edges towards infinite positive y. 
    or in short - it's either edge 5, 6, 7 or 11 - 
-- We shift 1.0 in z direction if both indicies third bit is set.
    So all edges towards infinite positive z. 
-- We do not shift in x direction if both indices first bit is _not_ set
    So all edges towards infinite negative x direction.
-- We do not shift in y direction if both indices second bit is _not_ set
    So all edges towards infinite negative y direction.
-- We do not shift in z direction if both indices third bit is _not_ set
    So all edges towards infinite negative z direction.
-- We shift up with the interpolated value if the indicies are in axis direction (e.g. x or y or z) 
    Just all edges which are parallel to the axis direction.
=> In short, the bitmasking operations allows here fast applying the interpolation correctly.
- Lastly we normalize the result values (using the edge intersection counter) and translate the values so the resulting mesh is centered around the middle of the grid (e.g. zero)

## Summary

Of course it's possible to provide a different solution for the interpolation algorithm due to it's worse readability.
However the lookup tables are something which should be used _AS IS_ because they are very difficult to construct.
If you need a working implementation feel free to use the one provided below (written in F#).

Results may look like this:

{% asset_img PlayingWithShaders.PNG [Block Torus] %}

## Sources
Sure, I used some sources too, the algorithm below is a translation from JS to F#.
The JS code is comming from [this](https://0fps.net/2012/07/12/smooth-voxel-terrain-part-2/) awesome blog. I really recommend to read this one too especially because it provides a working JS example!


#### Code
<script src="https://gist.github.com/realvictorprm/06bbce3c9935a1d148562ec01990216c.js"></script>
