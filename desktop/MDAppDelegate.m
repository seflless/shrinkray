//
//  MDAppDelegate.m
//  WebView Finagler
//
//  Created by Mark Douma on 1/23/2013.
//  Copyright (c) 2013 Mark Douma. All rights reserved.
//

#import "MDAppDelegate.h"
#import <WebKit/WebKit.h>
#import "tiny.h"

@implementation MDAppDelegate

pid_t serverPid;

+ (void)initialize {
    [[NSUserDefaults standardUserDefaults] registerDefaults:@{@"WebKitDeveloperExtras": @YES,
                                                              @"WebKitScriptDebuggerEnabled": @YES,
                                                              @"WebKitScriptProfilerEnabled": @YES}];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    
    // Get an available port
    int port = getPort();
    printf("port number %d\n", port);
    
    // Start basic http file server that hosts every file in Resources/html
        // Get main bundle's 'Resources' directory
    NSString* resourceDirectory = [[NSBundle mainBundle] resourcePath];
        // Add 'html' path to it for the actual html files directory
    NSString* htmlDirectory = [resourceDirectory stringByAppendingString:@"/html"] ;
    char* directory = [htmlDirectory cStringUsingEncoding:NSUTF8StringEncoding];
    printf(directory);
    NSLog(@"\n\nServing files in directory: \n%@\n\n", htmlDirectory);
        // Start actual static file hosting server. Save the server's forked process pid so we can force kill it on exit
    serverPid = serveFiles(directory, port);
    
    // Now load the wrapped website the webview
        // Create home page url using our dynamically selected port
    NSString* urlString = [NSString stringWithFormat:@"http://localhost:%d", port];
        // Convert string to a proper URL structure
    NSURL* fileURL = [NSURL URLWithString:urlString];
        // Tell the webview itself to load the url
	NSURLRequest *request = [NSURLRequest requestWithURL:fileURL];
	[self.webView.mainFrame loadRequest:request];
}

- (void)applicationWillTerminate:(NSNotification *)notification{
    // Kill the main file server process
    kill(serverPid, SIGTERM);
}



@end
