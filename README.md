### Shrinkray
Create desktop apps in Javascript. Lightweight alternative to Electron because of only supporting macOS (for now).

*Features*
 - [ ] CLI for converting static website into a macOS app.
 - [x] Tiny App sizes (macOS: < 100K, Windows: N/A)
 - [x] Debuggable (Right-click window, select "Inspect Element")
 - [ ] Fullscreen API
 - [ ] File Read/Write
 - [ ] Menu

#### Installation

```
npm install -g shrinkray
```

#### Usage
The input path must be to a folder that has an index.html in it, everything in the folder
will be copied into the generated app and accessible.

```
shrinkray -i <project>/html -o example.app
```

### Contributing

 1. Required Tools
   - [XCode](https://developer.apple.com/xcode/)
   - [Node/NPM](https://nodejs.org/en/download/)
 2. Clone the project
        git clone git@github.com:francoislaberge/shrinkray.git
        cd shrinkray
 3. Install Dependencies
        npm install
 4. Build App Template
        npm run build:app
 5. Publish to npm
        npm run publish:patch

#### Todos
  - [ ] Create npm module and cli that gets basic functionality working
  - [ ] Consider making Shrinkray's design goals being to make desktop style javascript apps easy to make, but also if made
        easy to host in a standard container that provides the same APIs as on desktop (Menus, file save/load, etc)'
