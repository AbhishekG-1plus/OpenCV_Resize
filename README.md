
# Custom_OpenCV_Resize_Function

## Step1
<img width="958" alt="Screenshot 2024-02-26 at 11 01 13 PM" src="https://github.com/AbhishekG-1plus/OpenCV_Resize/assets/77354191/99eb1772-b2e9-44ea-b825-c802780e6552">

<img width="959" alt="Screenshot 2024-02-26 at 11 00 31 PM" src="https://github.com/AbhishekG-1plus/OpenCV_Resize/assets/77354191/7bc0fa9b-89cd-4bd3-a853-817467b83a20">

<img width="956" alt="Screenshot 2024-02-26 at 11 00 16 PM" src="https://github.com/AbhishekG-1plus/OpenCV_Resize/assets/77354191/ea8ceab9-56d9-4ec2-b23e-1862714ada69">

<img width="959" alt="Screenshot 2024-02-26 at 10 59 25 PM" src="https://github.com/AbhishekG-1plus/OpenCV_Resize/assets/77354191/e4915294-2ffb-41e7-97bf-6ad59cfbcdd3">




## Step 2
```
Time taken for 1000 iteration using INTER_NEAREST : 209.858 ms
Time taken for 1000 iteration using INTER_LINEAR : 291.626 ms
Time taken for 1000 iteration using INTER_CUBIC : 1074.37 ms
```

## Step 3:

For simplicity I have converted the image to grayscale and then applied the following custom resize function.


<img width="958" alt="Screenshot 2024-02-26 at 11 04 17 PM" src="https://github.com/AbhishekG-1plus/OpenCV_Resize/assets/77354191/eceeea96-e296-47ed-be32-18d85da87d17">


<img width="957" alt="Screenshot 2024-02-26 at 11 03 49 PM" src="https://github.com/AbhishekG-1plus/OpenCV_Resize/assets/77354191/d2945706-f5ee-4481-a75b-a8893a3a6e65">

<img width="956" alt="Screenshot 2024-02-26 at 11 03 34 PM" src="https://github.com/AbhishekG-1plus/OpenCV_Resize/assets/77354191/deb8d1b2-2f4e-4105-914f-174ae6c4ee03">
Overshooting of features/pixel values. Gray scale image forced the cubic interpolation to overshoot pixel values which is clearly seen above. My naive implementation is also under optimized. I am exploring a vectorized code  that may perform better but experienced too many errors.

Performance of my naive implementation :

```
Time taken for 1000 iteration using **custom** INTER_NEAREST : 5069.87 ms
Time taken for 1000 iteration using **custom** INTER_LINEAR : 10831.9 ms
Time taken for 1000 iteration using **custom** INTER_CUBIC : 493069 ms
```

## Comparison

Time taken for 1000 iterations:

| Method | CV::RESIZE | CUSTOM RESIZE FUNCTION |
| --- | --- | --- |
| INTER_NEAREST | 209.858 ms | 5,069.87 ms |
| INTER_LINEAR | 291.626 ms | 10,831.9 ms |
| INTER_CUBIC | 1074.37 ms | 4,93,069 ms |

## Observations:

1. INTER_NEAREST is the fastest interpolation method but also leads to very pixelated images and high contrast images.
2. INTER_CUBIC is the slowest interpolation method but leads to more smooth images but some overshooting/undershooting of pixel values can be observed leading to aliasing artifacts.
3. INTER_LINEAR though fails to capture sudden change in pixel values. Performance is mediocre.
