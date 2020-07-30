# ImageCaptureAndCalibration  
## This is used to capture images using imaging source cameras and make calibration  
### procedures  
1. terminal 1  
roscore  
2. terminal 2,  go to the image capture folder, and enter  
source devel/setup.bash; rosrun camera_publish talker  
3. terminal 3, open rviz to check the captured images  
rosrun rviz rviz  
4. terminal  4, open camera control UI  
rosrun rqt_gui rqt_gui -s reconfigure  
 

