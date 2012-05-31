//
//  ARBrowserViewController.m
//  ARBrowser
//
//  Created by Samuel Williams on 5/04/11.
//  Copyright 2011 Samuel Williams. All rights reserved.
//

#import "ARBrowserViewController.h"
#import "ARWorldPoint.h"

@implementation ARBrowserViewController

@synthesize worldPoints = _worldPoints;

- (void)dealloc {
    [self setWorldPoints:nil];
	
    [super dealloc];
}

#pragma mark - View lifecycle

- (void)loadView {
	// Standard view size for iOS UIWindow
	CGRect frame = CGRectMake(0, 0, 320, 480);

	// Initialize the OpenGL view
	ARBrowserView * browserView = [[ARBrowserView alloc] initWithFrame:frame];

	// Print out FPS information.
	[browserView setDebug:YES];

	// Turn off the grid.
	//[browserView setDisplayGrid:NO];
	[browserView setDisplayGrid:YES];

	[browserView setAutoresizingMask:UIViewAutoresizingFlexibleHeight|UIViewAutoresizingFlexibleWidth];

	[browserView setDelegate:self];

	// Change the minimum and maximum distance of objects.
	[browserView setMinimumDistance:1.0];
	
	// Icons will never get bigger past this point until the minimumDistance where they are culled.
	[browserView setNearDistance:3.0];
	
	// Icons will never get smaller past this point until the maximumDistance where they are culled.
	[browserView setFarDistance:25.0];
	
	[browserView setMaximumDistance:400.0];
	
	scaleMarkers[0].distance = browserView.minimumDistance;
	scaleMarkers[0].scale = 1.0;
	
	scaleMarkers[1].distance = browserView.maximumDistance;
	scaleMarkers[1].scale = 4.0;
	
	UIPinchGestureRecognizer * pinchGesture = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(handlePinchGesture:)];
	[browserView addGestureRecognizer:pinchGesture];
	
	[self setView:browserView];
}

- (void)handlePinchGesture:(UIPinchGestureRecognizer*)sender {
	switch ([sender state]) {
		case UIGestureRecognizerStateBegan:
			initialObjectScale = scaleMarkers[1].scale;
			break;
		case UIGestureRecognizerStateChanged:
			scaleMarkers[1].scale = initialObjectScale * [sender scale];
			break;
		default:
			break;
	}
}

static float interpolate(float t, float a, float b) {
	//NSLog(@"interpolate: %0.3f, %0.3f, %0.3f", t, a, b);
	return ((1.0 - t) * a) + (t * b);
}

- (float) browserView: (ARBrowserView*)view scaleFactorFor:(ARWorldPoint*)point atDistance:(float)distance
{	
	if (distance < scaleMarkers[0].distance) {
		return scaleMarkers[0].scale;
	}
	
	if (distance > scaleMarkers[1].distance) {
		return scaleMarkers[1].scale;
	}
	
	float t = (distance - scaleMarkers[0].distance) / (scaleMarkers[1].distance / scaleMarkers[0].distance);
	
	return interpolate(t, scaleMarkers[0].scale, scaleMarkers[1].scale);
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void)viewDidAppear:(BOOL)animated {
	NSLog(@"ARBrowserViewController: Resuming Rendering.");
		
	ARBrowserView * browserView = (ARBrowserView*)[self view];
	
	[browserView startRendering];
	
	[super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated {
	NSLog(@"ARBrowserViewController: Pausing Rendering.");
	
	ARBrowserView * browserView = (ARBrowserView*)[self view];
	
	[browserView stopRendering];
	
	[super viewWillDisappear:animated];
}

- (void) update: (EAGLView*) view {
	// Additional OpenGL Rendering here.
}

- (void) browserView: (ARBrowserView*)view didSelect:(ARWorldPoint*)point {
	NSLog(@"Browser view did select: %@", point);
	
	NSString * developer = [point.metadata objectForKey:@"developer"];
	NSString * address = [point.metadata objectForKey:@"address"];
	
	NSLog(@"Developer %@ at %@", developer, address);
}

// Optional - supply either -worldPoints or this:
//- (NSArray *)worldPointsFromLocation:(ARWorldLocation *)origin withinDistance:(float)distance {
	// You can apply your own filtering or asynchronous fetching here.
//	return self.worldPoints;
//}

// This method may be deprecated in the future..
- (void)renderInLocalCoordinatesForBrowserView:(ARBrowserView *)view {
	
}

@end
