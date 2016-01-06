/* Copyright (c) 2007 Christopher J. W. Lloyd

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the
following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */
#import <Foundation/NSCoder.h>
#import <Foundation/NSPropertyList.h>
#import <Foundation/NSMapTable.h>

@class NSMutableArray, NSMutableData, NSMutableDictionary;

FOUNDATION_EXPORT NSString* const NSInvalidArchiveOperationException;

struct NSKeyedArchiverPriv;

@protocol NSKeyedArchiverDelegate;

FOUNDATION_EXPORT_CLASS
@interface NSKeyedArchiver : NSCoder

+ (NSData*)archivedDataWithRootObject:rootObject;
+ (BOOL)archiveRootObject:rootObject toFile:(NSString*)path;

- (instancetype)initForWritingWithMutableData:(NSMutableData*)data;

@property (assign) id<NSKeyedArchiverDelegate> delegate;
@property NSPropertyListFormat outputFormat;

+ (NSString*)classNameForClass:(Class)aClass;
+ (void)setClassName:(NSString*)className forClass:(Class)aClass;
- (NSString*)classNameForClass:(Class)aClass;
- (void)setClassName:(NSString*)className forClass:(Class)aClass;

- (void)encodeBool:(BOOL)value forKey:(NSString*)key;
- (void)encodeInt:(int)value forKey:(NSString*)key;
- (void)encodeInt32:(int)value forKey:(NSString*)key;
- (void)encodeInt64:(long long)value forKey:(NSString*)key;
- (void)encodeFloat:(float)value forKey:(NSString*)key;
- (void)encodeDouble:(double)value forKey:(NSString*)key;
- (void)encodeBytes:(const void*)aPointer length:(NSUInteger)length forKey:(NSString*)aKey;
- (void)encodeObject:object forKey:(NSString*)key;
- (void)encodeConditionalObject:object forKey:(NSString*)key;

- (void)finishEncoding;

@end

@protocol NSKeyedArchiverDelegate <NSObject>
- (void)archiver:(NSKeyedArchiver*)archiver willReplaceObject:object withObject:other;
- (id)archiver:(NSKeyedArchiver*)archiver willEncodeObject:object;
- (void)archiver:(NSKeyedArchiver*)archiver didEncodeObject:object;
- (void)archiverWillFinish:(NSKeyedArchiver*)archiver;
- (void)archiverDidFinish:(NSKeyedArchiver*)archiver;
@end

@interface NSObject (NSKeyedArchiver)
- (Class)classForKeyedArchiver;
+ (Class)classForKeyedUnarchiver;
+ (NSArray*)classFallbacksForKeyedArchiver;
- replacementObjectForKeyedArchiver:(NSKeyedArchiver*)archiver;
@end

#import <Foundation/NSKeyedUnarchiver.h>
