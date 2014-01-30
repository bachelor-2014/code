# Dependencies
- OpenCV (DUH) (http://docs.opencv.org/doc/tutorials/introduction/linux_install/linux_install.html#linux-installation)
- CMake (try your package manager)

# To run
## Display_image
- cd display_image
- cmake . 
- make
- ./Display_Image <path_to_image>

## Stich image
- cd image_sticher
- cmake .
- make
- ./StichImage imgs/S1.jpg imgs/S2.jpg imgs/S3.jpg imgs/S5.jpg imgs/S6.jpg
    - Or use pictures of your family etc.
- Use your favourite image viewer to open "result.jpg"