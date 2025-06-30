#include "image.hpp"

#include <cassert>

int main() {
    std::string file_path = "/home/alessio/workspace/greyscale-applier/true_color_images/house_1.ppm";
    ImageHandler fp(file_path); // creating new image
    // fp.print_img_data();

    std::string gs_file_path = "/home/alessio/workspace/greyscale-applier/true_color_images/house_1_gs.ppm";
    fp.gen_gs_img(gs_file_path);
}