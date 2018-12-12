//
//  ViewController.m
//  ICA location game
//
//  Created by AINLEY, JOSHUA on 21/11/2017.
//  Copyright © 2017 AINLEY, JOSHUA. All rights reserved.
//

#import "ViewController.h"


@implementation ViewController


// here i set up the location manager and make the delegate its self, from there i choose the settings of the location manager
// such as accuracy and whether or not to show buildings. here i also request access from the user to use the location services
// i updated the info.plist to allow requests, ithout this the app wouldnt be alowed access to gps.
- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.locationmanager = [[CLLocationManager alloc]init];
    self.locationmanager.desiredAccuracy = kCLLocationAccuracyBestForNavigation;
    if([self.locationmanager respondsToSelector:@selector(requestWhenInUseAuthorization)]){
        [self.locationmanager requestWhenInUseAuthorization];
    }
    self.locationmanager.delegate = self;
    [self.locationmanager startUpdatingLocation];
    self.mapView.showsUserLocation = YES;
    self.mapView.showsBuildings = YES;
    [self setAlreadyMade:NO];
    [self setMonitoredAlready:NO];

}

// sets the bool to see if the player has entered a bomb site or region
-(void)setEntered:(BOOL)entered
{
    _entered = entered;
}


// fired when user enters geofence
- (void)locationManager:(CLLocationManager *)manager didEnterRegion:(CLRegion *)region
{
    [self setEntered:YES];
    NSLog(@"yay");
    //[self.locationmanager stopMonitoringForRegion:region];
    [self setMonitoredAlready:YES];
    
}

// this segues to the game view
-(void)loadGameView
{
    NSString * storyboardName = @"Main";
    UIStoryboard *storyboard = [UIStoryboard storyboardWithName:storyboardName bundle: nil];
    UIViewController * vc = [storyboard instantiateViewControllerWithIdentifier:@"GameView"];
    [self.navigationController pushViewController:vc animated:YES];
}

-(void)locationManager:(CLLocationManager *)manager didStartMonitoringForRegion:(CLRegion *)region
{
    NSLog(@"Region being monitored");
    [self.locationmanager requestStateForRegion:region];
}

-(void)locationManager:(CLLocationManager *)manager monitoringDidFailForRegion:(nullable CLRegion *)region withError:(nonnull NSError *)error
{
    NSLog(@"It failed %@", error);
}

// fired when user exits geo fence
- (void)locationManager:(CLLocationManager *)manager didExitRegion:(CLRegion *)region
{
    [self setEntered:NO];
    [self setAlreadyMade:NO];
    NSLog(@"Aww");
    // handle
}

// checks to see if the user has already been in that specific geofence
-(void)setMonitoredAlready:(BOOL)MonitoredAlready
{
    _MonitoredAlready = MonitoredAlready;
}

// here i set the map overlays so the blue circles that the user sees are set here
-(MKOverlayRenderer *)mapView:(MKMapView *)mapView rendererForOverlay:(id<MKOverlay>)overlay
{
    MKCircleRenderer *circleView = [[MKCircleRenderer alloc] initWithOverlay:overlay];
    if(self.MonitoredAlready)
    {
        circleView.strokeColor = [UIColor blueColor];
        circleView.fillColor = [[UIColor blueColor] colorWithAlphaComponent:0];
    }
    else
    {
        circleView.strokeColor = [UIColor blueColor];
        circleView.fillColor = [[UIColor blueColor] colorWithAlphaComponent:0.4];
    }
    return circleView;
}

// here the updates for the map and gps are done, first off i update the map camera to centre on the users position
// then i set the height of the map so how far zoomend in i am, this happens constantly so the user will always see themselves
// next i set the bomb location, this is done by random. the bomb is set at a certain distance from the user but not next to them
// by using the longitude and latitude i place it at least 100m or so away form the user, i then set its centre coordiantes and give it an id
// once the bomb is set i start monitoring for it if it isnt already being monitored
// next i check if the bomb site has been entered then i launch into the game view
// after the game view ends i update the score on the scorelabel from the user defaults which isthe saved highscore
-(void)mapView:(MKMapView *)mapView didUpdateUserLocation:(nonnull MKUserLocation *)userLocation{
    MKMapCamera *camera = [MKMapCamera cameraLookingAtCenterCoordinate:userLocation.coordinate fromEyeCoordinate:CLLocationCoordinate2DMake(userLocation.coordinate.latitude, userLocation.coordinate.longitude) eyeAltitude:2000];
    
    if(!self.AlreadyMade){
        // this bomb is the test bomb and will always be here
        CLLocationCoordinate2D center = CLLocationCoordinate2DMake(54.570345, -1.233237);
        CLCircularRegion *Bomb = [[CLCircularRegion alloc] initWithCenter:center radius:50 identifier:@"Bomb"];
        MKCircle *circle = [MKCircle circleWithCenterCoordinate:center radius:(50)];
        
        double RandomLat = (self.mapView.userLocation.coordinate.latitude + 0.002) + (arc4random() % 1/2);
        double RandomLon = (self.mapView.userLocation.coordinate.longitude + 0.002) + (arc4random() % 1/2);
        
        CLLocationCoordinate2D Randomcenter = CLLocationCoordinate2DMake(RandomLat, RandomLon);
        CLCircularRegion *Bomb2 = [[CLCircularRegion alloc] initWithCenter:Randomcenter radius:(100) identifier:(@"Bomb2")];
        MKCircle *BombCircle = [MKCircle circleWithCenterCoordinate:Randomcenter radius:100];
        NSLog(@"Made again");
        [self.locationmanager startMonitoringForRegion:Bomb];
        
        // thissection doesnt work so well as the remmov overlay is a bit iffy
        if(self.TestMonitoredAlready == false){
            [self.mapView addOverlay:circle];
        }
        
        [self.locationmanager startMonitoringForRegion:Bomb2];
        if(self.MonitoredAlready == false){
            [self.mapView addOverlay:BombCircle];
        }
        
        if(self.MonitoredAlready == true){
            [self.mapView removeOverlay:BombCircle];
        }
        
        [self setAlreadyMade:YES];
    }
    
    [mapView setCamera:camera animated:YES];
    if(self.entered == YES)
    {
        NSLog(@"True");
        [self loadGameView];
    }
    [self setEntered:NO];
    
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSInteger score = [defaults integerForKey:@"Score"];
    NSLog(@"%zd", score);
    [self.scoreLabel setText:[NSString stringWithFormat:@"%zd", score]];
    
}


// these just set the bools to see if user has already monitored the bombs
-(void)setTestMonitoredAlready:(BOOL)TestMonitoredAlready
{
    _TestMonitoredAlready = TestMonitoredAlready;
}

-(void)setAlreadyMade:(BOOL)AlreadyMade
{
    _AlreadyMade = AlreadyMade;
}



//<-----------TODO: Create regions and circles around them based on user location and keep a test one for martin and for ICA------>



@end
