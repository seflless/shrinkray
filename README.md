### Shrinkray
Create desktop apps in Javascript. Lightweight alternative to Electron because of only supporting macOS (for now).

*Features*
 - [ ] CLI for converting static website into a macOS app.
 - [x] Tiny App sizes (macOS: < 100K, Windows: N/A)
 - [x] Debuggable (Right-click window, select "Inspect Element")
 - [ ] Fullscreen API
 - [ ] File Read/Write
 - [ ] Menu

#### Example Apps

<a href="https://github.com/francoislaberge/draw.io/releases/download/v7.0.0/drawio.app.zip">
    <img style="float:left" width="33%" src="http://francoislaberge.com/shrinkray/images/drawio-app.png"/>
</a>
<a href="https://github.com/francoislaberge/regulex/releases/download/v1.0.0/regulex.app.zip">
    <img style="float:left;" width="33%" src="http://francoislaberge.com/shrinkray/images/regulex-app.png"/>
</a>
<a href="https://github.com/francoislaberge/mini-paint/releases/download/v1.0.0/mini-paint.app.zip">
    <img style="float:left;" width="33%" src="http://francoislaberge.com/shrinkray/images/mini-paint-app.png"/>
</a>




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
