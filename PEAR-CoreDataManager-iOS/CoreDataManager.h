//
//  CoreDataManager.h
//  LessonApp
//
//  Created by hirokiumatani on 2015/07/05.
//  Copyright (c) 2015年 hirokiumatani. All rights reserved.
//
#import <CoreData/CoreData.h>
/**
 Thread Macro
 */
#define _THREAD_START dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_BACKGROUND, 0), ^{
#define _THREAD_END   dispatch_semaphore_signal(_semaphore);});dispatch_semaphore_wait(_semaphore, DISPATCH_TIME_FOREVER);
/**
 save success blocks 
 */
typedef void (^CoreDataSaveSuccess)();

/**
 fetch success blocks 
 */
typedef void (^CoreDataFetchSuccess)(NSArray *fetchLists);

/**
 fetch count blocks
 */
typedef void (^CoreDataNewCreateIDSuccess)(NSInteger new_create_id);

/** 
 save failed blocks
 */
typedef void (^CoreDataFailed)(NSError *error);

@interface CoreDataManager : NSObject
@property (nonatomic,strong)NSManagedObjectModel         *managedObjectModel;
@property (nonatomic,strong)NSPersistentStoreCoordinator *persistentStoreCoordinator;
@property (nonatomic,strong)NSManagedObjectContext       *managedObjectContext;

/**
 First setting of CoreData and sqllite. 
 must call the first.
 
 @param :coreDataName This is name of coredata. Set the same name as the 'xcdatamodeld'.
 @param :sqliteName This is name of sqlite name.
 */
+ (void)initSettingWithCoreDataName:(NSString *)coreDataName
                         sqliteName:(NSString *)sqliteName;

/**
 return the singleton instance
 @return The singleton instatnce
 */
+ (CoreDataManager *)sharedInstance;

/**
 Create the insert entity.
 @param :className class name of entity.
 @return id Insert entity.
 */
+ (id)createInsertEntityWithClassName:(NSString *)className;

/**
 Save data of entity
 @return :success Call back the success.
 @return :faied Call back the error.
 */
+ (void)saveWithSuccess:(CoreDataSaveSuccess)success
                 failed:(CoreDataFailed)failed;

/**
 fetch entity lists
 @param :entityClass class name of entity.
 @param :predicate Setting the search condition
 @return :success Call back the entity lists.
 @return :faied Call back the error.
 */
+ (void)fetchWithEntity:(NSString *)entityClass
              Predicate:(NSPredicate *)predicate
                success:(CoreDataFetchSuccess)success
                 failed:(CoreDataFailed)failed;

/**
 When creates the new entity , create the auto increment number.
 @param :entityClass class name of entity.
 @return :success Call back the auto increment number.
 @return :faied Call back the error.
 */
+ (void)autoIncrementIDWithEntityClass:(NSString *)entityClass
                               success:(CoreDataNewCreateIDSuccess)success
                                failed:(CoreDataFailed)failed;

@end
