#include <iostream>
#include <limits.h>
#include <memory>
#include <string>
#include <thinks/ppm.hpp>
#include <ifm3d/camera.h>
#include <ifm3d/fg.h>
#include <ifm3d/simpleimage.h>


using namespace std;


void write_XYZLight_File(ifm3d::SimpleImageBuffer::Img &input, ifm3d::SimpleImageBuffer::Img &input2)
{

	ofstream fout;
	fout.open("data.bin", ios::binary);

	//	for (int index = 0; index < input.width * input.height; index++)	{
	auto index = size_t{ 0 };
	for (auto col = size_t{ 0 }; col < input.height; ++col) {
		for (auto row = size_t{ 0 }; row < input.width; ++row) {

			struct temp {
				int16_t x, y, z, light;
			} temp;

			temp.z = *((int16_t*)(input.data.data()) + (index * 3));
			temp.x = *((int16_t*)(input.data.data()) + (index * 3 + 1));
			temp.y = *((int16_t*)(input.data.data()) + (index * 3 + 2));
			temp.light = *((int16_t*)(input2.data.data()) + (index));

			fout.write(reinterpret_cast<char *>(&temp), sizeof(temp));
			/*
			if (row >= 170) {
				std::cerr << "i,j : " << col << ", " << row << "["
					<< *((int16_t*)(input.data.data()) + (index * 3))
					<< "/" << *((int16_t*)(input.data.data()) + (index * 3 + 1))
					<< "/" << *((int16_t*)(input.data.data()) + (index * 3 + 2))
					<< "]" << std::endl;
			}
//	*/
			++index;
		}
	}

	fout.close();

}



int main(int argc, const char **argv)
{
	auto cam = ifm3d::Camera::MakeShared("192.168.0.69");

	ifm3d::SimpleImageBuffer::Ptr img = std::make_shared<ifm3d::SimpleImageBuffer>();
	ifm3d::FrameGrabber::Ptr fg =
		std::make_shared<ifm3d::FrameGrabber>(
			cam, ifm3d::IMG_AMP | ifm3d::IMG_CART | ifm3d::IMG_RDIS);

	if (!fg->WaitForFrame(img.get(), 1000))
	{
		std::cerr << "Timeout waiting for camera!" << std::endl;
		return -1;
	}

	std::cerr << " 0) " << std::endl;

	cam->ForceTrigger();

	ifm3d::SimpleImageBuffer::Img amplitude = img->AmplitudeImage();
	ifm3d::SimpleImageBuffer::Img xyz = img->XYZImage();

	std::cerr << " 1) " << std::endl;

	write_XYZLight_File(xyz, amplitude);


	std::cout << "Done with simpleimage ppmio example" << std::endl;
	return 0;



}








