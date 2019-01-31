#include <ppl.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <commonMacro.h>
#include <OpencvCommon.h>
using namespace concurrency;


__global__
void saxpy(int n, float a, float *x, float *y)
{
	int i = blockIdx.x*blockDim.x + threadIdx.x;
	if (i < n) y[i] = a*x[i] + y[i];
}

__global__
void filter(int width, int height, int channel, unsigned char *src, unsigned char *dst)
{
	int r = blockIdx.y * blockDim.y + threadIdx.y;
	int c = blockIdx.x * blockDim.x + threadIdx.x;
	if (r < height && c < width)
	{
		int colorIdx = (r*width + c) * channel;
		dst[colorIdx] = src[colorIdx];
		dst[colorIdx + 1] = src[colorIdx + 1];
		dst[colorIdx + 2] = src[colorIdx + 2];
	}
}


int main(void)
{
	cv::Mat img = cv::imread("IMG_1772.jpg");
	cv::Mat dstImg(img.size(), img.type());

	unsigned char *d_src, *d_dst;
	int elementN = img.cols * img.rows * img.channels();
	cudaMalloc(&d_src, elementN * sizeof(unsigned char));
	cudaMalloc(&d_dst, elementN * sizeof(unsigned char));

	cudaMemcpy(d_src, img.data, elementN * sizeof(unsigned char), cudaMemcpyHostToDevice);
	dim3 dimBlock(32, 32);
	dim3 dimGrid(std::ceil(img.cols / dimBlock.x),
				 std::ceil(img.rows / dimBlock.y));
	HL_INTERVAL_START;
	filter << < dimGrid, dimBlock >> > (img.cols, img.rows, img.channels(), d_src, d_dst);
	HL_INTERVAL_ENDSTR("CUDA IMAGE FILTER");

	HL_INTERVAL_START;
	cudaMemcpy(dstImg.data, d_dst, elementN * sizeof(unsigned char), cudaMemcpyDeviceToHost);
	HL_INTERVAL_ENDSTR("CUDA IMAGE COPY");

	int w = img.cols, h = img.rows, channel = img.channels();
	int colorW = w * channel;
	HL_INTERVAL_START;
	for (size_t i = 0, r = 0; i < w; i++, r += colorW)
	{
		for (size_t j = 0, c = 0; j < h; j++, c+= 3)
		{
			memcpy(dstImg.data + r + c, img.data + r + c, 3);
		}
	}
	HL_INTERVAL_ENDSTR("CPU IMAGE COPY");

	HL_INTERVAL_START;
	parallel_for(size_t(0), size_t(w), [&](size_t i)
	{
		int r = colorW * i;
		for (size_t j = 0, c = 0; j < h; j++, c += 3)
		{
			memcpy(dstImg.data + r + c, img.data + r + c, 3);
		}
	});
	/*memcpy_s(dstImg.data, elementN * sizeof(unsigned char),
			 img.data, elementN * sizeof(unsigned char));*/
	HL_INTERVAL_ENDSTR("CPU-Paralleled IMAGE COPY");

	/*HL_INTERVAL_START;
	img.copyTo(dstImg);
	HL_INTERVAL_ENDSTR("CV-CPU IMAGE COPY");*/

	HL_INTERVAL_START;
	int numTest = 1 << 20;
	std::vector<float> v1(numTest), v2(numTest);
	for (int i = 0; i < numTest; i++)
	{
		v1[i] = i;
		v2[i] = i;
	}
	HL_INTERVAL_ENDSTR("RELEASE-DEBUG TEST");

	cv::imshow("result", dstImg);
	cv::waitKey(0);

	cudaFree(d_src);
	cudaFree(d_dst);
	
}