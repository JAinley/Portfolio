//
//  GameControler.m
//  ICA location game
//
//  Created by AINLEY, JOSHUA on 08/12/2017.
//  Copyright © 2017 AINLEY, JOSHUA. All rights reserved.
//

#import "GameControler.h"
#import <AVFoundation/AVFoundation.h>

@interface GameControler (){
      AVAudioPlayer *_audioplayer;
}
@property (weak, nonatomic) IBOutlet UILabel *WinOrLoseLabel;
@property (weak, nonatomic) IBOutlet UILabel *ScoreLabel;

@end

@implementation GameControler

-(void)setScore:(int)Score
{
    _Score += Score;
}

// here is the code for the logic of the bomb game, the three buttons below are the wires the player needs to "cut" to defuse the bomb
// here also i show that the pictures are swapped out on the buttons to show that the wire has been cut and once cut i disable the button
// the reason to disable the button so if the user defuses the bomb they cannot cut the bomb wire and blo the bomb up
- (IBAction)CutGreenWire:(id)sender {
    [sender setBackgroundImage:[UIImage imageNamed:@"GreenWireCut"] forState:UIControlStateNormal];
    if(self.GreenWire == YES)
    {
        [self.bombPic setImage:[UIImage imageNamed:@"bombToExplode"]];
        NSLog(@"BOOOM");
        self.WinOrLoseLabel.text = @"BOMB has exploded, Go back to the map!";
        [self setBombExploded:YES];
        [_audioplayer play];
    }
    else
    {
        [self setGreenWireSafe:YES];
        self.greenWireButton.enabled = NO;
    }
    if(self.GreenWireSafe == YES && self.RedWireSafe == YES && self.BombExploded == NO)
    {
        NSLog(@"Yay bomb defused");
        self.WinOrLoseLabel.text = @"BOMB has been defused, Go back to the map!";
        //[self MapViewGame];
        self.blueWireButton.enabled = NO;
        [self setScore:1];
        [self setScoreLabel];
        
    }
    if(self.GreenWireSafe == YES && self.BlueWireSafe == YES && self.BombExploded == NO)
    {
        NSLog(@"Yay bomb defused");
        self.WinOrLoseLabel.text = @"BOMB has been defused, Go back to the map!";
        //[self MapViewGame];
        self.redWireButton.enabled = NO;
        [self setScore:1];
        [self setScoreLabel];
    }
        
}
- (IBAction)CtRedWire:(id)sender {
    [sender setBackgroundImage:[UIImage imageNamed:@"RedWireCut"] forState:UIControlStateNormal];
    if(self.RedWire == YES)
    {
        NSLog(@"BOOOM");
        self.WinOrLoseLabel.text = @"BOMB has exploded, Go back to the map!";
        [self.bombPic setImage:[UIImage imageNamed:@"bombToExplode"]];
        [self setBombExploded:YES];
        [_audioplayer play];
    }
    else{
        [self setRedWireSafe:YES];
        self.redWireButton.enabled = NO;
    }
    if(self.RedWireSafe == YES && self.GreenWireSafe == YES && self.BombExploded == NO)
    {
        NSLog(@"Yay bomb defused");
        self.WinOrLoseLabel.text = @"BOMB has been defused, Go back to the map!";
        //[self MapViewGame];
        self.blueWireButton.enabled = NO;
        [self setScore:1];
        [self setScoreLabel];
    }
    if(self.RedWireSafe == YES && self.BlueWireSafe == YES && self.BombExploded == NO)
    {
        NSLog(@"Yay bomb defused");
        self.WinOrLoseLabel.text = @"BOMB has been defused, Go back to the map!";
        //[self MapViewGame];
        self.greenWireButton.enabled = NO;
        [self setScore:1];
        [self setScoreLabel];
    }
    
}
- (IBAction)CutBlueWire:(id)sender {
    [sender setBackgroundImage:[UIImage imageNamed:@"BlueWireCut"] forState:UIControlStateNormal];
    if(self.BlueWire == YES)
    {
        NSLog(@"BOOOM");
        self.WinOrLoseLabel.text = @"BOMB has exploded, Go back to the map!";
        [self.bombPic setImage:[UIImage imageNamed:@"bombToExplode"]];
        [self setBombExploded:YES];
        [_audioplayer play];
    }
    else{
        [self setBlueWireSafe:YES];
        self.blueWireButton.enabled = NO;
    }
    if(self.BlueWireSafe == YES && self.RedWireSafe == YES && self.BombExploded == NO)
    {
        NSLog(@"Yay bomb defused");
        self.WinOrLoseLabel.text = @"BOMB has been defused, Go back to the map!";
        //[self MapViewGame];
        self.greenWireButton.enabled = NO;
        [self setScore:1];
        [self setScoreLabel];
    }
    if(self.BlueWireSafe == YES && self.GreenWireSafe == YES && self.BombExploded == NO)
    {
        NSLog(@"Yay bomb defused");
        self.WinOrLoseLabel.text = @"BOMB has been defused, Go back to the map!";
        //[self MapViewGame];
        self.redWireButton.enabled = NO;
       [self setScore:1];
        [self setScoreLabel];
    }
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.greenWireButton.enabled = YES;
    self.blueWireButton.enabled = YES;
    self.redWireButton.enabled = YES;
    
    // tried to implement sound however it didnt work but left somecode here incase i decide to go back to it
    NSString *path = [NSString stringWithFormat:@"/Users/p4039580/Downloads/Time Bomb Short-SoundBible.com-1562499525.mp3", [[NSBundle mainBundle] resourcePath]];
    NSURL *soundUrl = [NSURL fileURLWithPath:path];
    
    _audioplayer = [[AVAudioPlayer alloc] initWithContentsOfURL:soundUrl error:nil];
    
    // here when the game view controller is loaded the bomb wire is chosen at random
    [self ReturnRandNum];
    if(self.Wire == 0)
    {
        [self setRedWire:YES];
    }
    else if(self.Wire == 1)
    {
        [self setGreenWire:YES];;
    }
    else if (self.Wire == 2)
    {
        [self setBlueWire:YES];
    }
    // Do any additional setup after loading the view.
    // here i load the user defaults just the highscore of the game so that i may load the same score up again next time the user plays
    // it then sets the score of the game to the score previously played
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSInteger score = [defaults integerForKey:@"Score"];
    [self.ScoreLabel setText:[NSString stringWithFormat:@"%zd", score]];
    [self setScore:score];
    
}

