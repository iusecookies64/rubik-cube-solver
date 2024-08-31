set -e

echo "Building the project..."

cmake -S . -B ./build

make -C ./build

echo "Build Successful! Running..."

./build/RubiksCubeSolver