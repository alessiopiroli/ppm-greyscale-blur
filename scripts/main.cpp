#include "image.hpp"

int main() {
    std::string file_path = "/home/alessio/workspace/greyscale-applier/true_color_images/house_1.ppm";
    ImageHandler fp(file_path);
    // fp.print_content();
    std::cout << "Magic number: " << fp.get_magic_number() << std::endl;
}