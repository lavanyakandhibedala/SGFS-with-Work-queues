#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <asm/page.h>
#include <linux/uaccess.h>
#include <linux/uidgid.h>
#include <linux/types.h>
#include <linux/moduleloader.h>
#include <linux/sched.h>
#include <linux/time.h>
#include <linux/timer.h>
#include <linux/delay.h>
#include <linux/linkage.h>
#include <linux/fs_stack.h>
#include <linux/sort.h>



extern int n_files;
static struct task_struct *thread_st;
//#define MAX_NUM_FILES n_files
int num_files=0;
int delete_files=0;
int curr_files=0;
char file_names[100][100];



/*
 *  *
 *   *
 *    * Opening file
 *     */
struct file *file_open(const char *path, int flags, int rights) {
    struct file *filp = NULL;
    mm_segment_t oldfs;
    oldfs = get_fs();
    set_fs(get_ds());

    filp = filp_open(path, flags, &filp->f_pos);
    set_fs(oldfs);


    return filp;

}

/*
 *  *
 *   *
 *    * Close a file
 *     */
void file_close(struct file *file) {
    filp_close(file, NULL);
}


int processunlinkfiles(const char *path)
{
    int err = 0;
    struct file *trashbinfile = NULL;
    char *trashbinfolder_filename =NULL;
    struct inode *deletedir;
    struct dentry *deletevic;
    struct inode *infdirinode;
    struct dentry *infdentry;

    printk("deleting file %s\n",path);

    trashbinfolder_filename = kmalloc(strlen("/usr")+sizeof(char)*9 + strlen(path) +2 ,GFP_KERNEL);
    if (!trashbinfolder_filename)
    {
        printk("error creating in trash bin file file name \n");
        err = PTR_ERR(trashbinfolder_filename);
        goto out;

    }
    else
    {

        memset(trashbinfolder_filename, 0, strlen("/usr")+sizeof(char)*9 + strlen(path)+2);
        memcpy(trashbinfolder_filename, "/usr", strlen("/usr"));
        strcat(trashbinfolder_filename,"/trashbin");
        strcat(trashbinfolder_filename,"/");
        strcat(trashbinfolder_filename,path);
        printk("file name given for unlink %s\n",trashbinfolder_filename);
    }

    trashbinfile = file_open(trashbinfolder_filename, O_RDONLY, 0);

    if (!trashbinfile || IS_ERR(trashbinfile)) {
        printk("trashbin input file can not be opened %s\n", trashbinfolder_filename);
        err = -EPERM;
        goto out1;
    }
    else{
        printk("trash bin folder delete file %s opened properly\n",trashbinfolder_filename);
    }

    infdirinode = trashbinfile->f_path.dentry->d_inode;
    infdentry= trashbinfile->f_path.dentry;


    deletedir = trashbinfile->f_path.dentry->d_parent->d_inode; /* tempfile directory inode*/
    deletevic = trashbinfile->f_path.dentry;  /* temp file dentry*/
    file_close(trashbinfile);
    printk("print after file close\n");

    mutex_lock(&deletedir->i_mutex);
    err = vfs_unlink(deletedir, deletevic, NULL);
    if (err < 0)
    {
        printk("vfs_unlinks fails to delete given file  %s\n", trashbinfolder_filename);

    } else
    {
        printk("sucessfully deleted given trash bin file %s\n",trashbinfolder_filename);
    }
    mutex_unlock(&deletedir->i_mutex);



    goto out1;

    out1:
        kfree(trashbinfolder_filename);
        return err;

    out:
        return err;


}


static int printdir(struct dir_context * ctx, const char * name, int namelen, loff_t offset, u64 ino, unsigned int d_type)
{


    if( (memcmp(name, ".", 1) != 0) && (memcmp(name, "..", 2) != 0) )
    {

        strcpy(file_names[curr_files],name);
        curr_files++;
        printk("File: %.*s\n",namelen,name);

    }


    return 0;
}

static int compare(const void *lhs,const void *rhs)
{
    /*const char *lhs_string=* (const char *) (lhs);
 *     const char *rhs_string=* (const char *) (rhs);
 *         printk("in compare %s %s\n",lhs_string,rhs_string);
 *
 *             if(lhs_string>rhs_string) return 1;
 *                 if(lhs_string<rhs_string) return -1;*/

    return strcmp((char *)lhs,(char *)rhs);
}


static int deletefiles(char *path)
{
    int file_count=0;
    int err=0;
    int j=0;
    int extrafiles=0;
    struct file *tbdir = NULL;


    printk("trash bin directory path %s\n",path);

    tbdir = file_open(path, O_RDONLY, 0);

    if (!tbdir || IS_ERR(tbdir))
    {
        printk("error trash bin directory file  can not be opened %s\n", path);
        err = -EPERM;
        return err;
    }
    else{
        printk("trash bin directory opened properly\n");
    }


    struct dir_context my_ctx={.actor=&printdir};

    iterate_dir(tbdir,&my_ctx);

    file_close(tbdir);

    num_files=curr_files;

    printk("number of files in the directory %d\n",num_files);

    if(num_files>n_files)
    {
        extrafiles=num_files-n_files;
        sort(file_names,num_files,100,&compare,NULL);

        for(j=0;j<extrafiles;j++)
        {
            printk("delete file is %s\n",file_names[j]);
            processunlinkfiles(file_names[j]);
        }
    }



    return file_count;


}



static int thread_fn(void *unused)
{
    int err=0;
    int i=0;


    printk(KERN_INFO "Thread ran\n");

    while(i<10)
    {
        i++;
        printk("Thread running %d th time\n",i);

        curr_files=0;

        err=deletefiles("/usr/trashbin");
        num_files=curr_files;

        msleep(60000);
    }
    schedule();
    return 0;
}

static int __init
init_sys_deletethread(void)
{

    printk("installed new sys_delete thread module\n");


    thread_st=kthread_create(thread_fn,NULL,"deletethread");

    printk("Number of files is %d\n",n_files);
    //printk("Max number of files is %d\n",MAX_NUM_FILES);

    if(thread_st)
    {
        printk("Thread created successfully\n");
        wake_up_process(thread_st);
    }
    else{
        printk("Thread creation failed\n");
    }

    return 0;
}

static void __exit
exit_sys_deletethread(void)
{
    int err;
    err=kthread_stop(thread_st);
    if(!err)
        printk("thread stopped");
    else
        printk("thread didn't stopped");
}


module_init( init_sys_deletethread);
module_exit( exit_sys_deletethread);
MODULE_LICENSE("GPL");

