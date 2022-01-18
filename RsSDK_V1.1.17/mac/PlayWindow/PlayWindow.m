//
//  PlayWindow.m
//  PlayWindow
//
//  Created by lovingc2009 on 17/3/9.
//  Copyright © 2017年 YHO. All rights reserved.
//

#import "PlayWindow.h"

@implementation PlayWindow

-(void)mouseDown:(NSEvent *)event
{
    if (_playID == 0)
        return ;
}

-(void)mouseUp:(NSEvent *)event
{
    if (_playID == 0)
        return ;
}

-(void)mouseDragged:(NSEvent *)event
{
    if (_playID == 0)
        return ;
}

- (void)drawRect:(NSRect)dirtyRect {
    NSColor *color = [NSColor colorWithRed:(CGFloat)(random()%255)/255 green:(CGFloat)(random()%255)/255 blue:(CGFloat)(random()%255)/255 alpha:1];
    [color set];
    NSRectFill(dirtyRect);
    [super drawRect:dirtyRect];
}

@end
