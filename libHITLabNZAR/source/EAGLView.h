/*

===== IMPORTANT =====

This is sample code demonstrating API, technology or techniques in development.
Although this sample code has been reviewed for technical accuracy, it is not
final. Apple is supplying this information to help you plan for the adoption of
the technologies and programming interfaces described herein. This information
is subject to change, and software implemented based on this sample code should
be tested with final operating system software and final documentation. Newer
versions of this sample code may be provided with future seeds of the API or
technology. For information about updates to this and other developer
documentation, view the New & Updated sidebars in subsequent documentation
seeds.

=====================

File: EAGLView.h
Abstract: Convenience class that wraps the CAEAGLLayer from CoreAnimation into a
UIView subclass.

Version: 1.4

Disclaimer: IMPORTANT:  This Apple software is supplied to you by Apple Inc.
("Apple") in consideration of your agreement to the following terms, and your
use, installation, modification or redistribution of this Apple software
constitutes acceptance of these terms.  If you do not agree with these terms,
please do not use, install, modify or redistribute this Apple software.

In consideration of your agreement to abide by the following terms, and subject
to these terms, Apple grants you a personal, non-exclusive license, under
Apple's copyrights in this original Apple software (the "Apple Software"), to
use, reproduce, modify and redistribute the Apple Software, with or without
modifications, in source and/or binary forms; provided that if you redistribute
the Apple Software in its entirety and without modifications, you must retain
this notice and the following text and disclaimers in all such redistributions
of the Apple Software.
Neither the name, trademarks, service marks or logos of Apple Inc. may be used
to endorse or promote products derived from the Apple Software without specific
prior written permission from Apple.  Except as expressly stated in this notice,
no other rights or licenses, express or implied, are granted by Apple herein,
including but not limited to any patent rights that may be infringed by your
derivative works or by other works in which the Apple Software may be
incorporated.

The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO
WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED
WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE OR IN
COMBINATION WITH YOUR PRODUCTS.

IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, MODIFICATION AND/OR
DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY OF
CONTRACT, TORT (INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF
APPLE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Copyright (C) 2008 Apple Inc. All Rights Reserved.

*/

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

@class EAGLView;

/// The main EAGL delegate callbacks.
@protocol EAGLViewDelegate <NSObject>
@optional
/// Called whenever the EAGL surface has been resized.
- (void) didResizeEAGLSurfaceForView:(EAGLView*)view; 

- (void)touchesBegan: (NSSet *)touches withEvent: (UIEvent *)event inView: (EAGLView*)view;
- (void)touchesMoved: (NSSet *)touches withEvent: (UIEvent *)event inView: (EAGLView*)view;
- (void)touchesEnded: (NSSet *)touches withEvent: (UIEvent *)event inView: (EAGLView*)view;
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event inView: (EAGLView*)view;

/// Update the view by drawing using OpenGL commands.
- (void)update: (EAGLView*)view;
@end

/// Wraps the CAEAGLLayer from CoreAnimation into a convenient UIView subclass.
/// The view content is basically an EAGL surface you render your OpenGL scene into.
/// Note that setting the view non-opaque will only work if the EAGL surface has an alpha channel.
@interface EAGLView : UIView
{
	GLuint					_format;
	GLuint					_depthFormat;
	BOOL					_autoresize;
	EAGLContext				*_context;
	GLuint					_framebuffer;
	GLuint					_renderbuffer;
	GLuint					_depthBuffer;
	CGSize					_size;
	BOOL					_hasBeenCurrent;
	id<EAGLViewDelegate>	_delegate;
	
	//NSTimer * _frameTimer;
    CADisplayLink * _displayLink;
	
	BOOL _debug;
	
	NSDate * _lastDate;
	unsigned _count;
}

- (id) initWithFrame:(CGRect)frame;
- (id) initWithFrame:(CGRect)frame pixelFormat:(GLuint)format;
- (id) initWithFrame:(CGRect)frame pixelFormat:(GLuint)format depthFormat:(GLuint)depth preserveBackbuffer:(BOOL)retained;

@property(nonatomic,readonly) GLuint framebuffer;
@property(nonatomic,readonly) GLuint pixelFormat;
@property(nonatomic,readonly) GLuint depthFormat;
@property(nonatomic,readonly) EAGLContext *context;

/// Print out FPS and other related debugging information.
@property(nonatomic,assign) BOOL debug;

/// Controls whether the EAGL surface automatically resizes when the view bounds change. Otherwise, the EAGL surface contents are scaled to fix when rendered. NO by default.
@property(nonatomic) BOOL autoresize;
@property(nonatomic,readonly) CGSize surfaceSize;

@property(nonatomic,assign) id<EAGLViewDelegate> delegate;

- (void) startRendering;
- (void) stopRendering;

- (void) setCurrentContext;
- (BOOL) isCurrentContext;
- (void) clearCurrentContext;

/// Swap the back and front buffers so that the buffer than has been drawn is now visible.
/// This also checks the current OpenGL error and logs an error if needed.
- (void) swapBuffers; 

- (void) update;

- (CGPoint) convertPointFromViewToSurface:(CGPoint)point;
- (CGRect) convertRectFromViewToSurface:(CGRect)rect;
@end
