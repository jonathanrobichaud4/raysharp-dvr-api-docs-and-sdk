//
//  PlayWindow.m
//  iosPlayWnd
//
//  Created by Raysharp on 2018/2/1.
//  Copyright © 2018年 Raysharp. All rights reserved.
//

#import "PlayWindow.h"

@implementation PlayWindow

- (void)awakeFromNib {
    [super awakeFromNib];
    // Initialization code
    self.backgroundColor = [UIColor purpleColor];
}

@end

@interface UIView(dd)
- (void)screen;
@end
@implementation UIView(dd)
- (void)screen{
    NSLog(@"111");
}
@end
