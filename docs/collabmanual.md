
### Repository Managing
Write good git commit messages,  see [ref](https://cbea.ms/git-commit/) for instructions.

### Coding
Write good comments
Don't be too concerned about the rules of the form

### Implementation Preference Restriction

targets to wrap are listed below
Basic Type
- integer: 32/64/more bit
- bool:
- char: multilingual
- string: multilingual
- floating-point number: 32/64/more bit
- pointer: naked, std::unique_ptr, std::shared_ptr, std::weak_ptr.
- reference: ?
Compound Type
- vector2D, 3D, 4D: each component type
- constant array, variable arrary: random access, forward/backward
- dictionary (as well as other data structure no need for now)

If not planning to rewrite it now, at least use `using A = B` to reserve room for future changes.



### Project Developing
Build Makefile: in `Parallaria/code` folder use `cmake -B build -G "MinGW Makefiles"`
Compile Project: after building makefiles, in `Parallaria` folder use `cmake --build build`