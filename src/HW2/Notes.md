# Notes on Best Practices for HW2 Project

member variables are always initialized in the order they are declared in the class, not the order you write them in the constructor's initializer list.

## Pointers

Every object that is passed as a pointer is always assumed to be owned by the caller, which means the lifetime is handled by the caller. The caller is responsible for managing the memory of this object pointer and destructing it once the once is over. [ref](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#i11-never-transfer-ownership-by-a-raw-pointer-t-or-reference-t)

Only use smart pointers when ownership transfer is intended. A function that does not manipulate lifetime should take raw pointers or references instead. [ref](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#f7-for-general-use-take-t-or-t-arguments-rather-than-smart-pointers)

### Functions

You want to return a pointer, almost always a unique_ptr if you are transferring an object from a hierarchy that is to be used in an interface. Using a unique_ptr is the cheapest way to transfer a pointer safely. [ref](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#f26-use-a-unique_ptrt-to-transfer-ownership-where-a-pointer-is-needed)

Functions should only return pointers if it is to indicate position. This is because the use case of handling empty collection positions is easily handled through the use of pointers. [ref](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#f42-return-a-t-to-indicate-a-position-only)
