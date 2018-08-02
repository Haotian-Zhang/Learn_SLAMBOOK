# Dense-Monocular Mapping
## Description

1. 假设所有像素的深度满足某个初始的高斯分布;
2. 当新数据产生时,通过极线搜索和块匹配确定投影点位置;
3. 根据几何关系计算三角化后的深度以及不确定性;
4. 将当前观测融合进上一次的估计中。若收敛则停止计算,否则返回

## How to run the codes
### Build

```
mkdir build & cd build
cmake..
make -j
```

### Usage

```
cd ./build
./dense_mapping ../test_data/
```

## Results

You will see the map get denser and denser when the loop number increases. For simplicty, the datasets only contain 10 images and a .txt file contains poses correspongding to specific images. The following figure shows the images at loop 4 and loop 9.
<div align="center">
<img src="https://github.com/Haotian-Zhang/Learn_SLAMBOOK/raw/master/Chapter13/dense_monocular/4.png" height="300px" alt="depth" > 
<img src="https://github.com/Haotian-Zhang/Learn_SLAMBOOK/raw/master/Chapter13/dense_monocular/10.png" height="300px" alt="depth" > 
</div>

## Supply Materials

双线性内插值算法描述如下:

　　对于一个目的像素，设置坐标通过反向变换得到的浮点坐为 $$(i+u,j+v)$$ (其中 $i$ 、$j$ 均为浮点坐标的整数部分，$$u$$ 、$$v$$ 为浮点坐标的小数部分，是取值 [0,1) 区间的浮点数)，则这个像素得值 $f(i+u,j+v)$ 可由原图像中坐标为 $(i,j)$ 、$(i+1,j)$ 、$(i,j+1)$ 、$(i+1,j+1)$ 所对应的周围四个像素的值决定，即：
  
<a href="https://www.codecogs.com/eqnedit.php?latex=f(i&plus;u,j&plus;v)&space;=&space;(1-u)(1-v)f(i,j)&space;&plus;&space;(1-u)vf(i,j&plus;1)&space;&plus;&space;u(1-v)f(i&plus;1,j)&space;&plus;&space;uvf(i&plus;1,j&plus;1)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?f(i&plus;u,j&plus;v)&space;=&space;(1-u)(1-v)f(i,j)&space;&plus;&space;(1-u)vf(i,j&plus;1)&space;&plus;&space;u(1-v)f(i&plus;1,j)&space;&plus;&space;uvf(i&plus;1,j&plus;1)" title="f(i+u,j+v) = (1-u)(1-v)f(i,j) + (1-u)vf(i,j+1) + u(1-v)f(i+1,j) + uvf(i+1,j+1)" /></a>

其中f(i,j)表示源图像 $(i,j)$ 处的的像素值，以此类推，详情可见下图:

<div align="center">
<img src="https://github.com/Haotian-Zhang/Learn_SLAMBOOK/raw/master/Chapter13/dense_monocular/20131216232218953.png" height="300px" alt="depth" > 
</div>