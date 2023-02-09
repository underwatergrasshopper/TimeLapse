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
* @version 0.2.0
*/

#ifndef TIMELAPSE_H_
#define TIMELAPSE_H_

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN 

//------------------------------------------------------------------------------
// Example 1
//------------------------------------------------------------------------------

// TimeLapseF64 tl;
// 
// tl.Start();
// //... code ...
// tl.Stop();
// 
// printf("%fs\n", tl.Get());

//------------------------------------------------------------------------------
// Example 2
//------------------------------------------------------------------------------

// TimeLapseF64 tl;
// 
// tl.Reset();
// while (true) {
//     // ... code ...
//     tl.Update();
// 
//     printf("%fs\n", tl.Get());
// }

//==============================================================================
// Declarations
//==============================================================================

/** Measures difference in seconds between two points in code. */
template <typename Type>
class TimeLapse {
public:
    TimeLapse();

    virtual ~TimeLapse();

    /**
    Starts measuring time.
    */
    void Start();

    /**
    Stops measuring time. 
    Measured time difference can be obtained by calling Get method.
    */
    void Stop();

    /**
    Stops measuring time, only if difference between Start and TryStopIfAbove would be above time_lapse. Returns true then.
    Otherwise does nothing and returns false.
    Measured time difference can be obtained by calling Get method.
    @param time_lapse             Time in seconds.
    */
    bool StopIfAbove(const Type& time_lapse);

    /**
    Measures difference between Reset and Update or between previous Update and this Update.
    Measured time difference can be obtained by calling Get method.
    */
    void Update();

    /**
    Measures difference between Reset and TryUpdateIfAbove or between previous Update/TryUpdateIfAbove and this TryUpdateIfAbove, 
    only if measured time would be above time_lapse. Then returns true.
    Otherwise does nothing and returns false.
    Measured time difference can be obtained by calling Get method.
    @param time_lapse             Time in seconds.
    */
    bool UpdateIfAbove(const Type& time_lapse);

    /**
    Starts measuring time. Sets Stop point to be the same as Start point.
    */
    void Reset();

    /** 
    @return Time difference in seconds.
    */
    Type Get() const;

private:
    LARGE_INTEGER           m_begin;
    LARGE_INTEGER           m_end;
    Type                    m_diff;         ///< Time in seconds.

    static LARGE_INTEGER    sm_freq;
};

using TimeLapseF32 = TimeLapse<float>;
using TimeLapseF64 = TimeLapse<double>;

//==============================================================================
// Definitions
//==============================================================================

template <typename Type>
LARGE_INTEGER TimeLapse<Type>::sm_freq = [](){
    LARGE_INTEGER freq;
    // Quote from MSDN: "The frequency of the performance counter is fixed at system boot and is consistent across all processors."
    QueryPerformanceFrequency(&freq); 
    return freq;
}();


template <typename Type>
inline TimeLapse<Type>::TimeLapse() {
    m_end = m_begin = {};
    m_diff = Type();
}

template <typename Type>
inline TimeLapse<Type>::~TimeLapse() {

}

template <typename Type>
inline void TimeLapse<Type>::Start() {
    QueryPerformanceCounter(&m_begin);
}

template <typename Type>
inline void TimeLapse<Type>::Stop() {
    QueryPerformanceCounter(&m_end);
    m_diff = Type(m_end.QuadPart - m_begin.QuadPart) / sm_freq.QuadPart;
}

template <typename Type>
inline bool TimeLapse<Type>::StopIfAbove(const Type& time_lapse) {
    LARGE_INTEGER end;
    QueryPerformanceCounter(&end);

    const Type diff = Type(end.QuadPart - m_begin.QuadPart) / sm_freq.QuadPart;

    if (diff > time_lapse) {
        m_end = end;
        m_diff = diff;

        return true;
    }
    return false;
}

template <typename Type>
inline void TimeLapse<Type>::Update() {
    Stop();
    m_begin = m_end;
}

template <typename Type>
inline bool TimeLapse<Type>::UpdateIfAbove(const Type& time_lapse) {
    if (StopIfAbove(time_lapse)) {
        m_begin = m_end;

        return true;
    }
    return false;
}

template <typename Type>
inline void TimeLapse<Type>::Reset() {
    Start();
    m_end = m_begin;
    m_diff = 0;
}

template <typename Type>
inline Type TimeLapse<Type>::Get() const { 
    return m_diff; 
} 


#endif // TIMELAPSE_H_
