# DeepEdge_OpenCV_Resize

Step1

![Screenshot 2024-02-26 at 3.12.52 PM.png](DeepEdge_OpenCV_Resize%20b9f7fbb8e2d34b678543feda4e9492ff/Screenshot_2024-02-26_at_3.12.52_PM.png)

![Screenshot 2024-02-26 at 3.12.27 PM.png](DeepEdge_OpenCV_Resize%20b9f7fbb8e2d34b678543feda4e9492ff/Screenshot_2024-02-26_at_3.12.27_PM.png)

![Screenshot 2024-02-26 at 3.10.41 PM.png](DeepEdge_OpenCV_Resize%20b9f7fbb8e2d34b678543feda4e9492ff/Screenshot_2024-02-26_at_3.10.41_PM.png)

![Screenshot 2024-02-26 at 3.08.51 PM.png](DeepEdge_OpenCV_Resize%20b9f7fbb8e2d34b678543feda4e9492ff/Screenshot_2024-02-26_at_3.08.51_PM.png)

Overshooting of features/pixel values

Step 2
Time taken for 1000 iteration using INTER_NEAREST : 209.858 ms
Time taken for 1000 iteration using INTER_LINEAR : 291.626 ms
Time taken for 1000 iteration using INTER_CUBIC : 1074.37 ms

Step 3:

For simplicity I have converted the image to grayscale and then applied the following custom resize function.

![Screenshot 2024-02-26 at 10.45.21 PM.png](DeepEdge_OpenCV_Resize%20b9f7fbb8e2d34b678543feda4e9492ff/Screenshot_2024-02-26_at_10.45.21_PM.png)

![Screenshot 2024-02-26 at 10.44.59 PM.png](DeepEdge_OpenCV_Resize%20b9f7fbb8e2d34b678543feda4e9492ff/Screenshot_2024-02-26_at_10.44.59_PM.png)

![Screenshot 2024-02-26 at 10.44.47 PM.png](DeepEdge_OpenCV_Resize%20b9f7fbb8e2d34b678543feda4e9492ff/Screenshot_2024-02-26_at_10.44.47_PM.png)

Gray scale image forced the cubic interpolation to overshoot pixel values which is clearly seen above. My naive implementation is also under optimized. I am exploring a vectorized code  that may perform better but experienced too many errors.

Performance of my naive implementation :

Time taken for 1000 iteration using **custom** INTER_NEAREST : 5069.87 ms
Time taken for 1000 iteration using **custom** INTER_LINEAR : 10831.9 ms
Time taken for 1000 iteration using **custom** INTER_CUBIC : 493069 ms

Comparison

Time taken for 1000 iterations:

| Method | CV::RESIZE | CUSTOM RESIZE FUNCTION |
| --- | --- | --- |
| INTER_NEAREST | 209.858 ms | 5,069.87 ms |
| INTER_LINEAR | 291.626 ms | 10,831.9 ms |
| INTER_CUBIC | 1074.37 ms | 4,93,069 ms |

Observations:

1. INTER_NEAREST is the fastest interpolation method but also leads to very pixelated images and high contrast images.
2. INTER_CUBIC is the slowest interpolation method but leads to more smooth images but some overshooting/undershooting of pixel values can be observed leading to aliasing artifacts.
3. INTER_LINEAR though fails to capture sudden change in pixel values. Performance is mediocre.