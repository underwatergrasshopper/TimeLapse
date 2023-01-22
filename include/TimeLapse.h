////////////////////////////////////////////////////////////////////////////////
// MIT License
// 
// Copyright (c) 2023 underwatergrasshopper
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

/**
* @file TimeLapse.h
* @author underwatergrasshopper
* @version 0.1.0
*/

#ifndef TIMELAPSE_H_
#define TIMELAPSE_H_

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN 

/** Measures difference in seconds between two points in code. */
class TimeLapse {
public:
    TimeLapse() {
        m_end = m_begin = {};
        m_diff = 0;

        // Quote from MSDN: "The frequency of the performance counter is fixed at system boot and is consistent across all processors."
        QueryPerformanceFrequency(&m_freq); 
    }

    virtual ~TimeLapse() {}

    void Start() {
        QueryPerformanceCounter(&m_begin);
    }

    void Stop() {
        QueryPerformanceCounter(&m_end);
        m_diff = double(m_end.QuadPart - m_begin.QuadPart) / m_freq.QuadPart;
    }

    void Update() {
        Stop();
        m_begin = m_end;
    }

    void Reset() {
        Start();
        m_end = m_begin;
        m_diff = 0;
    }

    /** 
        @return Time difference in seconds:
            between Start method call and Stop method call,
            between Reset method call and Update method call,
            between two last Update method calls.
    */
    double Get() const { return m_diff; } 

private:
    LARGE_INTEGER           m_begin;
    LARGE_INTEGER           m_end;
    double                  m_diff;         ///< Time in seconds.

    LARGE_INTEGER           m_freq;
};

// --- Example 1 --- //
// TimeLapse tl;
// tl.Start();
// ... code ...
// tl.Stop();
// printf("%fs\n", tl.Get());

// --- Example 2 --- //
// TimeLapse tl;
// tl.Reset();
// while (true) {
//     ... code ...
//     tl.Update();
//     printf("%fs\n", ettlGet());
// }

#endif // TIMELAPSE_H_
