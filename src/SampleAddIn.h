/*
 *  Modern Native AddIn
 *  Copyright (C) 2018  Infactum
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 *  (c) Popeless
 *  Added Image Magick lib and auto orient method
 *  Delete all others methods
 *  Libs in pragma comments, need to be in SampleAddIn.lib folder
 *  (taken from image magick setup folder)
 *  This lib needs to compile in Release mod
 *
 *  Big Thanx to Infactum for this template!
 * 
 * ******************************************************************************
 *  Redisigned for test Image Magick
 *  Added libs (without them it didn't work
 *  Added ifstream to test binary images (not completed)
 *  
 *  This code might compile without errors only in release mode. 
 *  If you want to debug it correctly, you must compile all libs by yourself
 *  Webpage for answer:
 *  legacy.imagemagick.org/discourse-server/viewtopic.php?t=13970
 *
 * ******************************************************************************
 */

// 
#pragma comment(lib, "CORE_RL_Magick++_.lib")
#pragma comment(lib, "CORE_RL_MagickCore_.lib")
#pragma comment(lib, "CORE_RL_MagickWand_.lib")

#ifndef SAMPLEADDIN_H
#define SAMPLEADDIN_H

#include "Component.h"

#include <Magick++.h>

class SampleAddIn final : public Component {
public:
    const char *Version = u8"1.0.0";

    SampleAddIn();

private:
    std::string extensionName() override;

    variant_t samplePropertyValue();

    std::shared_ptr<variant_t> sample_property;

    void AutoOrient(const variant_t &picture_path);
};

#endif //SAMPLEADDIN_H
