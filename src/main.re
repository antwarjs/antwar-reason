open Common;

module Pages = {
  module Router = {
    type route =
      | Index
      | About
      | NotFound;

    let urlPathToStr = Util.concatUrlPath;

    let pathToRoute = urlPath =>
      switch (urlPath) {
      | [] => Index
      | ["about", _] => About
      | _ => NotFound
      };

    let routeToPath = route =>
      switch (route) {
      | Index => []
      | About => ["about"]
      | NotFound => ["404"]
      };

    let href = (~to_: route): string => routeToPath(to_) |> urlPathToStr;
  };

  let about =
    <div>
      <div> "About"->ReasonReact.string </div>
      <a href=Router.(href(~to_=Index))> "Home"->ReasonReact.string </a>
    </div>;

  let index =
    <div>
      <div> "Home"->ReasonReact.string </div>
      <a href=Router.(href(~to_=About))> "About"->ReasonReact.string </a>
    </div>;
};

let applyLayout = children => <main> children </main>;

module Transform = {
  let layout = (~index as _, compileUnit) => {
    let (path, component) = compileUnit;

    let applied =
      switch (path) {
      | ["about", "1"] => applyLayout(component)
      | ["about", _] => applyLayout(<div id="1"> component </div>)
      | _ => applyLayout(component)
      };

    (path, applied);
  };
};

module ReactCompiler = {
  module Component = {
    type t = ReasonReact.reactElement;
  };
  include Compiler.Make(Component, Filesystem.Node);
};

let config: list(ReactCompiler.compileUnit) = [
  ([], Pages.index),
  (["about"], Pages.about),
];

let compiler =
  ReactCompiler.make(
    ~buildDir="foo",
    ~processComponent=comp => ReactDOMServerRe.renderToStaticMarkup(comp),
    (),
  );

config
|> List.mapi((index, compileUnit) => Transform.layout(~index, compileUnit))
|> Array.of_list
|> ReactCompiler.compileAll(compiler);
