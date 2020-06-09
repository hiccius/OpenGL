## Chapter 4 - Lighting
### Content Summary
This section covers chapters *12. Colors*, *13. Basic Lighting*, *14. Materials*, *15. Lighting Maps* and **_[TO BE COMPLETED]_** of [LearnOpenGL](https://learnopengl.com).

The examples in this section show how to apply **lighting** on objects in OpenGL.

- The perceived color of an object can be interpreted as a combination of the **light's color** and the **object's color** (as in how much of the light's components an object reflects).

- In OpenGL, the **Phong lighting model** is a common model used to implement lighting. It is based on 3 components:
  - **Ambient** lighting: it affects the whole object.
  - **Diffuse** lighting: calculated as the dot product between the **light's direction vector** and the **normal vector** of the surface (perpendicular to the fragment's surface).
  - **Specular** lighting: calculated as the dot product between the **light's reflection vector** around the normal vector of the surface and the **view direction** (origin in view space).

- If the calculations are done in the view space, it is needed to translate the normal vectors from world space. To do this, a special matrix called the **normal matrix** (which is the **transpose of the inverse** of the view or view-model matrix) needs to be applied.

- Different materials have different **ambient**, **diffuse** and **specular** color vectors, as well as different **shininess** (the way the light is scattered over the object's surface).

- For objects with different materials that react differently to light, **lighting maps** (which are basically **textures** for lit scenes) are used. Usually a **diffuse map** is used for **ambient** and **diffuse** components, while a **specular map** (most of the times a black-and-white texture) is used for the **specular** component.

### Examples
The examples can be executed one by one without needing to pass any arguments, the only examples supporting an optional argument are [2. The Phong lighting model](#2-the-phong-lighting-model) and [7. Lighting maps](#7-lighting-maps). The examples need to be launched from the root *build* folder so they can find the right path for the shaders. To exit the examples, just press <kbd>ESC</kbd>.

#### 1. A dull scene
This example simply sets up the scene that will be used on the following examples: an **orangish cube** that will be lighten-up in the following examples and a smaller **white cube** close and slightly above it that will represent the light source in those examples.

<div align="center">
  <img src="images/01-dull_scene.png" height="450"><br>
  <sup><strong>Fig. 1: </strong> Nothing to see here </sup>
</div>

#### 2. The Phong lighting model
This example shows the **Phong lighting model** in action with its **ambient**, **diffuse** and **specular** components applied to the cube. Executing this example with the option ```--orbit``` changes the position of the light over time and the lighting effects can be seen more clearly.

<div align="center">
  <img src="images/02-phong_above.png" height="450"><br>
  <sup><strong>Fig. 2.1: </strong> The top of a brightened-up cube </sup>
</div>
<br>
<div align="center">
  <img src="images/02-phong_side.png" height="450"><br>
  <sup><strong>Fig. 2.2: </strong> One side of a brightened-up cube </sup>
</div>
<br>
<div align="center">
  <img src="images/02-orbiting_light.gif" height="450"><br>
  <sup><strong>Fig. 2.3: </strong> A lamp orbiting a cube </sup>
</div>

#### 3. Same but different
In this example, the calculations are done in the **view space** instead of the **world space** and the visible results are exactly the same.

<div align="center">
  <img src="images/03-view_space.png" height="450"><br>
  <sup><strong>Fig. 3: </strong> Same old, same old </sup>
</div>

#### 4. The Gouraud shading
This example implements the **Gouraud shading**, which is nothing more than the Phong lighting model calculated in the **vertex shader** instead of the fragment shader. It shows how the results are less realistic (although the calculations are done more efficiently) as there is a visible **stripe** in the union between the fragments of the cube.

<div align="center">
  <img src="images/04-gouraud.png" height="450"><br>
  <sup><strong>Fig. 4: </strong> Something odd is happening here </sup>
</div>

#### 5. Disco lights
In this example, the light color changes over time, with different values for its **ambient** and **diffuse** color vectors (they both share the same color but the ambient component is dimmer), while the light source's color also changes with them. It is visible how the cube reacts differently to changes in lighting conditions.

<div align="center">
  <img src="images/05-disco_lights.gif" height="450"><br>
  <sup><strong>Fig. 5: </strong> The cube reacts to different color lights </sup>
</div>

#### 6. A plastic cube
This example shows how the object's **ambient**, **diffuse** and **specular** components can be changed (while a white light is used) to make the material resemble cyan plastic.

<div align="center">
  <img src="images/06-cyan_plastic.png" height="450"><br>
  <sup><strong>Fig. 6: </strong> This cube is made of cyan plastic (or at least looks like it) </sup>
</div>

#### 7. Lighting maps
In this example, lighting maps are used to simulate a wooden container with a steel border. The color is set according to a **diffuse map** and the reflective properties of the steel are defined with a **specular map** containing white values for the most reflective parts. If the example is executed with the option ```--color```, a colored specular map is used for the steel border.

<div align="center">
  <img src="images/07-lighting_maps.png" height="450"><br>
  <sup><strong>Fig. 7.1: </strong> Different materials reacting differently to light </sup>
</div>
<br>
<div align="center">
  <img src="images/07-specular_color.png" height="450"><br>
  <sup><strong>Fig. 7.2: </strong> The steel here is not very realistic </sup>
</div>

#### 8. Emission maps
An **emission map** is added to the container of the previous example, simulating a texture that 'glows' regardless of lighting conditions.

<div align="center">
  <img src="images/08-emission_maps.png" height="450"><br>
  <sup><strong>Fig. 8: </strong> A movie reference </sup>
</div>
