#include "image.hpp"

#include <filesystem>
#include <algorithm>

int main() {
    
    // car_1 handler object
    std::string car_1_file_path = "/.../original_images/car_1.ppm";
    ImageHandler c1(car_1_file_path);

    // generating a greyscale version of car_1
    std::string car_1_gs_file_path = "/.../modified_images/car_1_gs.ppm";
    c1.gen_gs_img(car_1_gs_file_path);

    // generating a blurred version of car_1
    std::string car_1_blr_file_path = "/.../modified_images/car_1_blr.ppm";
    c1.gen_blr_image(car_1_blr_file_path, 3);

}