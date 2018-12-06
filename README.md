# antwar-reason (WIP)

> A port of the antwar site generator in Reason.

## Basic Concepts

This antwar version drives for a very simple data structure, which is fed into a
Compiler to build Bundles (prev. Interactive Components) and Pages (static
pages). 

Example for a configuration (extracted from our example `site/bootstrap.re`):

```
let config = [
  Bundle({id: "navigation", entry: "./site/navigation.bs.js"}),
  Page({urlPath: [], component: Pages.index}),
  Page({urlPath: ["about"], component: Pages.about}),
];
```

The compiler is representing a very simplistic transformation pipeline for `Components`.
It's not really coupled to any concrete Component model, so you can use the `Compiler` functor
to inject your own Component type:

```typescript
module ReactCompiler = {
  module Component = {
    type t = ReasonReact.reactElement;
  };

  include Compiler.Make(Component, Filesystem.Node);

  module Transform = {
    let template = (~index as _, compileUnit: CompileUnit.t) => "";
  };

  let processComponent = (comp: Component.t) =>
    ReactDOMServerRe.renderToStaticMarkup(comp);
};
```

For our use-case, we want to have a Compiler which is capable of transforming
React components, so we inject `ReasonReact.reactElement` as the `Component.t`
type. The compiler now `includes` following interesting interfaces:

- `ReactCompiler.compileAll`
- `ReactCompiler.compileBundle`
- `ReactCompiler.compilePage`

The `compileAll` function is the entry point for computing a configuration, the
other two functions do the low level work. The whole compiler is full of side-effects,
since it does a lot of IO (writing files etc.). It is also planned that the compiler
will yield transformation functions for wrapping / modifying passed in components.

The whole philosophy of this project is to have very powerful minimal building blocks and
compose everything together to a very sophisticated site generator. We only do very basic
concrete constructs to set the frame, everything else should be built on interfaces, one of
them being a `Component`.

Another goal of this project is to be able to build ReasonReact apps without
too much JS infrastructure.  So most of the JS tooling will be used via
child_processes for now, until we rebuilt essential tooling in OCaml as well.


## Development

The development happens hand in hand building an actual project located in the
`site` directory. The file `site/bootstrap.re` is the entrypoint of the static
site generator.

For development, run `npm install` to install all dependencies and `npm run
build` to build all Reason modules.

You can watch and rebuild all Reason files with `npm run watch`.

After the build, run `node site/bootstrap.bs.js` to run the generator.
