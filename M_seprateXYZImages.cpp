
void seprateXYZImages(ifm3d::SimpleImageBuffer::Img &input, ifm3d::SimpleImageBuffer::Img &X, ifm3d::SimpleImageBuffer::Img &Y, ifm3d::SimpleImageBuffer::Img &Z)
{
	X.width = Y.width = Z.width = input.width;
	X.height = Y.height = Z.height = input.height;
	X.format = Y.format = ifm3d::pixel_format::FORMAT_16S;
	Z.format = ifm3d::pixel_format::FORMAT_16U;
	X.data.resize(input.width*input.height * sizeof(int16_t));
	Y.data.resize(input.width*input.height * sizeof(int16_t));
	Z.data.resize(input.width*input.height * sizeof(uint16_t));

//	for (int index = 0; index < input.width * input.height; index++)	{
	auto index = size_t{ 0 };
	for (auto col = size_t{ 0 }; col < input.height; ++col) {
		for (auto row = size_t{ 0 }; row < input.width; ++row) {

			*((int16_t*)(X.data.data()) + index) = *((int16_t*)(input.data.data()) + (index * 3));
			*((int16_t*)(Y.data.data()) + index) = *((int16_t*)(input.data.data()) + (index * 3 + 1));
			*((uint16_t*)(Z.data.data()) + index) = *((uint16_t*)(input.data.data()) + (index * 3 + 2));

			std::cerr << "i,j : " << col << ", " << row << "["
				<< *((int16_t*)(input.data.data()) + (index * 3))
				<< "/" << *((int16_t*)(input.data.data()) + (index * 3 + 1))
				<< "/" << *((uint16_t*)(input.data.data()) + (index * 3 + 2))
				<< "]" << std::endl;

			++index;
		}
	}
}
