fj-sandbox
==========

Scripts for Firejail sandboxing. Inspired by (but **definitely not** as good as) the [Qubes][1] security model.

This is for people with older hardware, less RAM, or stricter hardware compatibility requirements. This is sandboxing where things run "close to the metal" without the overhead of virtual machines or containers.

Dependencies
------------

* Firejail
* Openbox (for x11 sandboxing)
* Xephyr (for x11 sandboxing)
* xsel (for sharing clipboard contents between sandboxes)

Install
-------

Run [install.sh][2]. This just creates a few symlinks to scripts like [new-sandbox][3].

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

You can also share clipboard content between sandboxes. In a host (non-sandboxed) terminal:

```bash
# Move contents of "personal" clipboard to "work" clipboard:
mv-clipboard personal work

# Move contents of "personal" clipboard to host clipboard
get-clipboard personal | xsel --clipboard

# Copy contents of host clipboard to "personal" clipboard
xsel --clipboard | set-clipboard personal
```

It's also pretty easy to create temporary sandboxes:

```bash
new-sandbox temp
start-temp
# do some work, shut the sandbox down...
remove-sandbox temp
```

Customizing Sandboxes
---------------------

To adjust options such as sandbox screen size, network interface, etc., check out the [default-config.sh][4] script. If you want to override any of these options, simply create a new "user-config.sh" script in the same directory, and re-export the environment variables you want to override.

I am pretty new to Firejail, and certainly no Linux expert. After creating a new sandbox, you should take a look at the new Firejail profile at `~/.config/firejail/<sandbox-name>.profile`. Adjust it to meet your needs. If you see any way to improve these default profiles, please send a pull request!

Hooks
-----

There are a couple hook script templates in the hooks directory. These enable you to automatically initialize any new sandboxes you create, and clean things up when sandboxes are destroyed.

Features I Might Add Later
--------------------------

* Script to mount USB drives for sandboxes
* `--help` usage messages for scripts, and perhaps a few options for a few scripts
* Script for file transfer between sandboxes (similar to clipboard-sharing scripts)
* Nix package manager integration (I'm currently using personal hook scripts for this and it's pretty nifty)
* Instead of an explicit Nix integration, perhaps a simple plugin system that allows for a separate Nix plugin to be developed

[1]: https://www.qubes-os.org/
[2]: install.sh
[3]: bin/new-sandbox
[4]: default-config.sh
