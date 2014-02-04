# Dependencies
- OpenCV (DUH) (http://docs.opencv.org/doc/tutorials/introduction/linux_install/linux_install.html#linux-installation)

# To run
## Display_image
- cd display_image
- make
- ./Display_Image <path_to_image>

## Stitch image
- cd image_sticher
- make
- ./StitchImage.out imgs/S1.jpg imgs/S2.jpg imgs/S3.jpg imgs/S5.jpg imgs/S6.jpg
    - Or use pictures of your family etc.
- Use your favourite image viewer to open "result.jpg"

## OpenCV version
- cd opencv_version
- make
- ./OpenCVVersion.out

## Frame grapper
- cd frame_grabber
- make
- ./FrameGrabber.out <movie_file> <frame_number>
- Use your favourite image viewer to open "result.jpg"

## Video stitcher
- cd video_stitcher
- make
- ./VideoStitcher.out <movie_file> <frame_interval>
- **Note: This program has not yet worked successfully**
