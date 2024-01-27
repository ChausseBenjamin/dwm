# Personal dwm configuration

My dwm setup is quite quirky as it relies on [sxhkd][1] for all keybindings
(except quitting dwm). If you wonder how a custom [dwm][2] instance can be
kept in sync with the upstream version, look at [this file](GIT_CONFIG.md)

As this build is used in both my laptop an my desktop (a.k.a. battlestation),
the makefile defines a CONFIG_FLAG which adapts certain parameters on compile
time to tailor to the current machine. For example, my desktop uses a 4k 32"
monitor. I therefore specify a bigger font size for my status bar.

My intent is to have `1 patch = 1 commit` (as much as possible) so that I can
easily backtrack if I change my mind about a patch later on.

## My current patches

### Quality of Life

- **defaultlayoutpermonitor** allows my vertical ultrawide to always be setup
- **activemonitor** lets me always know I'm on which monitor
- **alpha** gives my sweet eyecandy transparency in my statusbar
- **alwayscenter** make floating windows feel cohesive
- **fullscreen** is a hacky (functional) way of viewing windows in fullscreen
- **hide_vacant_tags** minimizes space used by my tag list
- **resizecorners** lets me resize a window by pinching any corner
- **mainmon** hides my statusbar on non-main monitors (cool for presentations)
- **statuscmd** lets me refresh dwmblocks when clicking on blocks
- **dwmc** let's me control all of dwm with external command (issued by sxhkd)

### Stack Management

- **movestack** lets me move a single window up and down the stack
- **rotatestack** shifts the entire window stack up/down

### Window Layouts

- **tilewide** is a good layout for horizontal ultrawide monitors
- **vanitygaps** adds some eyecandy gaps to my layouts below
- **cfacts** allows resizing based on a weight value in layouts below
  - **bottomstack** is a great layout for vertical ultrawide monitors
  - **centeredmaster** is a good layout for redacting while researching

[1]: https://github.com/baskerville/sxhkd
[2]: https://dwm.suckless.orgw
