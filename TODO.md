#### Todo
  - [ ] Clean up warnings in desktop.xcodeproj
  - [ ] Get draw.io wrapped once we have the embedded server. Also strip draw.io down even further to make it lean
  - [ ] Consider making Shrinkray's design goals being to make desktop style javascript apps easy to make, but also if made
        easy to host in a standard container that provides the same APIs as on desktop (Menus, file save/load, etc)'
  - [ ] Get a domain?
    - io domain?
    - shrinkrayjs.org?
  - Add support for generating .dmg and .pkg
  - Add support for .shrinkray file that specifies things like:
    - icons
	- app name
	- file extensions
	- Reference: [electron-builder](https://github.com/electron-userland/electron-builder)

### Done
- [x] Create npm module and cli that gets basic functionality working
- [x] Build in an HTTP server, and host files via http://localhost:<port> instead of file:///<path-to-index.html>
