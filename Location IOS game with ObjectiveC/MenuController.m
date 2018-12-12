//
//  MenuController.m
//  ICA location game
//
//  Created by AINLEY, JOSHUA on 21/11/2017.
//  Copyright © 2017 AINLEY, JOSHUA. All rights reserved.
//

#import "MenuController.h"

@interface MenuController ()

@end

@implementation MenuController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"bombainPic.jpg"]];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

// just a segue to the map view
-(void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if([segue.identifier isEqualToString:@"getLocation"])
    {
        if([segue.destinationViewController isKindOfClass:[ViewController class] ])
        {
            ViewController* newVC = (ViewController*) segue.destinationViewController;
            newVC.title = @"it worked";
        }
    }
}


/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
