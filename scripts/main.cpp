#include "image.hpp"

#include <filesystem>
#include <algorithm>

int main() {
    /*
    // car_1 handler object
    std::string car_1_file_path = "/home/alessio/workspace/greyscale-applier/original_images/car_1.ppm";
    ImageHandler c1(car_1_file_path);

    // generating a greyscale version of car_1
    std::string car_1_gs_file_path = "/home/alessio/workspace/greyscale-applier/modified_images/car_1_gs.ppm";
    c1.gen_gs_img(car_1_gs_file_path);

    // generating a blurred version of car_1
    std::string car_1_blr_file_path = "/home/alessio/workspace/greyscale-applier/modified_images/car_1_blr.ppm";
    c1.gen_blr_image(car_1_blr_file_path, 5);

    // -----------------------------------------------------------------------------------------

    // car_2 handler object
    std::string car_2_file_path = "/home/alessio/workspace/greyscale-applier/original_images/car_2.ppm";
    ImageHandler c2(car_2_file_path);

    // generating a greyscale version of car_2
    std::string car_2_gs_file_path = "/home/alessio/workspace/greyscale-applier/modified_images/car_2_gs.ppm";
    c2.gen_gs_img(car_2_gs_file_path);

    // generating a blurred version of car_2
    std::string car_2_blr_file_path = "/home/alessio/workspace/greyscale-applier/modified_images/car_2_blr.ppm";
    c2.gen_blr_image(car_2_blr_file_path, 5);

    // -----------------------------------------------------------------------------------------

    // borabora_1 handler object
    std::string borabora_1_file_path = "/home/alessio/workspace/greyscale-applier/original_images/borabora_1.ppm";
    ImageHandler b1(borabora_1_file_path);

    // generating a greyscale version of borabora_1
    std::string borabora_1_gs_file_path = "/home/alessio/workspace/greyscale-applier/modified_images/borabora_1_gs.ppm";
    b1.gen_gs_img(borabora_1_gs_file_path);

    // generating a blurred version of borabora_1
    std::string borabora_1_blr_file_path = "/home/alessio/workspace/greyscale-applier/modified_images/borabora_1_blr.ppm";
    b1.gen_blr_image(borabora_1_blr_file_path, 5);

    // -----------------------------------------------------------------------------------------

    // borabora_2 handler object
    std::string borabora_2_file_path = "/home/alessio/workspace/greyscale-applier/original_images/borabora_2.ppm";
    ImageHandler b2(borabora_2_file_path);

    // generating a greyscale version of borabora_2
    std::string borabora_2_gs_file_path = "/home/alessio/workspace/greyscale-applier/modified_images/borabora_2_gs.ppm";
    b2.gen_gs_img(borabora_2_gs_file_path);

    // generating a blurred version of borabora_2
    std::string borabora_2_blr_file_path = "/home/alessio/workspace/greyscale-applier/modified_images/borabora_2_blr.ppm";
    b2.gen_blr_image(borabora_2_blr_file_path, 5);

    // -----------------------------------------------------------------------------------------

    // post_1 handler object
    std::string post_1_file_path = "/home/alessio/workspace/greyscale-applier/original_images/post_1.ppm";
    ImageHandler p1(post_1_file_path);

    // generating a greyscale version of post_1
    std::string post_1_gs_file_path = "/home/alessio/workspace/greyscale-applier/modified_images/post_1_gs.ppm";
    p1.gen_gs_img(post_1_gs_file_path);

    // generating a blurred version of post_1
    std::string post_1_blr_file_path = "/home/alessio/workspace/greyscale-applier/modified_images/post_1_blr.ppm";
    p1.gen_blr_image(post_1_blr_file_path, 5);

    // -----------------------------------------------------------------------------------------

    // post_2 handler object
    std::string post_2_file_path = "/home/alessio/workspace/greyscale-applier/original_images/post_2.ppm";
    ImageHandler p2(post_2_file_path);

    // generating a greyscale version of post_2
    std::string post_2_gs_file_path = "/home/alessio/workspace/greyscale-applier/modified_images/post_2_gs.ppm";
    p2.gen_gs_img(post_2_gs_file_path);

    // generating a blurred version of post_2
    std::string post_2_blr_file_path = "/home/alessio/workspace/greyscale-applier/modified_images/post_2_blr.ppm";
    p2.gen_blr_image(post_2_blr_file_path, 5);
    */

    // string containing path to original images directory
    std::string original_path = "/home/alessio/workspace/greyscale-applier/original_images";

    // vector where to store the paths to the original images
    std::vector<std::string> org_imgs_path;

    // iterating through the file paths in the original files directory
    // and saving them to the vector
    using rec_dir_it = std::filesystem::recursive_directory_iterator;
    for (const auto& entry : rec_dir_it(original_path)) {
        org_imgs_path.push_back(entry.path().string());
    }

    // sorting the paths alphabetically
    std::sort(org_imgs_path.begin(), org_imgs_path.end());

    // where to store the names of the modified images
    std::vector<std::string> modified_names;

    // taking each directory in reverse and taking the file_name, reversing it
    // and creating a new file with the edited stuff
    // iterating through the original files names
    for (auto it = org_imgs_path.begin(); it != org_imgs_path.end(); ++it) {
        std::string tmp_string = *it;
        
    }

}