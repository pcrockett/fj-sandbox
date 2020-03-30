# Copy/paste/modified from firejail's default.profile

# Persistent local customizations
include default.local
# Persistent global definitions
include globals.local

##########################################################################
# Much of the following was copy/pasted from the firejail-provided disable-common.inc. 
# We removed a lot of ${HOME} blacklists, because each sandbox has its own home.
##########################################################################

# History files in clipboard managers
blacklist-nolog /tmp/clipmenu*

# X11 session autostart
blacklist /etc/X11/Xsession.d
blacklist /etc/xdg/autostart

# Session manager
?HAS_X11: blacklist /tmp/.ICE-unix

# KDE sockets
blacklist ${RUNUSER}/*.slave-socket
blacklist ${RUNUSER}/kdeinit5__*
blacklist ${RUNUSER}/kdesud_*
?HAS_NODBUS: blacklist ${RUNUSER}/ksocket-*
?HAS_NODBUS: blacklist /tmp/ksocket-*

# systemd
blacklist /var/lib/systemd
# blacklist /var/run/systemd
# creates problems on Arch where /etc/resolv.conf is a symlink to /var/run/systemd/resolve/resolv.conf

# VeraCrypt
blacklist ${PATH}/veracrypt
blacklist ${PATH}/veracrypt-uninstall.sh
blacklist /usr/share/applications/veracrypt.*
blacklist /usr/share/pixmaps/veracrypt.*
blacklist /usr/share/veracrypt

# TrueCrypt
blacklist ${PATH}/truecrypt
blacklist ${PATH}/truecrypt-uninstall.sh
blacklist /usr/share/applications/truecrypt.*
blacklist /usr/share/pixmaps/truecrypt.*
blacklist /usr/share/truecrypt

# zuluCrypt
blacklist ${PATH}/zuluCrypt-cli
blacklist ${PATH}/zuluMount-cli

# var
blacklist /var/cache/apt
blacklist /var/cache/pacman
blacklist /var/lib/apt
blacklist /var/lib/clamav
blacklist /var/lib/dkms
blacklist /var/lib/mysql/mysql.sock
blacklist /var/lib/mysqld/mysql.sock
blacklist /var/lib/pacman
blacklist /var/lib/upower
# blacklist /var/log - a virtual /var/log directory (mostly empty) is build up by default for
# every sandbox, unless --writeble-var-log switch is activated
blacklist /var/mail
blacklist /var/opt
blacklist /var/run/acpid.socket
blacklist /var/run/docker.sock
blacklist /var/run/minissdpd.sock
blacklist /var/run/mysql/mysqld.sock
blacklist /var/run/mysqld/mysqld.sock
blacklist /var/run/rpcbind.sock
blacklist /var/run/screens
blacklist /var/spool/anacron
blacklist /var/spool/cron
blacklist /var/spool/mail

# etc
blacklist /etc/anacrontab
blacklist /etc/cron*
blacklist /etc/profile.d
blacklist /etc/rc.local
# rc1.d, rc2.d, ...
blacklist /etc/rc?.d
blacklist /etc/kernel*
blacklist /etc/grub*
blacklist /etc/dkms
blacklist /etc/apparmor*
blacklist /etc/selinux
blacklist /etc/modules*
blacklist /etc/logrotate*
blacklist /etc/adduser.conf

# top secret
blacklist /.fscrypt
blacklist /etc/davfs2/secrets
blacklist /etc/group+
blacklist /etc/group-
blacklist /etc/gshadow
blacklist /etc/gshadow+
blacklist /etc/gshadow-
blacklist /etc/passwd+
blacklist /etc/passwd-
blacklist /etc/shadow
blacklist /etc/shadow+
blacklist /etc/shadow-
blacklist /etc/ssh
blacklist /home/.ecryptfs
blacklist /home/.fscrypt
blacklist /var/backup

# cloud provider configuration
blacklist /etc/boto.cfg

# system directories
blacklist /sbin
blacklist /usr/local/sbin
blacklist /usr/sbin

# system management
blacklist ${PATH}/at
blacklist ${PATH}/chage
blacklist ${PATH}/chfn
blacklist ${PATH}/chsh
blacklist ${PATH}/crontab
blacklist ${PATH}/evtest
blacklist ${PATH}/expiry
blacklist ${PATH}/fusermount
blacklist ${PATH}/gksu
blacklist ${PATH}/gksudo
blacklist ${PATH}/gpasswd
blacklist ${PATH}/kdesudo
blacklist ${PATH}/ksu
blacklist ${PATH}/mount
blacklist ${PATH}/mount.ecryptfs_private
blacklist ${PATH}/nc
blacklist ${PATH}/ncat
blacklist ${PATH}/newgidmap
blacklist ${PATH}/newgrp
blacklist ${PATH}/newuidmap
blacklist ${PATH}/ntfs-3g
blacklist ${PATH}/pkexec
blacklist ${PATH}/procmail
blacklist ${PATH}/sg
blacklist ${PATH}/strace
blacklist ${PATH}/su
blacklist ${PATH}/sudo
blacklist ${PATH}/umount
blacklist ${PATH}/unix_chkpwd
blacklist ${PATH}/xev
blacklist ${PATH}/xinput

# other SUID binaries
blacklist /usr/lib/virtualbox
blacklist /usr/lib64/virtualbox

# prevent lxterminal connecting to an existing lxterminal session
blacklist /tmp/.lxterminal-socket*
# prevent tmux connecting to an existing session
blacklist /tmp/tmux-*

# disable terminals running as server resulting in sandbox escape
blacklist ${PATH}/lxterminal
blacklist ${PATH}/gnome-terminal
blacklist ${PATH}/gnome-terminal.wrapper
blacklist ${PATH}/lilyterm
blacklist ${PATH}/mate-terminal
blacklist ${PATH}/mate-terminal.wrapper
blacklist ${PATH}/pantheon-terminal
blacklist ${PATH}/roxterm
blacklist ${PATH}/roxterm-config
blacklist ${PATH}/terminix
blacklist ${PATH}/tilix
blacklist ${PATH}/urxvtc
blacklist ${PATH}/urxvtcd
blacklist ${PATH}/xfce4-terminal
blacklist ${PATH}/xfce4-terminal.wrapper
# blacklist ${PATH}/konsole
# konsole doesn't seem to have this problem - last tested on Ubuntu 16.04

# kernel files
blacklist /initrd*
blacklist /vmlinuz*

# snapshot files
blacklist /.snapshots

# flatpak
blacklist /usr/share/flatpak
blacklist /var/lib/flatpak
# most of the time bwrap is SUID binary
blacklist ${PATH}/bwrap

# mail directories used by mutt

# kernel configuration
blacklist /proc/config.gz

# allow nix packages to be visible, but not changeable to sandboxes
read-only /nix

# /run/user/USERID is used for a lot of IPC - VSCodium being the chief example.
# Whitelisting some random file in this directory will cause the sandbox to see
# an empty directory. If some program inside the sandbox ever writes to this
# directory, those files will only be visible to the sandbox.
whitelist ${RUNUSER}/__not-used__

whitelist /usr/share/mozilla
include whitelist-usr-share-common.inc
# include whitelist-var-common.inc

# The below seccomp configuration still permits chroot syscall. If you want Firefox
# to work on Manjaro, either this needs to be set or you need to run the following:
#
#     sysctl --write kernel.unprivileged_userns_clone=0
#
# See https://github.com/netblue30/firejail/issues/2506
seccomp !chroot

machine-id
