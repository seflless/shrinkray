//
//  MDAppDelegate.h
//  WebView Finagler
//
//  Created by Mark Douma on 1/23/2013.
//  Copyright (c) 2013 Mark Douma. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class WebView;


@interface MDAppDelegate : NSObject <NSApplicationDelegate>

@property (weak) IBOutlet WebView *webView;
@property (assign) IBOutlet NSWindow *window;

@end
