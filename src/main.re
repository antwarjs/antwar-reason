type url_path = list(string);

module Util = {
  let concatUrlPath = (urlPath: url_path): string =>
    List.fold_left(
      (acc, str) =>
        switch (acc) {
        | "" => str
        | _ => "/" ++ str
        },
      "",
      urlPath,
    );
};

module ReactComponent = {
  type t = ReasonReact.reactElement;
};

module Compiler = (Component: {type t;}) => {
  /* (["about", "1"], hello) */
  type compileUnit = (url_path, Component.t);
  type transform = (~index: int, compileUnit) => compileUnit;

  type t = {
    buildDir: string,
    mapUrlToFile: url_path => string,
    processComponent: Component.t => string /* maybe Html_string.t? */
  };

  let defaultMapUrlToFile = Util.concatUrlPath;

  let defaultProcessComponent = (component: Component.t) => "";

  let make =
      (
        ~buildDir,
        ~mapUrlToFile=defaultMapUrlToFile,
        ~processComponent=defaultProcessComponent,
        (),
      ) => {
    buildDir,
    mapUrlToFile,
    processComponent,
  };

  let compilePage = (compileUnit: compileUnit, compiler: t): unit => ();
};

/*module type RouterSig => {*/
/*let routeToPath: route => url_path;*/
/*let pathToRoute: url_path => route;*/

/*let urlPathToStr: url_path => string;*/
/*let href: (~to_: route) => string;*/
/*};*/

module ReactCompiler = {
  include Compiler(ReactComponent);

  let a: compileUnit = (["test"], <div />);

  let compilePage = (compileUnit: compileUnit, compiler: t): unit => {
    let {processComponent} = compiler;
    let (_path, component) = compileUnit;

    processComponent(component) |> Js.log;
  };
};

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
      | Index => [""]
      | About => ["about"]
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

module AppliedCompiler = ReactCompiler;

module Transform = {
  let identity: AppliedCompiler.transform =
    (~index as _, compileUnit) => compileUnit;

  let layout: AppliedCompiler.transform =
    (~index as _, compileUnit) => {
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

let config: list(AppliedCompiler.compileUnit) = [
  ([], Pages.index),
  (["about"], Pages.about),
];

let compiler =
  AppliedCompiler.make(
    ~buildDir="foo",
    ~processComponent=comp => ReactDOMServerRe.renderToStaticMarkup(comp),
    (),
  );

config
|> List.mapi((index, compileUnit) => Transform.layout(~index, compileUnit))
|> List.iter(compileUnit =>
     AppliedCompiler.compilePage(compileUnit, compiler)
   );
