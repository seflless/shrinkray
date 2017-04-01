//
//  MDAppDelegate.m
//  WebView Finagler
//
//  Created by Mark Douma on 1/23/2013.
//  Copyright (c) 2013 Mark Douma. All rights reserved.
//

#import "MDAppDelegate.h"
#import <WebKit/WebKit.h>


@implementation MDAppDelegate

+ (void)initialize {
    [[NSUserDefaults standardUserDefaults] registerDefaults:@{@"WebKitDeveloperExtras": @YES,
                                                              @"WebKitScriptDebuggerEnabled": @YES,
                                                              @"WebKitScriptProfilerEnabled": @YES}];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    NSString* filePath = [[NSBundle mainBundle] pathForResource:@"index"
                                                         ofType:@"html"
                                                    inDirectory:@"html"];
        
    NSURL* fileURL = [NSURL fileURLWithPath:filePath];
	NSURLRequest *request = [NSURLRequest requestWithURL:fileURL];

    
    NSLog(@"%@", filePath);
    
	[self.webView.mainFrame loadRequest:request];
}

@end
