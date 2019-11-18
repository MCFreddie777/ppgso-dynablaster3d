#include <fstream>
#include <sstream>

#include "image.h"

namespace ppgso {
    namespace image {
        
        Image loadRAW(const std::string &raw, int width, int height) {
            Image image{width, height};
            auto &framebuffer = image.getFramebuffer();
            
            // Open file stream
            std::ifstream image_stream(raw, std::ios::binary);
            
            if (!image_stream.is_open()) {
                std::stringstream msg;
                msg << "Could not open image " << raw;
                throw std::runtime_error(msg.str());
            }
            
            // Load the resources
            image_stream.read((char *) framebuffer.data(),
                              framebuffer.size() * sizeof(Image::Pixel));
            image_stream.close();
            return image;
        }
        
        void saveRAW(Image &image, const std::string &raw) {
            std::ofstream image_stream(raw, std::ios::binary);
            
            if (!image_stream.is_open()) {
                std::stringstream msg;
                msg << "Could not open image " << raw;
                throw std::runtime_error(msg.str());
            }
            
            auto &framebuffer = image.getFramebuffer();
            
            // Save the resources
            image_stream.write((char *) framebuffer.data(),
                               static_cast<std::streamsize>(framebuffer.size() *
                                                            sizeof(Image::Pixel)));
            image_stream.close();
        }
        
    }
}
