# 3D Mesh Uniform Point Sampling
 Simple header-only uniform point generator over 3D surfaces.

<img src="https://github.com/To-Silva/3D-Mesh-Uniform-Point-Sampling/blob/master/misc/sampling.png" height="300">

GLM is the graphics math library used (only dependency used), but the code is easily changed to use others such as Eigen.

The point distribution is truly uniform, that is, it doesn't rely on vertex positions and has no face size biases. Face size bias is removed by sampling a triangle, picking a random index from a cumulative face area array.

A point ***P*** is generated using the following formula:

<img src="https://github.com/To-Silva/3D-Mesh-Uniform-Point-Sampling/blob/master/misc/pointGen.jpg" height="250">

**β** and **α** are random numbers. The square root of **β** sets the percentage from vertex **A** to the opposing edge, while **α** represents the percentage along that edge. Taking the square-root of **β** gives a uniform random point with
respect to surface area



Reference:

Bernard Chazelle David Dobkin Robert Osada, Thomas Funkhouser. Shape Distributions. ACM Transactions on Graphics, 2002.
