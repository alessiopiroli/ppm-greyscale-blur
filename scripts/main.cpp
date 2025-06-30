#include "image.hpp"

int main() {
    std::string file_path = "/home/alessio/workspace/greyscale-applier/true_color_images/house_1.ppm";
    ImageHandler fp(file_path);
    // fp.print_content();
    std::cout << "Magic number: " << fp.get_magic_number() << std::endl;
    std::cout << "Width: " << fp.get_width() << std::endl;
    std::cout << "Height: " << fp.get_height() << std::endl;
    std::cout << "Max color value: " << fp.get_max_color() << std::endl;
    std::cout << "Tot number of bytes: " << fp.get_num_bytes() << std::endl;
}