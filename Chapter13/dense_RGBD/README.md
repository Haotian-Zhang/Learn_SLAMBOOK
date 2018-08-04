# pointCloud Mapping
## Description
### PointCloud (PCL)

基本和Chapter5点云见图方法类似
1. 在生成每帧点云时,去掉深度值太大或无效的点。这主要是考虑到 RGBD-camera 的有效量程,超过量程之后的深度值会有较大误差;
2. 利用统计滤波器方法去除孤立点。该滤波器统计每个点与它最近 N 个点的距离值的分布,去除距离均值过大的点。这样,我们保留了那些“粘在一起”的点,去掉了孤立的噪声点;
3. 最后,利用体素滤波器(Voxel Filter) 进行降采样。由于多个视角存在视野重叠,在重叠区域会存在大量的位置十分相近的点。这会无益地占用许多内存空间。体素滤波保证在某个一定大小的立方体(或称体素)内仅有一个点,相当于对三维空间进行了降采样,从而节省了很多存储空间。

### Octomap 

就是一种灵活的、压缩的、又能随时更新的地图形式: 八叉树。

假设我们在RGB-D 图像中观测到某个像素带有深度 d，这说明了一件事:我们在深度值对应的空间点上观察到了一个占据数据,并且，从相机光心出发,到这个点的线段上，应该是没有物体
的(否则会被遮挡)。利用这个信息，可以很好地对八叉树地图进行更新，并且能处理运动的结构。

## How to build the codes
### Build

```
mkdir build & cd build
cmake..
make -j
```

### Usage
```
cd ./build
./pointcloud_mapping
or
./octomap_mapping
```

## Results
经过统计外点去除之后,我们消去了这些噪声,使得整个地图变得更干净。另一方面,我们在体素滤波器中,把分辨率调至 0.01,表示每立方厘米有一个点。这是一个比较高的分辨率,所以在截图中我们感觉不出地图的差异,然而程序输出中可以看到点数明
显减少了许多(从 90 万个点减到了 44 万个点,去除了一半左右)。

The following figure are the point cloud map after filtering:

<div align="center">
<img src="https://github.com/Haotian-Zhang/Learn_SLAMBOOK/raw/master/Chapter13/dense_RGBD/map.png" height="300px" alt="depth" > 
</div>

The following figure are the octomap when voxel volume= 16:

<div align="center">
<img src="https://github.com/Haotian-Zhang/Learn_SLAMBOOK/raw/master/Chapter13/dense_RGBD/octomap.png" height="300px" alt="depth" > 
</div>
