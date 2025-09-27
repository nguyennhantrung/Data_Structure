   //////////////////////////////////////////////////////////////////////////////////////////////
   /*
 Lets implement a custom vector data structure that store std::uint32_t elements:
 1. Define generic interface IVector which has the following methods:
   - `push_back`: add a new element at the end
   - `pop_back`: delete last element then return last element
   - `operator[]`: access element by index
   - `size_bytes`: get size of data stored in vector (in bytes)
 2. Define and implement concrete class `MyVector` that implements the IVector
   - Memory shall be dynamically allocated using malloc()
 3. Extend the implementation such that our Vector can store other data types
*/