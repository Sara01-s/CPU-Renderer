#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <picoPNG/src/picopng.hpp>
#include <fstream>
#include <exception>
#include <iostream>
#include <cstring>
#include <components/Physics.hpp>
#include <utility>
/*----------------------------------------------------------------------------------------*/


namespace VVE {

struct Entity_t {

    explicit Entity_t(std::string pngFile) {
        std::vector<unsigned char> pngPixels { };
        unsigned long outWidth { 0UL }, outHeight { 0UL };


        // ifstream is RAII (auto destroyed when out of scope)
        try {
			// using ifstream, "input file stream". C++ way of opening files. 
			// Because the file we want to open is a png and not a text file, 
			// we use ios::binary to get the bytes of the image
            std::ifstream file(pngFile.data(), std::ios::binary);

            std::vector<unsigned char> fileVector (
                std::istreambuf_iterator<char> { file }, // begin iterator
                std::istreambuf_iterator<char> { } // end iterator (istreambuf_iterator default constructor points to the end of the stream, aka "eof" (end of file))
            );
            //                              same as "&fileVector[0]"
            decodePNG(pngPixels, outWidth, outHeight, fileVector.data(), fileVector.size());
            //       ^            outputs           ^

            // Initialize entity using the decodePNG() outputs
            Name = pngFile.data();
            Width = outWidth;
            Height = outHeight;

            Sprite.reserve(pngPixels.size() / 4); // From uint32_t vector size to char vector size
            for (auto pngPixel = pngPixels.begin(); pngPixel != pngPixels.end(); pngPixel += 4) {
                uint32_t spritePixel =
                      static_cast<uint32_t> (*(pngPixel + 0)) << 16     // G
                    | static_cast<uint32_t> (*(pngPixel + 1)) << 8      // B  
                    | static_cast<uint32_t> (*(pngPixel + 2))           // A
                    | static_cast<uint32_t> (*(pngPixel + 3)) << 24;    // R
                Sprite.push_back(spritePixel);
            }

        }
        catch (...) {
            std::cout << "Tried to read PNG file but something failed. Check PNG format.\n";
        }
    }

    Entity_t& operator=(Entity_t other) {
        std::swap(Name, other.Name);
        std::swap(Physics, other.Physics);
        return *this;
    }

    bool operator==(std::nullptr_t) const { return false; }

    PhysicsComponent_t* Physics { nullptr };
    uint32_t Width  { 0 };
    uint32_t Height { 0 };

    std::vector<uint32_t> Sprite { };
    std::string Name { "new entity" };
};
    
} // namespace VVE
