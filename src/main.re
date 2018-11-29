module Pages = {
  module Router = {
    type route =
      | Index
      | About(string)
      | NotFound;

    let urlPathToStr = UrlPath.toUrl;

    let pathToRoute = urlPath =>
      switch (urlPath) {
      | [] => Index
      | ["about", sub] => About(sub)
      | _ => NotFound
      };

    let routeToPath = route =>
      switch (route) {
      | Index => []
      | About(sub) => ["about", sub]
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
      <a href=Router.(href(~to_=About("1")))> "About"->ReasonReact.string </a>
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
  /*include Compiler.Make(Component, Filesystem.Console);*/
};

let config: list(ReactCompiler.compileUnit) = [
  ([], Pages.index),
  (["about", "1"], Pages.about),
];

let compiler =
  ReactCompiler.make(
    ~buildDir=Path.join([Sys.getcwd(), "build"]),
    ~processComponent=comp => ReactDOMServerRe.renderToStaticMarkup(comp),
    (),
  );

config
|> List.mapi((index, compileUnit) => Transform.layout(~index, compileUnit))
|> Array.of_list
|> ReactCompiler.compileAll(compiler);
