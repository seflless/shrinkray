#!/bin/sh

# Clean last build
echo "Cleaning..."
rm -rf build
rm -rf template
mkdir -p template

# Build app
echo "Building desktop.app..."
/usr/bin/xcodebuild -target desktop -configuration Debug

# Copy app to template directory
echo "Copying to template..."
cd build/Debug/; zip -r -X ../../template/app.zip desktop.app
