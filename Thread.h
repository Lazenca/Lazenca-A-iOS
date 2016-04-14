#include <pthread.h>
static void showThreadList(void) {
    char name[256];
    mach_msg_type_number_t count;
    thread_act_array_t list;
    
    kern_return_t kret;
    
    kret = task_threads(target_task, &list, &count);
    
    if (kret == KERN_SUCCESS) {
        for (int i = 0; i < count; ++i) {
            pthread_t pt = pthread_from_mach_thread_np(list[i]);
            if (pt) {
                name[0] = '\0';
                int rc = pthread_getname_np(pt, name, sizeof name);
                printf("Thread %u: getname returned %d: %s\n", list[i], rc, name);
            } else {
                printf("Thread %u: no pthread found\n", list[i]);
            }
        }
    }else{
        printf("task_threads() failed with message %s!\n",mach_error_string(kret));
    }
}

void suspendThread(thread_t target_thread){
    kern_return_t kret;
    kret = thread_suspend(target_thread);
    if (kret == KERN_SUCCESS) {
        printf("thread_suspend() succeed with message %s!\n",mach_error_string(kret));
    }else{
        printf("task_threads() failed with message %s!\n",mach_error_string(kret));
    }
}

void resumeThread(thread_t target_thread){
    kern_return_t kret;
    kret = thread_resume(target_thread);
    if (kret == KERN_SUCCESS) {
        printf("thread_resume() resume with message %s!\n",mach_error_string(kret));
    }else{
        printf("task_threads() failed with message %s!\n",mach_error_string(kret));
    }
}