-(void)MapViewGame{
    [self.navigationController popViewControllerAnimated:YES];
}

// set all the bools of the wires
-(void)setBombExploded:(BOOL)BombExploded
{
    _BombExploded = BombExploded;
}
-(void)setRedWire:(BOOL)RedWire
{
    _RedWire = RedWire;
}
-(void)setBlueWire:(BOOL)BlueWire
{
    _BlueWire = BlueWire;
}
-(void)setGreenWire:(BOOL)GreenWire
{
    _GreenWire = GreenWire;
}
-(void)setRedWireSafe:(BOOL)RedWireSafe
{
    _RedWireSafe = RedWireSafe;
}
-(void)setGreenWireSafe:(BOOL)GreenWireSafe
{
    _GreenWireSafe = GreenWireSafe;
}
-(void)setBlueWireSafe:(BOOL)BlueWireSafe
{
    _BlueWireSafe = BlueWireSafe;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

// in this function i save the score as it is to the user defaults so that it is saved and i manually force a save just to be sure it has
// i then load the score back from the user defaults and set the score label that the user sees to that score so they may see their score
-(void)setScoreLabel
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [defaults setInteger:self.Score forKey:@"Score"];
    [defaults synchronize];
    
    NSInteger score = [defaults integerForKey:@"Score"];
    [self.ScoreLabel setText:[NSString stringWithFormat:@"%zd", score]];
}

// choses the wire number e.g bluewire = 1, redwire = 2 and greenwire = 3, this is to decide which one is the bomb wire
-(int)ReturnRandNum
{
    self.Wire = rand() % 3;
    return self.Wire;
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
