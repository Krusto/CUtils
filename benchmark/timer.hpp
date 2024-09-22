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
 * Timer Class
 */


/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include <chrono>
#include <iostream>

/***********************************************************************************************************************
Timer Class
***********************************************************************************************************************/

class Timer
{
public:
    Timer()
    {
        m_StartTime = std::chrono::system_clock::now();
        m_bRunning = true;
    }

    ~Timer()
    {
        m_EndTime = std::chrono::system_clock::now();
        m_bRunning = false;
    }

    inline double ElapsedMilliseconds()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime;

        if (m_bRunning) { endTime = std::chrono::system_clock::now(); }
        else { endTime = m_EndTime; }

        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
    }

    inline double ElapsedSeconds() { return ElapsedMilliseconds() / 1000.0; }

    inline void Stop()
    {
        m_EndTime = std::chrono::system_clock::now();
        m_bRunning = false;
    }

    inline void StopAndLog()
    {
        Stop();
        std::cout << "Elapsed time:" << ElapsedMilliseconds() << "ms(" << ElapsedSeconds() << "s)" << std::endl;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool m_bRunning = false;
};
