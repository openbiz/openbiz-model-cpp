//
//  AppDelegate.m
//  openbizRestfulTest
//
//  Created by Jixian Wang on 14-10-1.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#import "AppDelegate.h"
#include "UserInfo.h"

@interface AppDelegate ()

@property (weak) IBOutlet NSWindow *window;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

-(IBAction)btnTest:(id)sender{
    GAPP::User *u = new GAPP::User();
    u->test();
//    u->fetch();
  //  openbiz::getVersion();
    delete u;
}

@end
