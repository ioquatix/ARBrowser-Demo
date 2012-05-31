//
//  ARBrowserViewController.h
//  ARBrowser
//
//  Created by Samuel Williams on 5/04/11.
//  Copyright 2011 Samuel Williams. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "ARBrowserView.h"

typedef struct {
	CGFloat distance;
	CGFloat scale;
} ARScaleMarker;

/// Simple example of an ARBrowserViewDelegate.
@interface ARBrowserViewController : UIViewController <EAGLViewDelegate, ARBrowserViewDelegate> {
	NSArray * _worldPoints;

	CGFloat initialObjectScale;
	ARScaleMarker scaleMarkers[2];
}

@property(nonatomic,retain) NSArray * worldPoints;

@end
