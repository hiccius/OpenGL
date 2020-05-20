## Chapter 1 - The Basics
### Content Summary
This section covers chapters *5. Hello Triangle* and *6. Shaders* of [LearnOpenGL](https://learnopengl.com).

The examples in this chapter implement basic **OpenGL** functions. 

- They set up a window (including a resize callback and a key to exit the program), load the appropiate functions to initialise the environment and implement a simple **render loop**. 

- Each of the examples compile a **vertex shader** and a **fragment shader** and link them into a **shader program**. These simple shaders work with **input** and **output** variables and **uniforms** to apply simple modifications over the graphics pipeline. 

- The examples also introduce the concepts of **Vertex Buffer Objects (VBOs)**, **Vertex Array Objects (VAOs)** and one of them makes use of an **Element Buffer Object (EBO)**.

### Examples
#### 1. A Basic Triangle
<div align="center">
<img src="images/01-triangle.png" height="500"><br>
<sup><strong>Fig 1:</strong> A basic (and orange!) triangle</sup>
</div>
Implementation of a simple triangle usign a basic vertex shader that draws 3 vertices (defined in a VBO and the corresponding attributes in VAO) and a fragment shader that colours the resulting triangle in orange.

#### 2. Two Basic Triangles 
