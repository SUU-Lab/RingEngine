
#include "LaunchState.hpp"

namespace ring {

void Main(LaunchState*);

} // namespace ring

// #import <Cocoa/Cocoa.h>

int main(int argc, char *argv[])
{
    ring::LaunchState launchState = {};
    ring::Main(&launchState);
    
    // [NSApplication sharedApplication];
    // [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    
    // @autoreleasepool
    // {
    //     NSMenu* bar = [[NSMenu alloc] init];
    //     [NSApp setMainMenu:bar];
        
    //     NSMenuItem* appMenuItem = [bar addItemWithTitle:@""
    //                                              action:NULL
    //                                       keyEquivalent:@""];
    //     NSMenu* appMenu = [[NSMenu alloc] init];
    //     [appMenuItem setSubmenu:appMenu];
        
    //     [appMenu addItemWithTitle:@"Quit"
    //                        action:@selector(terminate:)
    //                 keyEquivalent:@"q"];
    
    //     NSImage* image = [[NSImage alloc] initWithSize:NSMakeSize(128, 128)];
    //     [image lockFocus];
    //     [[NSColor redColor] setFill];
    //     [NSBezierPath fillRect:NSMakeRect(0, 0, 128, 128)];
    //     [image unlockFocus];

    //     [NSApp setApplicationIconImage:image];
    // }
    
    // AppDelegate* delegate = [[AppDelegate alloc] init];
    // if (delegate == nil)
    //     return -1;
    
    // [NSApp setDelegate:delegate];
    // [NSApp run];
    
    return 0;
}
