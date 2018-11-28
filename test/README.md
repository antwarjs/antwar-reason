# Reason Association Style Guide

## Release Tachyons CSS bundle

This will create the minified & unminified CSS bundle in the `css` directory.
The bundle is the full tachyos build, it provides all styles you need to build
every component you find in this style-guide.

```
npm run css:release
```


## Development / Run Style Guide locally

**Install Project dependencies:**

```
npm install
```

**BuckleScript related tasks:**

```
# Build Reason sources
npm run bs:build

# Run in watch mode
npm run bs:watch

# Start server for development
npm start

# Build the website in production mode
npm run build
```

## Deployment

**Netlify:**

- Add your project to netlify
- Define following build task: `npm run netlify`
- Define `build/`as your output folder
