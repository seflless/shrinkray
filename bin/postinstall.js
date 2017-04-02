#!/usr/bin/env node
var execSync = require('child_process').execSync;
var path = require('path');
var templateFolder = path.resolve(__dirname, '../template');

execSync('unzip ' + templateFolder + '/app.zip -d ' + templateFolder);
