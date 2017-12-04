#include<linux/module.h>
#include<net/tcp.h>

static struct proto caesar_cipher_base_prot;
static struct proto ulp_caeser_cipher_prot;

#define TCP_NONE 100;

struct caeser_cipher_context {
    int key;
    int (*setsockopt)(struct sock *sk, int level, int optname, char __user *optval, unsigned int optlen);
    int (*getsockopt)(struct sock *sk, int level, int optname, char __user *optval, int __user *optlen);
    int (*sendmsg)(struct sock *sk, struct msghdr *msg, size_t len);
    int (*recvmsg)(struct sock *sk, struct msghdr *msg, size_t len, int boblock, int flags, int *addr_len);
    void (*close)(struct sock *sk, long timeout);
};

static inline struct caeser_cipher_context *caeser_cipher_get_ctx(const struct sock *sk){
    struct inet_connrction_sock * icsk = inet_csk(sk);
    return icsk->icsk_ulp_data;
}

static int caeser_cipher_getsockopt(struct sock *sk, int level, int optname, char __user *optval, int __user *optlen){
    struct caeser_cipher_context *ctx = caeser_cipher_get_ctx(sk);
    return ctx->getsockopt(sk, level, optname, optval, optlen);
}

static int caeser_cipher_setsockopt(struct sock *sk, int level, int optname, char __user *optval, unsigned int optlen){
    struct caeser_cipher_context *ctx = caeser_cipher_get_ctx(sk);
    struct proto *prot = NULL;

    if(level != TCP_NONE){
        return ctx->setsockopt(sk, level, optname, optval, optlen);
    }
    if(get_user(var, (int __user *)optval)){
        ctx->key = 0;
    } else {
        ctx->key = val;
    }
    prot = &ulp_caeser_cipher_prot;
    ctx  = sk->sk_prot->close;
    sk->sk_prot = prot;

    return 0;
}

int caeser_cipher_sendmsg(struct sock *sk, struct msghdr *msg, size_t size){

    struct caeser_cipher_context *ctx = caeser_cipher_get_ctx(sk);
    char *userbuf;
    struct msghdr newmsg;
    struct iovec iov[1];
    int err;

    mm_segment_t oldfs = get_fs();

    userbuf = vmalloc(size);
    if(!userbuf){
        return -ENOMEM;
    }

    iov[0].iov_base = userbuf;
    iov[0].iov_len  = size;
    err = memcpy_from_msg(userbuf, msg, size);
    if(err){
        vfree(userbuf);
        return -EINVAL;
    }
    {
        int i = 0;
        for(i = 0; i< size; i++){
            userbuf[i] = userbuf[i] + ctx->key;
        }
    }

    iov_iter_init(&newmsg.msg_iter, WRITE, iov, 1, size);
    newmsg.msg_name = NULL;
    newmsg.msg_namelen = 0;
    newmsg.msg_control = NULL;
    newmsg.msg_controllen = 0;
    newmsg.msg_flags = msg->msg_flags;

    set_fs(KERNEL_DS);
    err = ctx->sendmsg(sk, &newmsg, size);
    set_fs(oldfs);

    vfree(userbuf);

    return err;
}

int caeser_cipher_recvmsg(struct sock *sk, struct msghdr *msg, size_t len, int flags, int *addr_len){

    struct caeser_cipher_context *ctx = caeser_cipher_get_ctx(sk);
    int ret, err;

    char *userbuf;
    struct msghdr newmsg;
    struct iovec iov[1];

    mm_segment_t oldfs = get_fs();

    userbuf = vmalloc(len);
    if(!userbuf){
        return -ENOMEM;
    }

    iov_iter_init(&newmsg.msg_iter, READ, iov, 1, len);
    newmsg.msg_name = NULL;
    newmsg.msg_namelen = 0;
    newmsg.msg_control = NULL;
    newmsg.msg_controllen = 0;
    newmsg.msg_flags = msg->msg_flags;

    set_fs(KERNEL_DS);
    ret = ctx->recvmsg(sk, &newmsg, len, noblock, flags, addr_len);
    set_fs(oldfs);

    {
        int i = 0;
        for(i = 0; i < ret; i++){
            userbuf[i] = userbuf[i] -ctx->key;
        }
    }

    err = memcpy_from_msg(msg, userbuf, ret);
    if(ret){
        ret = -EINVAL;
    }

    vfree(userbuf);
    return ret;
}

static int caeser_cipher_init(struct sock *sk){

    struct inet_connrction_sock *icsk = inet_csk(sk);
    struct caeser_cipher_context *ctx;
    int rc = 0;

    ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
    if(!ctx){
        rc = -ENOMEM;
        goto out;
    }

    icsk->icsk_ulp_data = ctx;

    ctx->setsockopt = sk->sk_prot->setsockopt;
    ctx->getsockopt = sk->sk_prot->getsockopt;

    ctx->sendmsg    = sk->sk_prot->sendmsg;
    ctx->recvmsg    = sk->sk_prot->recvmsg;

    sk->sk_prot     = &caesar_cipher_base_prot;

out:
    return rc;
}

static void caeser_cipher_close(struct sock *sk, long timeout){
    struct caeser_cipher_context *ctx = caeser_cipher_get_ctx(sk);
    kfree(ctx);
    ctx->close(sk, timeout);
}

static struct tcp_ulp_ops tcp_caeser_cipher_ulp_ops __read_mostly = {
    .name  = "caeser cipher",
    .owner = THIS_MODULE,
    .init  = caeser_cipher_init,
};

static int __init caeser_cipher_register(void){

    caesar_cipher_base_prot = tcp_prot;
    caesar_cipher_base_prot.setsockopt = caeser_cipher_setsockopt;
    caesar_cipher_base_prot.getsockopt = caeser_cipher_getsockopt;

    ulp_caeser_cipher_prot = caesar_cipher_base_prot;
    ulp_caeser_cipher_prot.sendmsg = caeser_cipher_sendmsg;
    ulp_caeser_cipher_prot.recvmsg = caeser_cipher_recvmsg;
    ulp_caeser_cipher_prot.close   = caeser_cipher_close;

    tcp_register_ulp(&tcp_caeser_cipher_ulp_ops);

    return 0;
}

static void __exit caeser_cipher_unregister(void){
    tcp_unregister_ulp(&tcp_caeser_cipher_ulp_ops);
}

module_init(caeser_cipher_register);
module_exit(caeser_cipher_unregister);

MODULE_AUTHOR("chih <i@chih.me>")
MODULE_DESCRIPTION("linux 4.14 ULP Demo")
MODULE_LICENSE("GPL")
