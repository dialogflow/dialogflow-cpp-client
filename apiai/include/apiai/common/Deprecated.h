/**
 * Copyright 2017 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef DEPRECATED_H
#define DEPRECATED_H

//#include <type_info>

#ifdef __GNUC__
    #define DEPRECATED __attribute__ ((deprecated))
#elif defined(_MSC_VER)
    #define DEPRECATED __declspec(deprecated)
#else
    #define DEPRECATED
    #pragma warning("DEPRECATED is not defined")
#endif

#ifdef __GNUC__
    #define PUSH_DEPRECATED_WARNING() \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")

    #define POP_DEPRECATED_WARNING() \
        _Pragma("GCC diagnostic pop")
#elif defined(_MSC_VER)
    #define PUSH_DEPRECATED_WARNING() \
        __pragma(warning( push, 0 )) \
        __pragma(warning( disable: warning-code, 0 ))

    #define POP_DEPRECATED_WARNING() \
        __pragma(warning( pop ))
#else
    #define PUSH_DEPRECATED_WARNING()
    #define POP_DEPRECATED_WARNING()

    #pragma warning("PUSH_DEPRECATED_WARNING and POP_DEPRECATED_WARNING is not defined")
#endif

#define IGNODE_DEPRECATED_WARNING(__CODE__) \
    PUSH_DEPRECATED_WARNING() \
    __CODE__ \
    POP_DEPRECATED_WARNING()

#endif // DEPRECATED_H
