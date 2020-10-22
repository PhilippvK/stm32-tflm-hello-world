# Hello World Example

This demo is a simple Neural Network powered estimator for the values of the *sin* function at different points. We represent this as a floating 'ball', which glides around a sine shaped trajectory.

## Build
```
mkdir build
cd build
cmake -DTF_COMMIT=37c2bf5016fcbed261476386eced503e907cdc01 ..
make
make flash
```
For more details about build instruction, see [the main README](../../README.md).

You might have to run ```make flash``` several times if you get a deployment error.

### Rebuilding the project
It is mandatory to delete ```CMakeCache.txt``` before re-building your project. Moreover, you should delete the *_deps* folder under *build* before running ```cmake ..``` again.
