//
//  ViewController.h
//  ICA location game
//
//  Created by AINLEY, JOSHUA on 21/11/2017.
//  Copyright © 2017 AINLEY, JOSHUA. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>
#import <CoreLocation/CoreLocation.h>

@interface ViewController : UIViewController <MKMapViewDelegate,  CLLocationManagerDelegate, MKOverlay, UINavigationControllerDelegate> {
    MKOverlayRenderer *overlay;
    MKCircle *circleregion;
    
}
@property (strong, nonatomic)CLLocationManager *locationmanager;
@property (weak, nonatomic) IBOutlet MKMapView *mapView;
@property (assign, nonatomic)BOOL entered;
@property (strong, nonatomic) IBOutlet UIView *maptitle;
@property (assign, nonatomic) BOOL AlreadyMade;
@property (assign, nonatomic) BOOL MonitoredAlready;
@property (assign, nonatomic) BOOL TestMonitoredAlready;
@property (weak, nonatomic) IBOutlet UILabel *scoreLabel;

@property(nonatomic)int MyScore;

@end

