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
cd build/Debug/;
	# Copy desktop.app to templates folder
cp -R desktop.app ../../template/
	# Make a zip of it too for publishing distribution
zip -r -X ../../template/app.zip desktop.app
