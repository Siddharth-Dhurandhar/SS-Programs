/*
============================================================================
Name : 28.c
Author : Siddharth Dhurandhar
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure)
Date:  20th Sept, 2024.
============================================================================
*/
#include <sys/msg.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <time.h>
typedef struct mesg_buffer
{
    /* data */
    long mesg_type;
    char mesg_text[100];
} mesg_buffer;
int main(int argc, char const *argv[])
{
    /* code */
    mesg_buffer message;
    // generate unique no
    key_t key = ftok(".", 1); // projext path is current directory and project id=1
    // create massage queue using msgget
    //  msgget creates a message queue
    //  and returns identifier
    int msgid = msgget(key, 0666 | IPC_CREAT);
    struct msqid_ds buf;
    msgctl(msgid, IPC_STAT, &buf);
    struct ipc_perm msg_perm = buf.msg_perm; /* Ownership and permissions */
    printf("access permission %d\n", msg_perm.mode);
    buf.msg_perm.mode = 0776;
    msgctl(msgid, IPC_SET, &buf);
    /*
    Write  the values of some members of the msqid_ds structure pointed to by buf to the
    kernel data  structure  associated  with  this  message  queue,  updating  also  its
    msg_ctime  member.   The following members of the structure are updated: msg_qbytes,
    msg_perm.uid, msg_perm.gid, and (the least significant  9  bits  of)  msg_perm.mode.
    The effective UID of the calling process must match the owner (msg_perm.uid) or cre‐
    ator (msg_perm.cuid) of the message queue, or the caller must be privileged.  Appro‐
    priate  privilege  (Linux: the CAP_SYS_RESOURCE capability) is required to raise the
    msg_qbytes value beyond the system parameter MSGMNB.
    */

    struct msqid_ds cbuf;
    msgctl(msgid, IPC_STAT, &cbuf);
    struct ipc_perm u_msg_perm = cbuf.msg_perm; /* Ownership and permissions */
    printf("access permission %d\n", u_msg_perm.mode);
    return 0;
}
