//
//  main.m
//  WebView Finagler
//
//  Created by Mark Douma on 1/23/2013.
//  Copyright (c) 2013 Mark Douma. All rights reserved.
//

#import <Cocoa/Cocoa.h>

int main(int argc, char *argv[])
{
    /*
     * Procedural way enabling the webinspector so people can debug their 'desktop' applications.
     * Another way would be to have them use this terminal command instead:
     * https://developer.apple.com/library/content/documentation/AppleApplications/Conceptual/Safari_Developer_Guide/GettingStarted/GettingStarted.html#//apple_ref/doc/uid/TP40007874-CH2-SW1
     *
     * We need to do this as early in the app initialization as possible, or it doesn't get picked up, suggested via this thread:
     * https://stackoverflow.com/questions/695038/is-there-a-way-to-use-the-webkit-web-inspector-from-a-cocoa-webview-object#comment509019_695078
     */
    [[NSUserDefaults standardUserDefaults] setBool:TRUE forKey:@"WebKitDeveloperExtras"];
    [[NSUserDefaults standardUserDefaults] synchronize];

	return NSApplicationMain(argc, (const char **)argv);
}
