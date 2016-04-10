#import <Foundation/Foundation.h>
#import <sys/types.h>
#import <sys/sysctl.h>

void ProcessList();

@interface RunningProcess : NSObject
- (NSArray *)runningProcesses;
@end

void ProcessList(){
    RunningProcess *runningProc = [[RunningProcess alloc] init];
    NSArray *str = [runningProc runningProcesses];
    for(int i=0;i<[str count];i++){
        NSLog(@"%@",[str objectAtIndex:i]);
    }
}

@implementation RunningProcess
- (NSArray *)runningProcesses {
    int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0};
    size_t miblen = 4;
    size_t size = 0;
    
    int st = sysctl(mib, miblen, NULL, &size, NULL, 0);
    
    struct kinfo_proc *process = NULL;
    struct kinfo_proc *newprocess = NULL;
    
    do {
        size += size / 10;
        newprocess = (kinfo_proc * )realloc(process, size);
        if (!newprocess){
            if (process){
                free(process);
            }
            return nil;
        }
        process = newprocess;
        st = sysctl(mib, miblen, process, &size, NULL, 0);
    } while (st == -1 && errno == ENOMEM);
    
    if (st == 0){
        if (size % sizeof(struct kinfo_proc) == 0){
            int nprocess = size / sizeof(struct kinfo_proc);
            if (nprocess){
                NSMutableArray * array = [[NSMutableArray alloc] init];
                
                for (int i = nprocess - 1; i >= 0; i--){
                    NSString *processID = [[NSString alloc] initWithFormat:@"%d", process[i].kp_proc.p_pid];
                    NSString *processName = [[NSString alloc] initWithFormat:@"%s", process[i].kp_proc.p_comm];
                    
                    // Create an array of the objects
                    NSArray *ItemArray = [NSArray arrayWithObjects:processID, processName, nil];
                    
                    // Create an array of keys
                    NSArray *KeyArray = [NSArray arrayWithObjects:@"PID", @"Name", nil];
                    
                    // Create the dictionary
                    NSDictionary *dict = [[NSDictionary alloc] initWithObjects:ItemArray forKeys:KeyArray];
                    
                    [processID release];
                    [processName release];
                    [array addObject:dict];
                    [dict release];
                }
                free(process);
                return [array autorelease];
            }
        }
    }
    return nil;
}
@end

