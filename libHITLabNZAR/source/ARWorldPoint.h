//
//  ARWorldPoint.h
//  ARBrowser
//
//  Created by Samuel Williams on 13/04/11.
//  Copyright 2011 Samuel Williams. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ARWorldLocation.h"
#import <MapKit/MapKit.h>

/// Simple bounding sphere data structure.
typedef struct {
	Vec3 center;
	float radius;
} ARBoundingSphere;

/// Provides the basic interface for renderable objects on the screen.
@protocol ARRenderable
/// Draw the object.
- (void) draw;

/// Return a bounding sphere for the object.
- (ARBoundingSphere) boundingSphere;
@end

/// Provides a renderable model and associated metadata for a given ARWorldLocation.
@interface ARWorldPoint : ARWorldLocation <MKAnnotation> {
	id<ARRenderable> model;
	
	NSMutableDictionary * metadata;
}

/// The renderable model for the given location.
@property(nonatomic,retain) id<ARRenderable> model;

/// The associated metadata for the given location.
/// This property is the primary method by which additional data should be managed for a specific point, e.g. street address, telephone number.
@property(nonatomic,retain) NSMutableDictionary * metadata;

/// Return true of the point will render using earth-centered earth-fixed coordinates:
@property(nonatomic,assign) BOOL fixed;

/// Title for MKAnnotation (returns metadata.title)
- (NSString *)title;

/// Subtitle for MKAnnotation (returns metadata.subtitle)
- (NSString *)subtitle;

@end
