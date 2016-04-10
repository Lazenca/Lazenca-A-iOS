#import "Util.h"

int setPid(){
    target_task = 0;
    kern_return_t kret;
    char *err;
    
    kret = task_for_pid(mach_task_self(), pid, &target_task);
    printf("pid : %d, target_task : %d\n",pid,target_task);
    
    if(kret != KERN_SUCCESS){
        err = mach_error_string(kret);
        printf("task_for_pid(%d) failed. (%x: %s) \n", target_task, kret, err);
    }else{
        return 1;
    }
    return 0;
}

int attach(){
    kern_return_t kret;
    tmp_target_task = 0;
    kret = task_for_pid(mach_task_self(),pid,&tmp_target_task);
    if (kret) {
        printf("task_for_pid() failed with message %s!\n",mach_error_string(kret));
    }else{
        printf("attach - target_task : %d, tmp_target_task : %d\n",target_task, tmp_target_task);
        kret = task_suspend(target_task);
        if (kret != KERN_SUCCESS) {
            printf("task_suspend() failed with message %s!\n",mach_error_string(kret));
        }else{
            printf("task_suspend - Success\n");
            return 1;
        }
    }
    return 0;
}
