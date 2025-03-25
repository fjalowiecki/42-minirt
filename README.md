# miniRT

miniRT is a lightweight ray tracer written in C. It uses [MiniLibX](mlx/) for graphics and a custom [libft](libft/libft.h) for common utility functions, and it renders simple 3D scenes defined via scene description files in the `input_files/` directory.

## Functionalities

- **Scene Parsing:**  
  Reads and validates scene description files to build the 3D world.

- **Geometry Support:**  
  Implements ray intersections with spheres, planes, cylinders, and cones.

- **Ray Tracing:**  
  Performs ray casting to determine pixel colors based on lighting and shadows.

- **Graphics Rendering:**  
  Uses MiniLibX to create an interactive window, handle events, and render the generated image.

- **Resource Management:**  
  Provides error handling and memory cleanup to ensure stability.

## Project Structure

- **include/**  
  Contains header files with project-wide definitions and data structures (e.g. [minirt.h](include/minirt.h), [vec_utils.h](include/vec_utils.h)).

- **src/**  
  Implements:
  - **Input parsing:** Reads and validates scene files ([input_parser_00.c](src/input_parser_00.c), [input_parser_01.c](src/input_parser_01.c)).
  - **Object creation:** Functions to set up lights and geometry ([obj_setters.c](src/obj_setters.c), [figures_setters.c](src/figures_setters.c)).
  - **Ray-object intersections:** Intersection algorithms for spheres, planes, cylinders, and cones ([hit_sphere.c](src/hit_sphere.c), [hit_plane.c](src/hit_plane.c), [hit_cylinder_00.c](src/hit_cylinder_00.c), [hit_cone_00.c](src/hit_cone_00.c)).
  - **Image generation:** Ray casting, pixel coloring, and image creation ([img_creat_main.c](src/img_creat_main.c), [img_creat_pixel_color.c](src/img_creat_pixel_color.c)).
  - **Vector operations:** Basic vector math ([vec_utils_00.c](src/vec_utils_00.c), [vec_utils_01.c](src/vec_utils_01.c)).
  - **Error handling and resource management:** Memory cleanup and error reporting ([error_msg.c](src/error_msg.c), [free_resources.c](src/free_resources.c)).
  - **MLX utilities:** Functions to handle drawing and window events ([mlx_utils.c](src/mlx_utils.c)).

- **libft/**  
  A custom C library providing various standard utility functions (see [libft/libft.h](libft/libft.h) for details).

- **input_files/**  
  Contains sample scene files (with `.rt` extension) such as [valid_01.rt](input_files/valid_01.rt) and [valid_02.rt](input_files/valid_02.rt).

- **Makefile**  
  Build instructions for the project (see [Makefile](Makefile)).

## Requirements

- A C compiler (e.g., `gcc` or `cc`)
- [MiniLibX](mlx/) for graphics (the Makefile will clone and configure it if needed)
- Development libraries for X11 (`libX11`, `libXext`, etc.)
- Standard C library

## Installation and Build

1. **Clone the repository:**

   ```sh
   git clone https://github.com/fjalowiecki/42-minirt
   cd minirt
   ```

2. **Build the project:**

   ```sh
   make all
   ```

   This will compile the sources, build the libft library, and set up MiniLibX from the mlx directory.

## Usage

Run the executable by providing a scene file (with `.rt` extension) as an argument. For example:

```sh
./minirt input_files/valid_01.rt
```

## Cleanup

- To remove object files:

  ```sh
  make clean
  ```

- To perform a full clean (including the executable):

  ```sh
  make fclean
  ```

- To rebuild the project:

  ```sh
  make re
  ```