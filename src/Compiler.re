module Make = (Component: {type t;}, Fs: Filesystem.T) => {
  module CompileUnit = CompileUnit.Make(Component);

  type url_path = UrlPath.t;
  type component = Component.t;

  type transform = (~index: int, CompileUnit.t) => CompileUnit.t;

  type t = {
    buildDir: string,
    mapUrlToFile: url_path => string,
    processComponent: component => string /* maybe Html_string.t? */
  };

  /*
      [] => "index.html"
      ["about"] => "about/index.html"
      ["about", "2"] => "about/2/index.html"
   */
  let defaultMapUrlToFile = urlPath =>
    Path.(join([join(urlPath)] @ ["index.html"]));

  let make =
      (
        ~buildDir,
        ~mapUrlToFile=defaultMapUrlToFile,
        ~processComponent=_ => "",
        (),
      ) => {
    buildDir,
    mapUrlToFile,
    processComponent,
  };

  let setup = ({buildDir}: t): unit => Fs.mkdirp(buildDir);

  let compilePage = (compiler: t, page: CompileUnit.page): unit => {
    let {buildDir, processComponent, mapUrlToFile} = compiler;
    let {CompileUnit.urlPath, component} = page;

    let filepath = Path.(join([buildDir, mapUrlToFile(urlPath)]));

    let content = processComponent(component);

    Fs.mkdirp(Path.dirname(filepath));
    Fs.writeFile(~filepath, content);
  };

  let compileBundle =
      (compiler: t, bundle: CompileUnit.bundle)
      : Js.Promise.t(Js.Result.t(string, string)) => {
    let {buildDir} = compiler;
    let {CompileUnit.id, entry} = bundle;

    /*
        For fastpack, we need to create a directory per bundle, since it's not
        capable to output a different filename than `index.js`
        See: https://github.com/fastpack/fastpack/issues/145
     */
    let outputDir = Path.(join([buildDir, id]));

    Bundler.Fastpack.(
      make(
        ~entry="./site/app.bs.js",
        ~task=Build,
        ~dev=true,
        ~output="./build/foo",
        ~preprocess=[
          "\\.css$:style-loader!css-loader?importLoaders=1!postcss-loader?path=./postcss.config.js",
        ],
        (),
      )
      |> exec
      |> Js.Promise.then_(code =>
           if (code === 0) {
             Js.log(
               "Building bundle '"
               ++ Path.join([outputDir, "index.js"])
               ++ "' successful",
             );
             Js.Promise.resolve(Js.Result.Ok(id));
           } else {
             Js.log("Building bundle '" ++ id ++ "' failed");
             Js.Promise.resolve(Js.Result.Error(id));
           }
         )
    );
  };

  let compileAll = (compiler: t, input: list(CompileUnit.t)): Js.Promise.t(unit) => {
    setup(compiler);

    /* Steps to do
          - Categorize all compileUnits to bundles / static pages
          - Run fastpack for each bundle, wait until all bundles are built
          - Remember all succcessfully built bundles, so we can use them in the pages
          - Render all Static pages, check for bundle deps and insert the
            code for mounting the bundle

       */

    let bundles =
      List.fold_left(
        (ret, next) =>
          switch (next) {
          | CompileUnit.Bundle(bundle) => [bundle, ...ret]
          | _ => ret
          },
        [],
        input,
      );

    List.map(bundle => compileBundle(compiler, bundle), bundles)
    |> Array.of_list
    |> Js.Promise.all
    |> Js.Promise.then_(results => {
         Js.log(results);
         Js.Promise.resolve();
       });
    /*let compile = compilePage(compiler);*/
    /*Array.iter(compile, input);*/
  };
};
