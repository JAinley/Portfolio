//
//  GameControler.h
//  ICA location game
//
//  Created by AINLEY, JOSHUA on 08/12/2017.
//  Copyright © 2017 AINLEY, JOSHUA. All rights reserved.
//

#import "ViewController.h"

@interface GameControler : ViewController

@property(assign, nonatomic)BOOL GreenWire;
@property(assign, nonatomic)BOOL RedWire;
@property(assign, nonatomic)BOOL BlueWire;

@property(assign, nonatomic)BOOL GreenWireSafe;
@property(assign, nonatomic)BOOL RedWireSafe;
@property(assign, nonatomic)BOOL BlueWireSafe;

@property(assign, nonatomic)BOOL BombExploded;

@property (weak, nonatomic) IBOutlet UIButton *blueWireButton;
@property (weak, nonatomic) IBOutlet UIButton *redWireButton;
@property (weak, nonatomic) IBOutlet UIButton *greenWireButton;

@property(nonatomic)int Wire;
@property(nonatomic)int Score;

@property (weak, nonatomic) IBOutlet UIImageView *bombPic;

@property(strong, nonatomic)UIImage *explosion;

-(int)ReturnRandNum;
@end
