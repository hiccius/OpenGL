## Chapter 7 - Advanced Features
### Content Summary
This section covers chapters *29. Advanced GLSL*, *30. Geometry Shader* and **_[TO BE COMPLETED]_** of [LearnOpenGL](https://learnopengl.com).

The examples in this section show different _advanced_ features of OpenGL.

- Some interesting **vertex shader** variables are:
    - ***gl_Position***: an output variable representing the **clip-space** position.
    - ***gl_PointSize***: an output variable that can be used to set the **size of points** when they are the primitive rendered from the vertex data. Needs to be activated first.
    - ***gl_VertexID***: an input variable that contains the **ID** of the vertex being drawn.

- Some interesting **fragment shader** variables are:
    - ***gl_FragCoord***: an input variable representing the **screen coordinates** (**x** and **y**) and the **depth value** of the fragment. Can be used to apply different transformations on different parts of the screen.
    - ***gl_FrontFace***: an input boolean variable that is true if the fragment is part of a **front-facing** face and false otherwise.
    - ***gl_FragDepth***: an output variable that can be used to manually set the **depth value** of a fragment. By default, it takes the same value as *gl_FragCoord.z*. Setting this variable disables **early depth testing**, unless (from *OpenGL 4.2*) it is redeclared with a depth condition to hint some limits (like always larger or smaller than *gl_FragCoord.z*).

- Variables in shaders can be grouped together in **interface blocks** for **input** or **output** variables. They are declared in a similar way to ```structs``` but using the ```in``` or ```out``` keyword. The **block name** needs to be the same so they can be matched across shaders, their **instance name** can be different.

- **Uniform buffer objects** can be used to avoid the need to manually set the same uniform variables on different shaders (for example when using view and projection matrices). The variables need to be declared in a **uniform block** in shaders and a **uniform block layout** can be specified - *shared* by default but *std140* is most commonly used as it has a fixed set of rules for offsets and padding of variables based on multiples of a **base alignment** for each variable type. Memory needs to be allocated before filling the buffer and it also needs to be linked to a **binding point** (the whole buffer or parts of it to different binding points) so the shader can find the data (the shader also needs to have its uniform blocks linked to the same binding points as the uniform buffer objects).

- Between the vertex and fragment shaders there is another optional shader, the **geometry shader**. This shader takes the vertices of a single **primitive** (e.g. a point, a triangle) and is able to apply transformations and generate other primitives or more vertices.
    - It is important to take into account that the variables received from the **vertex shader** (position, color...) are passed as **arrays** - one element for each vertex - and that the variables which go to the **fragment shader** are sent when a vertex is **emitted**, so they need to have the right value before making the appropriate call.
    - Geometry shaders are used to dynamically generate shapes on the fly and are useful to draw simple shapes which appear multiple times on a scene in an easier way than defining all of them as vertices for the vertex shader.

### Examples
The examples can be executed one by one without needing to pass any arguments, the only examples supporting an optional argument are [6. xxx](#6-xxx). The examples need to be launched from the root *build* folder so they can find the right path for the shaders. To exit the examples, just press <kbd>ESC</kbd>.

#### 1. Points in space
This example sets the variable *gl_PointSize* equal to the **depth value** when drawing points on the screen, making them appear larger the farther they are from the viewer.

<div align="center">
  <img src="images/01-points.gif" height="450"><br>
  <sup><strong>Fig. 1: </strong> Growing points </sup>
</div>

#### 2. Split window
In this example, a different **color** is used in the fragment shader depending on the value of *gl_FragCoord*.

<div align="center">
  <img src="images/02-halves.gif" height="450"><br>
  <sup><strong>Fig. 2: </strong> A color transition </sup>
</div>

#### 3. Oriented faces
This example takes a different texture depending on the value of *gl_FrontFace*, using one for **front-facing** faces and a another for **back-facing** faces.

<div align="center">
  <img src="images/03-faces.gif" height="450"><br>
  <sup><strong>Fig. 3: </strong> In and out </sup>
</div>

#### 4. Colored cubes
In this example, four different shaders are used for each cube and because view and projection matrices are the same for all of them, an **uniform buffer object** is used to store these matrices and make them available for the four shaders.

<div align="center">
  <img src="images/04-cubes.png" height="450"><br>
  <sup><strong>Fig. 4: </strong><i> Chis chis chis </i></sup>
</div>

#### 5. Winter houses
In this example, four houses of different colors are drawn using the **geometry shader** from just **single points** passed to the **vertex shader** with different colors associated to them. All the triangles and the extra vertices are generated in this shader.

<div align="center">
  <img src="images/05-houses.png" height="450"><br>
  <sup><strong>Fig. 5: </strong> Notting Hill in winter </sup>
</div>
