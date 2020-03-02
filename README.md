fj-sandbox
==========

Scripts for Firejail sandboxing. Inspired by (but **definitely not** as good as) the [Qubes][1] security model.

This is for people with older hardware, less RAM, or stricter hardware compatibility requirements. This is sandboxing where things run "close to the metal" without the overhead of virtual machines or containers.

Dependencies
------------

* Firejail
* Openbox (for x11 sandboxing)
* Xephyr (for x11 sandboxing)

Install
-------

Run [install.sh][2]. This just creates a symlink to the [new-sandbox][3] script.

Basic Usage
-----------

Create two sandboxes and start them:

```bash
new-sandbox personal
new-sandbox work

start-personal
start-work
```

This runs an instance of openbox for both the _personal_ and _work_ sandboxes, with their own private home directories, sandboxed from the rest of the system. There are two ways to launch applications inside sandboxes:

* Right-click anywhere in the openbox window and use the menu
* Run `firejail --join=<sandbox-name> <app>` (for example, `firejail --join=personal firefox`)

Each sandbox has a dedicated home directory found at `~/sandboxes/<sandbox-name>`. Moving files between sandboxes is as easy as moving the file from one directory to another.

Customizing Sandboxes
---------------------

I am pretty new to Firejail, and certainly no Linux expert. After creating a new sandbox, you should take a look at the new Firejail profile at `~/.config/firejail/<sandbox-name>.profile`. Adjust it to meet your needs. If you see any way to improve these default profiles, please send a pull request!

Hooks
-----

Right now there's support for only one hook: A [post-create hook][4]. This hook is an optional script that automatically gets called after you create a new sandbox. It allows you to customize how sandboxes are initialized. For example, you could set up a default Firefox profile, or SSH settings, etc.

[1]: https://www.qubes-os.org/
[2]: install.sh
[3]: new-sandbox
[4]: hooks/post-create.sh.template
