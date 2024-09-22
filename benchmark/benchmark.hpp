#pragma once

/**
 * @file
 * @author Krusto Stoyanov ( k.stoianov2@gmail.com )
 * @brief 
 * @version 1.0
 * @date 
 * 
 * @section LICENSE
 * MIT License
 * 
 * Copyright (c) 2024 Krusto
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * @section DESCRIPTION
 * 
 * Benchmark Class
 */


/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "timer.hpp"
#include <chrono>
#include <functional>
#include <iostream>
#include <string_view>

/***********************************************************************************************************************
Benchmark Class
***********************************************************************************************************************/

class Benchmark
{
public:
    static void Run(std::string_view Name, std::function<void()> func, uint32_t iterations = 1u)
    {
        std::cout << "\nRunning " << std::string(Name.data()) << " benchmark\n";
        {
            Timer timer;
            for (size_t i = 0; i < iterations; i++) { func(); }
            timer.Stop();
            std::cout << "\nIterated " << iterations << " times\n";
            std::cout << "Total Elapsed Time: " << timer.ElapsedMilliseconds() << "ms(" << timer.ElapsedSeconds()
                      << "s)" << std::endl;
            std::cout << "Elapsed time for 1 iteration: " << timer.ElapsedMilliseconds() / ((float) iterations) << "ms("
                      << timer.ElapsedSeconds() / ((float) iterations) << "s)" << std::endl;
        }
    }
};
