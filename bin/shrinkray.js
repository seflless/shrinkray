#!/usr/bin/env node
var program = require('commander');
var fs = require('fs-extra');
var path = require('path');

program
  .option('-i, --input [input]', 'Input directory (ex. project/html)')
  .option('-o, --output [output]', 'The desired app path (ex. output/example.app)')
  .parse(process.argv);

// If no args were passed, print out help instructions
if( process.argv.length === 2 ) {
	program.help();
	process.exit(1);
}

if(!program.input){
	console.log("\nError: Input directory required");
	program.help();
	process.exit(1);
}
if(!program.output){
	console.log("\nError: Output path required");
	program.help();
	process.exit(1);
}

// Ensure output has .app extension
if( path.parse(program.output).ext !== ".app") {
	console.log("\nError: Output path requires '.app' extension");
	program.help();
	process.exit(1);
}

// Copy template to output location
var templateAppPath = path.resolve(__dirname, "../template/desktop.app");
var outputAppPath = path.resolve(program.output);
fs.copySync(templateAppPath, outputAppPath );

// Replace html content with supplied content
var outputAppHTMLPath = path.resolve(outputAppPath, "Contents/Resources/html");
fs.copySync(program.input, outputAppHTMLPath );

console.log("App generation complete. \n  " + outputAppPath);
