obj-$(CONFIG_F2FS_FS) += f2fs.o

f2fs-y		:= dir.o file.o inode.o namei.o hash.o super.o inline.o
f2fs-y		+= checkpoint.o gc.o data.o node.o segment.o recovery.o
f2fs-$(CONFIG_F2FS_STAT_FS) += debug.o
f2fs-$(CONFIG_F2FS_FS_XATTR) += xattr.o
f2fs-$(CONFIG_F2FS_FS_POSIX_ACL) += acl.o
f2fs-$(CONFIG_F2FS_IO_TRACE) += trace.o
f2fs-$(CONFIG_F2FS_FS_ENCRYPTION) += crypto_policy.o crypto.o \
		crypto_key.o crypto_fname.o

F2FS_SHA1 := $(shell cd $(KBUILD_SRC); git rev-list -1 HEAD fs/f2fs 2>/dev/null)
ifneq ($(strip $(F2FS_SHA1)),)
	ccflags-y += -DF2FS_SHA1=\"$(F2FS_SHA1)\"
endif
